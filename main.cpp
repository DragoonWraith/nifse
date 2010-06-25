#include "main.h"

IDebugLog							gLog				("NifSE.log");

PluginHandle						g_pluginHandle		= kPluginHandle_Invalid;
UInt32								g_pluginVersion		= 999;

// various OBSE interfaces
static OBSEArrayVarInterface* arrInterface;
static OBSEMessagingInterface* msgInterface;
static OBSESerializationInterface* serInterface;
static OBSEStringVarInterface* strInterface;

typedef OBSEArrayVarInterface::Array	OBSEArray;
typedef OBSEArrayVarInterface::Element	OBSEElement;

// helper function for creating an OBSE StringMap from a std::map<std::string, OBSEElement>
OBSEArray* StringMapFromStdMap(const std::map<std::string, OBSEElement>& data, Script* callingScript)
{
	// create empty string map
	OBSEArray* arr = arrInterface->CreateStringMap(NULL, NULL, 0, callingScript);

	// add each key-value pair
	for (std::map<std::string, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		arrInterface->SetElement(arr, iter->first.c_str(), iter->second);
	}

	return arr;
}

// helper function for creating an OBSE Map from a std::map<double, OBSEElement>
OBSEArray* MapFromStdMap(const std::map<double, OBSEElement>& data, Script* callingScript)
{
	OBSEArray* arr = arrInterface->CreateMap(NULL, NULL, 0, callingScript);
	for (std::map<double, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		arrInterface->SetElement(arr, iter->first, iter->second);
	}

	return arr;
}

// helper function for creating OBSE Array from std::vector<OBSEElement>
OBSEArray* ArrayFromStdVector(const std::vector<OBSEElement>& data, Script* callingScript)
{
	OBSEArray* arr = arrInterface->CreateArray(&(data[0]), data.size(), callingScript);
	return arr;
}

