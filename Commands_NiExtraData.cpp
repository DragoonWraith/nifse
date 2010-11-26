#include "Commands_NiExtraData.h"

#include "NiExtraData.h"

#include "nif_math.h"

// returns the string stored in the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataGetName_Execute(COMMAND_ARGS) {
	*result = 0;
	string edName = " ";

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataGetName","Getting the name of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						edName = ed->GetName();
						dPrintAndLog("NiExtraDataGetName","Returning \""+edName+"\".\n");
					}
					else
						dPrintAndLog("NiExtraDataGetName","Block #"+UIntToString(blockID)+" is not NiExtraData; block type is \""+nifPtr->nifList[blockID]->GetType().GetTypeName()+"\".\n");
				}
				else
					dPrintAndLog("NiExtraDataGetName","Block #"+UIntToString(blockID)+" is out of range.\n");
			}
			else
				dPrintAndLog("NiExtraDataGetName","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataGetName","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataGetName","Failed to extract arguments.\n");

	strInterface->Assign(PASS_COMMAND_ARGS, edName.c_str());
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataGetName,
	NiEDGetName,
	"If the Nth block of the given Nif is a NiStringExtraData, gets the value of the string.",
	0,
	kParams_OneInt_OneOptionalInt
);

// sets the name of the specified StringExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataSetName_Execute(COMMAND_ARGS) {
	*result = 0;

	char newName[kMaxMessageLength] = " ";
	int nifID = -1;
	UInt32 blockID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &newName, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataSetName","Setting the name of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(newName)+"\".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
						if ( ed ) {
							*result = 1;
							ed->SetName(newName);
							dPrintAndLog("NiExtraDataSetName","ExtraData value set successfully.\n");
							nifPtr->logChange(blockID, kNiflibType_NiStringExtraData, kNiEDAct_SetName, newName, true);
						}
						else
							dPrintAndLog("NiExtraDataSetName","Block #"+UIntToString(blockID)+" is not NiExtraData; block type is \""+nifPtr->nifList[blockID]->GetType().GetTypeName()+"\".\n");
					}
					else
						dPrintAndLog("NiExtraDataSetName","Block #"+UIntToString(blockID)+" is out of range.\n");
				}
				else
					dPrintAndLog("NiExtraDataSetName","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiExtraDataSetName","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataSetName","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataSetName","Failed to extract arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataSetName,
	NiEDSetName,
	"Sets the name of the Nth ExtraData of the given Nif.",
	0,
	kParams_OneString_OneInt_OneOptionalInt
);

