#include "Commands_NiObjectNET.h"

#include "obj/NiObject.h"
#include "obj/NiObjectNET.h"

#include "NiExtraData.h"

// returns the name of the specified ObjectNET of the NifFile
// associated with given nifID.
static bool Cmd_NiObjectNETGetName_Execute(COMMAND_ARGS) {
	*result = 0;
	string nameStr = " ";

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETGetName","Getting the name of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
					if ( objNET ) {
						nameStr = objNET->GetName();
						dPrintAndLog("NiObjectNETGetName","Returning \""+nameStr+"\".\n");
					}
					else
						dPrintAndLog("NiObjectNETGetName","Block is not ObjectNET.\n");
				}
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, nameStr.c_str());
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETGetName,
	NiObjNETGetName,
	"Returns the name of the NiObjectNET on the given Nif",
	0,
	kParams_TwoInts
);

// sets the name of the specified ExtraData in the
// NifFile associated with the given nifID.
static bool Cmd_NiObjectNETSetName_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuName[kMaxMessageLength] = " ";
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuName, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETSetName","Setting the name of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+" to \""+string(nuName)+"\".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
						if ( objNET ) {
							*result = 1;
							objNET->SetName(nuName);
							dPrintAndLog("NiObjectNETSetName","ExtraData name set successfully.\n");
							nifPtr->logChange(blockID, kNiflibType_NiObjectNET, kNiObjNETAct_SetName, nuName, true);
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETSetName,
	NiObjNETSetName,
	"Sets the name of the NiObjectNET to the passed string.",
	0,
	kParams_OneString_TwoInts
);

// returns the number of ExtraData in the NifFile associated
// with given nifID.
static bool Cmd_NiObjectNETGetNumExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumExtraData","Getting the number of ExtraData nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
					if ( objNET ) {
						*result = objNET->GetExtraData().size();
						dPrintAndLog("NifGetNumExtraData","Returning "+UIntToString(*result)+".\n");
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETGetNumExtraData,
	NiObjNETGetNumED,
	"Returns the number of ExtraData nodes in the given Nif",
	0,
	kParams_OneInt_OneOptionalInt
);

// returns an array of ExtraData in the NifFile associated
// with given nifID.
static bool Cmd_NiObjectNETGetExtraData_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETGetExtraData","Getting ExtraData nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
					if ( objNET ) {
						vector<OBSEElement> edvec = vector<OBSEElement>();
						list<Niflib::NiExtraDataRef> eds = objNET->GetExtraData();
						for ( list<Niflib::NiExtraDataRef>::iterator i = eds.begin(); i != eds.end(); ++i )
							edvec.push_back((*i)->internal_block_number);
						arr = ArrayFromStdVector(edvec, scriptObj);
					}
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiObjectNETGetExtraData","Returning node's extra data.\n");
	else
		dPrintAndLog("NiObjectNETGetExtraData","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETGetExtraData,
	NiObjNETGetED,
	"Returns an array of ExtraData nodes to the given node",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiObjectNETGetExtraDataByName_Execute(COMMAND_ARGS) {
	*result = -1;

	char edName[kMaxMessageLength];
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edName, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETGetExtraDataByName","Getting the index of ExtraData \""+string(edName)+"\" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
					if ( objNET ) {
						list<Niflib::NiExtraDataRef> eds = objNET->GetExtraData();
						for ( list<Niflib::NiExtraDataRef>::iterator i = eds.begin(); i != eds.end(); ++i )
							if ( (*i)->GetName().compare(edName) == 0 )
								*result = (*i)->internal_block_number;
						if ( *result == -1 )
							dPrintAndLog("NiObjectNETGetExtraDataByName","ExtraData not found.\n");
						else
							dPrintAndLog("NiObjectNETGetExtraDataByName","ExtraData found.\n");
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETGetExtraDataByName,
	NiObjNETGetEDByName,
	"Returns the index of the named ExtraData of the specified Nif.",
	0,
	kParams_OneString_OneInt_OneOptionalInt
);

static bool Cmd_NiObjectNETAddExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	char name[kMaxMessageLength];
	UInt32 typeID = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &name, &typeID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETAddExtraData","Adding ExtraData \""+string(name)+"\" of type #"+UIntToString(typeID)+" to nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
						if ( objNET ) {
							try {
								*result = Util_NiObjectNETAddExtraData(nifPtr, objNET, typeID, name);
								dPrintAndLog("NiObjectNETAddExtraData","Addition successful.\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiObjectNETAddExtraData","Addition failed; exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiObjectNETAddExtraData","Nif node not an extra-data-supporting type.\n");
					}
					else
						dPrintAndLog("NiObjectNETAddExtraData","Nif node index out of bounds.\n");
				}
				else
					dPrintAndLog("NiObjectNETAddExtraData","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiObjectNETAddExtraData","Nif not found.\n");
		}
		else
			dPrintAndLog("NiObjectNETAddExtraData","Nif not found.\n");
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETAddExtraData,
	NiObjNETAddED,
	"Adds an ExtraData node of the given type to the given Nif",
	0,
	kParams_TwoStrings_OneInt_OneOptionalInt
);