// returns NifFile associated with given mod and index.
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
bool getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr) {
	dPrintAndLog("getRegNif","Finding nif registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
	if ( RegList.find(modID) != RegList.end() ) {
		if ( RegList[modID].find(nifID) != RegList[modID].end() ) {
			dPrintAndLog("getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" found.");
			if ( RegList[modID][nifID]->root ) {
				dPrintAndLog("getRegNif","Nif root is good.");
				nifPtr = RegList[modID][nifID];
				return true;
			}
			else {
				dPrintAndLog("getRegNif","Nif root is no good.");
				return false;
			}
		}
		else {
			dPrintAndLog("getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" not found.");
			return false;
		}
	}
	else {
		dPrintAndLog("getRegNif","Mod #"+UIntToString(modID)+" not found.");
		return false;
	}
}

// returns the modID and index of nif with given filename.
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
bool getRegNif(string filename, NifFile* &nifPtr) {
	dPrintAndLog("getRefNif","Finding nif with filename \""+filename+"\".");
	if ( RegListByFilename.find(filename) != RegListByFilename.end() ) {
		pair<UInt8, UInt32> nifIDs = *(RegListByFilename[filename]);
		return getRegNif(nifIDs.first, nifIDs.second, nifPtr);
	}
	dPrintAndLog("getRegNif","Filename not registered.");
	return false;
}

// registers a nif in the next available index for its modID
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
SInt64 NifFile::reg() {
	dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList.");
	if ( modID != 255 ) {
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8,map<UInt32,NifFile*> >(modID,map<UInt32,NifFile*>()) );
		UInt32 i = 0;
		while ( !((RegList[modID].insert(pair<UInt32, NifFile*>(i, this))).second) )
			++i;
		nifID = i;
		if ( editable ) {
			basePath = filePath;
			filePath = string("ni\\") + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
			RegListByFilename[filePath.substr(s_nifScriptPathLen,filePath.length()-s_nifScriptPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
		}
		else
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
		dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(i)+".");
		return nifID;
	}
	return nifID = -1;
}

// registers nif in given modID and index; mostly for loading.
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
SInt64 NifFile::reg(UInt8 modIndex, UInt32 nifIndex) {
	dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
	if ( modIndex != modID )
		return nifID = -1;
	if ( modID != 255 ) {
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8, map<UInt32, NifFile*> >(modID, map<UInt32, NifFile*>()));
		if ( (RegList[modID].insert(pair<UInt32, NifFile*>(nifIndex, this))).second ) {
			nifID = nifIndex;
			if ( editable ) {
				basePath = filePath;
				filePath = string("ni\\") + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
				RegListByFilename[filePath.substr(s_nifScriptPathLen,filePath.length()-s_nifScriptPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
			}
			else
				RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
			return nifID;
		}
	}
	return nifID = -1;
}

// returns true if the given NifFile is on RegList
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
bool NifFile::isreg() {
	if ( RegList.find(modID) != RegList.end() )
		if ( RegList[modID].find(nifID) != RegList[modID].end() )
			return true;
	return false;
}

// removes given NifFile from RegList and does memory cleanup. Used in ~NifFile
// declared in NifFile.h so Hooks_NifSE.cpp and NifFile.cpp can use it
void NifFile::dereg() {
	if ( isreg() ) {
//		delete RegListByFilename[RegList[modID][nifID]->filePath];
		RegListByFilename.erase(RegList[modID][nifID]->filePath);
//		delete RegList[modID][nifID];
		RegList[modID].erase(nifID);
	}
	if ( RegList[modID].empty() )
		RegList.erase(modID);
}

// creates a NifFile from given file in folders or archives.
// returns nifID of the NifFile.
static bool Cmd_NifOpen_Execute(COMMAND_ARGS) {
	*result = -1;

	char oriPath[kMaxMessageLength] = " ";
	int forEdit = 0;
	if (!ExtractArgs(PASS_EXTRACT_ARGS, &oriPath, &forEdit)) return true;
	dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" opened"+(forEdit!=0?(" for editing."):(" for reading.")));

	try {
		NifFile* nifPtr = new NifFile(string(oriPath), scriptObj->GetModIndex(), (forEdit!=0));
		if ( nifPtr->nifID >= 0 ) {
			*result = nifPtr->nifID;
			dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" registered as #"+UIntToString(nifPtr->modID)+"-"+UIntToString(*result)+".\n");
		}
		else
			dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" failed to register!\n");
	}
	catch (exception& except) {
		dPrintAndLog("NifOpen","Failed to create NifFile; exception \""+string(except.what())+"\" thrown.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifOpen,
	"Registers a nif for a mod to read or modify. Optional second argument is a boolean for editing - default is const.",
	0,
	2,
	kParams_OneString_OneOptionalBool
);

// deregisters and deletes NifFile of given nifID
static bool Cmd_NifClose_Execute(COMMAND_ARGS) {
	*result = 0;

	UInt32 nifID = 0;
	if (!ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) return true;

	UInt8 modID = scriptObj->GetModIndex();
	dPrintAndLog("NifClose","Closing nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
	NifFile* nifPtr = NULL;
	if ( getRegNif(modID, nifID, nifPtr) ) {
		delete nifPtr;
	}
	else
		dPrintAndLog("NifClose","Nif not found.\n");
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifClose,
	"Deletes the given NifFile, and if an editable file, deletes the file itself as well",
	0,
	1,
	kParams_OneInt
);

// returns the path where NifFile associated with the given nifID can be found
// for editable nifs, does not actually exist until called for by Oblivion
// but Oblivion needs to be calling the correct filename.
static bool Cmd_NifGetPath_Execute(COMMAND_ARGS) {
	*result = 0;
	string pathStr = " ";

	int nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetPath","Getting the path to nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				pathStr = nifPtr->filePath;
				dPrintAndLog("NifGetPath","Returning \""+pathStr+"\".\n");
			}
			else
				dPrintAndLog("NifGetPath","Nif file not deleted.\n");
		}
		else
			dPrintAndLog("NifGetPath","Nif not found.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, pathStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetPath,
	"Returns the path of a given registered Nif",
	0,
	1,
	kParams_OneInt
);

// returns the path where the path to the originally opened nif file
// can be found. For uneditable nif's, this is the same as the path.
static bool Cmd_NifGetOriginalPath_Execute(COMMAND_ARGS) {
	*result = 0;
	string pathStr = " ";

	int nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetOriginalPath","Getting the original path to nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				pathStr = nifPtr->basePath;
				dPrintAndLog("NifGetOriginalPath","Returning \""+pathStr+"\".\n");
			}
			else
				dPrintAndLog("NifGetOriginalPath","Nif file not deleted.\n");
		}
		else
			dPrintAndLog("NifGetOriginalPath","Nif not found.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, pathStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetOriginalPath,
	"Returns the original path of a given registered Nif",
	0,
	1,
	kParams_OneInt
);

// returns the number of ExtraData in the NifFile associated
// with given nifID.
static bool Cmd_NifGetNumExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumExtraData","Getting number of ExtraData nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->root->GetExtraData().size();
			dPrintAndLog("NifGetNumExtraData","Returning "+UIntToString(*result)+" ExtraData nodes.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNumExtraData,
	"Returns the number of ExtraData nodes in the given Nif",
	0,
	1,
	kParams_OneInt
);

static bool Cmd_NifAddExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	char name[kMaxMessageLength];
	char type[kMaxMessageLength];
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &name, &type, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		string typeStr = string(type);
		dPrintAndLog("NifAddExtraData","Adding ExtraData \""+string(name)+"\" of type \""+typeStr+"\" to nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			unsigned int ver = nifPtr->nifVersion;
			Niflib::NiObject* nuNiObj = NULL;
			unsigned int typeCode;
			if ( type == Niflib::NiExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiExtraData::Create();
				typeCode = ED_ExtraData;
			}
			else if ( type == Niflib::BSBound::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::BSBound::Create();
				typeCode = ED_Bound;
			}
			else if ( typeStr == Niflib::BSFurnitureMarker::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::BSFurnitureMarker::Create();
				typeCode = ED_Furniture;
			}
			else if ( typeStr == Niflib::NiBinaryExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiBinaryExtraData::Create();
				typeCode = ED_Binary;
			}
			else if ( typeStr == Niflib::NiBinaryVoxelData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiBinaryVoxelData::Create();
				typeCode = ED_BinaryVoxel;
			}
			else if ( typeStr == Niflib::NiBooleanExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiBooleanExtraData::Create();
				typeCode = ED_Boolean;
			}
			else if ( typeStr == Niflib::NiColorExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiColorExtraData::Create();
				typeCode = ED_Color;
			}
			else if ( typeStr == Niflib::NiFloatExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiFloatExtraData::Create();
				typeCode = ED_Float;
			}
			else if ( typeStr == Niflib::NiFloatsExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiFloatsExtraData::Create();
				typeCode = ED_Floats;
			}
			else if ( typeStr == Niflib::NiIntegerExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiIntegerExtraData::Create();
				typeCode = ED_Int;
			}
			else if ( typeStr == Niflib::BSXFlags::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::BSXFlags::Create();
				typeCode = ED_BSXFlags;
			}
			else if ( typeStr == Niflib::NiIntegersExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiIntegersExtraData::Create();
				typeCode = ED_Ints;
			}
			else if ( typeStr == Niflib::NiStringExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiStringExtraData::Create();
				typeCode = ED_Str;
			}
			else if ( typeStr == Niflib::NiStringsExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiStringsExtraData::Create();
				typeCode = ED_Strs;
			}
			else if ( typeStr == Niflib::NiTextKeyExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiTextKeyExtraData::Create();
				typeCode = ED_TextKey;
			}
			else if ( typeStr == Niflib::NiVectorExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiVectorExtraData::Create();
				typeCode = ED_Vector;
			}
			else if ( typeStr == Niflib::NiVertWeightsExtraData::TYPE.GetTypeName() ) {
				nuNiObj = Niflib::NiVertWeightsExtraData::Create();
				typeCode = ED_VertWeights;
			}
			else
				dPrintAndLog("NifAddExtraData","ExtraData type \""+typeStr+"\" unknown.\n");

			if ( nuNiObj ) {
				Niflib::NiExtraDataRef nuED = DynamicCast<Niflib::NiExtraData>(nuNiObj);
				if ( nuED ) {
					nuED->SetName(name);
					nifPtr->root->AddExtraData(nuED, ver);
					*result = nifPtr->root->GetExtraData().size() - 1;
					dPrintAndLog("NifAddExtraData","Addition successful.\n");
					nifPtr->extraDataChanges += changeLog(*result,typeCode,Act_Add,name);
				}
				else
					dPrintAndLog("NifAddExtraData","New NiObject not cast to NiExtraData.\n");
			}
			else
				dPrintAndLog("NifAddExtraData","New NiObject not created.\n");
		}
		else
			dPrintAndLog("NifAddExtraData","Nif not found.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifAddExtraData,
	"Adds an ExtraData node of the given type to the given Nif",
	0,
	3,
	kParams_TwoStrings_OneInt
);

// removes the specified ExtraData in the NifFile
// associated with the given nifID.
static bool Cmd_NifDeleteNthExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifDeleteNthExtraData","Deleting ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				NiExtraDataRef ed = nifPtr->findExtraData(edID);
				if ( ed ) {
					nifPtr->root->RemoveExtraData(ed);
					nifPtr->extraDataChanges += changeLog(edID, ED_ExtraData, Act_Remove);
					*result = 1;
					dPrintAndLog("NifDeleteNthExtraData","Deletion successful.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifDeleteNthExtraData,
	"Deletes the Nth ExtraData node of the given Nif",
	0,
	2,
	kParams_TwoInts
);

// returns the name of the specified ExtraData of the NifFile
// associated with given nifID.
static bool Cmd_NifGetNthExtraDataName_Execute(COMMAND_ARGS) {
	*result = 0;
	string edStr = " ";

	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthExtraDataName","Getting the name of ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				Niflib::NiExtraDataRef extraData = nifPtr->findExtraData(edID);
				edStr = extraData->GetName();
				dPrintAndLog("NifGetNthExtraDataName","Returning \""+edStr+"\".\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, edStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthExtraDataName,
	"Returns the name of the Nth ExtraData on the given Nif",
	0,
	2,
	kParams_TwoInts
);

// sets the name of the specified ExtraData in the
// NifFile associated with the given nifID.
static bool Cmd_NifSetNthExtraDataName_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuName[kMaxMessageLength] = " ";
	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuName, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthExtraDataName","Setting the name of ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuName)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				NiExtraDataRef ed = nifPtr->findExtraData(edID);
				if ( ed ) {
					*result = 1;
					ed->SetName(nuName);
					clearPrevChange(nifPtr->extraDataChanges, edID, ED_ExtraData, Act_SetName);
					nifPtr->extraDataChanges += changeLog(edID, ED_ExtraData, Act_SetName, nuName);
					dPrintAndLog("NifSetNthExtraDataName","ExtraData name set successfully.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthExtraDataName,
	"Sets the name of the ExtraData to the passed string.",
	0,
	3,
	kParams_OneString_TwoInts
);

static bool Cmd_NifGetExtraDataIndexByName_Execute(COMMAND_ARGS) {
	*result = -1;

	char edName[kMaxMessageLength];
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edName, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetExtraDataIndexByName","Getting the index of ExtraData \""+string(edName)+"\" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->getEDIndexByName(edName);
			if ( *result == nifPtr->root->GetExtraData().size() ) {
				*result = -1;
				dPrintAndLog("NifGetExtraDataIndexByName","ExtraData not found.\n");
			}
			else
				dPrintAndLog("NifGetExtraDataIndexByName","ExtraData found.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetExtraDataIndexByName,
	"Returns the index of the named ExtraData of the specified Nif.",
	0,
	2,
	kParams_OneString_OneInt
);

// returns the type of the specified ExtraData in the NifFile
// associated with the given nifID.
static bool Cmd_NifGetNthExtraDataType_Execute(COMMAND_ARGS) {
	*result = 0;
	string edStr = " ";

	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthExtraDataType","Getting the type of ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				NiExtraDataRef extraData = nifPtr->findExtraData(edID);
				edStr = extraData->GetType().GetTypeName();
				dPrintAndLog("NifGetNthExtraDataType","Returning \""+edStr+"\".\n");
			}
			else
				dPrintAndLog("NifGetNthExtraDataType","ExtraData out of range.\n");
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, edStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthExtraDataType,
	"Returns the type of the Nth ExtraData on the given Nif",
	0,
	2,
	kParams_TwoInts
);

// returns the string stored in the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NifGetNthExtraDataString_Execute(COMMAND_ARGS) {
	*result = 0;
	string edStr = " ";

	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthExtraDataString","Getting string value of ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				NiStringExtraDataRef ed = DynamicCast<NiStringExtraData>(nifPtr->findExtraData(edID));
				if ( ed ) {
					edStr = ed->GetData();
					dPrintAndLog("NifGetNthExtraDataString","Returning \""+edStr+"\".\n");
				}
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, edStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthExtraDataString,
	"If the Nth ExtraData of the given Nif is a String, gets the value of the ExtraData.",
	0,
	2,
	kParams_TwoInts
);

// sets the string stored in the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NifSetNthExtraDataString_Execute(COMMAND_ARGS) {
	*result = 0;

	char newStr[kMaxMessageLength] = " ";
	int edID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &newStr, &edID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthExtraDataString","Setting the string value of ExtraData #"+UIntToString(edID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(newStr)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( edID >= 0 && edID < nifPtr->root->GetExtraData().size() ) {
				NiStringExtraDataRef ed = DynamicCast<NiStringExtraData>(nifPtr->findExtraData(edID));
				if ( ed ) {
					*result = 1;
					ed->SetData(newStr);
					clearPrevChange(nifPtr->extraDataChanges, edID, ED_Str, Act_ED_SetValue);
					nifPtr->extraDataChanges += changeLog(edID, ED_Str, Act_ED_SetValue, newStr);
					dPrintAndLog("NifSetNthExtraDataString","ExtraData value set successfully.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthExtraDataString,
	"If the Nth ExtraData of the given Nif is a String, sets the value of the ExtraData to the passed string.",
	0,
	3,
	kParams_OneString_TwoInts
);

// returns the number of Children in the NifFile associated
// with given nifID.
static bool Cmd_NifGetNumChildren_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumChildren","Getting number of Children nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->root->GetChildren().size();
			dPrintAndLog("NifGetNumChildren","Returning "+UIntToString(*result)+" Children nodes.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNumChildren,
	"Returns the number of Children nodes in the given Nif",
	0,
	1,
	kParams_OneInt
);

static bool Cmd_NifGetNthChildName_Execute(COMMAND_ARGS) {
	*result = 0;
	string chStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildName","Getting the name of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				chStr = child->GetName();
				dPrintAndLog("NifGetNthChildName","Returning \""+chStr+"\".\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, chStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildName,
	"Returns the name of the specified child of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the name of the specified ExtraData in the
// NifFile associated with the given nifID.
static bool Cmd_NifSetNthChildName_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuName[kMaxMessageLength] = " ";
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuName, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildName","Setting the name of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuName)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					*result = 1;
					child->SetName(nuName);
					clearPrevChange(nifPtr->childrenChanges, chID, Ch_AVObj, Act_SetName);
					nifPtr->childrenChanges += changeLog(chID, Ch_AVObj, Act_SetName, nuName);
					dPrintAndLog("NifSetNthChildName","Child name set successfully.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildName,
	"Sets the name of the Child to the passed string.",
	0,
	3,
	kParams_OneString_TwoInts
);

static bool Cmd_NifGetChildIndexByName_Execute(COMMAND_ARGS) {
	*result = -1;

	char chName[kMaxMessageLength];
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chName, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetChildIndexByName","Getting the index of Child \""+string(chName)+"\" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->getChildIndexByName(chName);
			if ( *result == nifPtr->root->GetChildren().size() ) {
				*result = -1;
				dPrintAndLog("NifGetChildIndexByName","Child not found.\n");
			}
			else
				dPrintAndLog("NifGetChildIndexByName","Child found.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetChildIndexByName,
	"Returns the index of the named child of the specified Nif.",
	0,
	2,
	kParams_OneString_OneInt
);

// returns the type of the specified Child in the NifFile
// associated with the given nifID.
static bool Cmd_NifGetNthChildType_Execute(COMMAND_ARGS) {
	*result = 0;
	string chStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildType","Getting the type of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				chStr = child->GetType().GetTypeName();
				dPrintAndLog("NifGetNthChildType","Returning \""+chStr+"\".\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, chStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildType,
	"Returns the type of the Nth Child on the given Nif",
	0,
	2,
	kParams_TwoInts
);

// removes the specified Child in the NifFile
// associated with the given nifID.
static bool Cmd_NifDeleteNthChild_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifDeleteNthChild","Deleting Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					nifPtr->root->RemoveChild(child);
					nifPtr->root->GetChildren() = nifPtr->root->GetChildren();
					nifPtr->childrenChanges += changeLog(chID, Ch_AVObj, Act_Remove);
					*result = 1;
					dPrintAndLog("NifDeleteNthChild","Deletion successful.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifDeleteNthChild,
	"Deletes the Nth Child node of the given Nif",
	0,
	2,
	kParams_TwoInts
);

// gets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalTransform_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix = NULL;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalTransform","Getting local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					vector<vector<OBSEElement> > vrow;
					OBSEArray* orow;
					for ( int i = 0; i < 4; ++i ) {
						vrow.push_back(vector<OBSEElement>());
						for ( int j = 0; j < 4; ++j ) {
							vrow[i].push_back(child->GetLocalTransform().rows[i][j]);
						}
						orow = ArrayFromStdVector(vrow[i], scriptObj);
						vmatrix.push_back(orow);
					}
					omatrix = ArrayFromStdVector(vmatrix, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NifGetNthChildLocalTransform","Returning child's local transform.\n");
	else
		dPrintAndLog("NifGetNthChildLocalTransform","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalTransform,
	"Gets the local transform of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local transform of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTransform_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalTransform","This function will not be supported until OBSE v0019 and NifSE v1.1. Please use NifSetNthChildLocalTransformTEMP, instead.");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTransform,
	"Unsupported until OBSE v0019.",
	0,
	3,
	kParams_OneMatrix44_TwoInts
);

// gets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> translation;
	OBSEArray* arr;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalTranslation","Getting local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					translation.push_back(child->GetLocalTranslation().x);
					translation.push_back(child->GetLocalTranslation().y);
					translation.push_back(child->GetLocalTranslation().z);
					arr = ArrayFromStdVector(translation, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NifGetNthChildLocalTranslation","Returning child's local translation.\n");
	else
		dPrintAndLog("NifGetNthChildLocalTranslation","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalTranslation,
	"Gets the local translation of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTranslation_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalTranslation","This function will not be supported until OBSE v0019 and NifSE v1.1. Please use NifSetNthChildLocalTranslationTEMP, instead.\n");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTranslation,
	"Unsupported until OBSE v0019.",
	0,
	3,
	kParams_OneVector3_TwoInts
);

// gets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalRotation_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalRotation","Getting local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					vector<vector<OBSEElement> > vrow;
					OBSEArray* orow;
					for ( int i = 0; i < 3; ++i ) {
						vrow.push_back(vector<OBSEElement>());
						for ( int j = 0; j < 3; ++j ) {
							vrow[i].push_back(child->GetLocalRotation().rows[i][j]);
						}
						orow = ArrayFromStdVector(vrow[i], scriptObj);
						vmatrix.push_back(orow);
					}
					omatrix = ArrayFromStdVector(vmatrix, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NifGetNthChildLocalRotation","Returning child's local rotation.\n");
	else
		dPrintAndLog("NifGetNthChildLocalRotation","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalRotation,
	"Gets the local rotation of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalRotation_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalRotation","This function will not be supported until OBSE v0019 and NifSE v1.1. Please use NifSetNthChildLocalRotationTEMP, instead.\n");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalRotation,
	"Unsupported until OBSE v0019.",
	0,
	3,
	kParams_OneMatrix33_TwoInts
);

// gets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalScale","Getting local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					*result = child->GetLocalScale();
#ifdef _DEBUG
					Console_Print("NifGetNthChildLocalScale - Returning %.2f.\n", *result);
#endif
					_MESSAGE("NifGetNthChildLocalScale - Returning %.2f.\n", *result);
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalScale,
	"Gets the local scale of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	float nuScale = 0;
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuScale, &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalScale","Setting local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					child->SetLocalScale(nuScale);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocScale);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocScale,FloatToString(nuScale));
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalScale","Local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(((*result)!=0)?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalScale,
	"Unsupported until OBSE v0019.",
	0,
	3,
	kParams_OneFloat_TwoInts
);

// sets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTransformTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuTransform = vector< vector<float> >(4, vector<float>(4, 0));
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuTransform[0][0], &nuTransform[0][1], &nuTransform[0][2], &nuTransform[0][3], 
									   &nuTransform[1][0], &nuTransform[1][1], &nuTransform[1][2], &nuTransform[1][3],
									   &nuTransform[2][0], &nuTransform[2][1], &nuTransform[2][2], &nuTransform[2][3],
									   &nuTransform[3][0], &nuTransform[3][1], &nuTransform[3][2], &nuTransform[3][3],
									   &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalTransform","Setting local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					Niflib::Matrix44 newTransform (nuTransform[0][0], nuTransform[0][1], nuTransform[0][2], nuTransform[0][3], 
												   nuTransform[1][0], nuTransform[1][1], nuTransform[1][2], nuTransform[1][3],
												   nuTransform[2][0], nuTransform[2][1], nuTransform[2][2], nuTransform[2][3],
												   nuTransform[3][0], nuTransform[3][1], nuTransform[3][2], nuTransform[3][3]);
					child->SetLocalTransform(newTransform);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocTransform);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocTransform,MatrixToString(nuTransform));
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalTransform","Local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTransformTEMP,
	"Sets the local transform of the Nth Child of the given Nif.",
	0,
	18,
	kParams_Matrix44f_TwoInts
);

// sets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTranslationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	Niflib::Vector3 nuTranslation;
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &(nuTranslation.x), &(nuTranslation.y), &(nuTranslation.z), &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalTranslation","Setting local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					child->SetLocalTranslation(nuTranslation);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocTranslation);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocTranslation,"["+FloatToString(nuTranslation.x)+"|"+FloatToString(nuTranslation.y)+"|"+FloatToString(nuTranslation.z)+"|");
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalTranslation","Local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTranslationTEMP,
	"Sets the local translation of the Nth Child of the given Nif.",
	0,
	5,
	kParams_Vector3f_TwoInts
);

