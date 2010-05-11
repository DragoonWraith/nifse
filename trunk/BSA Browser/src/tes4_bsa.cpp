#define ZLIB_WINAPI

#include "../include/tes4_bsa.h"
#include "string.h"
#include "zlib\zlib.h"
#include <string>
#include <exception>
#include <sstream>

typedef unsigned char byte;

namespace TES_BSA {

	unsigned int Hash2(const string & str) {
		
		unsigned int hash = 0;
		for( unsigned int i=0; i<str.length(); i++ ) {
					hash *= 0x1003f;
					hash += (unsigned char)str[i];
			}
			return hash;
	}

	UINT64 Hash( const string & file, const string & ext ) {
		
		UINT64 hash = 0;

		if ( file.length() > 0 ) {
			hash = (unsigned long)(
				(((byte)file[file.length()-1])*0x1)+
				((file.length()>2?(byte)file[file.length()-2]:(byte)0)*0x100)+
				(file.length()*0x10000)+
				(((byte)file[0])*0x1000000)
				);
		}
		if ( file.length() > 3 ) {
			hash += (UINT64)( Hash2( file.substr(1, file.length() - 3) ) * 0x100000000 );
		}
		if ( ext.length() > 0 ) {
			hash += (UINT64)( Hash2(ext) * 0x100000000 );
			byte i = 0;
			if ( ext == ".nif" ) {
				i = 1; 
			} else if ( ext == ".kf" ) {
				i = 2;
			} else if ( ext==".dds" ) {
				i = 3;
			} else if ( ext==".wav" ) {
				i = 4;
			}

			if ( i != 0 ) {
				byte a = (byte)( ((i & 0xfc) << 5 ) + (byte)( (hash & 0xff000000) >> 24) );
				byte b = (byte)( ((i & 0xfe) << 6 ) + (byte)(hash & 0xff));
				byte c = (byte)( (i << 7) + (byte)( (hash & 0xff00) >> 8) );
				hash -= hash & 0xFF00FFFF;
				hash += (unsigned int)( (a << 24) + b + (c << 8) );
			}
		}

		return hash;
	}
	
	static void Inflate(char* in, unsigned int insize, char* out, unsigned int outsize) {
		int ret;
		z_stream strm;

		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = inflateInit(&strm);
		if ( ret != Z_OK) {
			throw exception("Inflation of zipped BSA entry failed");
		}

		strm.avail_in = insize;
		strm.next_in = (Bytef*)in;

		strm.avail_out = outsize;
			strm.next_out = (Bytef*)out;
			
		ret = inflate( &strm, Z_FINISH );
		if ( ret < 0 ) {
			switch ( ret ) {
				case Z_ERRNO :
					throw exception("Z_ERRNO");
					break;
				case Z_STREAM_ERROR :
					throw exception("Z_STREAM_ERROR");
					break;
				case Z_DATA_ERROR :
					throw exception("Z_DATA_ERROR");
					break;
				case Z_MEM_ERROR :
					throw exception("Z_MEM_ERROR");
					break;
				case Z_BUF_ERROR :
					throw exception("Z_BUF_ERROR");
					break;
				case Z_VERSION_ERROR :
					throw exception("Z_VERSION_ERROR");
					break;
				default:
					throw exception("unknown zlib error");
			}
		}

		inflateEnd(&strm);
	}
	
	TES4BSA_Archive::TES4BSA_Archive( const char * file_name ) {
		//Open BSA file
		file.open( file_name, ifstream::binary|ifstream::in );
		if ( !(file.is_open()) )
			throw exception((string("Cannot open BSA file \"")+file_name+"\"!").c_str());

		//Read header
		file.read( (char*)&header, sizeof(BSAHeader4) );

		//Read folder info
		folderInfo = new BSAFolderInfo4[header.folderCount];
		fileInfo = new BSAFileInfo4[header.fileCount];
		file.read( (char*)folderInfo, sizeof(BSAFolderInfo4) * header.folderCount );
		int count=0;
		for( unsigned int i=0; i<header.folderCount; i++ ) {
			byte b;
			file.read((char*)&b, 1);
			file.seekg( b, ios_base::cur );
			folderInfo[i].offset=count;
			file.read( (char*)&fileInfo[count], sizeof(BSAFileInfo4) * folderInfo[i].count );
			count += folderInfo[i].count;
		}

		//flip compressed bits if needed
		if ( header.archiveFlags & 0x100 ) {
			for( unsigned int i=0; i < header.fileCount; i++ ) {
				fileInfo[i].size^=( 1 << 30 );
			}
		}
	}

