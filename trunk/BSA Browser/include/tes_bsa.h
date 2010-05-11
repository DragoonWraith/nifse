#ifndef _TES_BSA_H_
#define _TES_BSA_H_

#include <iostream>
#include <fstream>
#include <vector>

namespace TES_BSA {

typedef unsigned long long UINT64;

const unsigned int FILE_NOT_FOUND = 0xFFFFFFFF;
const unsigned int MAX_BSA_NAME_SIZE = 256;

using namespace std;

class BSA_Archive {
public:
	virtual unsigned int getArchiveFlags() const = 0;
	virtual unsigned int getFileFlags() const = 0;
	virtual UInt32 FindFileNumber( const char * file_name ) = 0;
	virtual unsigned int GetFileSize( unsigned int file_number ) = 0;
	virtual void GetFileData( unsigned int file_number, char * dest ) = 0;
	virtual unsigned int GetFileCount() = 0;
	virtual const char * GetFileName( unsigned int file_number ) = 0;
};

BSA_Archive * LoadBSA( const char * file_name );

}

#endif