#include "Commands_NiNode.h"

#include "obj/NiObject.h"
#include "obj/NiObjectNET.h"
#include "obj/NiAVObject.h"
#include "obj/NiNode.h"

// returns the number of Children in the NifFile associated
// with given nifID.
static bool Cmd_NiNodeGetNumChildren_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeGetNumChildren","Getting number of Children nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifPtr->nifList[blockID]);
					if ( node ) {
						*result = node->GetChildren().size();
						dPrintAndLog("NiNodeGetNumChildren","Returning "+UIntToString(*result)+" Children nodes.\n");
					}
					else
						dPrintAndLog("NiNodeGetNumChildren","Not NiNode.\n");
				}
				else
					dPrintAndLog("NiNodeGetNumChildren","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiNodeGetNumChildren","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiNodeGetNumChildren","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiNodeGetNumChildren","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeGetNumChildren,
	NiNodeGetNumCh,
	"Returns the number of Children nodes in the given Nif",
	0,
	kParams_OneInt_OneOptionalInt
);

// returns an array of Children in the NifFile associated
// with given nifID.
static bool Cmd_NiNodeGetChildren_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeGetChildren","Getting Children nodes to nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifPtr->nifList[blockID]);
					if ( node ) {
						vector<OBSEElement> chvec = vector<OBSEElement>();
						vector<Niflib::NiAVObjectRef> chs = node->GetChildren();
						for ( vector<Niflib::NiAVObjectRef>::iterator i = chs.begin(); i != chs.end(); ++i )
							chvec.push_back((*i)->internal_block_number);
						arr = ArrayFromStdVector(chvec, scriptObj);
					}
					else
						dPrintAndLog("NiNodeGetChildren","Not NiNode.");
				}
				else
					dPrintAndLog("NiNodeGetChildren","Block index out of range.");
			}
			else
				dPrintAndLog("NiNodeGetChildren","Nif root bad.");
		}
		else
			dPrintAndLog("NiNodeGetChildren","Could not find Nif.");
	}
	else
		dPrintAndLog("NiNodeGetChildren","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiNodeGetChildren","Returning node's children.\n");
	else
		dPrintAndLog("NiNodeGetChildren","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeGetChildren,
	NiNodeGetCh,
	"Returns an array of Children nodes to the given node",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiNodeGetChildByName_Execute(COMMAND_ARGS) {
	*result = -1;

	char chName[kMaxMessageLength];
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chName, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeGetChildByName","Getting the index of Child \""+string(chName)+"\" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifPtr->nifList[blockID]);
					if ( node ) {
						vector<Niflib::NiAVObjectRef> chs = node->GetChildren();
						for ( vector<Niflib::NiAVObjectRef>::iterator i = chs.begin(); i != chs.end(); ++i ) {
							if ( (*i)->GetName().compare(chName) == 0 ) {
								*result = (*i)->internal_block_number;
								break;
							}
						}
						if ( *result == -1 )
							dPrintAndLog("NiNodeGetChildByName","Child not found.\n");
						else
							dPrintAndLog("NiNodeGetChildByName","Child found; returning "+UIntToString(*result)+".\n");
					}
					else
						dPrintAndLog("NiNodeGetChildByName","Not NiNode.\n");
				}
				else
					dPrintAndLog("NiNodeGetChildByName","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiNodeGetChildByName","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiNodeGetChildByName","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiNodeGetChildByName","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeGetChildByName,
	NiNodeGetChByName,
	"Returns the index of the named Child of the specified Nif.",
	0,
	kParams_OneString_OneInt_OneOptionalInt
);

static bool Cmd_NiNodeDeleteChild_Execute(COMMAND_ARGS) {
	*result = -1;

	int chID = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeDeleteChild","Deleting Child (block #"+UIntToString(chID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifPtr->nifList[blockID]);
						if ( node ) {
							vector<Niflib::NiAVObjectRef> chs = node->GetChildren();
							for ( vector<Niflib::NiAVObjectRef>::iterator i = chs.begin(); i != chs.end(); ++i ) {
								if ( (*i)->internal_block_number == chID ) {
									node->RemoveChild(*i);
									nifPtr->logChange(blockID, kNiflibType_NiNode, kNiNodeAct_DelChild, UIntToString(chID));
									*result = 1;
									break;
								}
							}
							if ( *result )
								dPrintAndLog("NiNodeDeleteChild","Child deleted.\n");
							else
								dPrintAndLog("NiNodeDeleteChild","Child not deleted: Child not found.\n");
						}
						else
							dPrintAndLog("NiNodeDeleteChild","Not a NiNode.\n");
					}
					else
						dPrintAndLog("NiNodeDeleteChild","Nif block index out of bounds.\n");
				}
				else
					dPrintAndLog("NiNodeDeleteChild","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiNodeDeleteChild","Nif not found.\n");
		}
		else
			dPrintAndLog("NiNodeDeleteChild","Nif not found.\n");
	}
	else
		dPrintAndLog("NiNodeDeleteChild","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeDeleteChild,
	NiNodeDelChild,
	"Deletes the NiNode's Child of the specified Nif.",
	0,
	kParams_TwoInts_OneOptionalInt
);

void NifFile::loadChNiNode(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifList[block]);
		if ( node ) {
			switch (act) {
				case kNiNodeAct_DelChild:
					{
						UInt32 chID = StringToUInt(val);
						if ( chID < nifList.size() ) {
							vector<Niflib::NiAVObjectRef> chs = node->GetChildren();
							for ( vector<Niflib::NiAVObjectRef>::iterator i = chs.begin(); i != chs.end(); ++i )
								if ( *i == Niflib::DynamicCast<Niflib::NiAVObject>(nifList[StringToUInt(val)]) )
									node->RemoveChild(*i);
							dPrintAndLog("NifLoad - NiNode","Child (block #"+val+") deleted.");
						}
						else
							dPrintAndLog("NifLoad - NiNode","\n\n\t\tBlock #"+val+" out of range! Loaded nif will be incorrect!\n");
					}
					break;

				case kNiNodeAct_AddChild:
				case kNiNodeAct_AddEffect:
				case kNiNodeAct_DelEffect:
				case kNiNodeAct_AddSkin:
				case kNiNodeAct_DelSkin:
				case kNiNodeAct_SetSkinFlag:
					dPrintAndLog("NifLoad - NiNode","\n\n\t\tThis version of NifSE does not support these changes! Loaded nif will be incorrect!\n");

				default:
					dPrintAndLog("NifLoad - NiNode","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiNode","\n\n\t\tIndicated block is not a NiNode! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiNode","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