// sets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalRotationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuRotation = vector< vector<float> >(3, vector<float>(3, 0));
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuRotation[0][0], &nuRotation[0][1], &nuRotation[0][2],
									   &nuRotation[1][0], &nuRotation[1][1], &nuRotation[1][2],
									   &nuRotation[2][0], &nuRotation[2][1], &nuRotation[2][2],
									   &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalRotation","Setting local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					Niflib::Matrix33 newRotation (nuRotation[0][0], nuRotation[0][1], nuRotation[0][2],
												  nuRotation[1][0], nuRotation[1][1], nuRotation[1][2],
												  nuRotation[2][0], nuRotation[2][1], nuRotation[2][2]);
					child->SetLocalRotation(newRotation);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocRotation);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocRotation,MatrixToString(nuRotation));
				}
				else
					dPrintAndLog("NifSetNthChildLocalRotation","Child not found.");
			}
			else
				dPrintAndLog("NifSetNthChildLocalRotation","Child index out of range.");
		}
		else
			dPrintAndLog("NifSetNthChildLocalRotation","Nif not found.");
	}
	dPrintAndLog("NifSetNthChildLocalRotation","Local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalRotationTEMP,
	"Sets the local rotation of the Nth Child of the given Nif.",
	0,
	11,
	kParams_Matrix33f_TwoInts
);

