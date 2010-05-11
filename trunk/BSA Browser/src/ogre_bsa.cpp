#include "OgreStableHeaders.h"

#include "../include/ogre_bsa.h"

#include "OgreLogManager.h"
#include "OgreException.h"
#include "OgreStringVector.h"
#include "OgreRoot.h"


namespace Ogre {

	using namespace TES_BSA;

    //-----------------------------------------------------------------------
    BsaArchive::BsaArchive(const String& name, const String& archType )
        : Archive(name, archType), bsa(NULL)
    {
    }
    //-----------------------------------------------------------------------
    BsaArchive::~BsaArchive()
    {
		unload();
    }
    //-----------------------------------------------------------------------
    void BsaArchive::load()
    {
        if ( bsa == NULL)
        {
			try {
				bsa = LoadBSA( mName.c_str() );
				//bsa = new TES3BSA_Archive( mName.c_str() );
			} catch ( exception & e ) {
				stringstream temp;
				temp << "BSA file failed to open - " << e.what();
				OGRE_EXCEPT( 0, temp.str().c_str(), "BsaArchive::load" );
			} catch ( ... ) {
				OGRE_EXCEPT( 0, "BSA file failed to open", "BsaArchive::load" );
			}
        }
    }
    //-----------------------------------------------------------------------
    void BsaArchive::unload()
    {
		//Delete BSA file memory if one was loaded.
		if ( bsa != NULL ) {
			delete bsa;
			bsa = NULL;
		}
    
    }
    //-----------------------------------------------------------------------
	DataStreamPtr BsaArchive::open(const String& filename) const
    {
		if ( bsa == NULL ) {
			// return null pointer
			return DataStreamPtr();
		}

		//Get file number of matching file if it exists
		unsigned int file_num = bsa->FindFileNumber( filename.c_str() );

		if ( file_num == FILE_NOT_FOUND ) {
			LogManager::getSingleton().logMessage( mName + " - Unable to open file " + filename + ", file was not found.", LML_CRITICAL);

			// return null pointer
			return DataStreamPtr();
		}			

        //Read file data
		unsigned int file_size = bsa->GetFileSize( file_num );
		
		//Read data from BSA into memory buffer
		char * file_data = new char[file_size]; //Will be freed by MemoryDataStream
		bsa->GetFileData( file_num, file_data );

		// Construct & return stream
        return DataStreamPtr( new MemoryDataStream( (void*)file_data, file_size, true ) );
    }
    //-----------------------------------------------------------------------
    StringVectorPtr BsaArchive::list(bool recursive)
    {
		if ( bsa == NULL ) {
			// return null pointer
			return StringVectorPtr();
		}
		
		StringVectorPtr ret = StringVectorPtr(new StringVector());

        //TODO:  Find out what recursive does and if we need to support it
		
		for ( unsigned int i = 0; i < bsa->GetFileCount(); ++i ) {
			ret->push_back( bsa->GetFileName(i) );
		}

        return ret;

    }
    //-----------------------------------------------------------------------
    FileInfoListPtr BsaArchive::listFileInfo(bool recursive)
    {
        FileInfoList * fil = new FileInfoList();
        
		for ( unsigned int i = 0; i < bsa->GetFileCount(); ++i ) {
			FileInfo temp;
			temp.archive = this;
			temp.filename = bsa->GetFileName(i);
			StringUtil::splitFilename( temp.filename, temp.basename, temp.path );
			temp.compressedSize = bsa->GetFileSize(i);
			temp.uncompressedSize = bsa->GetFileSize(i);
			
			fil->push_back( temp );
		}

        return FileInfoListPtr(fil);
    }
    //-----------------------------------------------------------------------
    StringVectorPtr BsaArchive::find(const String& pattern, bool recursive)
    {
        StringVectorPtr ret = StringVectorPtr(new StringVector());

		//TODO:  Implement this

   //     FileInfoList::iterator i, iend;
   //     iend = mFileList.end();
   //     for (i = mFileList.begin(); i != iend; ++i)
   //     {
			//if (recursive || i->path.empty())
   //         {
   //             // Check basename matches pattern (zip is case insensitive)
   //             if (StringUtil::match(i->basename, pattern, false))
   //             {
   //                 ret->push_back(i->filename);
   //             }
   //         }
   //         else
   //         {
   //             // Check full name
   //             if (StringUtil::match(i->filename, pattern, false))
   //             {
   //                 ret->push_back(i->filename);
   //             }

   //         }
   //     }
        return ret;
    }
    //-----------------------------------------------------------------------
	FileInfoListPtr BsaArchive::findFileInfo(const String& pattern, 
        bool recursive)
    {
        FileInfoListPtr ret = FileInfoListPtr(new FileInfoList());

		//TODO:  Implement this

        //FileInfoList::iterator i, iend;
        //iend = mFileList.end();
        //for (i = mFileList.begin(); i != iend; ++i)
        //{
        //    if (recursive || i->path.empty())
        //    {
        //        // Check name matches pattern (zip is case insensitive)
        //        if (StringUtil::match(i->basename, pattern, false))
        //        {
        //            ret->push_back(*i);
        //        }
        //    }
        //    else
        //    {
        //        // Check full name
        //        if (StringUtil::match(i->filename, pattern, false))
        //        {
        //            ret->push_back(*i);
        //        }

        //    }
        //}
        return ret;
    }
    //-----------------------------------------------------------------------
	bool BsaArchive::exists(const String& filename)
	{
		if ( bsa == NULL ) {
			return false;
		}

		if ( bsa->FindFileNumber( filename.c_str() ) != FILE_NOT_FOUND ) {
			return true;
		} else {
			return false;
		}

	}
	//-----------------------------------------------------------------------
    //-----------------------------------------------------------------------

	const String& BsaArchiveFactory::getType(void) const
    {
        static String name = "BSA";
        return name;
	}
}
