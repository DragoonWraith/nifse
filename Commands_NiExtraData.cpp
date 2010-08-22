#include "Commands_NiExtraData.h"

#include "NiExtraData.h"

// returns the number stored in the specified ExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataGetNumber_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataGetString","Getting string value of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						UInt32 edType = getNiflibTypeIndex(ed->TYPE);
						switch (edType) {
							case kNiflibType_NiBooleanExtraData:
								*result = Niflib::DynamicCast<Niflib::NiBooleanExtraData>(ed)->GetData();
								dPrintAndLog("NiExtraDataGetNumber","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
								break;

							case kNiflibType_NiFloatExtraData:
								*result = Niflib::DynamicCast<Niflib::NiFloatExtraData>(ed)->GetData();
								dPrintAndLog("NiExtraDataGetNumber","Returning "+FloatToString(*result)+".\n");
								break;

							case kNiflibType_NiIntegerExtraData:
								*result = Niflib::DynamicCast<Niflib::NiIntegerExtraData>(ed)->GetData();
								dPrintAndLog("NiExtraDataGetNumber","Returning "+UIntToString(*result)+".\n");
								break;

							case kNiflibType_BSXFlags:
								*result = Niflib::DynamicCast<Niflib::BSXFlags>(ed)->GetData();
								dPrintAndLog("NiExtraDataGetNumber","Returning "+UIntToString(*result)+".\n");
								break;

							default:
								dPrintAndLog("NiExtraDataSetNumber","ExtraData is not a numerical type!\n");
								break;
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataGetNumber,
	NiEDGetNum,
	"If the Nth block of the given Nif is a numerical type, gets the value.",
	0,
	kParams_OneInt_OneOptionalInt
);

// sets the number stored in the specified ExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataSetNumber_Execute(COMMAND_ARGS) {
	*result = 0;

	double newVal = 0;
	int nifID = -1;
	UInt32 blockID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &newVal, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataSetNumber","Setting the numerical value of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to "+FloatToString(newVal)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
						if ( ed ) {
							UInt32 edType = getNiflibTypeIndex(ed->TYPE);
							switch (edType) {
								case kNiflibType_NiBooleanExtraData:
									Niflib::DynamicCast<Niflib::NiBooleanExtraData>(ed)->SetData(newVal!=0);
									*result = 1;
									dPrintAndLog("NiExtraDataSetNumber","ExtraData value set successfully.\n");
									nifPtr->logChange(blockID, kNiflibType_NiBooleanExtraData, kNiEDAct_SetNum, string(newVal!=0?"1":"0"), true);
									break;

								case kNiflibType_NiFloatExtraData:
									Niflib::DynamicCast<Niflib::NiFloatExtraData>(ed)->SetData(newVal);
									*result = 1;
									dPrintAndLog("NiExtraDataSetNumber","ExtraData value set successfully.\n");
									nifPtr->logChange(blockID, kNiflibType_NiFloatExtraData, kNiEDAct_SetNum, FloatToString(newVal), true);
									break;

								case kNiflibType_NiIntegerExtraData:
									Niflib::DynamicCast<Niflib::NiIntegerExtraData>(ed)->SetData(newVal);
									*result = 1;
									dPrintAndLog("NiExtraDataSetNumber","ExtraData value set successfully.\n");
									nifPtr->logChange(blockID, kNiflibType_NiIntegerExtraData, kNiEDAct_SetNum, SIntToString(newVal), true);
									break;

								case kNiflibType_BSXFlags:
									Niflib::DynamicCast<Niflib::BSXFlags>(ed)->SetData(newVal);
									*result = 1;
									dPrintAndLog("NiExtraDataSetNumber","ExtraData value set successfully.\n");
									nifPtr->logChange(blockID, kNiflibType_BSXFlags, kNiEDAct_SetNum, SIntToString(newVal), true);
									break;

								default:
									dPrintAndLog("NiExtraDataSetNumber","ExtraData is not a numerical type!\n");
									break;
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
	NiExtraDataSetNumber,
	NiEDSetNum,
	"If the Nth ExtraData of the given Nif is a numerical type, sets the value of the ExtraData to the passed number.",
	0,
	kParams_OneFloat_OneInt_OneOptionalInt
);

// returns the string stored in the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataGetString_Execute(COMMAND_ARGS) {
	*result = 0;
	string edStr = " ";

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataGetString","Getting string value of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiStringExtraDataRef ed = Niflib::DynamicCast<Niflib::NiStringExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						edStr = ed->GetData();
						dPrintAndLog("NiExtraDataGetString","Returning \""+edStr+"\".\n");
					}
				}
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, edStr.c_str());
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataGetString,
	NiEDGetStr,
	"If the Nth block of the given Nif is a NiStringExtraData, gets the value of the string.",
	0,
	kParams_OneInt_OneOptionalInt
);

