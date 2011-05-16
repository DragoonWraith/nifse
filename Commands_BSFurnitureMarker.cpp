#include "Commands_BSFurnitureMarker.h"
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
				OBSEElement off[3] = { i->offset.x, i->offset.y, i->offset.z };
				offset = arrInterface->CreateArray( off, 3, scriptObj );

				OBSEElement vals[4] = { offset, i->orientation, i->positionRef1, i->positionRef2 };
				frnPos = arrInterface->CreateStringMap(keys, vals, 4, scriptObj);

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
		dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Getting the position refs of BSFurnitureMarker (nif " NIFIDSTR+").");
		try {
			GETBLOCK(BSFurnitureMarker, block);
			std::vector<Niflib::FurniturePosition> vec = std::vector<Niflib::FurniturePosition>();
			OBSEElement j = OBSEElement();
			OBSEElement k = OBSEElement();
			OBSEElement l = OBSEElement();
			Niflib::FurniturePosition furn = Niflib::FurniturePosition();
			string log = "[";
			for(UInt32 i = 0; i < arrInterface->GetArraySize(arr); ++i) {
				if ( !arrInterface->GetElement(arr, i, j) )
					throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not exist.").c_str());

				if ( arrInterface->GetElement(j.Array(), "orient", k) ) {
					furn.orientation = k.Number();
					log += UIntToString(furn.orientation)+"/";
				}
				else
					throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have an orientation.").c_str());
				if ( arrInterface->GetElement(j.Array(), "posRf1", k) ) {
					furn.positionRef1 = k.Number();
					log += UIntToString(furn.positionRef1)+"/";
				}
				else
					throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its first position reference.").c_str());
				if ( arrInterface->GetElement(j.Array(), "posRf2", k) ) {
					furn.positionRef2 = k.Number();
					log += UIntToString(furn.positionRef2)+"/";
				}
				else
					throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its second position reference.").c_str());
				if ( arrInterface->GetElement(j.Array(), "offset", k) ) {
					if ( arrInterface->GetElement(k.Array(), (double)0, l) ) {
						furn.offset.x = l.Number();
						log += FloatToString(furn.offset.x)+"/";
					}
					else
						throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its x offset.").c_str());
					if ( arrInterface->GetElement(k.Array(), (double)1, l) ) {
						furn.offset.y = l.Number();
						log += FloatToString(furn.offset.y)+"/";
					}
					else
						throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its y offset.").c_str());
					if ( arrInterface->GetElement(k.Array(), (double)2, l) ) {
						furn.offset.z = l.Number();
						log += FloatToString(furn.offset.z)+"/";
					}
					else
						throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its z offset.").c_str());
				}
				else
					throw std::exception(("FurniturePosition #"+UIntToString(i)+" does not have its offset.").c_str());
				vec.push_back(furn);
				log += "|";
			}
			block->SetFurniturePositions(vec);
			*result = 1;
			nifPtr->logChange(blockID, kNiflibType_BSFurnitureMarker, kNiBSFurnMrkAct_SetPositionRefs, log, true);
			dPrintAndLog("BSFurnitureMarkerSetPositionRefs", "Set position refs.\n");
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
	"Sets the position refs of the given BSFurnitureMarker.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

void NifFile::loadChBSFurnMkr(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::BSFurnitureMarkerRef furn = Niflib::DynamicCast<Niflib::BSFurnitureMarker>(nifList[block]);
		if ( furn ) {
			switch (act) {
				case kNiBSFurnMrkAct_SetPositionRefs:
					try {
						vector<string> vec = StringToVectorS(val);
						vector<string> poss;
						Niflib::FurniturePosition pos = Niflib::FurniturePosition();
						vector<Niflib::FurniturePosition> posv = vector<Niflib::FurniturePosition>();
						for ( vector<string>::iterator i = vec.begin(); i != vec.end(); ++i ) {
							poss = split(*i, '/');
							if ( poss.size() != 5 )
								throw std::exception("Position reference vector is mis-sized.");
							pos.orientation = StringToUInt(poss[0]);
							pos.positionRef1 = StringToUInt(poss[1]);
							pos.positionRef2 = StringToUInt(poss[2]);
							pos.offset.x = StringToFloat(poss[3]);
							pos.offset.y = StringToFloat(poss[4]);
							pos.offset.z = StringToFloat(poss[5]);
							posv.push_back(pos);
						}
						furn->SetFurniturePositions(posv);
						dPrintAndLog("NifLoad - BSFurnitureMarker","External texture change loaded.");
					}
					catch (std::exception e) {
						dPrintAndLog("NifLoad - BSFurnitureMarker","\n\n\t\tException \""+string(e.what())+"\" thrown; loaded nif will be incorrect!\n");
					}
					break;

				default:
					dPrintAndLog("NifLoad - BSFurnitureMarker","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - BSFurnitureMarker","\n\n\t\tIndicated block is not a BSFurnitureMarker! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - BSFurnitureMarker","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
