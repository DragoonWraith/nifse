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

static bool Cmd_NiNodeAddChild_Execute(COMMAND_ARGS) {
	*result = 0;

	char name[kMaxMessageLength];
	UInt32 typeID = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &name, &typeID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeAddChild","Adding child \""+string(name)+"\" of type #"+UIntToString(typeID)+" to nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifPtr->nifList[blockID]);
						if ( node ) {
							try {
								*result = Util_NiNodeAddChild(nifPtr, node, typeID, name);
								nifPtr->logChange(node->internal_block_number,kNiflibType_NiNode,kNiNodeAct_AddChild,UIntToString(typeID)+logValType+name);
								dPrintAndLog("NiNodeAddChild","Addition successful; child is block #"+UIntToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiNodeAddChild","Addition failed; exception \""+string(e.what())+"\" thrown.");
							}
						}
						else
							dPrintAndLog("NiNodeAddChild","Nif node not a child-supporting type.\n");
					}
					else
						dPrintAndLog("NiNodeAddChild","Nif node index out of bounds.\n");
				}
				else
					dPrintAndLog("NiNodeAddChild","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiNodeAddChild","Nif not found.\n");
		}
		else
			dPrintAndLog("NiNodeAddChild","Nif not found.\n");
	}
	else
		dPrintAndLog("NiNodeAddChild","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeAddChild,
	NiNodeAddCh,
	"Adds an AVObject block of the given type to the given Nif",
	0,
	kParams_OneString_TwoInts_OneOptionalInt
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

static bool Cmd_NiNodeCopyChild_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifIDfrom = -1;
	int blockIDfrom = -1;
	int nifIDto = -1;
	UInt32 blockIDto = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifIDfrom, &blockIDfrom, &nifIDto, &blockIDto)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiNodeCopyChild","Copying Node (Nif #"+UIntToString(modID)+"-"+UIntToString(nifIDfrom)+" block #"+UIntToString(blockIDfrom)+" as a child of Node (Nif #"+UIntToString(modID)+"-"+UIntToString(nifIDto)+" block #"+UIntToString(blockIDto)+".");
		NifFile* nifFromPtr = NULL;
		NifFile* nifToPtr = NULL;
		if ( NifFile::getRegNif(modID, nifIDfrom, nifFromPtr) && NifFile::getRegNif(modID, nifIDto, nifToPtr) ) {
			if ( nifFromPtr->root && nifToPtr->root ) {
				if ( nifToPtr->editable ) {
					if ( blockIDfrom < nifFromPtr->nifList.size() && blockIDto < nifToPtr->nifList.size() ) {
						Niflib::NiObjectRef child = nifFromPtr->nifList[blockIDfrom];
						Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifToPtr->nifList[blockIDto]);
						if ( child->GetType().IsDerivedType(Niflib::NiAVObject::TYPE) && node ) {
							std::stringstream* nifStream = new std::stringstream(std::ios::binary|std::ios::in|std::ios::out);
							Niflib::WriteNifTree(*nifStream, child, *(nifFromPtr->headerInfo));
							vector<Niflib::NiObjectRef> copiedBranch = Niflib::ReadNifList(*nifStream, nifFromPtr->headerInfo);
							if ( !(copiedBranch.empty()) ) {
								Niflib::NiAVObjectRef childCopy = Niflib::DynamicCast<Niflib::NiAVObject>(copiedBranch[0]);
								if ( childCopy ) {
									while ( childCopy->GetParent() ) {
										childCopy = childCopy->GetParent();
									}
									for ( vector<Niflib::NiObjectRef>::iterator i = copiedBranch.begin(); i != copiedBranch.end(); ++i ) {
										nifToPtr->nifList.push_back(*i);
										(*i)->internal_block_number = nifToPtr->nifList.size();
									}
									node->AddChild(childCopy);
									*result = 1;
									dPrintAndLog("NiNodeCopyChild","Branch successfully copied.\n");
								}
								else
									dPrintAndLog("NiNodeCopyChild","Could not find copied child.\n");
							}
							else
								dPrintAndLog("NiNodeCopyChild","Copied branch is empty.\n");
						}
						else
							dPrintAndLog("NiNodeCopyChild","Not a NiNode.\n");
					}
					else
						dPrintAndLog("NiNodeCopyChild","Nif block index out of bounds.\n");
				}
				else
					dPrintAndLog("NiNodeCopyChild","Nif to copy to not editable.\n");
			}
			else
				dPrintAndLog("NiNodeCopyChild","Nif not found.\n");
		}
		else
			dPrintAndLog("NiNodeCopyChild","Nif not found.\n");
	}
	else
		dPrintAndLog("NiNodeCopyChild","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiNodeCopyChild,
	NiNodeCopyCh,
	"Copies the NiNode of the specified Nif as a child of the NiNode of the other Nif.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

UInt32 Util_NiNodeAddChild(NifFile* nifPtr, Niflib::NiNodeRef node, UInt32 typeID, const string& name) {
	Niflib::NiAVObjectRef nuAVObj = Niflib::DynamicCast<Niflib::NiAVObject>(getNiflibType(typeID)->Create());

	if ( nuAVObj ) {
		nuAVObj->SetName(name);
		nuAVObj->internal_block_number = nifPtr->nifList.size();
		node->AddChild(nuAVObj);
		nifPtr->nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(nuAVObj));
		return nuAVObj->internal_block_number;
	}
	else
		throw std::exception("Passed type is not derived from NiAVobject.");
}

void NifFile::loadChNiNode(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiNodeRef node = Niflib::DynamicCast<Niflib::NiNode>(nifList[block]);
		if ( node ) {
			switch (act) {
				case kNiNodeAct_AddChild:
					try {
						string::size_type i = val.find(logValType);
						UInt32 avType = StringToUInt(val.substr(0, i));
						string avName = val.substr(i+1);
						Util_NiNodeAddChild(this, node, avType, avName);
						dPrintAndLog("NifLoad - NiNode","NiAVObject \""+avName+"\" added to nif.");
					}
					catch (std::exception e) {
						dPrintAndLog("NifLoad - NiNode","\n\n\t\tNiAVObject not added! Exception \""+string(e.what())+"\" thrown. Loaded nif will be incorrect!\n");
					}
					break;

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