// sets the string stored in the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataSetString_Execute(COMMAND_ARGS) {
	*result = 0;

	char newStr[kMaxMessageLength] = " ";
	int nifID = -1;
	UInt32 blockID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &newStr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthExtraDataString","Setting the string value of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(newStr)+"\".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiStringExtraDataRef ed = Niflib::DynamicCast<Niflib::NiStringExtraData>(nifPtr->nifList[blockID]);
						if ( ed ) {
							*result = 1;
							ed->SetData(newStr);
							dPrintAndLog("NifSetNthExtraDataString","ExtraData value set successfully.\n");
							nifPtr->logChange(blockID, kNiflibType_NiStringExtraData, kNiEDAct_SetStr, newStr, true);
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataSetString,
	NiEDSetStr,
	"If the Nth ExtraData of the given Nif is a String, sets the value of the ExtraData to the passed string.",
	0,
	kParams_OneString_OneInt_OneOptionalInt
);

// returns the array stored in the specified ExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataGetArray_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataGetArray","Getting array of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiStringExtraDataRef ed = Niflib::DynamicCast<Niflib::NiStringExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						UInt32 edType = getNiflibTypeIndex(ed->TYPE);
						vector<Niflib::byte> binData;
						Niflib::Color4 colorData;
						vector<float> floatData;
						vector<unsigned int> intData;
						vector<string> strData;
						Niflib::Vector3 vecData;

						vector<OBSEElement> ovec;
						map<string,OBSEElement> omap;
						switch (edType) {
							case kNiflibType_NiBinaryExtraData:
								binData = Niflib::DynamicCast<Niflib::NiBinaryExtraData>(ed)->GetData();
								for ( vector<Niflib::byte>::iterator i = binData.begin(); i != binData.end(); ++i )
									ovec.push_back(*i);
								break;

							case kNiflibType_NiColorExtraData:
								colorData = Niflib::DynamicCast<Niflib::NiColorExtraData>(ed)->GetData();
								omap[string("r")] = colorData.r;
								omap[string("g")] = colorData.g;
								omap[string("b")] = colorData.b;
								omap[string("a")] = colorData.a;
								break;

							case kNiflibType_NiFloatsExtraData:
							case kNiflibType_NiVertWeightsExtraData:
								floatData = Niflib::DynamicCast<Niflib::NiFloatsExtraData>(ed)->GetData();
								for ( vector<float>::iterator i = floatData.begin(); i != floatData.end(); ++i )
									ovec.push_back(*i);
								break;

							case kNiflibType_NiIntegersExtraData:
								intData = Niflib::DynamicCast<Niflib::NiIntegersExtraData>(ed)->GetData();
								for ( vector<unsigned int>::iterator i = intData.begin(); i != intData.end(); ++i )
									ovec.push_back(*i);
								break;

							case kNiflibType_NiStringsExtraData:
								strData = Niflib::DynamicCast<Niflib::NiStringsExtraData>(ed)->GetData();
								for ( vector<string>::iterator i = strData.begin(); i != strData.end(); ++i )
									ovec.push_back(i->c_str());
								break;

							case kNiflibType_NiVectorExtraData:
								vecData = Niflib::DynamicCast<Niflib::NiVectorExtraData>(ed)->GetData();
								omap[string("x")] = vecData.x;
								omap[string("y")] = vecData.y;
								omap[string("z")] = vecData.z;
								break;

							default:
								dPrintAndLog("NiExtraDataGetArray","ExtraData is not an array-holding type.");
						}
						if ( !(ovec.empty()) )
							arr = ArrayFromStdVector(ovec, scriptObj);
						else if ( !(omap.empty()) )
							arr = StringMapFromStdMap(omap, scriptObj);
					}
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiExtraDataGetArray","Returning ExtraData's array.\n");
	else
		dPrintAndLog("NiExtraDataGetArray","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataGetArray,
	NiEDGetArr,
	"If the Nth block of the given Nif is an ExtraData that stores an array, gets a copy of that array.",
	0,
	kParams_OneInt_OneOptionalInt
);

