#include "Commands_NiAlphaProperty.h"

#include "obj/NiAlphaProperty.h"

static bool Cmd_NiAlphaPropertyGetBlendState_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetBlendState","Getting the blend state of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetBlendState();
							dPrintAndLog("NiAlphaPropertyGetBlendState","Returning "+string(*result!=0?"TRUE":"FALSE")+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetBlendState","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetBlendState","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetBlendState","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetBlendState","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetBlendState","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetBlendState","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetBlendState,
	NiAlphaPropGetBlendState,
	"Returns the blend state of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetSourceBlendFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Getting the source blend function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetSourceBlendFunc();
							dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetSourceBlendFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetSourceBlendFunction,
	NiAlphaPropGetSrcBlendFunc,
	"Returns the blend function of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetDestinationBlendFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Getting the destination blend function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetDestBlendFunc();
							dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetDestinationBlendFunction,
	NiAlphaPropGetDestBlendFunc,
	"Returns the destination blend function of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetTestState_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetTestState","Getting the test state of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetTestState();
							dPrintAndLog("NiAlphaPropertyGetTestState","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetTestState","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetTestState","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetTestState","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetTestState","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetTestState","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetTestState","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetTestState,
	NiAlphaPropGetTestState,
	"Returns the test state of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetTestFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetTestFunction","Getting the test function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetTestFunc();
							dPrintAndLog("NiAlphaPropertyGetTestFunction","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetTestFunction","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetTestFunction","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetTestFunction","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetTestFunction","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetTestFunction","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetTestFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetTestFunction,
	NiAlphaPropGetTestFunc,
	"Returns the test function of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetTestThreshold_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetTestThreshold","Getting the test threshold of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetTestThreshold();
							dPrintAndLog("NiAlphaPropertyGetTestThreshold","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetTestThreshold","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetTestThreshold","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetTestThreshold","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetTestThreshold","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetTestThreshold","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetTestThreshold","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetTestThreshold,
	NiAlphaPropGetTestThresh,
	"Returns the test threshold of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertyGetTriangleSortMode_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Getting the triangle sort mode of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
					if ( alphaPr ) {
						try {
							*result = alphaPr->GetTriangleSortMode();
							dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Returning "+string(*result!=0?"TRUE":"FALSE")+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Not a NiAlphaProperty.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetTriangleSortMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertyGetTriangleSortMode,
	NiAlphaPropGetTriSort,
	"Returns the triangle sort mode of the given NiAlphaProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetBlendState_Execute(COMMAND_ARGS) {
	*result = 0;

	int blend = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &blend, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetBlendState","Setting the blend state of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
						if ( alphaPr ) {
							try {
								alphaPr->SetBlendState(blend!=0);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetBlendState, UIntToString(blend), true);
								dPrintAndLog("NiAlphaPropertySetBlendState","Blend state set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiAlphaPropertySetBlendState","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiAlphaPropertySetBlendState","Not a NiAlphaProperty.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetBlendState","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetBlendState","Nif not ediatable.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetBlendState","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetBlendState","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetBlendState","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetBlendState,
	NiAlphaPropSetBlendState,
	"Sets the blend state of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetSourceBlendFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int blendFunc = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &blendFunc, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Setting the source blend function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( Niflib::NiAlphaProperty::BF_ONE <= blendFunc && blendFunc <= Niflib::NiAlphaProperty::BF_SRC_ALPHA_SATURATE ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
							if ( alphaPr ) {
								try {
									alphaPr->SetSourceBlendFunc((Niflib::NiAlphaProperty::BlendFunc)blendFunc);
									*result = 1;
									nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetSrcBlendFunc, UIntToString(blendFunc), true);
									dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Source blend function set.\n");
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Not a NiAlphaProperty.\n");
						}
						else
							dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Invalid blend function specified; value must be between 0 and 10, inclusive.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetSourceBlendFunction,
	NiAlphaPropSetSrcBlendFunc,
	"Sets the blend function of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetDestinationBlendFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int blendFunc = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &blendFunc, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetDestinationBlendFunction","Setting the destination blend function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( Niflib::NiAlphaProperty::BF_ONE <= blendFunc && blendFunc <= Niflib::NiAlphaProperty::BF_SRC_ALPHA_SATURATE ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
							if ( alphaPr ) {
								try {
									alphaPr->SetDestBlendFunc((Niflib::NiAlphaProperty::BlendFunc)blendFunc);
									*result = 1;
									nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetDestBlendFunc, UIntToString(blendFunc), true);
									dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Destination blend function set.\n");
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Not a NiAlphaProperty.\n");
						}
						else
							dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetSourceBlendFunction","Invalid blend function specified; value must be between 0 and 10, inclusive.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertyGetDestinationBlendFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetDestinationBlendFunction,
	NiAlphaPropSetDestBlendFunc,
	"Sets the destination blend function of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetTestState_Execute(COMMAND_ARGS) {
	*result = 0;

	int test = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &test, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetTestState","Setting the test state of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
						if ( alphaPr ) {
							try {
								alphaPr->SetTestState(test!=0);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetTestState, UIntToString(test), true);
								dPrintAndLog("NiAlphaPropertySetTestState","Test state set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiAlphaPropertySetTestState","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiAlphaPropertySetTestState","Not a NiAlphaProperty.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetTestState","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetTestState","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetTestState","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetTestState","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetTestState","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetTestState,
	NiAlphaPropSetTestState,
	"Sets the test state of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetTestFunction_Execute(COMMAND_ARGS) {
	*result = 0;

	int testFunc = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &testFunc, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetTestFunction","Setting the test function of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( Niflib::NiAlphaProperty::TF_ALWAYS <= testFunc && testFunc <= Niflib::NiAlphaProperty::TF_NEVER ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
							if ( alphaPr ) {
								try {
									alphaPr->SetTestFunc((Niflib::NiAlphaProperty::TestFunc)testFunc);
									*result = 1;
									nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetTestFunc, UIntToString(testFunc), true);
									dPrintAndLog("NiAlphaPropertySetTestFunction","Test function set.\n");
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiAlphaPropertySetTestFunction","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiAlphaPropertySetTestFunction","Not a NiAlphaProperty.\n");
						}
						else
							dPrintAndLog("NiAlphaPropertySetTestFunction","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetTestFunction","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetTestFunction","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetTestFunction","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetTestFunction","Invalid test function; must be between 0 and 7, inclusive.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetTestFunction","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetTestFunction,
	NiAlphaPropSetTestFunc,
	"Sets the test function of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetTestThreshold_Execute(COMMAND_ARGS) {
	*result = 0;

	int thresh = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &thresh, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetTestThreshold","Setting the test threshold of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
						if ( alphaPr ) {
							try {
								alphaPr->SetTestThreshold(thresh);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetTestThreshold, UIntToString(thresh), true);
								dPrintAndLog("NiAlphaPropertySetTestThreshold","Test threshold set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiAlphaPropertySetTestThreshold","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiAlphaPropertySetTestThreshold","Not a NiAlphaProperty.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetTestThreshold","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetTestThreshold","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetTestThreshold","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetTestThreshold","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetTestThreshold","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetTestThreshold,
	NiAlphaPropSetTestThresh,
	"Sets the test threshold of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAlphaPropertySetTriangleSortMode_Execute(COMMAND_ARGS) {
	*result = 0;

	int tri = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &tri, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Setting the triangle sort mode of NiAlphaProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifPtr->nifList[blockID]);
						if ( alphaPr ) {
							try {
								alphaPr->SetTriangleSortMode(tri!=0);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiAlphaProperty, kNiAlphaPropAct_SetTriSort, UIntToString(tri), true);
								dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Triangle sort mode set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Not a NiAlphaProperty.\n");
					}
					else
						dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAlphaPropertySetTriangleSortMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAlphaPropertySetTriangleSortMode,
	NiAlphaPropSetTriSort,
	"Sets the triangle sort mode of the given NiAlphaProperty.",
	0,
	kParams_TwoInts_OneOptionalInt
);

void NifFile::loadChNiAlphaProperty(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::NiAlphaPropertyRef alphaPr = Niflib::DynamicCast<Niflib::NiAlphaProperty>(nifList[block]);
		UInt32 valInt = StringToUInt(val);
		if ( alphaPr ) {
			switch (act) {
				case kNiAlphaPropAct_SetBlendState:
					alphaPr->SetBlendState(valInt!=0);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty blend state change loaded.");
					break;

				case kNiAlphaPropAct_SetSrcBlendFunc:
					alphaPr->SetSourceBlendFunc((Niflib::NiAlphaProperty::BlendFunc)valInt);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty source blend function change loaded.");
					break;

				case kNiAlphaPropAct_SetDestBlendFunc:
					alphaPr->SetDestBlendFunc((Niflib::NiAlphaProperty::BlendFunc)valInt);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty destination blend function change loaded.");
					break;

				case kNiAlphaPropAct_SetTestState:
					alphaPr->SetTestState(valInt!=0);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty test state change loaded.");
					break;

				case kNiAlphaPropAct_SetTestFunc:
					alphaPr->SetTestFunc((Niflib::NiAlphaProperty::TestFunc)valInt);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty test function change loaded.");
					break;

				case kNiAlphaPropAct_SetTestThreshold:
					alphaPr->SetTestThreshold(valInt);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty test threshold change loaded.");
					break;

				case kNiAlphaPropAct_SetTriSort:
					alphaPr->SetTriangleSortMode(valInt!=0);
					dPrintAndLog("NifLoad - NiAlphaProperty","NiAlphaProperty triangle sort mode change loaded.");
					break;

				default:
					dPrintAndLog("NifLoad - NiAlphaProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiAlphaProperty","\n\n\t\tIndicated block is not a NiAlphaProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiAlphaProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
