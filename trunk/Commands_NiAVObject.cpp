#include "Commands_NiAVObject.h"

#include "obj/NiObject.h"
#include "obj/NiObjectNET.h"
#include "obj/NiAVObject.h"
using Niflib::NiAVObjectRef;

#include "NiProperties.h"

// gets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectGetLocalTransform_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetLocalTransform","Getting local Transform of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						vector<vector<OBSEElement> > vrow;
						OBSEArray* orow = NULL;
						for ( int i = 0; i < 4; ++i ) {
							vrow.push_back(vector<OBSEElement>());
							for ( int j = 0; j < 4; ++j ) {
								vrow[i].push_back(avObj->GetLocalTransform().rows[i][j]);
							}
							orow = ArrayFromStdVector(vrow[i], scriptObj);
							vmatrix.push_back(orow);
						}
						omatrix = ArrayFromStdVector(vmatrix, scriptObj);
					}
					else
						dPrintAndLog("NiAVObjectGetLocalTransform","Not NiAVObject.");
				}
				else
					dPrintAndLog("NiAVObjectGetLocalTransform","Block index out of range.");
			}
			else
				dPrintAndLog("NiAVObjectGetLocalTransform","Nif root bad.");
		}
		else
			dPrintAndLog("NiAVObjectGetLocalTransform","Could not find Nif.");
	}
	else
		dPrintAndLog("NiAVObjectGetLocalTransform","Error extracting arguments");

	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NiAVObjectGetLocalTransform","Returning child's local transform.\n");
	else
		dPrintAndLog("NiAVObjectGetLocalTransform","Failed to create and return array.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetLocalTransform,
	NiAVObjGetLocTransf,
	"Gets the local transform of the Nth Child of the given Nif.",
	0,
	kParams_OneInt_OneOptionalInt
);

// gets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectGetLocalTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetLocalTranslation","Getting local Translation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						vector<OBSEElement> translation;
						translation.push_back(avObj->GetLocalTranslation().x);
						translation.push_back(avObj->GetLocalTranslation().y);
						translation.push_back(avObj->GetLocalTranslation().z);
						arr = ArrayFromStdVector(translation, scriptObj);
					}
					else
						dPrintAndLog("NiAVObjectGetLocalTranslation","Not NiAVObject.");
				}
				else
					dPrintAndLog("NiAVObjectGetLocalTranslation","Block index out of range.");
			}
			else
				dPrintAndLog("NiAVObjectGetLocalTranslation","Nif root bad.");
		}
		else
			dPrintAndLog("NiAVObjectGetLocalTranslation","Could not find Nif.");
	}
	else
		dPrintAndLog("NiAVObjectGetLocalTranslation","Error extracting arguments");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiAVObjectGetLocalTranslation","Returning child's local translation.\n");
	else
		dPrintAndLog("NiAVObjectGetLocalTranslation","Failed to create and return array.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetLocalTranslation,
	NiAVObjGetLocTransl,
	"Gets the local translation of the Nth Child of the given Nif.",
	0,
	kParams_OneInt_OneOptionalInt
);

// gets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectGetLocalRotation_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetLocalRotation","Getting local Rotation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						vector<vector<OBSEElement> > vrow;
						OBSEArray* orow = NULL;
						for ( int i = 0; i < 3; ++i ) {
							vrow.push_back(vector<OBSEElement>());
							for ( int j = 0; j < 3; ++j ) {
								vrow[i].push_back(avObj->GetLocalRotation().rows[i][j]);
							}
							orow = ArrayFromStdVector(vrow[i], scriptObj);
							vmatrix.push_back(orow);
						}
						omatrix = ArrayFromStdVector(vmatrix, scriptObj);
					}
					else
						dPrintAndLog("NiAVObjectGetLocalRotation","Selected block is not an AV Object.");
				}
				else
					dPrintAndLog("NiAVObjectGetLocalRotation","Block index is out of range.");
			}
			else
				dPrintAndLog("NiAVObjectGetLocalRotation","Nif root is bad.");
		}
		else
			dPrintAndLog("NiAVObjectGetLocalRotation","Nif is not registered.");
	}
	else
		dPrintAndLog("NiAVObjectGetLocalRotation","Failed to extract arguments.");

	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NiAVObjectGetLocalRotation","Returning child's local rotation.\n");
	else
		dPrintAndLog("NiAVObjectGetLocalRotation","Failed to create and return array.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetLocalRotation,
	NiAVObjGetLocRot,
	"Gets the local rotation of the Nth Child of the given Nif.",
	0,
	kParams_OneInt_OneOptionalInt
);