static bool Cmd_NifNthChildHasMaterial_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasMaterial","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Material Property.");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasMaterial","Child found.");
				Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
				if ( mat ) {
					*result = 1;
					dPrintAndLog("NifNthChildHasMaterial","Material property found.\n");
				}
				else
					dPrintAndLog("NifNthChildHasMaterial","Material property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasMaterial","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasMaterial,
	"Returns whether the specified child of the specified Nif has a material property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifGetNthChildMaterial_Execute(COMMAND_ARGS) {
	*result = 0;
	string matStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildMaterial","Getting the name of Child #"+UIntToString(chID)+"'s Material Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifGetNthChildMaterial","Child found.");
				Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
				if ( mat ) {
					dPrintAndLog("NifGetNthChildMaterial","Material property found.");
					matStr = mat->GetName();
					dPrintAndLog("NifGetNthChildMaterial","Returning \""+matStr+"\".\n");
				}
				else
					dPrintAndLog("NifGetNthChildMaterial","Material property not found.\n");
			}
			else
				dPrintAndLog("NifGetNthChildMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifGetNthChildMaterial","Nif root bad.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, matStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildMaterial,
	"Returns the name of the specified child's material property of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifSetNthChildMaterial_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuMat[kMaxMessageLength];
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuMat, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildMaterial","Setting the name of Child #"+UIntToString(chID)+"'s Material Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuMat)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					dPrintAndLog("NifSetNthChildMaterial","Child found.");
					Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
					if ( mat ) {
						mat->SetName(nuMat);
						*result = 1;
						dPrintAndLog("NifSetNthChildMaterial","Material property set.");
						clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_PropMat_SetName);
						nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_PropMat_SetName,nuMat);
					}
					else
						dPrintAndLog("NifSetNthChildMaterial","Material property not found.\n");
				}
				else
					dPrintAndLog("NifSetNthChildMaterial","Child not found.");
			}
			else
				dPrintAndLog("NifSetNthChildMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifSetNthChildMaterial","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildMaterial,
	"Sets the name of the specified child's material property of the specified Nif.",
	0,
	3,
	kParams_OneString_TwoInts
);

static bool Cmd_NifNthChildHasTexturingProp_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasTexturingProp","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Texturing Property.");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasTexturingProp","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifNthChildHasTexturingProp","Texturing property found.\n");
					*result = 1;
				}
				else
					dPrintAndLog("NifNthChildHasTexturingProp","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasTexturingProp","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasTexturingProp","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasTexturingProp,
	"Returns whether the specified child of the specified Nif has a Base Texture property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifNthChildHasBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasBaseTexture","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Base Texture.");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasBaseTexture","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifNthChildHasBaseTexture","Texturing property found.");
					*result = (tex->HasTexture(Niflib::BASE_MAP)?1:0);
					dPrintAndLog("NifNthChildHasBaseTexture","Returning "+((*result)!=0?string("TRUE"):string("FALSE"))+".\n");
				}
				else
					dPrintAndLog("NifNthChildHasBaseTexture","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasBaseTexture","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasBaseTexture,
	"Returns whether the specified child of the specified Nif has a Base Texture property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifGetNthChildBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	string texStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildBaseTexture","Getting the name of Child #"+UIntToString(chID)+"'s Texture Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifGetNthChildBaseTexture","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifGetNthChildBaseTexture","Texturing property found.");
					if ( tex->HasTexture(Niflib::BASE_MAP) ) {
						texStr = tex->GetTexture(Niflib::BASE_MAP).source->GetTextureFileName();
						dPrintAndLog("NifGetNthChildBaseTexture","Returning \""+texStr+"\".\n");
					}
					else
						dPrintAndLog("NifGetNthChildBaseTexture","Texturing property does not have a base texture.\n");
				}
				else
					dPrintAndLog("NifGetNthChildBaseTexture","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifGetNthChildBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifGetNthChildBaseTexture","Nif root bad.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, texStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildBaseTexture,
	"Returns the name of the specified child's material property of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifSetNthChildBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuTex[kMaxMessageLength];
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuTex, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildBaseTexture","Setting the name of Child #"+UIntToString(chID)+"'s Texture Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuTex)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					dPrintAndLog("NifSetNthChildBaseTexture","Child found.");
					Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
					if ( tex ) {
						dPrintAndLog("NifSetNthChildBaseTexture","Texturing property found.");
						if ( tex->HasTexture(Niflib::BASE_MAP) ) {
							*result = 1;
							tex->GetTexture(Niflib::BASE_MAP).source->SetExternalTexture(nuTex);
							dPrintAndLog("NifSetNthChildBaseTexture","New texture set.\n");
							clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_PropTex_SetBaseMap);
							nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_PropTex_SetBaseMap,nuTex);
						}
						else
							dPrintAndLog("NifSetNthChildBaseTexture","Texturing property does not have a base texture.\n");
					}
					else
						dPrintAndLog("NifSetNthChildBaseTexture","Texturing property not found.\n");
				}
				else
					dPrintAndLog("NifSetNthChildBaseTexture","Child not found.\n");
			}
			else
				dPrintAndLog("NifSetNthChildBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifSetNthChildBaseTexture","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildBaseTexture,
	"Sets the name of the specified child's material property of the specified Nif.",
	0,
	3,
	kParams_OneString_TwoInts
);

#ifdef _DEBUG
static bool Cmd_NifWriteToDisk_Execute(COMMAND_ARGS) {
	*result = 0;

	char filename[kMaxMessageLength] = " ";
	UInt32 nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &filename, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifWriteToDisk","Writing nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to disk as \""+string(filename)+"\".");
		NifFile* nifPtr = NULL;
		getRegNif(modID,nifID,nifPtr);
		if ( nifPtr->root ) {
			Niflib::WriteNifTree(GetOblivionDirectory()+"Data\\Meshes\\ni\\"+filename,DynamicCast<Niflib::NiObject>(nifPtr->root),nifPtr->headerInfo);
			*result = 1;
			dPrintAndLog("NifWriteToDisk","Nif written to disk.\n");
		}
		else
			dPrintAndLog("NifWriteToDisk","Nif not found.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifWriteToDisk,
	"Writes the nif to disk permanently. For testing only!",
	0,
	2,
	kParams_OneString_OneInt
);
#endif