void NifFile::loadChNiExtraDataObject(UInt32 block, UInt32 type, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifList[block]);
		if ( ed ) {
			switch (type) {
				case kNiflibType_NiBooleanExtraData:
					{
						Niflib::NiBooleanExtraDataRef boolED = Niflib::DynamicCast<Niflib::NiBooleanExtraData>(ed);
						boolED->SetData(val.compare("1")==0?true:false);
					}
					dPrintAndLog("NifLoad - NiExtraData","Loaded NiBooleanExtraData change.");
					break;

				case kNiflibType_NiFloatExtraData:
					{
						Niflib::NiFloatExtraDataRef floatED = Niflib::DynamicCast<Niflib::NiFloatExtraData>(ed);
						floatED->SetData(StringToFloat(val));
					}
					dPrintAndLog("NifLoad - NiExtraData","Loaded NiFloatExtraData change.");
					break;

				case kNiflibType_NiIntegerExtraData:
				case kNiflibType_BSXFlags:
					{
						Niflib::NiIntegerExtraDataRef intED = Niflib::DynamicCast<Niflib::NiIntegerExtraData>(ed);
						intED->SetData(StringToSInt(val));
					}
					dPrintAndLog("NifLoad - NiExtraData","Loaded NiIntegerExtraData change.");
					break;

				case kNiflibType_NiStringExtraData:
					{
						Niflib::NiStringExtraDataRef strED = Niflib::DynamicCast<Niflib::NiStringExtraData>(ed);
						strED->SetData(val);
					}
					dPrintAndLog("NifLoad - NiExtraData","Loaded NiStringExtraData change.");
					break;

					case kNiflibType_BSBound:
					case kNiflibType_BSDecalPlacementVectorExtraData:
					case kNiflibType_BSFurnitureMarker:
					case kNiflibType_BSWArray:
					case kNiflibType_NiArkAnimationExtraData:
					case kNiflibType_NiArkImporterExtraData:
					case kNiflibType_NiArkShaderExtraData:
					case kNiflibType_NiArkTextureExtraData:
					case kNiflibType_NiArkViewportInfoExtraData:
					case kNiflibType_NiBinaryExtraData:
					case kNiflibType_NiBinaryVoxelExtraData:
					case kNiflibType_NiColorExtraData:
					case kNiflibType_NiFloatsExtraData:
					case kNiflibType_NiIntegersExtraData:
					case kNiflibType_NiStringsExtraData:
					case kNiflibType_NiTextKeyExtraData:
					case kNiflibType_NiVectorExtraData:
					case kNiflibType_NiVertWeightsExtraData:
						dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tChanges to that type of ExtraData are not supported! Loaded nif will be incorrect!\n");

					default:
						dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tUnknown ExtraData type!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tBlock #"+UIntToString(block)+" is not an ExtraData type! Loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tBlock index out of range! Loaded nif will be incorrect!\n");
}