// gets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectGetLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetLocalScale","Getting local Scale of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						*result = avObj->GetLocalScale();
						dPrintAndLog("NiAVObjectGetLocalScale""Returning "+FloatToString(*result)+".\n");
					}
					else
						dPrintAndLog("NiAVObjectGetLocalScale","Not NiAVObject.");
				}
				else
					dPrintAndLog("NiAVObjectGetLocalScale","Block index out of range.");
			}
			else
				dPrintAndLog("NiAVObjectGetLocalScale","Nif root bad.");
		}
		else
			dPrintAndLog("NiAVObjectGetLocalScale","Could not find Nif.");
	}
	else
		dPrintAndLog("NiAVObjectGetLocalScale","Error extracting arguments");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetLocalScale,
	NiAVObjGetLocScale,
	"Gets the local scale of the Nth Child of the given Nif.",
	0,
	kParams_OneInt_OneOptionalInt
);

// sets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectSetLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	float nuScale = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuScale, &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalScale","Setting local Scale of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							avObj->SetLocalScale(nuScale);
							*result = 1;
							nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocScale,FloatToString(nuScale),true);
							dPrintAndLog("NiAVObjectSetLocalScale","Local scale set.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalScale","Not NiAVObject.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalScale","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalScale","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalScale","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalScale","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalScale","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalScale,
	NiAVObjSetLocScale,
	"Sets the local scale of the chosen AVObject.",
	0,
	kParams_OneFloat_OneInt_OneOptionalInt
);

// sets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectSetLocalTransformTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuTransform = vector< vector<float> >(4, vector<float>(4, 0));
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuTransform[0][0], &nuTransform[0][1], &nuTransform[0][2], &nuTransform[0][3], 
									   &nuTransform[1][0], &nuTransform[1][1], &nuTransform[1][2], &nuTransform[1][3],
									   &nuTransform[2][0], &nuTransform[2][1], &nuTransform[2][2], &nuTransform[2][3],
									   &nuTransform[3][0], &nuTransform[3][1], &nuTransform[3][2], &nuTransform[3][3],
									   &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalTransform","Setting local Transform of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							Niflib::Matrix44 newTransform (nuTransform[0][0], nuTransform[0][1], nuTransform[0][2], nuTransform[0][3], 
														   nuTransform[1][0], nuTransform[1][1], nuTransform[1][2], nuTransform[1][3],
														   nuTransform[2][0], nuTransform[2][1], nuTransform[2][2], nuTransform[2][3],
														   nuTransform[3][0], nuTransform[3][1], nuTransform[3][2], nuTransform[3][3]);
							avObj->SetLocalTransform(newTransform);
							*result = 1;
							nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocTransf,MatrixToString(newTransform),true);
							dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Local transform set.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Not NiAVObject.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalTransformTEMP","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalTransformTEMP,
	NiAVObjSetLocTransfT,
	"Sets the local transform of the Nth Child of the given Nif.",
	0,
	kParams_Matrix44f_OneInt_OneOptionalInt
);

// sets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectSetLocalTranslationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	Niflib::Vector3 newTranslation;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &(newTranslation.x), &(newTranslation.y), &(newTranslation.z), &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalTranslation","Setting local Translation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							avObj->SetLocalTranslation(newTranslation);
							*result = 1;
							nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocTransl,VectorToString(newTranslation),true);
							dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Set local translation.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Not NiAVObject.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalTranslationTEMP","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalTranslationTEMP,
	NiAVObjSetLocTranslT,
	"Sets the local translation of the Nth Child of the given Nif.",
	0,
	kParams_Vector3f_OneInt_OneOptionalInt
);

// sets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NiAVObjectSetLocalRotationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuRotation = vector< vector<float> >(3, vector<float>(3, 0));
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuRotation[0][0], &nuRotation[0][1], &nuRotation[0][2],
									   &nuRotation[1][0], &nuRotation[1][1], &nuRotation[1][2],
									   &nuRotation[2][0], &nuRotation[2][1], &nuRotation[2][2],
									   &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalRotation","Setting local Rotation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							Niflib::Matrix33 newRotation (nuRotation[0][0], nuRotation[0][1], nuRotation[0][2],
														  nuRotation[1][0], nuRotation[1][1], nuRotation[1][2],
														  nuRotation[2][0], nuRotation[2][1], nuRotation[2][2]);
							avObj->SetLocalRotation(newRotation);
							*result = 1;
							nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocRot,MatrixToString(newRotation),true);
							dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Local rotation set.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Child not found.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Child index out of range.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Nif not found.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Nif not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalRotationTEMP","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalRotationTEMP,
	NiAVObjSetLocRotT,
	"Sets the local rotation of the Nth Child of the given Nif.",
	0,
	kParams_Matrix33f_OneInt_OneOptionalInt
);

