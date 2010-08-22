#include "Commands_NiObject.h"

#include "obj/NiObject.h"

static bool Cmd_NiObjectGetType_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectGetTypeName","Getting the type of object #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectRef obj = nifPtr->nifList[blockID];
					if ( obj ) {
						*result = getNiflibTypeIndex(obj->GetType());
						dPrintAndLog("NiObjectGetTypeName","Returning "+UIntToString(*result)+".\n");
					}
				}
				else
					dPrintAndLog("NiObjectGetTypeName","Object index out of range.\n");
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectGetType,
	NiObjGetType,
	"Returns the type of the Nth block of the given Nif",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiObjectGetTypeName_Execute(COMMAND_ARGS) {
	*result = 0;
	string typeStr = " ";

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectGetTypeName","Getting the type name of object #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectRef obj = nifPtr->nifList[blockID];
					if ( obj ) {
						typeStr = obj->GetType().GetTypeName();
						dPrintAndLog("NiObjectGetTypeName","Returning \""+typeStr+"\".\n");
					}
				}
				else
					dPrintAndLog("NiObjectGetTypeName","Object index out of range.\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, typeStr.c_str());
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectGetTypeName,
	NiObjGetTypeName,
	"Returns the name of the type of the Nth block of the given Nif",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiObjectTypeDerivesFrom_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifType = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifType, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectTypeDerivesFrom","Getting whether the type of object #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" is derived from type #"+UIntToString(nifType)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectRef obj = nifPtr->nifList[blockID];
					if ( obj ) {
						try {
							Niflib::Type ancestor = getNiflibType(nifType);
							dPrintAndLog("NiObjectTypeDerivesFrom","Testing whether \""+obj->GetType().GetTypeName()+"\" derives from \""+ancestor.GetTypeName()+"\".");
							*result = ancestor.IsDerivedType(obj->GetType());
							dPrintAndLog("NiObjectTypeDerivesFrom","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
						}
						catch (std::exception e) {
							dPrintAndLog("NiObjectTypeDerivesFrom","Niflib type exception: \""+string(e.what())+"\".\n");
						}
					}
				}
				else
					dPrintAndLog("NiObjectTypeDerivesFrom","Object index out of range.\n");
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectTypeDerivesFrom,
	NiObjIsDeriv,
	"Returns the type of the Nth block of the given Nif",
	0,
	kParams_TwoInts_OneOptionalInt
);