// returns the number stored in the specified ExtraData
// in the NifFile associated with the given nifID.
static bool Cmd_NiExtraDataGetNumber_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataGetNumber","Getting numerical value of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
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
								dPrintAndLog("NiExtraDataGetNumber","ExtraData is not a numerical type!\n");
								break;
						}
					}
					else
						dPrintAndLog("NiExtraDataGetNumber","Block is not NiExtraData.\n");
				}
				else
					dPrintAndLog("NiExtraDataGetNumber","Block is out of range.\n");
			}
			else
				dPrintAndLog("NiExtraDataGetNumber","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataGetNumber","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataGetNumber","Failed to extract arguments.\n");

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
		dPrintAndLog("NiExtraDataSetNumber","Setting the numerical value of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to "+FloatToString(newVal)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
						if ( ed ) {
							UInt32 edType = getNiflibTypeIndex(ed->GetType());
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
						else
							dPrintAndLog("NiExtraDataSetNumber","Block is not NiExtraData.\n");
					}
					else
						dPrintAndLog("NiExtraDataSetNumber","Block is out of range.\n");
				}
				else
					dPrintAndLog("NiExtraDataSetNumber","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiExtraDataSetNumber","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataSetNumber","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataSetNumber","Failed to extract arguments.\n");

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
		dPrintAndLog("NiExtraDataGetString","Getting string value of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiStringExtraDataRef ed = Niflib::DynamicCast<Niflib::NiStringExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						edStr = ed->GetData();
						dPrintAndLog("NiExtraDataGetString","Returning \""+edStr+"\".\n");
					}
					else
						dPrintAndLog("NiExtraDataGetString","Block is not NiStringExtraData.\n");
				}
				else
					dPrintAndLog("NiExtraDataGetString","Block is out of range.\n");
			}
			else
				dPrintAndLog("NiExtraDataGetString","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataGetString","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataGetString","Failed to extract arguments.\n");

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
		dPrintAndLog("NiExtraDataSetString","Setting the string value of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(newStr)+"\".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiStringExtraDataRef ed = Niflib::DynamicCast<Niflib::NiStringExtraData>(nifPtr->nifList[blockID]);
						if ( ed ) {
							*result = 1;
							ed->SetData(newStr);
							dPrintAndLog("NiExtraDataSetString","ExtraData value set successfully.\n");
							nifPtr->logChange(blockID, kNiflibType_NiStringExtraData, kNiEDAct_SetStr, newStr, true);
						}
						else
							dPrintAndLog("NiExtraDataSetString","Block is not NiStringExtraData.\n");
					}
					else
						dPrintAndLog("NiExtraDataSetString","Block is out of range.\n");
				}
				else
					dPrintAndLog("NiExtraDataSetString","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiExtraDataSetString","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiExtraDataSetString","Nif not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataSetString","Failed to extract arguments.\n");

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
		dPrintAndLog("NiExtraDataGetArray","Getting array of ExtraData (block #"+UIntToString(blockID)+") of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
					if ( ed ) {
						UInt32 edType = getNiflibTypeIndex(ed->GetType());
						dPrintAndLog("NiExtraDataGetArray","ExtraData type: \""+ed->GetType().GetTypeName()+"\" (#"+UIntToString(edType)+").");
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
								ovec.push_back(vecData.x);
								ovec.push_back(vecData.y);
								ovec.push_back(vecData.z);
								break;

							default:
								dPrintAndLog("NiExtraDataGetArray","ExtraData is not an array-holding type.");
						}
						if ( !(ovec.empty()) )
							arr = ArrayFromStdVector(ovec, scriptObj);
						else if ( !(omap.empty()) )
							arr = StringMapFromStdMap(omap, scriptObj);
					}
					else
						dPrintAndLog("NiExtraDataGetArray","Block is not NiExtraData.");
				}
				else
					dPrintAndLog("NiExtraDataGetArray","Block is out of range.");
			}
			else
				dPrintAndLog("NiExtraDataGetArray","Nif root is bad.");
		}
		else
			dPrintAndLog("NiExtraDataGetArray","Nif not found.");
	}
	else
		dPrintAndLog("NiExtraDataGetArray","Failed to extract arguments.");

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