// gets the number of properties that the AVObject has
static bool Cmd_NiAVObjectGetNumProperties_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetNumProperties","Getting the number of properties held by of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						*result = avObj->GetProperties().size();
						dPrintAndLog("NiAVObjectGetNumProperties","Returning "+UIntToString(*result)+".");
					}
					else
						dPrintAndLog("NiAVObjectGetNumProperties","Not NiAVObject.\n");
				}
				else
					dPrintAndLog("NiAVObjectGetNumProperties","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAVObjectGetNumProperties","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectGetNumProperties","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectGetNumProperties","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetNumProperties,
	NiAVObjGetNumProps,
	"Gets the number of properties to the given AVObject.",
	0,
	kParams_OneInt_OneOptionalInt
);

// gets an array of properties that the AVObject has
static bool Cmd_NiAVObjectGetProperties_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetProperties","Getting the properties held by of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						vector<OBSEElement> prvec = vector<OBSEElement>();
						vector<Niflib::NiPropertyRef> prs = avObj->GetProperties();
						for ( vector<Niflib::NiPropertyRef>::iterator i = prs.begin(); i != prs.end(); ++i )
							prvec.push_back((*i)->internal_block_number);
						arr = ArrayFromStdVector(prvec, scriptObj);
					}
					else
						dPrintAndLog("NiAVObjectGetProperties","Not NiAVObject.");
				}
				else
					dPrintAndLog("NiAVObjectGetProperties","Block index out of range.");
			}
			else
				dPrintAndLog("NiAVObjectGetProperties","Nif root bad.");
		}
		else
			dPrintAndLog("NiAVObjectGetProperties","Could not find Nif.");
	}
	else
		dPrintAndLog("NiAVObjectGetProperties","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiAVObjectGetProperties","Returning node's extra data.\n");
	else
		dPrintAndLog("NiAVObjectGetProperties","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetProperties,
	NiAVObjGetProps,
	"Gets the properties to the given AVObject.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAVObjectGetPropertyByType_Execute(COMMAND_ARGS) {
	*result = -1;

	int prType = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &prType, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectGetPropertyByType","Getting the index of the \""+UIntToString(prType)+"\" Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
					if ( avObj ) {
						*result = avObj->GetPropertyByType(*(getNiflibType(prType)))->internal_block_number;
						dPrintAndLog("NiAVObjectGetPropertyByType","Returning "+UIntToString(blockID)+".\n");
					}
					else
						dPrintAndLog("NiAVObjectGetPropertyByType","Not NiAVObject.\n");
				}
				else
					dPrintAndLog("NiAVObjectGetPropertyByType","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAVObjectGetPropertyByType","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectGetPropertyByType","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectGetPropertyByType","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetPropertyByType,
	NiAVObjGetEDByType,
	"Returns the index of the Property of the given type on the specified Nif.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiAVObjectAddProperty_Execute(COMMAND_ARGS) {
	*result = 0;

	char name[kMaxMessageLength];
	UInt32 typeID = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &name, &typeID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectAddProperty","Adding Property \""+string(name)+"\" of type #"+UIntToString(typeID)+" to nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							try {
								*result = Util_NiAVObjectAddProperty(nifPtr, avObj, typeID, name);
								dPrintAndLog("NiAVObjectAddProperty","Addition successful; property is block #"+UIntToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiAVObjectAddProperty","Addition failed; exception \""+string(e.what())+"\" thrown.");
							}
						}
						else
							dPrintAndLog("NiAVObjectAddProperty","Nif node not an extra-data-supporting type.\n");
					}
					else
						dPrintAndLog("NiAVObjectAddProperty","Nif node index out of bounds.\n");
				}
				else
					dPrintAndLog("NiAVObjectAddProperty","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectAddProperty","Nif not found.\n");
		}
		else
			dPrintAndLog("NiAVObjectAddProperty","Nif not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectAddProperty","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectAddProperty,
	NiAVObjAddED,
	"Adds an Property node of the given type to the given Nif",
	0,
	kParams_OneString_TwoInts_OneOptionalInt
);