	TES4BSA_Archive::~TES4BSA_Archive() {
		//Free memory allocated when file was opened
		delete [] folderInfo;
		delete [] fileInfo;

		//Close file
		file.close();
	}

	unsigned int TES4BSA_Archive::getArchiveFlags() const {
		return header.archiveFlags;
	}

	unsigned int TES4BSA_Archive::getFileFlags() const {
		return header.fileFlags;
	}

	UInt32 TES4BSA_Archive::FindFileNumber( const char * file_name ) {
		//Copy string to a non-const STL string
		string file = file_name;
		string extension;
		string folder;
		
		//All files in a BSA archive are lowercase.
		for ( unsigned int i = 0; i < file.length(); i++ ) {
			file[i] = tolower(file[i]);
			if ( file[i] == '/' ) {
				file[i] = '\\';
			}
		}

		int index = file.rfind("\\");
		if ( index != -1 ) {
			folder = file.substr(0,index);
			file = file.substr(index+1);
		}
		else {
			folder="";
		}

		index = file.rfind(".");
		if ( index != -1 ) {
			extension = file.substr(index);
			file = file.substr( 0, index );
		}
		else {
			extension="";
		}

		//Get the hash value for this file name
		UINT64 filehash = Hash( file, extension );
		UINT64 folderhash = Hash ( folder, "" );

		//Perform a binary search of the folder hash table
		UInt32 l = 0;
		UInt32 r = header.folderCount;
		UInt32 m1;
		bool match_found = false;
		while ( r >= l ) {
			m1 = ( l + r ) / 2;
			if ( m1 > header.folderCount )
				throw exception("FOLDER INDEX OUT OF BOUNDS");
			if ( folderhash == folderInfo[m1].hash ) {
				match_found = true;
				break;
			}
			//Did not find a match, continue search
			if ( folderhash < folderInfo[m1].hash ) {
				r = m1 - 1;
			} else {
				l = m1 + 1;
			}
		}

		if ( match_found == false ) {
			throw exception("FOLDER NOT FOUND");
		}

		//Perform a binary search of the file hash table
		l = folderInfo[m1].offset;
		r = folderInfo[m1].count + l;
		UInt32 m2;
		match_found = false;
		while ( r >= l ) {
			m2 = ( l + r ) / 2;
			if ( m2 > header.fileCount )
				throw exception("FILE INDEX OUT OF BOUNDS");
			if ( filehash == fileInfo[m2].hash ) {
				match_found = true;
				break;
			}
			//Did not find a match, continue search
			if ( filehash < fileInfo[m2].hash ) {
				r = m2 - 1;
			}
			else {
				l = m2 + 1;
			}
		}

		//If no match was found, throw exception, otherwise return the offset
		if ( match_found == false ) {
			throw exception("FILE NOT FOUND");
		}
		else {
			return m2;
		}
	}

	unsigned int TES4BSA_Archive::GetFileSize( unsigned int file_number ) {
		if ( file_number > header.fileCount ) {
			throw range_error( "BSA Archive file number out of range.");
		}
		else {
			if ( fileInfo[file_number].size & (1 << 30) ) {
				unsigned int size;
				file.seekg( fileInfo[file_number].offset, ios_base::beg );
				file.read( (char*)&size, 4 );
				return size;
			}
			else {
				return fileInfo[file_number].size;
			}
		}
	}

	void TES4BSA_Archive::GetFileData( unsigned int file_number, char * dest ) {
		if ( file_number > header.fileCount ) {
			throw range_error( "BSA Archive file number out of range.");
		}
		else {
			unsigned int offset = fileInfo[file_number].offset;
			unsigned int size = fileInfo[file_number].size;
			if ( fileInfo[file_number].size & (1<<30) ) {
				size^=(1<<30);
				unsigned int size2;
				char* data=new char[size-4];
				file.seekg( offset, ios_base::beg );
				file.read( (char*)&size2, 4 );
				file.read( data, size-4 );
				Inflate(data, size-4, dest, size2);
				delete [] data;
			}
			else {
				file.seekg( offset, ios_base::beg );
				file.read( dest, size );
			}
		}
	}

	unsigned int TES4BSA_Archive::GetFileCount() {
		return header.fileCount;
	}

	const char * TES4BSA_Archive::GetFileName( unsigned int file_number ) {
		return "";
	}

}