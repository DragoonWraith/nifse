#include "Commands_NiObject.h"

#include "obj/NiObject.h"

static bool Cmd_NiObjectGetType_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiObjectGetType","Getting the type of object #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiObjectRef obj = nifPtr->nifList[blockID];
					if ( obj ) {
						try {
							*result = getNiflibTypeIndex(obj->GetType());
							dPrintAndLog("NiObjectGetType","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiObjectGetType","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiObjectGetType","Bad object.\n");
				}
				else
					dPrintAndLog("NiObjectGetType","Object index out of range.\n");
			}
			else
				dPrintAndLog("NiObjectGetType","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiObjectGetType","Nif not found.\n");
	}
	else
		dPrintAndLog("NiObjectGetType","Error extracting arguments.\n");

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
						try {
							typeStr = obj->GetType().GetTypeName();
							dPrintAndLog("NiObjectGetTypeName","Returning \""+typeStr+"\".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiObjectGetTypeName","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiObjectGetTypeName","Bad object.\n");
				}
				else
					dPrintAndLog("NiObjectGetTypeName","Object index out of range.\n");
			}
			else
				dPrintAndLog("NiObjectGetTypeName","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiObjectGetTypeName","Nif not found.\n");
	}
	else
		dPrintAndLog("NiObjectGetTypeName","Error extracting arguments.\n");

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
							const Niflib::Type* ancestor = getNiflibType(nifType);
							dPrintAndLog("NiObjectTypeDerivesFrom","Testing whether \""+obj->GetType().GetTypeName()+"\" derives from \""+ancestor->GetTypeName()+"\".");
							bool isDeriv = obj->GetType().IsDerivedType(*ancestor);
							*result = (isDeriv?1:0);
							dPrintAndLog("NiObjectTypeDerivesFrom","Returning "+string(isDeriv?"TRUE":"FALSE")+".\n");
						}
						catch (std::exception e) {
							dPrintAndLog("NiObjectTypeDerivesFrom","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiObjectTypeDerivesFrom","Bad object.\n");
				}
				else
					dPrintAndLog("NiObjectTypeDerivesFrom","Object index out of range.\n");
			}
			else
				dPrintAndLog("NiObjectTypeDerivesFrom","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiObjectTypeDerivesFrom","Nif not found.\n");
	}
	else
		dPrintAndLog("NiObjectTypeDerivesFrom","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiObjectTypeDerivesFrom,
	NiObjIsDeriv,
	"Returns the type of the Nth block of the given Nif",
	0,
	kParams_TwoInts_OneOptionalInt
);
