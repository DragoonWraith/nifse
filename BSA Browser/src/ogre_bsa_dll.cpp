#include "../include/ogre_bsa.h"

namespace Ogre {

	//Global factory
    ArchiveFactory * bsaFactory = NULL;

    //-----------------------------------------------------------------------
    extern "C" void dllStartPlugin(void)
    {
		if ( bsaFactory == NULL ) {
			// Create new archive manager
			bsaFactory = new BsaArchiveFactory();

			// Register
			ArchiveManager::getSingleton().addArchiveFactory( bsaFactory );
		}
	}
	extern "C" void dllShutdownPlugin( void )
	{
		//Nothing
	}    
	extern "C" void dllStopPlugin(void)
    {
		if ( bsaFactory != NULL ) {
			delete bsaFactory;
			bsaFactory = NULL;
		}
    }
}
