#pragma once

#include "Utilities.h"

#include "NiflibTypes.h"

#include "niflib.h"
#include "obj/NiObject.h"
#include "obj/NiNode.h"

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
	string delta;

	// save functions
	void logChange(const UInt32 &block, const UInt32 &type, const UInt32 &action, const string &value = "", const bool &clrPrev = false);
	void clrChange(const UInt32 &block, const UInt32 &type, const UInt32 &action);

	// load functions
	void loadChNiExtraData(UInt32 block, UInt32 act, UInt32 type, string& val);
	void loadChNiObjectNET(UInt32 block, UInt32 act, string& val);
	void loadChNiAVObject(UInt32 block, UInt32 act, string& val);
	void loadChNiNode(UInt32 block, UInt32 act, string& val);
	void loadChNiAlphaProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiTexturingProperty(UInt32 block, UInt32 act, string& val);
	void loadChNiSourceTexture(UInt32 block, UInt32 act, string& val);
};

const char logNode = ':';
const char logNumber = '#';
const char logType = '-';
const char logAction = '=';
const char logValType = '|';
const char logValue = '\n';

// Utility function, determines if Nif is (0) missing, (1) in a folder, (2) in an archive, or (3) in RegList
UInt32 CheckFileLocation(string path, NifFile* nifPtr = NULL);

// Utility function for reading nif out of a file, a BSA archive, or the RegList
void WriteNifToStream(string path, UInt32& loc, std::iostream* stream);
