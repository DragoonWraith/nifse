#ifndef _TES3_BSA_H_
#define _TES3_BSA_H_

#include "tes_bsa.h"

namespace TES_BSA {

struct BSAFileInfo3 {
	unsigned int size;
	unsigned int offset;
};

struct BSAHeader3 {
	unsigned int bsaVersion;
	unsigned int directorySize;
	unsigned int fileCount;
};

struct BSAHash3 {
	unsigned int value1;
	unsigned int value2;
	bool operator<( const BSAHash3 & rhs );
	bool operator==( const BSAHash3 & rhs );
};

class TES3BSA_Archive : public BSA_Archive {
public:
	TES3BSA_Archive( const char * file_name );
	~TES3BSA_Archive();

	unsigned int FindFileNumber( const char * file_name );
	unsigned int GetFileSize( unsigned int file_number );
	void GetFileData( unsigned int file_number, char * dest );
	unsigned int GetFileCount();
	const char * GetFileName( unsigned int file_number );

protected:
	BSAHash3 Hash( const string & str );

	ifstream file;
	BSAHeader3 header;
	BSAFileInfo3 * fileInfo;
	unsigned int * fileNameOffsets;
	BSAHash3 * hashValues;
	char name_buffer[MAX_BSA_NAME_SIZE];
	unsigned int fileNamesOffset;
	unsigned int fileDataOffset;
};

} //End namespace

#endif