static bool Cmd_NiAVObjectDeleteProperty_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	int prID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &prID, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectDeleteProperty","Deleting Property with Block #"+UIntToString(prID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+".");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
						if ( avObj ) {
							if ( prID < nifPtr->nifList.size() ) {
								Niflib::NiPropertyRef pr = Niflib::DynamicCast<Niflib::NiProperty>(nifPtr->nifList[prID]);
								if ( pr ) {
									avObj->RemoveProperty(pr);
									*result = 1;
									dPrintAndLog("NiAVObjectDeleteProperty","Property deleted.\n");
									nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_DelProp,UIntToString(prID));
								}
								else
									dPrintAndLog("NiAVObjectDeleteProperty","Block not NiProperty; not deleted. Block type: \""+nifPtr->nifList[prID]->GetType().GetTypeName()+"\".\n");
							}
							else
								dPrintAndLog("NiAVObjectDeleteProperty","Block indicated for Property is out of range; block not deleted.\n");
						}
						else
							dPrintAndLog("NiAVObjectDeleteProperty","Block not NiObjectNET; ExtraData not deleted. Block type: \""+nifPtr->nifList[blockID]->GetType().GetTypeName()+"\".\n");
					}
					else
						dPrintAndLog("NiAVObjectDeleteProperty","Block indicated for ObjectNET is out of range; ExtraData not deleted.\n");
				}
				else
					dPrintAndLog("NiAVObjectDeleteProperty","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiAVObjectDeleteProperty","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectDeleteProperty","Nif not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectDeleteProperty","Could not extract arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectDeleteProperty,
	NiAVObjDelED,
	"Deletes the Nth block of the given Nif if it is an Property",
	0,
	kParams_TwoInts_OneOptionalInt
);


UInt32 Util_NiAVObjectAddProperty(NifFile* nifPtr, Niflib::NiAVObjectRef avObj, UInt32 typeID, const string& name) {
	Niflib::NiPropertyRef nuProp = NULL;
	switch (typeID) {
		case kNiflibType_BSDistantTreeShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::BSDistantTreeShaderProperty::Create());
			break;

		case kNiflibType_BSShaderLightingProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::BSShaderLightingProperty::Create());
			break;

		case kNiflibType_BSShaderNoLightingProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::BSShaderNoLightingProperty::Create());
			break;

		case kNiflibType_BSShaderPPLightingProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::BSShaderPPLightingProperty::Create());
			break;

		case kNiflibType_BSShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::BSShaderProperty::Create());
			break;

		case kNiflibType_DistantLODShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::DistantLODShaderProperty::Create());
			break;

		case kNiflibType_HairShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::HairShaderProperty::Create());
			break;

		case kNiflibType_Lighting30ShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::Lighting30ShaderProperty::Create());
			break;

		case kNiflibType_NiAlphaProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiAlphaProperty::Create());
			break;

		case kNiflibType_NiDitherProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiDitherProperty::Create());
			break;

		case kNiflibType_NiFogProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiFogProperty::Create());
			break;

		case kNiflibType_NiMaterialProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiMaterialProperty::Create());
			break;

		case kNiflibType_NiMultiTextureProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiMultiTextureProperty::Create());
			break;

		case kNiflibType_NiProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiProperty::Create());
			break;

		case kNiflibType_NiShadeProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiShadeProperty::Create());
			break;

		case kNiflibType_NiSpecularProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiSpecularProperty::Create());
			break;

		case kNiflibType_NiStencilProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiStencilProperty::Create());
			break;

		case kNiflibType_NiTextureModeProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiTextureModeProperty::Create());
			break;

		case kNiflibType_NiTextureProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiTextureProperty::Create());
			break;

		case kNiflibType_NiTexturingProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiTexturingProperty::Create());
			break;

		case kNiflibType_NiTransparentProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiTransparentProperty::Create());
			break;

		case kNiflibType_NiVertexColorProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiVertexColorProperty::Create());
			break;

		case kNiflibType_NiWireframeProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiWireframeProperty::Create());
			break;

		case kNiflibType_NiZBufferProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::NiZBufferProperty::Create());
			break;

		case kNiflibType_SkyShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::SkyShaderProperty::Create());
			break;

		case kNiflibType_TallGrassShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::TallGrassShaderProperty::Create());
			break;

		case kNiflibType_TileShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::TileShaderProperty::Create());
			break;

		case kNiflibType_VolumetricFogShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::VolumetricFogShaderProperty::Create());
			break;

		case kNiflibType_WaterShaderProperty:
			nuProp = Niflib::DynamicCast<Niflib::NiProperty>(Niflib::WaterShaderProperty::Create());
			break;

		default:
			throw std::exception("Property type unknown!");
	}

	if ( nuProp ) {
		nuProp->SetName(name);
		nuProp->internal_block_number = nifPtr->nifList.size();
		avObj->AddProperty(nuProp);
		nifPtr->nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(nuProp));
		nifPtr->logChange(avObj->internal_block_number,kNiflibType_NiAVObject,kNiAVObjAct_AddProp,UIntToString(typeID)+logValType+name);
		return nuProp->internal_block_number;
	}
	else
		throw std::exception("New NiProperty not created.");
}

