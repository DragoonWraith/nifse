#ifndef _ogre_bsa_h_
#define _ogre_bsa_h_

#include "Ogre.h"

#include "OgreArchive.h"
#include "OgreArchiveFactory.h"
#include "tes_bsa.h"

namespace Ogre {

    /** Specialisation of the Archive class to allow reading of files from a zip
        format source archive.
    @remarks
        This archive format supports all archives compressed in the standard
        zip format, including iD pk3 files.
    */
    class BsaArchive : public Archive 
    {
    protected:
        // BSA Archive file
		TES_BSA::BSA_Archive * bsa;
    public:
        BsaArchive(const String& name, const String& archType );
        ~BsaArchive();
        /// @copydoc Archive::isCaseSensitive
        bool isCaseSensitive(void) const { return false; }

        /// @copydoc Archive::load
        void load();
        /// @copydoc Archive::unload
        void unload();

        /// @copydoc Archive::open
        DataStreamPtr open(const String& filename) const;

        /// @copydoc Archive::list
        StringVectorPtr list(bool recursive = true );

        /// @copydoc Archive::listFileInfo
        FileInfoListPtr listFileInfo(bool recursive = true );

        /// @copydoc Archive::find
        StringVectorPtr find(const String& pattern, bool recursive = true);

        /// @copydoc Archive::findFileInfo
        FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true);

        /// @copydoc Archive::exists
		bool exists(const String& filename);
    };

    /** Specialisation of ArchiveFactory for BSA files. */
    class BsaArchiveFactory : public ArchiveFactory
    {
    public:
        virtual ~BsaArchiveFactory() {}
        /// @copydoc FactoryObj::getType
        const String& getType(void) const;
        /// @copydoc FactoryObj::createInstance
        Archive *createInstance( const String& name ) 
        {
            return new BsaArchive(name, "BSA");
        }
        /// @copydoc FactoryObj::destroyInstance
        void destroyInstance( Archive* arch) { delete arch; }
    };
}

#endif
