#ifndef _TES4_BSA_H_
#define _TES4_BSA_H_

#include "tes_bsa.h"

namespace TES_BSA {

struct BSAFileInfo4 {
	UINT64 hash;
	unsigned int size;
	unsigned int offset;
};

struct BSAFolderInfo4 {
	UINT64 hash;
	unsigned int count;
	//This is initially the offset to the FileInfo records, but overwrite it with the fileInfo index instead
	int offset;
};

struct BSAHeader4 {
	char ID[4];
	unsigned int bsaVersion;
	unsigned int directorySize;
	unsigned int archiveFlags;
	unsigned int folderCount;
	unsigned int fileCount;
	unsigned int totalFolderNameLength;
	unsigned int totalFileNameLength;
	unsigned int fileFlags;
};

class TES4BSA_Archive : public BSA_Archive {
public:
	TES4BSA_Archive( const char * file_name );
	~TES4BSA_Archive();

	unsigned int getArchiveFlags() const;
	unsigned int getFileFlags() const;

	UInt32 FindFileNumber( const char * file_name );
	unsigned int GetFileSize( unsigned int file_number );
	void GetFileData( unsigned int file_number, char * dest );
	unsigned int GetFileCount();
	const char * GetFileName( unsigned int file_number );

	void CompressionBitWrong( unsigned int file_number );
protected:
	ifstream file;
	BSAHeader4 header;

	BSAFolderInfo4 * folderInfo;
	BSAFileInfo4 * fileInfo;
};

}

#endif
