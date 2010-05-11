#include "../include/tes3_bsa.h"
#include "string.h"
#include <string>
#include <exception>
#include <sstream>

//Work around memory manager issues
#include "ogre.h"

namespace TES_BSA {

TES3BSA_Archive::TES3BSA_Archive( const char * file_name ) {
	//Open BSA file
	file.open( file_name, ifstream::binary );

	//Read header
	file.read( (char*)&header, sizeof(BSAHeader3) );

	//Read file size/offset section
	fileInfo = new BSAFileInfo3[header.fileCount];
	file.read( (char*)fileInfo, sizeof(BSAFileInfo3) * header.fileCount );

	//Read archive directory offset section
	fileNameOffsets = new unsigned int[header.fileCount];
	file.read( (char*)fileNameOffsets, sizeof(unsigned int) * header.fileCount );

	//Store file names offset
	fileNamesOffset = (unsigned int)file.tellg();
	
	//Seek over the file names section, don't store it.
	unsigned int names_size = header.directorySize - (12 * header.fileCount);
	file.seekg( names_size, ios_base::cur );

	//Read hash table section
	hashValues = new BSAHash3[header.fileCount];
	file.read( (char*)hashValues, sizeof(BSAHash3) * header.fileCount );

	//Store file data offset
	fileDataOffset = (unsigned int)file.tellg();
}

TES3BSA_Archive::~TES3BSA_Archive() {
	//Free memory allocated when file was opened
	delete [] fileInfo;
	delete [] fileNameOffsets;
	delete [] hashValues;

	//Close file
	file.close();
}

BSAHash3 TES3BSA_Archive::Hash( const string & str ) {

	BSAHash3 result;

	unsigned int len = (unsigned int)str.length();

	//Use GhostWheel's code to hash the string
	unsigned int l = (len>>1);
	unsigned int sum, off, temp, i, n;

	for(sum = off = i = 0; i < l; i++) {
		sum ^= (((unsigned int)(str[i]))<<(off&0x1F));
		off += 8;
	}
	result.value1 = sum;

	for(sum = off = 0; i < len; i++) {
		temp = (((unsigned int)(str[i]))<<(off&0x1F));
		sum ^= temp;
		n = temp & 0x1F;
		sum = (sum << (32-n)) | (sum >> n);  // binary "rotate right"
		off += 8;
	}
	result.value2 = sum;

	return result;
}

unsigned int TES3BSA_Archive::FindFileNumber( const char * file_name ) {
	//Copy string to a non-const STL string
	string name = file_name;
	
	//All files in a BSA archive are lowercase.
	for ( unsigned int i = 0; i < name.length(); i++ ) {
		name[i] = tolower(name[i]);
		if ( name[i] == '/' ) {
			name[i] = '\\';
		}
	}

	//Get the hash value for this file name
	BSAHash3 hash = Hash( name );

	//Perform a binary search of the hash table
	unsigned int l = 0;
	unsigned int r = header.fileCount;
	unsigned int m = 0;
	bool match_found = false;
	while ( r >= l ) {
		m = ( l + r ) / 2;
		if ( hash == hashValues[m] ) {
			//BSA files do not allow hash collisoins, so this is
			//a guaranteed match.  Exit loop.
			match_found = true;
			break;
		}
		//Did not find a match, continue search
		if ( hash < hashValues[m] ) {
			r = m - 1;
		} else {
			l = m + 1;
		}
	}

	//If no match was found, return 0xFFFFFFFF, otherwise return the offset
	if ( match_found == false ) {
		return FILE_NOT_FOUND;
	} else {
		return m;
	}
}

unsigned int TES3BSA_Archive::GetFileSize( unsigned int file_number ) {
	if ( file_number > header.fileCount ) {
		throw range_error( "BSA Archive file number out of range.");
	} else {
		return fileInfo[file_number].size;
	}
}

void TES3BSA_Archive::GetFileData( unsigned int file_number, char * dest ) {
	if ( file_number > header.fileCount ) {
		throw range_error( "BSA Archive file number out of range.");
	} else {
		unsigned int offset = fileDataOffset + fileInfo[file_number].offset;
		unsigned int size = fileInfo[file_number].size;
		file.seekg( offset, ios_base::beg );
		file.read( dest, size );
	}
}

unsigned int TES3BSA_Archive::GetFileCount() {
	return header.fileCount;
}

const char * TES3BSA_Archive::GetFileName( unsigned int file_number ) {
	//Seek to the start of the file name
	unsigned int offset = fileNamesOffset + fileNameOffsets[file_number];
	file.seekg( offset, ios_base::beg );

	//Read MAX_BSA_NAME_SIZE characters from file into the buffer.
	//The C string will end at the first zero regardless
	file.getline( name_buffer, MAX_BSA_NAME_SIZE, '\0' );

	//In case the name was truncated, add a zero on the end
	name_buffer[MAX_BSA_NAME_SIZE - 1] = 0;

	return name_buffer;
}

bool BSAHash3::operator<( const BSAHash3 & rhs ) {
	//Compare the first value, and only continue to the second
	//if they are equal
	if ( value1 < rhs.value1 ) {
		return true;
	} else if ( value1 > rhs.value1 ) {
		return false;
	} else {
		//value 1 == rhs.value1
		if ( value2 < rhs.value2 ) {
			return true;
		} else {
			return false;
		}
	}
}

bool BSAHash3::operator==( const BSAHash3 & rhs ) {
	//Two hashes are equal if both sets of values are equal
	if ( value1 == rhs.value1 && value2 == rhs.value2 ) {
		return true;
	} else {
		return false;
	}
}

} //End Namespace