static bool Cmd_NifGetAltGrip_Execute(COMMAND_ARGS) { // returns path to model using opposite number of hands
	dPrintAndLog("NifGetAltGrip");
	TESForm* form = NULL;

	if (ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form))
	{
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESObjectWEAP* weapon = (TESObjectWEAP*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESObjectWEAP, 0);
			if ( weapon ) { // only weapons have handedness
				dPrintAndLog("NifGetAltGrip","Weapon: "+string(weapon->fullName.name.m_data));
				if ( weapon->type <= 3 ) { // only works on blades/blunt weapons
					TESModel* model = (TESModel*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESModel, 0);
					string oriPath = model->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","AltWeapon");
					if ( CheckFileLocation(altPath) == 0 ) {
						CopyNif(oriPath,altPath);
						NifFile alt (altPath);
						if ( alt.root ) {
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt.getEDByName("Prn"));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetAltGrip","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "SideWeapon" ) { // one-handed according to Nif
									Prn->SetData("BackWeapon");
									dPrintAndLog("NifGetAltGrip","Weapon switched from 1h to 2h! Prn = "+Prn->GetData());
								}
								else if ( Prn->GetData() == "BackWeapon" ) { // two-handed according to Nif
									Prn->SetData("SideWeapon");
									dPrintAndLog("NifGetAltGrip","Weapon switched from 2h to 1h! Prn = "+Prn->GetData());
								}
								else {
									PrintAndLog("NifGetAltGrip","Unknown weapon type! Prn = "+Prn->GetData());
									return true;
								}
								alt.commitChanges();
								dPrintAndLog("NifGetAltGrip","New Alt-Grip Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetAltGrip","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else {
							PrintAndLog("NifGetAltGrip","Nif could not be read!");
							return true;
						}
					}

					// return the new mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetAltGrip","Alt grip model path returned to Oblivion! path = "+altPath);
				}
				else // weapon->type > 3
					PrintAndLog("NifGetAltGrip","Invalid weapon type!");
			}
			else // !weapon
				PrintAndLog("NifGetAltGrip","Argument not weapon!");
		}
		else // !form
			PrintAndLog("NifGetAltGrip","Invalid argument!");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetAltGrip","Failed to determine passed argument!");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetAltGrip,"Returns the opposite handed version of a weapon mesh. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);

static bool Cmd_NifGetOffHand_Execute(COMMAND_ARGS) {
	dPrintAndLog("NifGetOffHand");

	TESForm* form = NULL;
	if (ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form))
	{
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESObjectWEAP* weapon = (TESObjectWEAP*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESObjectWEAP, 0);
			if ( weapon ) { // only weapons can be wielded off-hand
				dPrintAndLog("NifGetOffHand","Weapon: "+string(weapon->fullName.name.m_data));
				if ( weapon->type <= 3 ) { // only works on blades/blunt weapons
					TESModel* model = (TESModel*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESModel, 0);
					string oriPath = model->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","Torch");
					if ( CheckFileLocation(altPath) == 0 ) {
						CopyNif(oriPath,altPath);
						NifFile alt (altPath);
						if ( alt.root ) {
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt.getEDByName("Prn"));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetOffHand","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "SideWeapon" || Prn->GetData() == "BackWeapon" ) { // one of two weapon values
									Prn->SetData("Torch");
									dPrintAndLog("NifGetOffHand","Weapon switched to Shield! Prn = "+Prn->GetData());
								}
								else {
									PrintAndLog("NifGetOffHand","Unknown weapon type! Prn = "+Prn->GetData());
									return true;
								}
								NiAVObjectRef Scabbard = alt.getChildByName("Scb");
								if ( Scabbard != NULL ) {
									dPrintAndLog("NifGetOffHand","Removing scabbard!");
									alt.root->RemoveChild(Scabbard);
								}
								else
									dPrintAndLog("NifGetOffHand","No scabbard to remove!");
								alt.commitChanges();
								dPrintAndLog("NifGetOffHand","New off-hand Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetOffHand","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else { // !alt.root
							PrintAndLog("NifGetOffHand","Nif could not be read!");
							return true;
						}
					}

					// return the mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetOffHand","Off hand model path returned to Oblivion! path = "+altPath);
				}
				else // weapon->type > 3
					PrintAndLog("NifGetOffHand","Invalid weapon type!");
			}
			else // !weapon
				PrintAndLog("NifGetOffHand","Argument not weapon!");
		}
		else // !form
			PrintAndLog("NifGetOffHand","Invalid argument!");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetOffHand","Failed to determine passed argument!");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetOffHand,"Returns the off-hand version of a weapon mesh. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);

// this function is not tested
static bool Cmd_NifGetBackShield_Execute(COMMAND_ARGS) {
	dPrintAndLog("NifGetBackShield");

	TESForm * form = NULL;
	if ( ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form) ) {
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESBipedModelForm	* bip = (TESBipedModelForm *)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESBipedModelForm, 0);
			if ( bip ) { // to be shield must be BipedModel
				dPrintAndLog("NifGetBackShield","Shield: "+string(form->GetFullName()->name.m_data));
				if ( bip->GetSlot() == TESBipedModelForm::kPart_Shield ) { // only works on shields
					string oriPath = bip->bipedModel->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","Bip01 L Shoulder Helper");
					if ( CheckFileLocation(altPath) == 0 ) {
						CopyNif(oriPath,altPath);
						NifFile alt (altPath);
						if ( alt.root ) {
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt.getEDByName("Prn"));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetBackShield","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "Bip01 L ForearmTwist" ) { // is a shield
									Prn->SetData("Bip01 L Shoulder Helper");
									dPrintAndLog("NifGetBackShield","Shield switched to shoulder! Prn = "+Prn->GetData());
								}
								else {
									PrintAndLog("NifGetBackShield","Unknown shield type! Prn = "+Prn->GetData());
									return true;
								}
								for ( alt.childIt = alt.root->GetChildren().begin() ; alt.childIt != alt.root->GetChildren().end() ; ++(alt.childIt) ) {
									dPrintAndLog("NifGetBackShield",string("Shield \"")+form->GetFullName()->name.m_data+"\" Child \""+(*(alt.childIt))->GetName()+"\" translated and rotated!");
									(*(alt.childIt))->SetLocalTranslation((*(alt.childIt))->GetLocalTranslation()+Niflib::Vector3(25,-11,-20));
									(*(alt.childIt))->SetLocalRotation((*(alt.childIt))->GetLocalRotation()*Niflib::Matrix33(-0.9249,-0.1247,0.3593,-0.4966,0.9655,-0.1710,-0.3256,-0.2287,-0.9174));
								}
								alt.commitChanges();
								dPrintAndLog("NifGetBackShield","New back shield Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetBackShield","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else { // !alt.root
							PrintAndLog("NifGetBackShield","Nif could not be read!");
							return true;
						}
					}

					// return the mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetBackShield","Back shield model path returned to Oblivion! path = "+altPath);
				}
				else // shield->BipedModel.getSlot() != kPart_Shield
					PrintAndLog("NifGetBackShield","Invalid armor type (needs shield)!");
			}
			else // !shield
				PrintAndLog("NifGetBackShield","Argument not armor!");
		}
		else // !form
			PrintAndLog("NifGetBackShield","Invalid argument!");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetBackShield","Failed to determine passed argument!");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetBackShield,"Returns a version of a shield suitable for placing on one's back. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);

static void NifSE_SaveCallback(void * reserved) {
	dPrintAndLog("NifSave","Saving registered nifs");
	UInt8 modIndex;
	UInt32 nifIndex;
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = RegList.begin(); RegListIter != RegList.end(); ++RegListIter ) {
		modIndex = RegListIter->first;
		dPrintAndLog("NifSave","Saving Nifs associated with mod #"+UIntToString(modIndex)+".");
		serInterface->WriteRecord('MOD ', g_pluginVersion, (void *)(&modIndex), sizeof(UInt8));
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter ) {
			nifIndex = NifListIter->first;
			dPrintAndLog("NifLoad","Nif #"+UIntToString(modIndex)+"-"+UIntToString(nifIndex)+" found.");
			if ( NifListIter->second->root ) {
				dPrintAndLog("NifSave","Saving Nif #"+UIntToString(RegListIter->first)+"-"+UIntToString(NifListIter->first)+".");
				serInterface->WriteRecord('niID', g_pluginVersion, (void *)(&nifIndex), sizeof(UInt32));
				if ( NifListIter->second->editable ) {
					dPrintAndLog("NifSave","Saving filepath \""+NifListIter->second->basePath+"\" ("+UIntToString(NifListIter->second->filePath.length())+"); editable nif.");
					serInterface->WriteRecord('niRe', g_pluginVersion, (void *)(NifListIter->second->basePath.c_str()), NifListIter->second->basePath.length());
				}
				else { // constant
					dPrintAndLog("NifSave","Saving filepath \""+NifListIter->second->filePath+"\" ("+UIntToString(NifListIter->second->filePath.length())+"); constant nif.");
					serInterface->WriteRecord('niRc', g_pluginVersion, (void *)(NifListIter->second->filePath.c_str()), NifListIter->second->filePath.length());
				}

				if ( NifListIter->second->extraDataChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving ExtraData changes.");
					serInterface->WriteRecord('niED', g_pluginVersion, (void *)(NifListIter->second->extraDataChanges.c_str()), NifListIter->second->extraDataChanges.length());
				}

				if ( NifListIter->second->collisionChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Collision changes.");
					serInterface->WriteRecord('niCo', g_pluginVersion, (void *)(NifListIter->second->collisionChanges.c_str()), NifListIter->second->collisionChanges.length());
				}

				if ( NifListIter->second->childrenChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Children changes.");
					serInterface->WriteRecord('niCh', g_pluginVersion, (void *)(NifListIter->second->childrenChanges.c_str()), NifListIter->second->childrenChanges.length());
				}

				if ( NifListIter->second->effectChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Effect changes.");
					serInterface->WriteRecord('niEf', g_pluginVersion, (void *)(NifListIter->second->effectChanges.c_str()), NifListIter->second->effectChanges.length());
				}
			}
		}
	}
	dPrintAndLog("NifSave","Save complete.\n");
}

