#pragma once

#include "Utilities.h"
#include "changeLog.h"
#include "NiflibTypes.h"

#include "niflib.h"
#include "obj/NiObject.h"
#include "obj/NiNode.h"

enum {
	kBasicAct_Open,
	kBasicAct_Close
};

class NifFile{
public:
	string filePath; // actual file for this modified Nif relative to Oblivion\Data\Meshes
	UInt32 loc;		 // 1 = in folder ; 2 = in BSA ; 3 = in RegList

	bool editable;	 // whether or not the Nif is to be edited (and therefore needs a unique copy)
	string basePath; // file it is based on, also relative to Oblivion\Data\Meshes
	UInt32 baseLoc;	 // 1 = in folder ; 2 = in BSA ; 3 = in RegList

	UInt32 nifVersion;
	UInt32 nifSEversion;

	UInt8 modID;
	SInt64 nifID;

	Niflib::NiNodeRef root;  // in-memory understanding of the mesh
	vector<Niflib::NiObjectRef> nifList;
	vector<Niflib::NiObjectRef>::size_type nifSize;
	Niflib::NifInfo* headerInfo;


	NifFile();
	NifFile(const string& file, UInt8 modIndex = 255, bool editable = false);
	NifFile(const string& oriPath, const string& altPath);
	NifFile(const string& file, UInt8 modIndex, UInt32 nifIndex, bool editable, UInt32 nifSEv = 0x00010003);
	NifFile(const string& oriPath, const string& altPath, UInt32 nifIndex);
	~NifFile();

	void loadNif();
	void readNif();
	Niflib::NiNodeRef findRoot();

	string getAbsPath() const;
	string getAbsPath(const string& path) const;
	string getAbsBasePath() const;
	string getVersion() const;

	void write(string path = "");

	// directory of registered NifFiles.
	static map < UInt8, map < UInt32, NifFile* > > RegList;
	static map <string, pair<UInt8, UInt32>* > RegListByFilename;

	static bool getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr);
	static bool getRegNif(string filename, NifFile* &nifPtr);


	// save/load data
	static vector<changeLog> delta;

	// save functions
	void logChange(const UInt32 &block, const UInt32 &type, const UInt32 &action, const string &value = "", const bool &clrPrev = false);
	void clrChange(const UInt32 &block, const UInt32 &type, const UInt32 &action);
	void frzChange(NifFile* depends);
	bool delChange();

	// load functions
	void loadChNifFile(UInt32 act);
	void loadChNiExtraData(UInt32 block, UInt32 act, UInt32 type, string& val);
	void loadChNiObjectNET(UInt32 block, UInt32 act, string& val);
	void loadChNiAVObject(UInt32 block, UInt32 act, string& val);
	void loadChNiNode(UInt32 block, UInt32 act, string& val);
	void loadChNiNodeDefer(UInt32 block, UInt32 act, string& val);
	void loadChNiAlphaProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiMatProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiStenProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiTexturingProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiVertColorProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiSourceTexture(UInt32 block, UInt32 act, string& val);
	void loadChBSFurnMkr(UInt32 block, UInt32 act, string& val);
};

template <class T>
Niflib::Ref<T> getNifBlock(NifFile*& nifPtr, UInt8 modID, UInt32 nifID, UInt32 blockID, bool mustBeEditable = false) {
	if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
		if ( nifPtr->root ) {
			if ( nifPtr->editable || !mustBeEditable ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::Ref<T> block = Niflib::DynamicCast<T>(nifPtr->nifList[blockID]);
					if ( block )
						return block;
					else
						throw std::exception("Block is not of expected type.");
				}
				else
					throw std::exception("Block index is out of range.");
			}
			else
				throw std::exception("Nif must be editable and is not.");
		}
		else
			throw std::exception("Nif root bad.");
	}
	else
		throw std::exception("Could not find nif.");
}
