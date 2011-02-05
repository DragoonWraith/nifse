#include "Commands_NiStencilProperty.h"
#include "obj/BSFurnitureMarker.h"

#include "Command_Macros.h"

static bool Cmd_BSFurnitureMarkerGetPositionRefs_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("BSFurnitureMarkerGetPositionRefs", "Getting the position refs of BSFurnitureMarker (nif " NIFIDSTR+").");
		try {
			GETBLOCK(BSFurnitureMarker, block);
			std::vector<Niflib::FurniturePosition> frnVec = block->GetFurniturePositions();
			const char* keys[4] = { "offset", "orient", "posRf1", "posRf2" };
			OBSEArray* frnPos = NULL;
			OBSEArray* offset = NULL;
			for ( std::vector<Niflib::FurniturePosition>::iterator i = frnVec.begin(); i != frnVec.end(); ++i ) {
				if ( offset ) {
					arrInterface->SetElement(offset, (double)0, i->offset.x);
					arrInterface->SetElement(offset, (double)1, i->offset.y);
					arrInterface->SetElement(offset, (double)2, i->offset.z);
				}
				else {
					OBSEElement off[3] = { i->offset.x, i->offset.y, i->offset.z };
					offset = arrInterface->CreateArray( off, 3, scriptObj );
				}

				if ( frnPos ) {
					arrInterface->SetElement(frnPos, "offset", offset);
					arrInterface->SetElement(frnPos, "orient", i->orientation);
					arrInterface->SetElement(frnPos, "posRf1", i->positionRef1);
					arrInterface->SetElement(frnPos, "posRf2", i->positionRef2);
				}
				else {
					OBSEElement vals[4] = { offset, i->orientation, i->positionRef1, i->positionRef2 };
					frnPos = arrInterface->CreateStringMap(keys, vals, 4, scriptObj);
				}

				if ( arr )
					arrInterface->AppendElement(arr, frnPos);
				else {
					OBSEElement frn = frnPos;
					arr = arrInterface->CreateArray(&frn, 1, scriptObj);
				}
			}
			dPrintAndLog("BSFurnitureMarkerGetPositionRefs", "Returning an array of furniture positions.");
		} catch (std::exception e) {
			*result = 0;
			dPrintAndLog("BSFurnitureMarkerGetPositionRefs", "Exception \""+string(e.what())+"\" thrown.");
		}
	} else
		dPrintAndLog("BSFurnitureMarkerGetPositionRefs", "Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("BSFurnitureMarkerGetPositionRefs","Returning block's position refs.\n");
	else
		dPrintAndLog("BSFurnitureMarkerGetPositionRefs","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	BSFurnitureMarkerGetPositionRefs,
	BSFurnMrkGetPosRefs,
	"Gets the position refs of the given BSFurnitureMarker.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_BSFurnitureMarkerSetPositionRefs_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Getting the "position refs" of ""BSFurnitureMarker"" (nif " NIFIDSTR+").");
		try {
			GETBLOCK(BSFurnitureMarker, block);
			*result = 1;
			nifPtr->logChange(blockID, kNiflibType_BSFurnitureMarker, act, VectorToString(, true);
			dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Set "position refs".\n");
		} catch (std::exception e) {
			*result = 0;
			dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Exception \""+string(e.what())+"\" thrown.\n");
		}
	} else
		dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Error extracting arguments.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	BSFurnitureMarkerSetPositionRefs,
	BSFurnMrkSetPosRefs,
	"Sets the "position refs" of the given ""BSFurnitureMarker"".",
	0,
	kParams_OneArray_OneInt_OneOptionalInt;
);
