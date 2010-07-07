#include "Commands_ExtraData.h"

// returns the number of ExtraData in the NifFile associated
// with given nifID.
static bool Cmd_NifGetNumExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumExtraData","Getting number of ExtraData nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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
		NifFile::getRegNif(modID, nifID, nifPtr);
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