static bool Cmd_NiObjectNETDeleteExtraData_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	int edID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &edID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectNETDeleteExtraData","Deleting ExtraData with Block #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifPtr->nifList[blockID]);
						if ( objNET ) {
							if ( edID < nifPtr->nifList.size() ) {
								Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
								if ( ed ) {
									objNET->RemoveExtraData(ed);
									nifPtr->nifList.erase(nifPtr->nifList.begin()+edID);
									*result = 1;
									dPrintAndLog("NiObjectNETDeleteExtraData","ExtraData deleted.");
									nifPtr->logChange(blockID, kNiflibType_NiObjectNET, kNiObjNETAct_DelED, UIntToString(edID));
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectNETDeleteExtraData,
	NiObjNETDelED,
	"Deletes the Nth block of the given Nif if it is an ExtraData",
	0,
	kParams_TwoInts_OneOptionalInt
);

UInt32 Util_NiObjectNETAddExtraData(NifFile* nifPtr, Niflib::NiObjectNETRef objNET, UInt32 typeID, const string& name) {
	Niflib::NiExtraDataRef nuED = NULL;
	switch (typeID) {
		case kNiflibType_NiExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiExtraData::Create());
			break;

		case kNiflibType_BSBound:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::BSBound::Create());
			break;

		case kNiflibType_BSFurnitureMarker:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::BSFurnitureMarker::Create());
			break;

		case kNiflibType_NiBinaryExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiBinaryExtraData::Create());
			break;

		case kNiflibType_NiBinaryVoxelData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiBinaryVoxelData::Create());
			break;

		case kNiflibType_NiBooleanExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiBooleanExtraData::Create());
			break;

		case kNiflibType_NiColorExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiColorExtraData::Create());
			break;

		case kNiflibType_NiFloatExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiFloatExtraData::Create());
			break;

		case kNiflibType_NiFloatsExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiFloatsExtraData::Create());
			break;

		case kNiflibType_NiIntegerExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiIntegerExtraData::Create());
			break;

		case kNiflibType_BSXFlags:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::BSXFlags::Create());
			break;

		case kNiflibType_NiIntegersExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiIntegersExtraData::Create());
			break;

		case kNiflibType_NiStringExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiStringExtraData::Create());
			break;

		case kNiflibType_NiStringsExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiStringsExtraData::Create());
			break;

		case kNiflibType_NiTextKeyExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiTextKeyExtraData::Create());
			break;

		case kNiflibType_NiVectorExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiVectorExtraData::Create());
			break;

		case kNiflibType_NiVertWeightsExtraData:
			nuED = Niflib::StaticCast<Niflib::NiExtraData>(Niflib::NiVertWeightsExtraData::Create());
			break;

		default:
			throw std::exception("Extra data type unknown.");
	}

	if ( nuED ) {
		nuED->SetName(name);
		nuED->internal_block_number = nifPtr->nifList.size();
		objNET->AddExtraData(nuED, nifPtr->nifVersion);
		nifPtr->nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(nuED));
		nifPtr->logChange(objNET->internal_block_number, kNiflibType_NiObjectNET, kNiObjNETAct_AddED, name);
		return nuED->internal_block_number;
	}
	else
		throw std::exception("New NiExtraData not created.");
}

void NifFile::loadChNiObjectNET(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiObjectNETRef objNET = Niflib::DynamicCast<Niflib::NiObjectNET>(nifList[block]);
		if ( objNET ) {
			switch (act) {
				case kNiObjNETAct_SetName:
					objNET->SetName(val);
					dPrintAndLog("NifLoad - NiObjectNET","NiObjectNET name change loaded; name set to \""+val+"\".");
					break;

				case kNiObjNETAct_AddED:
					try {
						string::size_type i = val.find(logValType);
						UInt32 edType = StringToUInt(val.substr(0, i));
						string edName = val.substr(i+1);
						Util_NiObjectNETAddExtraData(this, objNET, edType, edName);
						dPrintAndLog("NifLoad - NiObjectNET","NiExtraData \""+edName+"\" added to nif.");
					}
					catch (std::exception e) {
						dPrintAndLog("NifLoad - NiObjectNET","\n\n\t\tNiExtraData node not added! Exception \""+string(e.what())+"\" thrown. Loaded nif will be incorrect!\n");
					}
					break;

				case kNiObjNETAct_DelED:
					for ( list<Niflib::NiExtraDataRef>::iterator i = objNET->GetExtraData().begin(); i != objNET->GetExtraData().end(); ++i )
						if ( *i == Niflib::DynamicCast<Niflib::NiExtraData>(nifList[StringToUInt(val)]) )
							objNET->RemoveExtraData(*i);
					dPrintAndLog("NifLoad - NiObjectNET","ExtraData (block #"+val+") deleted.");
					break;

				case kNiObjNETAct_AddCtlr:
				case kNiObjNETAct_DelCtlr:
					dPrintAndLog("NifLoad - NiObjectNET","\n\n\t\tThis version of NifSE does not support these changes! Loaded nif will be incorrect!\n");

				default:
					dPrintAndLog("NifLoad - NiObjectNET","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiObjectNET","\n\n\t\tIndicated block is not a NiObjectNET! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiObjectNET","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