void NifFile::loadChNiAVObject(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifList[block]);
		if ( avObj ) {
			switch (act) {
				case kNiAVObjAct_SetLocTransf:
					{
						vector< vector< float > > vmat = StringToMatrix(val);
						if ( vmat.size() != 4 ) {
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tSaved transform matrix is incorrectly sized! Loaded nif will be incorrect!\n");
							break;
						}
						if ( vmat[0].size() != 4 || vmat[1].size() != 4 || vmat[2].size() != 4 || vmat[3].size() != 4 ) {
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tSaved transform matrix is incorrectly sized! Loaded nif will be incorrect!\n");
							break;
						}
						avObj->SetLocalTransform(Niflib::Matrix44(vmat[0][0], vmat[0][1], vmat[0][2], vmat[0][3],
																  vmat[1][0], vmat[1][1], vmat[1][2], vmat[1][3],
																  vmat[2][0], vmat[2][1], vmat[2][2], vmat[2][3],
																  vmat[3][0], vmat[3][1], vmat[3][2], vmat[3][3]));
					}
					dPrintAndLog("NifLoad - NiAVObject","Local Transform change loaded.");
					break;

				case kNiAVObjAct_SetLocTransl:
					{
						vector<float> vvec = StringToVector(val);
						if ( vvec.size() != 3 ) {
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tSaved translation vector is incorrectly sized! Loaded nif will be incorrect!\n");
							break;
						}
						avObj->SetLocalTranslation(Niflib::Vector3(vvec[0], vvec[1], vvec[2]));
					}
					dPrintAndLog("NifLoad - NiAVObject","Local Translation change loaded.");
					break;

				case kNiAVObjAct_SetLocRot:
					{
						vector< vector< float > > vmat = StringToMatrix(val);
						if ( vmat.size() != 3 ) {
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tSaved rotation matrix is incorrectly sized! Loaded nif will be incorrect!\n");
							break;
						}
						if ( vmat[0].size() != 3 || vmat[1].size() != 3 || vmat[2].size() != 3 ) {
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tSaved rotation matrix is incorrectly sized! Loaded nif will be incorrect!\n");
							break;
						}
						avObj->SetLocalRotation(Niflib::Matrix33(vmat[0][0], vmat[0][1], vmat[0][2],
																 vmat[1][0], vmat[1][1], vmat[1][2],
																 vmat[2][0], vmat[2][1], vmat[2][2]));
					}
					dPrintAndLog("NifLoad - NiAVObject","Local Rotation change loaded.");
					break;

				case kNiAVObjAct_SetLocScale:
					avObj->SetLocalScale(StringToFloat(val));
					dPrintAndLog("NifLoad - NiAVObject","Local Scale change loaded.");
					break;

				case kNiAVObjAct_AddProp:
					try {
						string::size_type i = val.find(logValType);
						UInt32 prType = StringToUInt(val.substr(0, i));
						string prName = val.substr(i+1);
						Util_NiAVObjectAddProperty(this, avObj, prType, prName);
						dPrintAndLog("NifLoad - NiAVObject","NiProperty \""+prName+"\" added to nif.");
					}
					catch (std::exception e) {
						dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tNiProperty not added! Exception \""+string(e.what())+"\" thrown. Loaded nif will be incorrect!\n");
					}
					break;

				case kNiAVObjAct_DelProp:
					{
						UInt32 prID = StringToUInt(val);
						if ( prID < nifList.size() ) {
							vector<Niflib::NiPropertyRef> prs = avObj->GetProperties();
							for ( vector<Niflib::NiPropertyRef>::iterator i = prs.begin(); i != prs.end(); ++i )
								if ( *i == Niflib::DynamicCast<Niflib::NiProperty>(nifList[prID]) )
									avObj->RemoveProperty(*i);
							dPrintAndLog("NifLoad - NiAVObject","Property (block #"+val+") deleted.");
						}
						else
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tBlock #"+val+" out of range! Loaded nif will be incorrect!\n");
					}
					break;

				case kNiAVObjAct_SetFlags:
				case kNiAVObjAct_SetVel:
				case kNiAVObjAct_SetVis:
				case kNiAVObjAct_SetCollObj:
				case kNiAVObjAct_SetCollMode:
					dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tThis version of NifSE does not support these changes! Loaded nif will be incorrect!\n");

				default:
					dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tIndicated block is not a NiAVObject! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