static bool Cmd_NiExtraDataSetArray_Execute(COMMAND_ARGS) {
	*result = 0;

	int arrID = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arrID, &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiExtraDataSetArray","Setting the array value of ExtraData #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		OBSEArray* arr = arrInterface->LookupArrayByID(arrID);
		if ( arr ) {
			NifFile* nifPtr = NULL;
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifPtr->nifList[blockID]);
							if ( ed ) {
								UInt32 edType = getNiflibTypeIndex(ed->TYPE);
								string change = "";
								UInt32 arrSize = arrInterface->GetArraySize(arr);
								switch (edType) {
									case kNiflibType_NiBinaryExtraData:
										{
											vector<Niflib::byte> data = vector<Niflib::byte>();
											bool dataGood = true;
											if ( arrSize > 0 ) {
												OBSEElement* eles = new OBSEElement[arrSize];
												if ( arrInterface->GetElements(arr, eles, NULL) ) {
													for ( UInt32 i = 0; i < arrSize; ++i )
														if ( eles[i].GetType() == OBSEElement::kType_Numeric )
															data.push_back(eles[i].Number());
														else {
															dataGood = false;
															dPrintAndLog("NiExtraDataSetArray","Passed array contains non-byte data.\n");
														}
												}
												else {
													dataGood = false;
													dPrintAndLog("NiExtraDataSetArray","Could not get elements from passed array.\n");
												}
												delete [] eles;
											}
											else
												dPrintAndLog("NiExtraDataSetArray","Passed array is empty; clearing NiBinaryExtraData.");

											if ( dataGood ) {
												Niflib::NiBinaryExtraDataRef binED = Niflib::DynamicCast<Niflib::NiBinaryExtraData>(ed);
												if ( binED ) {
													binED->SetData(data);
													dPrintAndLog("NiExtraDataSetArray","NiBinaryExtraData block set.\n");
													change = VectorToString(data);
												}
												else
													dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not NiBinaryExtraData.\n");
											}
										}
										break;

									case kNiflibType_NiColorExtraData:
										if ( arrSize == 4 ) {
											Niflib::NiColorExtraDataRef colorED = Niflib::DynamicCast<Niflib::NiColorExtraData>(ed);
											if ( ed ) {
												OBSEElement ele;
												Niflib::Color4 data;
												if ( !(arrInterface->GetElement(arr, "r", ele)) ) {
													if ( !(arrInterface->GetElement(arr, (double)0, ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'r'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.r = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'r' is not numeric.\n");
													break;
												}

												if ( !(arrInterface->GetElement(arr, "g", ele)) ) {
													if ( !(arrInterface->GetElement(arr, (double)1, ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'r'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.g = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'g' is not numeric.\n");
													break;
												}

												if ( !(arrInterface->GetElement(arr, "b", ele)) ) {
													if ( !(arrInterface->GetElement(arr, (double)2, ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'b'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.b = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'b' is not numeric.\n");
													break;
												}

												if ( !(arrInterface->GetElement(arr, "a", ele)) ) {
													if ( !(arrInterface->GetElement(arr, (double)3, ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'a'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.a = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'a' is not numeric.\n");
													break;
												}

												colorED->SetData(data);
												dPrintAndLog("NiExtraDataSetArray","NiColorExtraData block set.\n");
												change = Color4ToString(data);
											}
											else
												dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not a NiColorExtraData.\n");
										}
										else
											dPrintAndLog("NiExtraDataSetArray","NiColorExtraData arrays require exactly 4 elements; passed array has "+UIntToString(arrSize)+".\n");
										break;

									case kNiflibType_NiFloatsExtraData:
										{
											vector<float> data = vector<float>();
											bool dataGood = true;
											if ( arrSize > 0 ) {
												OBSEElement* eles = new OBSEElement[arrSize];
												if ( arrInterface->GetElements(arr, eles, NULL) ) {
													for ( UInt32 i = 0; i < arrSize; ++i )
														if ( eles[i].GetType() == OBSEElement::kType_Numeric )
															data.push_back(eles[i].Number());
														else {
															dataGood = false;
															dPrintAndLog("NiExtraDataSetArray","Passed array contains non-float data.\n");
														}
												}
												else {
													dataGood = false;
													dPrintAndLog("NiExtraDataSetArray","Could not get elements from passed array.\n");
												}
												delete [] eles;
											}
											else
												dPrintAndLog("NiExtraDataSetArray","Passed array is empty; clearing NiFloatsExtraData.");

											if ( dataGood ) {
												Niflib::NiFloatsExtraDataRef fltsED = Niflib::DynamicCast<Niflib::NiFloatsExtraData>(ed);
												if ( fltsED ) {
													fltsED->SetData(data);
													dPrintAndLog("NiExtraDataSetArray","NiFloatsExtraData block set.\n");
													change = VectorToString(data);
												}
												else
													dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not NiFloatsExtraData.\n");
											}
										}
										break;

									case kNiflibType_NiIntegersExtraData:
										{
											vector<unsigned int> data = vector<unsigned int>();
											bool dataGood = true;
											if ( arrSize > 0 ) {
												OBSEElement* eles = new OBSEElement[arrSize];
												if ( arrInterface->GetElements(arr, eles, NULL) ) {
													for ( UInt32 i = 0; i < arrSize; ++i ) {
														if ( eles[i].GetType() == OBSEElement::kType_Numeric ) {
															if ( eles[i].Number() > 0 )
																data.push_back(eles[i].Number());
															else {
																dataGood = false;
																dPrintAndLog("NiExtraDataSetArray","Passed array contains negative data; NiIntegersExtraData accepts only unsigned ints.\n");
															}
														}
														else {
															dataGood = false;
															dPrintAndLog("NiExtraDataSetArray","Passed array contains non-integer data.\n");
														}
													}
												}
												else {
													dataGood = false;
													dPrintAndLog("NiExtraDataSetArray","Could not get elements from passed array.\n");
												}
												delete [] eles;
											}
											else
												dPrintAndLog("NiExtraDataSetArray","Passed array is empty; clearing NiIntegersExtraData.");

											if ( dataGood ) {
												Niflib::NiIntegersExtraDataRef intsED = Niflib::DynamicCast<Niflib::NiIntegersExtraData>(ed);
												if ( intsED ) {
													intsED->SetData(data);
													dPrintAndLog("NiExtraDataSetArray","NiIntegersExtraData block set.\n");
													change = VectorToString(data);
												}
												else
													dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not NiIntegersExtraData.\n");
											}
										}
										break;

									case kNiflibType_NiStringsExtraData:
										{
											vector<string> data = vector<string>();
											bool dataGood = true;
											if ( arrSize > 0 ) {
												OBSEElement* eles = new OBSEElement[arrSize];
												if ( arrInterface->GetElements(arr, eles, NULL) ) {
													for ( UInt32 i = 0; i < arrSize; ++i )
														if ( eles[i].GetType() == OBSEElement::kType_String )
															data.push_back(eles[i].String());
														else {
															dataGood = false;
															dPrintAndLog("NiExtraDataSetArray","Passed array contains non-string data.\n");
														}
												}
												else {
													dataGood = false;
													dPrintAndLog("NiExtraDataSetArray","Could not get elements from passed array.\n");
												}
												delete [] eles;
											}
											else
												dPrintAndLog("NiExtraDataSetArray","Passed array is empty; clearing NiStringsExtraData.");

											if ( dataGood ) {
												Niflib::NiStringsExtraDataRef strsED = Niflib::DynamicCast<Niflib::NiStringsExtraData>(ed);
												if ( strsED ) {
													strsED->SetData(data);
													dPrintAndLog("NiExtraDataSetArray","NiStringsExtraData block set.\n");
													change = VectorToString(data);
												}
												else
													dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not NiStringsExtraData.\n");
											}
										}
										break;

									case kNiflibType_NiVectorExtraData:
										if ( arrSize == 3 ) {
											Niflib::NiVectorExtraDataRef vecED = Niflib::DynamicCast<Niflib::NiVectorExtraData>(ed);
											if ( ed ) {
												OBSEElement ele;
												Niflib::Vector3 data;
												if ( !(arrInterface->GetElement(arr, (double)0, ele)) ) {
													if ( !(arrInterface->GetElement(arr, "x", ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'x'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.x = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'x' is not numeric.\n");
													break;
												}

												if ( !(arrInterface->GetElement(arr, (double)1, ele)) ) {
													if ( !(arrInterface->GetElement(arr, "y", ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'y'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.y = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'y' is not numeric.\n");
													break;
												}

												if ( !(arrInterface->GetElement(arr, (double)2, ele)) ) {
													if ( !(arrInterface->GetElement(arr, "z", ele)) ) {
														dPrintAndLog("NiExtraDataSetArray","No value found for 'z'.\n");
														break;
													}
												}
												if ( ele.GetType() == OBSEElement::kType_Numeric )
													data.z = ele.Number();
												else {
													dPrintAndLog("NiExtraDataSetArray","Value for 'z' is not numeric.\n");
													break;
												}

												vecED->SetData(data);
												dPrintAndLog("NiExtraDataSetArray","NiVectorExtraData block set.\n");
												change = VectorToString(data);
											}
											else
												dPrintAndLog("NiExtraDataSetArray","ExtraData block indicated is not a NiVectorExtraData.\n");
										}
										else
											dPrintAndLog("NiExtraDataSetArray","NiVectorExtraData arrays require exactly 3 elements; passed array has "+UIntToString(arrSize)+".\n");
										break;

									default:
										dPrintAndLog("NiExtraDataSetArray","ExtraData is not an array-holding type.\n");
								}
								if ( change.size() > 0 ) {
									*result = 1;
									nifPtr->logChange(blockID, edType, kNiEDAct_SetArr, change);
								}
							}
							else
								dPrintAndLog("NiExtraDataSetArray","Index does not refer to an ExtraData block.\n");
						}
						else
							dPrintAndLog("NiExtraDataSetArray","ExtraData index out of range.\n");
					}
					else
						dPrintAndLog("NiExtraDataSetArray","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiExtraDataSetArray","Nif not found.\n");
			}
			else
				dPrintAndLog("NiExtraDataSetArray","Nif not found.\n");
		}
		else
			dPrintAndLog("NiExtraDataSetArray","Array not found.\n");
	}
	else
		dPrintAndLog("NiExtraDataSetArray","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiExtraDataSetArray,
	NiEDSetArr,
	"If the Nth block of the given Nif is an ExtraData that stores an array, sets the value of that array.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

void NifFile::loadChNiExtraData(UInt32 block, UInt32 act, UInt32 type, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiExtraDataRef ed = Niflib::DynamicCast<Niflib::NiExtraData>(nifList[block]);
		if ( ed ) {
			switch (act) {
				case kNiEDAct_SetName:
					ed->SetName(val);
					dPrintAndLog("NifLoad - NiExtraData","Loaded NiExtraData name change.");
					break;

				case kNiEDAct_SetNum:
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

						default:
							dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tCannot set the number of a non-numerical ExtraData! Loaded nif will be incorrect!\n");
					}
					break;

				case kNiEDAct_SetStr:
					if ( type == kNiflibType_NiStringExtraData ) {
						Niflib::NiStringExtraDataRef strED = Niflib::DynamicCast<Niflib::NiStringExtraData>(ed);
						if ( strED ) {
							strED->SetData(val);
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiStringExtraData change.");
						}
						else
							dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tCannot set the string of a non-string ExtraData! Loaded nif will be incorrect!\n");
					}
					else
						dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tCannot set the string of a non-string ExtraData! Loaded nif will be incorrect!\n");
					break;

				case kNiEDAct_SetArr:
					switch(type) {
						case kNiflibType_NiBinaryExtraData:
							{
								Niflib::NiBinaryExtraDataRef binED = Niflib::DynamicCast<Niflib::NiBinaryExtraData>(ed);
								binED->SetData(StringToVectorB(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiBinaryExtraData change.");
							break;

						case kNiflibType_NiColorExtraData:
							{
								Niflib::NiColorExtraDataRef colorED = Niflib::DynamicCast<Niflib::NiColorExtraData>(ed);
								colorED->SetData(StringToColor4(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiColorExtraData change.");
							break;

						case kNiflibType_NiFloatsExtraData:
							{
								Niflib::NiFloatsExtraDataRef fltsED = Niflib::DynamicCast<Niflib::NiFloatsExtraData>(ed);
								fltsED->SetData(StringToVector(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiFloatsExtraData change.");
							break;

						case kNiflibType_NiIntegersExtraData:
							{
								Niflib::NiIntegersExtraDataRef intsED = Niflib::DynamicCast<Niflib::NiIntegersExtraData>(ed);
								intsED->SetData(StringToVectorU(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiIntegersExtraData change.");
							break;

						case kNiflibType_NiStringsExtraData:
							{
								Niflib::NiStringsExtraDataRef strsED = Niflib::DynamicCast<Niflib::NiStringsExtraData>(ed);
								strsED->SetData(StringToVectorS(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiStringsExtraData change.");
							break;

						case kNiflibType_NiVectorExtraData:
							{
								Niflib::NiVectorExtraDataRef vecED = Niflib::DynamicCast<Niflib::NiVectorExtraData>(ed);
								vecED->SetData(StringToVector3(val));
							}
							dPrintAndLog("NifLoad - NiExtraData","Loaded NiVectorExtraData change.");
							break;

						default:
							dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tCannot set the array of a non-array ExtraData! Loaded nif will be incorrect!\n");
					}
					break;

				case kNiEDAct_SetBSBound:
					dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tChanges to BSBound ExtraData are not supported in this version of NifSE! Loaded nif will be incorrect!\n");
					break;

				default:
					dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tUnknown ExtraData action! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tBlock #"+UIntToString(block)+" is not an ExtraData type! Loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiExtraData","\n\n\t\tBlock index out of range! Loaded nif will be incorrect!\n");
}

