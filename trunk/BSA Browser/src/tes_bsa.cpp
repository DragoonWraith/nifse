#include "../include/tes_bsa.h"
#include "../include/tes4_bsa.h"

namespace TES_BSA {

BSA_Archive * LoadBSA( const char * file_name ) {
	ifstream file;
	char version[4];

	file.open( file_name, ifstream::binary );
	file.read(version,4);
	file.close();

	if ( version[0]=='B' && version[1]=='S' && version[2]=='A' ) {
		return new TES4BSA_Archive(file_name);
	}
	else {
		throw exception("Not a recognised BSA archive");
	}
}

} //End namespace