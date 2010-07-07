#include "New.h"

void NifSE_NewCallback(void * reserved) {
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = NifFile::RegList.begin(); RegListIter != NifFile::RegList.end(); ++RegListIter )
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter )
			std::remove(NifListIter->second->filePath.c_str());
	NifFile::RegList.clear();
}