string ReadString(UInt32 length) {
	char* tempStr = new char[length+1];
	serInterface->ReadRecordData(tempStr, length);
	tempStr[length] = '\0';
	string changes = string(tempStr);
	delete[] tempStr;
	return changes;
}

void LoadChangelog(string &changes, string &chNode, UInt32 &chType, UInt32 &chAct, string &chVal) {
	string::size_type posS;
	string::size_type posF;

	posS = 0;
	posF = changes.find(logNode,posS);
	chNode = changes.substr(posS,posF-posS);
	dPrintAndLog("LoadChangelog","Change node: \""+chNode+"\".");

	posS = posF+1;
	posF = changes.find(logType,posS);
	chType = StringToUInt(changes.substr(posS,posF-posS));
	dPrintAndLog("LoadChangelog","Change type: \""+changes.substr(posS,posF-posS)+"\".");

	posS = posF+1;
	posF = changes.find(logAction,posS);
	chAct = StringToUInt(changes.substr(posS,posF-posS));
	dPrintAndLog("LoadChangelog","Change action: \""+changes.substr(posS,posF-posS)+"\".");
	
	posS = posF+1;
	posF = changes.find(logValue,posS);
	chVal = changes.substr(posS,posF-posS);
	dPrintAndLog("LoadChangelog","Change value: \""+chVal+"\".");

	changes.erase(0,posF+1);
}

