#include "New.h"

void NifSE_NewCallback(void * reserved) {
	NifFile::RegList.clear();
	NifFile::RegListByFilename.clear();
}