static void NifSE_LoadCallback(void * reserved) {
	dPrintAndLog("NifLoad","loading saved NifFiles");
	UInt32 type, version, length;

	UInt32 modID;
	UInt8 testInt;
	UInt32 nifID;
	string nifPath;

	string changes;
	string chNode;
	UInt32 chType;
	UInt32 chAct;
	string chVal;

	NiExtraDataRef edNode;
	Niflib::NiStringExtraDataRef edStrNode;

	NiAVObjectRef avNode;
	vector<float> vvector;
	vector< vector<float> > vmatrix;
	Niflib::Vector3 nvector3;
	Niflib::Matrix33 nmatrix33;
	Niflib::Matrix44 nmatrix44;

	NifFile* nifPtr = NULL;

	dPrintAndLog("NifLoad","Clearing previous RegList.");
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = RegList.begin(); RegListIter != RegList.end(); ++RegListIter )
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter )
			std::remove(NifListIter->second->filePath.c_str());
	RegList.clear();

	dPrintAndLog("NifLoad","Previous RegList cleared.");
	while( serInterface->GetNextRecordInfo(&type, &version, &length) ) {
		dPrintAndLog("NifLoad",string("Type '")+((char*)&type)[3]+((char*)&type)[2]+((char*)&type)[1]+((char*)&type)[0]+"'\tVersion "+UIntToString(version)+"\tLength "+UIntToString(length));
		switch (type) {
			case 'test':
				dPrintAndLog("NifLoad","'test' record.");
				serInterface->ReadRecordData(&testInt, sizeof(UInt8));
				dPrintAndLog("NifLoad","Saved test number = "+UIntToString(testInt));
				break;

			case 'MOD ':
				dPrintAndLog("NifLoad","'MOD ' record - new mod's NifFiles.");
				serInterface->ReadRecordData(&modID, sizeof(UInt8));
				dPrintAndLog("NifLoad","Saved modID: "+UIntToString(modID)+".");
				if ( !(serInterface->ResolveRefID(modID << 24, &modID)) )
					modID = 255; // mod not loaded
				else
					modID = modID >> 24;
				dPrintAndLog("NifLoad","modID resolved: "+UIntToString(modID)+".");
				break;

			case 'niID':
				dPrintAndLog("NifLoad","'niID' record - new NifFile.");
				if ( modID != 255 )
					serInterface->ReadRecordData(&nifID, sizeof(UInt32));
				dPrintAndLog("NifLoad","New NifFile #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
				break;

			case 'niRe':
				dPrintAndLog("NifLoad","'niRe' record - new filename, editable.");
				if ( modID != 255 ) {
					nifPath = ReadString(length);
					nifPtr = new NifFile(nifPath, modID, nifID, true);
					dPrintAndLog("NifLoad","Filename is \""+nifPath+"\".");
				}
				break;

			case 'niRc':
				dPrintAndLog("NifLoad","'niRc' record - new filename, const.");
				if ( modID != 255 ) {
					nifPath = ReadString(length);
					nifPtr = new NifFile(nifPath, modID, nifID, false);
					dPrintAndLog("NifLoad","Filename is \""+nifPath+"\".");
				}
				break;

			case 'niED':
				dPrintAndLog("NifLoad","'niED' record - new ExtraData changes.");
				if ( modID != 255 ) {
					changes = ReadString(length);
					dPrintAndLog("NifLoad","ExtraData changelog loaded.");
					edNode = NULL;
					edStrNode = NULL;
					while ( changes.length() != 0 ) {
						LoadChangelog(changes, chNode, chType, chAct, chVal);
						dPrintAndLog("NifLoad","Changes loaded.");
						switch (chAct) {
							case Act_Add:
								dPrintAndLog("NifLoad","Adding new ExtraData node.");
								switch (chType) {
									case ED_ExtraData:
										dPrintAndLog("NifLoad","Adding NiExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiExtraData::Create()));
										break;

									case ED_Bound:
										dPrintAndLog("NifLoad","Adding BSBound node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSBound::Create()));
										break;

									case ED_Furniture:
										dPrintAndLog("NifLoad","Adding BSFurnitureMarker node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSFurnitureMarker::Create()));
										break;

									case ED_Binary:
										dPrintAndLog("NifLoad","Adding NiBinaryExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBinaryExtraData::Create()));
										break;

									case ED_BinaryVoxel:
										dPrintAndLog("NifLoad","Adding NiBinaryVoxelData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBinaryVoxelData::Create()));
										break;

									case ED_Boolean:
										dPrintAndLog("NifLoad","Adding NiBooleanExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBooleanExtraData::Create()));
										break;

									case ED_Color:
										dPrintAndLog("NifLoad","Adding NiColorExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiColorExtraData::Create()));
										break;

									case ED_Float:
										dPrintAndLog("NifLoad","Adding NiFloatExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiFloatExtraData::Create()));
										break;

									case ED_Floats:
										dPrintAndLog("NifLoad","Adding NiFloatsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiFloatsExtraData::Create()));
										break;

									case ED_Int:
										dPrintAndLog("NifLoad","Adding NiIntegerExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiIntegerExtraData::Create()));
										break;

									case ED_BSXFlags:
										dPrintAndLog("NifLoad","Adding BSXFlags node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSXFlags::Create()));
										break;

									case ED_Ints:
										dPrintAndLog("NifLoad","Adding NiIntegersExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiIntegersExtraData::Create()));
										break;

									case ED_Str:
										dPrintAndLog("NifLoad","Adding NiStringExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiStringExtraData::Create()));
										break;

									case ED_Strs:
										dPrintAndLog("NifLoad","Adding NiStringsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiStringsExtraData::Create()));
										break;

									case ED_TextKey:
										dPrintAndLog("NifLoad","Adding NiTextKeyExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiTextKeyExtraData::Create()));
										break;

									case ED_Vector:
										dPrintAndLog("NifLoad","Adding NiVectorExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiVectorExtraData::Create()));
										break;

									case ED_VertWeights:
										dPrintAndLog("NifLoad","Adding NiVertWeightsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiVertWeightsExtraData::Create()));
										break;

									default:
										dPrintAndLog("Unknown ExtraData type.");
								}
								if ( edNode ) {
									edNode->SetName(chVal);
									nifPtr->root->AddExtraData(edNode, nifPtr->nifVersion);
									dPrintAndLog("NifLoad","ED node \""+chVal+"\" added.");
								}
								break;

							default:
								if ( chNode[0] == logNumber && StringToUInt(chNode.substr(1,chNode.length()-1)) < nifPtr->root->GetExtraData().size() )
									edNode = nifPtr->findExtraData(StringToUInt(chNode.substr(1,chNode.length()-1)));
								else
									edNode = nifPtr->getEDByName(chNode);

								if ( !edNode ) {
									dPrintAndLog("NifLoad","ExtraData node does not exist.");
									break;
								}
								else
									dPrintAndLog("NifLoad","ExtraData node found.");

								switch (chType) {
									case ED_ExtraData:
										dPrintAndLog("NifLoad","Changing ExtraData node.");
										switch (chAct) {
											case Act_Remove:
												nifPtr->root->RemoveExtraData(edNode);
												dPrintAndLog("NifLoad","ED node removed.");
												break;

											case Act_SetName:
												edNode->SetName(chVal);
												dPrintAndLog("NifLoad","ED node renamed \""+chVal+"\".");
												break;

											default:
												dPrintAndLog("NifLoad","Unknown ED node operation.");
										}
										break;

									case ED_Str:
										dPrintAndLog("NifLoad","Changing ExtraStringDataNode.");
										edStrNode = DynamicCast<NiStringExtraData>(edNode);
										if ( edStrNode ) {
											switch (chAct) {
												case Act_ED_SetValue:
													dPrintAndLog("NifLoad","Setting String data to \""+chVal+"\".");
													edStrNode->SetData(chVal);
													break;

												default:
													dPrintAndLog("NifLoad","Unknown ED String node operation.");
											}
										}
										else
											dPrintAndLog("NifLoad","ED String node failed.");
										break;

									case ED_Bound:
									case ED_Furniture:
									case ED_Binary:
									case ED_BinaryVoxel:
									case ED_Boolean:
									case ED_Color:
									case ED_Float:
									case ED_Floats:
									case ED_Int:
									case ED_BSXFlags:
									case ED_Ints:
									case ED_Strs:
									case ED_TextKey:
									case ED_Vector:
									case ED_VertWeights:
										dPrintAndLog("NifLoad","Changes to this ED node type are unsupported.");
										break;

									default:
										dPrintAndLog("NifLoad","Unknown node type.");
								}
						}
					}
				}
				break;

			case 'niCo':
				dPrintAndLog("NifLoad","'niCo' record - Collision changes not supported.");
				break;

			case 'niCh':
				dPrintAndLog("NifLoad","'niCh' record - new Children changes.");
				if ( modID != 255 ) {
					changes = ReadString(length);
					dPrintAndLog("NifLoad","Children changelog loaded.");
					avNode = NULL;
					while ( changes.length() != 0 ) {
						LoadChangelog(changes, chNode, chType, chAct, chVal);
						if ( chNode[0] == logNumber )
							avNode = nifPtr->root->GetChildren()[StringToUInt(chNode.substr(1,chNode.length()-1))];
						else
							avNode = nifPtr->getChildByName(chNode);
						
						switch (chType) {
							case Ch_AVObj:
								dPrintAndLog("NifLoad","Changing AVObject node.");
								switch (chAct) {
									case Act_Remove:
										nifPtr->root->RemoveChild(avNode);
										dPrintAndLog("NifLoad","AV node removed.");
										break;

									case Act_SetName:
										avNode->SetName(chVal);
										dPrintAndLog("NifLoad","AV node renamed \""+chVal+"\".");
										break;

									case Act_AV_SetLocTransform:
										vmatrix = StringToMatrix(chVal);
										if ( vmatrix.size() == 4 ) {
											if ( vmatrix[0].size() == 4 && vmatrix[1].size() == 4 && vmatrix[2].size() == 4 && vmatrix[3].size() == 4 ) {
												nmatrix44 = Niflib::Matrix44(vmatrix[0][0], vmatrix[0][1], vmatrix[0][2], vmatrix[0][3],
																			 vmatrix[1][0], vmatrix[1][1], vmatrix[1][2], vmatrix[1][3],
																			 vmatrix[2][0], vmatrix[2][1], vmatrix[2][2], vmatrix[2][3],
																			 vmatrix[3][0], vmatrix[3][1], vmatrix[3][2], vmatrix[3][3]);
												avNode->SetLocalTransform(nmatrix44);
												dPrintAndLog("NifLoad","AV node Local Transform set.");
											}
											else
												dPrintAndLog("NifLoad","Transform matrix missized: Is "+UIntToString(vmatrix.size())+" wide, should be 4.");
										}
										else
											dPrintAndLog("NifLoad","Transform matrix missized: Is "+UIntToString(vmatrix.size())+" tall, should be 4.");
										break;

									case Act_AV_SetLocTranslation:
										vvector = StringToVector(chVal);
										if ( vvector.size() == 3 ) {
											nvector3 = Niflib::Vector3(vvector[0], vvector[1], vvector[2]);
											avNode->SetLocalTranslation(nvector3);
											dPrintAndLog("NifLoad","AV node Local Translation set.");
										}
										else
											dPrintAndLog("NifLoad","Translation vector missized: Is "+UIntToString(vvector.size())+", should be 3.");
										break;

									case Act_AV_SetLocRotation:
										vmatrix = StringToMatrix(chVal);
										if ( vmatrix.size() == 3 ) {
											if ( vmatrix[0].size() == 3 && vmatrix[1].size() == 3 && vmatrix[2].size() == 3 ) {
												nmatrix33 = Niflib::Matrix33(vmatrix[0][0], vmatrix[0][1], vmatrix[0][2],
																			 vmatrix[1][0], vmatrix[1][1], vmatrix[1][2],
																			 vmatrix[2][0], vmatrix[2][1], vmatrix[2][2]);
												avNode->SetLocalRotation(nmatrix33);
												dPrintAndLog("NifLoad","AV node Local Rotation set.");
											}
											else
												dPrintAndLog("NifLoad","Rotation matrix missized: Is "+UIntToString(vmatrix.size())+" wide, should be 3.");
										}
										else
											dPrintAndLog("NifLoad","Rotation matrix missized: Is "+UIntToString(vmatrix.size())+" tall, should be 3.");
										break;

									case Act_AV_PropMat_SetName:
										dPrintAndLog("NifLoad","Child material changed to \""+chVal+"\".");
										avNode->GetPropertyByType(Niflib::NiMaterialProperty::TYPE)->SetName(chVal);
										break;

									case Act_AV_PropTex_SetBaseMap:
										dPrintAndLog("NifLoad","Child base texture set to \""+chVal+"\".");
										DynamicCast<Niflib::NiTexturingProperty>(avNode->GetPropertyByType(Niflib::NiTexturingProperty::TYPE))->GetTexture(Niflib::BASE_MAP).source->SetExternalTexture(chVal);
										break;

									default:
										dPrintAndLog("NifLoad","Unknown AV node operation.");
								}
								break;

							case Ch_NiCam:
							case Ch_NiGeom:
							case Ch_NiParticles:
							case Ch_NiAutoNormParticles:
							case Ch_NiParticleMeshes:
							case Ch_NiParticleSystem:
							case Ch_NiMeshParticleSystem:
							case Ch_NiRotParticles:
							case Ch_NiTriBasedGeom:
							case Ch_NiClod:
							case Ch_NiTriShape:
							case Ch_NiTriStrips:
							case Ch_NiNode:
							case Ch_AvoidNode:
							case Ch_FxWidget:
							case Ch_FxButton:
							case Ch_FxRadioButton:
							case Ch_NiBillboard:
							case Ch_NiBone:
							case Ch_NiBSAnim:
							case Ch_NiBSParticle:
							case Ch_NiSwitch:
							case Ch_NiLOD:
							case Ch_RootCol:
								dPrintAndLog("NifLoad","Child node type changes unsupported.");
								break;

							default:
								dPrintAndLog("NifLoad","Unknown node type.");
						}
					}
				}
				break;

			case 'niEf':
				dPrintAndLog("NifLoad","'niEf' record - Effects changes not supported.");
				break;

			default:
				dPrintAndLog("NifLoad","Unknown record type.");
		}
	}
	dPrintAndLog("NifLoad","Load complete.\n");
}

static void NifSE_NewCallback(void * reserved) {
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = RegList.begin(); RegListIter != RegList.end(); ++RegListIter )
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter )
			std::remove(NifListIter->second->filePath.c_str());
	RegList.clear();
}

static void MessageHandler(OBSEMessagingInterface::Message* msg) {
	switch (msg->type) {
		case OBSEMessagingInterface::kMessage_PostLoad:
//			msgInterface->RegisterListener(g_pluginHandle, "CSE", MessageHandler);
			_MESSAGE("OBSE Plugins loaded. Listening for CSE dispatches.");
			break;

		case 'CSEL':
			msgInterface->Dispatch(g_pluginHandle, g_pluginVersion, &FunctionDocMap, sizeof(&FunctionDocMap), "CSE");
			_MESSAGE("CSE Documentation dispatched.");
			break;
	}
}

extern "C" {

	bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
	{
		_MESSAGE("query");

		// fill out the info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "NifSE";
		info->version = g_pluginVersion;

		// version checks
		if(!obse->isEditor)
		{
			if(obse->obseVersion < OBSE_VERSION_INTEGER)
			{
				_ERROR("OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
				return true;
			}

			if(obse->oblivionVersion != OBLIVION_VERSION)
			{
				_ERROR("Incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
				return true;
			}

			strInterface = (OBSEStringVarInterface*)obse->QueryInterface(kInterface_StringVar);
			if(!strInterface)
			{
				_ERROR("string_var Interface not found");
				return false;
			}

			if(strInterface->version < OBSEStringVarInterface::kVersion)
			{
				_ERROR("Incorrect string_var version found (got %08X need %08X)", strInterface->version, OBSESerializationInterface::kVersion);
				return false;
			}

			serInterface = (OBSESerializationInterface *)obse->QueryInterface(kInterface_Serialization);
			if(!serInterface)
			{
				_ERROR("Serialization Interface not found");
				return false;
			}

			if(serInterface->version < OBSESerializationInterface::kVersion)
			{
				_ERROR("Incorrect Serialization version found (got %08X need %08X)", serInterface->version, OBSESerializationInterface::kVersion);
				return false;
			}

			arrInterface = (OBSEArrayVarInterface*)obse->QueryInterface(kInterface_ArrayVar);
			if (!arrInterface)
			{
				_ERROR("Array interface not found");
				return false;
			}
		}
		else
		{
			msgInterface = (OBSEMessagingInterface*)obse->QueryInterface(kInterface_Messaging);
			if(!msgInterface)
			{
				_ERROR("Messaging Interface not found");
				return false;
			}

			if(msgInterface->version < OBSEMessagingInterface::kVersion)
			{
				_ERROR("Incorrect messaging version found (got %08X need %08X)", msgInterface->version, OBSEMessagingInterface::kVersion);
				return false;
			}
		}

		// version checks pass

		return true;
	}

	bool OBSEPlugin_Load(const OBSEInterface * obse)
	{
		_MESSAGE("load");

		g_pluginHandle = obse->GetPluginHandle();

		// register commands
		obse->SetOpcodeBase(0x25CF);
#ifdef _DEBUG
		obse->RegisterCommand(		&kCommandInfo_NifWriteToDisk									); //0x2000
#endif
		obse->SetOpcodeBase(0x24F0); // to 0x24FF (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NifGetAltGrip										); //0x24F0 T
		obse->RegisterCommand(		&kCommandInfo_NifGetOffHand										); //0x24F1 T
		obse->RegisterCommand(		&kCommandInfo_NifGetBackShield									); //0x24F2 T
		// ------------------------------------- End of Deprecated Functions ------------------------------------- //

		obse->RegisterCommand(		&kCommandInfo_NifOpen											); //0x24F3 T S L
		obse->RegisterCommand(		&kCommandInfo_NifClose											); //0x24F4 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetPath,						kRetnType_String); //0x24F5 T
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOriginalPath,				kRetnType_String); //0x24F6 T

		obse->RegisterCommand(		&kCommandInfo_NifGetNumExtraData								); //0x24F7 T
		obse->RegisterCommand(		&kCommandInfo_NifAddExtraData									); //0x24F8 T S L ?
		obse->RegisterCommand(		&kCommandInfo_NifDeleteNthExtraData								); //0x24F9 T S L ?

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataName,			kRetnType_String); //0x24FA T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthExtraDataName							); //0x24FB T S L
		obse->RegisterCommand(		&kCommandInfo_NifGetExtraDataIndexByName						); //0x24FC T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataType,			kRetnType_String); //0x24FE T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataString,			kRetnType_String); //0x24FD T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthExtraDataString							); //0x24FF T S L
		// ----------------------------------------- 0x2450 out of range ----------------------------------------- //

		obse->SetOpcodeBase(0x2510); // to 0x252F (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NifGetNumChildren									); //0x2510 T
		obse->RegisterCommand(		&kCommandInfo_NifDeleteNthChild									); //0x2511 T S L

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildName,				kRetnType_String); //0x2512 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildName								); //0x2513   S L
		obse->RegisterCommand(		&kCommandInfo_NifGetChildIndexByName							); //0x2514 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildType,				kRetnType_String); //0x2515 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalTransform,		kRetnType_Array	); //0x2516 T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTransform						); //0x2517 

		obse->SetOpcodeBase(0x2518);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalTranslation,	kRetnType_Array	); //0x2518 T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTranslation					); //0x2519 

		obse->SetOpcodeBase(0x251A);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalRotation,		kRetnType_Array	); //0x251A T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalRotation						); //0x251B 

		obse->SetOpcodeBase(0x251C);
		obse->RegisterCommand(		&kCommandInfo_NifGetNthChildLocalScale							); //0x251C T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalScale							); //0x251D T S L

		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTransformTEMP					); //0x251E T S L
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTranslationTEMP				); //0x251F T S L
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalRotationTEMP					); //0x2520 T S L

		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasMaterial							); //0x2521 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddMaterial							); //0x2522 
		obse->SetOpcodeBase(0x2523);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildMaterial,			kRetnType_String); //0x2523 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildMaterial							); //0x2524 T S L

		// ----------------------------------------- 0x2530 out of range ----------------------------------------- //

		obse->SetOpcodeBase(0x25C0); // to 25CF (inclusive)
		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasTexturingProp						); //0x25C0 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddTexturingProp						); //0x25C1 
		obse->SetOpcodeBase(0x25C2);
		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasBaseTexture							); //0x25C2 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddBaseTexture							); //0x25C3 
		obse->SetOpcodeBase(0x25C4);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildBaseTexture,		kRetnType_String); //0x25C4 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildBaseTexture							); //0x25C5 T S L

		// ----------------------------------------- 0x25D0 out of range ----------------------------------------- //

		// set up serialization callbacks when running in the runtime
		if(!obse->isEditor)
		{
			BSAlist = GetBSAfiles();
			_MESSAGE("List of BSA files: (excluding BSA files known to contain non-NIF data)");
			for ( BSAit = BSAlist.begin(); BSAit != BSAlist.end(); ++BSAit ) {
				_MESSAGE(("\t"+(*BSAit)).c_str());
			}
			_MESSAGE(("\t\t"+UIntToString(BSAlist.size())+" total.").c_str());

			_MESSAGE("\nRegistering String Interface.");
			strInterface->Register(strInterface);

			_MESSAGE("\nSetting Serialization callbacks.");
			serInterface->SetSaveCallback(g_pluginHandle, NifSE_SaveCallback);
			serInterface->SetLoadCallback(g_pluginHandle, NifSE_LoadCallback);
			serInterface->SetNewGameCallback(g_pluginHandle, NifSE_NewCallback);

			_MESSAGE("\nInitializing NifSE Hooks.");
			Hooks_NifSE_Init();
		}
		else {
			_MESSAGE("Listening to OBSE dispatches.");
			msgInterface->RegisterListener(g_pluginHandle, "OBSE", MessageHandler);

			_MESSAGE("\nDocumenting functions for CSE.");
			doc("NifGetAltGrip");
			doc("NifGetOffHand");
			doc("NifGetBackShield");
			doc("NifOpen");
			doc("NifClose");
			doc("NifGetPath");
			doc("NifGetOriginalPath");
			doc("NifGetNumExtraData");
			doc("NifAddExtraData");
			doc("NifDeleteNthExtraData");
			doc("NifGetNthExtraDataName");
			doc("NifSetNthExtraDataName");
			doc("NifGetExtraDataIndexByName");
			doc("NifGetNthExtraDataType");
			doc("NifGetNthExtraDataString");
			doc("NifSetNthExtraDataString");
			doc("NifGetNumChildren");
			doc("NifDeleteNthChild");
			doc("NifGetNthChildName");
			doc("NifSetNthChildName");
			doc("NifGetChildIndexByName");
			doc("NifGetNthChildType");
			doc("NifGetNthChildLocalTransform");
			doc("NifGetNthChildLocalTranslation");
			doc("NifGetNthChildLocalRotation");
			doc("NifGetNthChildLocalScale");
			doc("NifSetNthChildLocalScale");
			doc("NifSetNthChildLocalTransformTEMP");
			doc("NifSetNthChildLocalTranslationTEMP");
			doc("NifSetNthChildLocalRotationTEMP");
			doc("NifNthChildHasMaterial");
			doc("NifGetNthChildMaterial");
			doc("NifSetNthChildMaterial");
			doc("NifNthChildHasTexturingProp");
			doc("NifNthChildHasBaseTexture");
			doc("NifGetNthChildBaseTexture");
			doc("NifSetNthChildBaseTexture");
		}

		_MESSAGE("\n\tInitialization complete.\n\n");

		return true;
	}

};