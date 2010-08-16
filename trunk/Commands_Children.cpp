#include "Commands_Children.h"

// returns the number of Children in the NifFile associated
// with given nifID.
static bool Cmd_NifGetNumChildren_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumChildren","Getting number of Children nodes in nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->root->GetChildren().size();
			dPrintAndLog("NifGetNumChildren","Returning "+UIntToString(*result)+" Children nodes.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNumChildren,
	"Returns the number of Children nodes in the given Nif",
	0,
	1,
	kParams_OneInt
);

static bool Cmd_NifGetNthChildName_Execute(COMMAND_ARGS) {
	*result = 0;
	string chStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildName","Getting the name of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				chStr = child->GetName();
				dPrintAndLog("NifGetNthChildName","Returning \""+chStr+"\".\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, chStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildName,
	"Returns the name of the specified child of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the name of the specified ExtraData in the
// NifFile associated with the given nifID.
static bool Cmd_NifSetNthChildName_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuName[kMaxMessageLength] = " ";
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuName, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildName","Setting the name of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuName)+"\".");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					*result = 1;
					child->SetName(nuName);
					clearPrevChange(nifPtr->childrenChanges, chID, Ch_AVObj, Act_SetName);
					nifPtr->childrenChanges += changeLog(chID, Ch_AVObj, Act_SetName, nuName);
					dPrintAndLog("NifSetNthChildName","Child name set successfully.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildName,
	"Sets the name of the Child to the passed string.",
	0,
	3,
	kParams_OneString_TwoInts
);

static bool Cmd_NifGetChildIndexByName_Execute(COMMAND_ARGS) {
	*result = -1;

	char chName[kMaxMessageLength];
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chName, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetChildIndexByName","Getting the index of Child \""+string(chName)+"\" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			*result = nifPtr->getChildIndexByName(chName);
			if ( *result == nifPtr->root->GetChildren().size() ) {
				*result = -1;
				dPrintAndLog("NifGetChildIndexByName","Child not found.\n");
			}
			else
				dPrintAndLog("NifGetChildIndexByName","Child found.\n");
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetChildIndexByName,
	"Returns the index of the named child of the specified Nif.",
	0,
	2,
	kParams_OneString_OneInt
);

// returns the type of the specified Child in the NifFile
// associated with the given nifID.
static bool Cmd_NifGetNthChildType_Execute(COMMAND_ARGS) {
	*result = 0;
	string chStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildType","Getting the type of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				chStr = child->GetType().GetTypeName();
				dPrintAndLog("NifGetNthChildType","Returning \""+chStr+"\".\n");
			}
		}
	}
	strInterface->Assign(PASS_COMMAND_ARGS, chStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildType,
	"Returns the type of the Nth Child on the given Nif",
	0,
	2,
	kParams_TwoInts
);

// removes the specified Child in the NifFile
// associated with the given nifID.
static bool Cmd_NifDeleteNthChild_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifDeleteNthChild","Deleting Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					nifPtr->root->RemoveChild(child);
					nifPtr->childrenChanges += changeLog(chID, Ch_AVObj, Act_Remove);
					*result = 1;
					dPrintAndLog("NifDeleteNthChild","Deletion successful.\n");
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifDeleteNthChild,
	"Deletes the Nth Child node of the given Nif",
	0,
	2,
	kParams_TwoInts
);

// gets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalTransform_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix = NULL;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalTransform","Getting local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					vector<vector<OBSEElement> > vrow;
					OBSEArray* orow;
					for ( int i = 0; i < 4; ++i ) {
						vrow.push_back(vector<OBSEElement>());
						for ( int j = 0; j < 4; ++j ) {
							vrow[i].push_back(child->GetLocalTransform().rows[i][j]);
						}
						orow = ArrayFromStdVector(vrow[i], scriptObj);
						vmatrix.push_back(orow);
					}
					omatrix = ArrayFromStdVector(vmatrix, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NifGetNthChildLocalTransform","Returning child's local transform.\n");
	else
		dPrintAndLog("NifGetNthChildLocalTransform","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalTransform,
	"Gets the local transform of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local transform of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTransform_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalTransform","This function will not be supported until OBSE v0020 and NifSE v1.1. Please use NifSetNthChildLocalTransformTEMP, instead.");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTransform,
	"Unsupported until OBSE v0020.",
	0,
	3,
	kParams_OneMatrix44_TwoInts
);

// gets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> translation;
	OBSEArray* arr;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalTranslation","Getting local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					translation.push_back(child->GetLocalTranslation().x);
					translation.push_back(child->GetLocalTranslation().y);
					translation.push_back(child->GetLocalTranslation().z);
					arr = ArrayFromStdVector(translation, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NifGetNthChildLocalTranslation","Returning child's local translation.\n");
	else
		dPrintAndLog("NifGetNthChildLocalTranslation","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalTranslation,
	"Gets the local translation of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTranslation_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalTranslation","This function will not be supported until OBSE v0020 and NifSE v1.1. Please use NifSetNthChildLocalTranslationTEMP, instead.\n");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTranslation,
	"Unsupported until OBSE v0020.",
	0,
	3,
	kParams_OneVector3_TwoInts
);

// gets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalRotation_Execute(COMMAND_ARGS) {
	*result = 0;
	vector<OBSEElement> vmatrix = vector<OBSEElement>();
	OBSEArray* omatrix;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalRotation","Getting local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					vector<vector<OBSEElement> > vrow;
					OBSEArray* orow;
					for ( int i = 0; i < 3; ++i ) {
						vrow.push_back(vector<OBSEElement>());
						for ( int j = 0; j < 3; ++j ) {
							vrow[i].push_back(child->GetLocalRotation().rows[i][j]);
						}
						orow = ArrayFromStdVector(vrow[i], scriptObj);
						vmatrix.push_back(orow);
					}
					omatrix = ArrayFromStdVector(vmatrix, scriptObj);
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(omatrix, result) )
		dPrintAndLog("NifGetNthChildLocalRotation","Returning child's local rotation.\n");
	else
		dPrintAndLog("NifGetNthChildLocalRotation","Failed to create and return array.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalRotation,
	"Gets the local rotation of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalRotation_Execute(COMMAND_ARGS) {
	PrintAndLog("NifSetNthChildLocalRotation","This function will not be supported until OBSE v0020 and NifSE v1.1. Please use NifSetNthChildLocalRotationTEMP, instead.\n");
	*result = 0;
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalRotation,
	"Unsupported until OBSE v0020.",
	0,
	3,
	kParams_OneMatrix33_TwoInts
);

// gets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NifGetNthChildLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildLocalScale","Getting local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					*result = child->GetLocalScale();
#ifdef _DEBUG
					Console_Print("NifGetNthChildLocalScale - Returning %.2f.\n", *result);
#endif
					_MESSAGE("NifGetNthChildLocalScale - Returning %.2f.\n", *result);
				}
			}
		}
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildLocalScale,
	"Gets the local scale of the Nth Child of the given Nif.",
	0,
	2,
	kParams_TwoInts
);

// sets the local scale of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalScale_Execute(COMMAND_ARGS) {
	*result = 0;

	float nuScale = 0;
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuScale, &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalScale","Setting local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					child->SetLocalScale(nuScale);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocScale);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocScale,FloatToString(nuScale));
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalScale","Local Scale of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(((*result)!=0)?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalScale,
	"Unsupported until OBSE v0019.",
	0,
	3,
	kParams_OneFloat_TwoInts
);

// sets the local transformation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTransformTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuTransform = vector< vector<float> >(4, vector<float>(4, 0));
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuTransform[0][0], &nuTransform[0][1], &nuTransform[0][2], &nuTransform[0][3], 
									   &nuTransform[1][0], &nuTransform[1][1], &nuTransform[1][2], &nuTransform[1][3],
									   &nuTransform[2][0], &nuTransform[2][1], &nuTransform[2][2], &nuTransform[2][3],
									   &nuTransform[3][0], &nuTransform[3][1], &nuTransform[3][2], &nuTransform[3][3],
									   &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalTransform","Setting local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					Niflib::Matrix44 newTransform (nuTransform[0][0], nuTransform[0][1], nuTransform[0][2], nuTransform[0][3], 
												   nuTransform[1][0], nuTransform[1][1], nuTransform[1][2], nuTransform[1][3],
												   nuTransform[2][0], nuTransform[2][1], nuTransform[2][2], nuTransform[2][3],
												   nuTransform[3][0], nuTransform[3][1], nuTransform[3][2], nuTransform[3][3]);
					child->SetLocalTransform(newTransform);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocTransform);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocTransform,MatrixToString(nuTransform));
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalTransform","Local Transform of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTransformTEMP,
	"Sets the local transform of the Nth Child of the given Nif.",
	0,
	18,
	kParams_Matrix44f_TwoInts
);

// sets the local translation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalTranslationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	Niflib::Vector3 nuTranslation;
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &(nuTranslation.x), &(nuTranslation.y), &(nuTranslation.z), &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalTranslation","Setting local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					child->SetLocalTranslation(nuTranslation);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocTranslation);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocTranslation,"["+FloatToString(nuTranslation.x)+"|"+FloatToString(nuTranslation.y)+"|"+FloatToString(nuTranslation.z)+"|");
				}
			}
		}
	}
	dPrintAndLog("NifSetNthChildLocalTranslation","Local Translation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalTranslationTEMP,
	"Sets the local translation of the Nth Child of the given Nif.",
	0,
	5,
	kParams_Vector3f_TwoInts
);

// sets the local rotation of the
// specified Child of the given NifFile
static bool Cmd_NifSetNthChildLocalRotationTEMP_Execute(COMMAND_ARGS) {
	*result = 0;

	vector< vector<float> > nuRotation = vector< vector<float> >(3, vector<float>(3, 0));
	int chID = -1;
	int nifID = -1;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuRotation[0][0], &nuRotation[0][1], &nuRotation[0][2],
									   &nuRotation[1][0], &nuRotation[1][1], &nuRotation[1][2],
									   &nuRotation[2][0], &nuRotation[2][1], &nuRotation[2][2],
									   &chID, &nifID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildLocalRotation","Setting local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					Niflib::Matrix33 newRotation (nuRotation[0][0], nuRotation[0][1], nuRotation[0][2],
												  nuRotation[1][0], nuRotation[1][1], nuRotation[1][2],
												  nuRotation[2][0], nuRotation[2][1], nuRotation[2][2]);
					child->SetLocalRotation(newRotation);
					*result = 1;
					clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_SetLocRotation);
					nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocRotation,MatrixToString(nuRotation));
				}
				else
					dPrintAndLog("NifSetNthChildLocalRotation","Child not found.");
			}
			else
				dPrintAndLog("NifSetNthChildLocalRotation","Child index out of range.");
		}
		else
			dPrintAndLog("NifSetNthChildLocalRotation","Nif not found.");
	}
	dPrintAndLog("NifSetNthChildLocalRotation","Local Rotation of Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has"+(*result!=0?(" "):(" not "))+"been set.\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildLocalRotationTEMP,
	"Sets the local rotation of the Nth Child of the given Nif.",
	0,
	11,
	kParams_Matrix33f_TwoInts
);

static bool Cmd_NifNthChildHasMaterial_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasMaterial","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Material Property.");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasMaterial","Child found.");
				Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
				if ( mat ) {
					*result = 1;
					dPrintAndLog("NifNthChildHasMaterial","Material property found.\n");
				}
				else
					dPrintAndLog("NifNthChildHasMaterial","Material property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasMaterial","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasMaterial,
	"Returns whether the specified child of the specified Nif has a material property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifGetNthChildMaterial_Execute(COMMAND_ARGS) {
	*result = 0;
	string matStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildMaterial","Getting the name of Child #"+UIntToString(chID)+"'s Material Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifGetNthChildMaterial","Child found.");
				Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
				if ( mat ) {
					dPrintAndLog("NifGetNthChildMaterial","Material property found.");
					matStr = mat->GetName();
					dPrintAndLog("NifGetNthChildMaterial","Returning \""+matStr+"\".\n");
				}
				else
					dPrintAndLog("NifGetNthChildMaterial","Material property not found.\n");
			}
			else
				dPrintAndLog("NifGetNthChildMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifGetNthChildMaterial","Nif root bad.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, matStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildMaterial,
	"Returns the name of the specified child's material property of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifSetNthChildMaterial_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuMat[kMaxMessageLength];
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuMat, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildMaterial","Setting the name of Child #"+UIntToString(chID)+"'s Material Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuMat)+"\".");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					dPrintAndLog("NifSetNthChildMaterial","Child found.");
					Niflib::NiPropertyRef mat = child->GetPropertyByType(Niflib::NiMaterialProperty::TYPE);
					if ( mat ) {
						mat->SetName(nuMat);
						*result = 1;
						dPrintAndLog("NifSetNthChildMaterial","Material property set.");
						clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_PropMat_SetName);
						nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_PropMat_SetName,nuMat);
					}
					else
						dPrintAndLog("NifSetNthChildMaterial","Material property not found.\n");
				}
				else
					dPrintAndLog("NifSetNthChildMaterial","Child not found.");
			}
			else
				dPrintAndLog("NifSetNthChildMaterial","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifSetNthChildMaterial","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildMaterial,
	"Sets the name of the specified child's material property of the specified Nif.",
	0,
	3,
	kParams_OneString_TwoInts
);

static bool Cmd_NifNthChildHasTexturingProp_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasTexturingProp","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Texturing Property.");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasTexturingProp","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifNthChildHasTexturingProp","Texturing property found.\n");
					*result = 1;
				}
				else
					dPrintAndLog("NifNthChildHasTexturingProp","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasTexturingProp","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasTexturingProp","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasTexturingProp,
	"Returns whether the specified child of the specified Nif has a Base Texture property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifNthChildHasBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifNthChildHasBaseTexture","Getting whether Child #"+UIntToString(chID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has a Base Texture.");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifNthChildHasBaseTexture","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifNthChildHasBaseTexture","Texturing property found.");
					*result = (tex->HasTexture(Niflib::BASE_MAP)?1:0);
					dPrintAndLog("NifNthChildHasBaseTexture","Returning "+((*result)!=0?string("TRUE"):string("FALSE"))+".\n");
				}
				else
					dPrintAndLog("NifNthChildHasBaseTexture","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifNthChildHasBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifNthChildHasBaseTexture","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifNthChildHasBaseTexture,
	"Returns whether the specified child of the specified Nif has a Base Texture property.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifGetNthChildBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	string texStr = " ";

	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNthChildBaseTexture","Getting the name of Child #"+UIntToString(chID)+"'s Texture Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				dPrintAndLog("NifGetNthChildBaseTexture","Child found.");
				Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
				if ( tex ) {
					dPrintAndLog("NifGetNthChildBaseTexture","Texturing property found.");
					if ( tex->HasTexture(Niflib::BASE_MAP) ) {
						texStr = tex->GetTexture(Niflib::BASE_MAP).source->GetTextureFileName();
						dPrintAndLog("NifGetNthChildBaseTexture","Returning \""+texStr+"\".\n");
					}
					else
						dPrintAndLog("NifGetNthChildBaseTexture","Texturing property does not have a base texture.\n");
				}
				else
					dPrintAndLog("NifGetNthChildBaseTexture","Texturing property not found.\n");
			}
			else
				dPrintAndLog("NifGetNthChildBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifGetNthChildBaseTexture","Nif root bad.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, texStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNthChildBaseTexture,
	"Returns the name of the specified child's material property of the specified Nif.",
	0,
	2,
	kParams_TwoInts
);

static bool Cmd_NifSetNthChildBaseTexture_Execute(COMMAND_ARGS) {
	*result = 0;

	char nuTex[kMaxMessageLength];
	int chID = -1;
	int nifID = -1;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nuTex, &chID, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifSetNthChildBaseTexture","Setting the name of Child #"+UIntToString(chID)+"'s Texture Property of nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to \""+string(nuTex)+"\".");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID, nifID, nifPtr);
		if ( nifPtr->root ) {
			if ( chID >= 0 && chID < nifPtr->root->GetChildren().size() ) {
				Niflib::NiAVObjectRef child = nifPtr->root->GetChildren()[chID];
				if ( child ) {
					dPrintAndLog("NifSetNthChildBaseTexture","Child found.");
					Niflib::NiTexturingPropertyRef tex = DynamicCast<Niflib::NiTexturingProperty>(child->GetPropertyByType(Niflib::NiTexturingProperty::TYPE));
					if ( tex ) {
						dPrintAndLog("NifSetNthChildBaseTexture","Texturing property found.");
						if ( tex->HasTexture(Niflib::BASE_MAP) ) {
							*result = 1;
							tex->GetTexture(Niflib::BASE_MAP).source->SetExternalTexture(nuTex);
							dPrintAndLog("NifSetNthChildBaseTexture","New texture set.\n");
							clearPrevChange(nifPtr->childrenChanges,chID,Ch_AVObj,Act_AV_PropTex_SetBaseMap);
							nifPtr->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_PropTex_SetBaseMap,nuTex);
						}
						else
							dPrintAndLog("NifSetNthChildBaseTexture","Texturing property does not have a base texture.\n");
					}
					else
						dPrintAndLog("NifSetNthChildBaseTexture","Texturing property not found.\n");
				}
				else
					dPrintAndLog("NifSetNthChildBaseTexture","Child not found.\n");
			}
			else
				dPrintAndLog("NifSetNthChildBaseTexture","Child index out of range.\n");
		}
		else
			dPrintAndLog("NifSetNthChildBaseTexture","Nif root bad.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifSetNthChildBaseTexture,
	"Sets the name of the specified child's material property of the specified Nif.",
	0,
	3,
	kParams_OneString_TwoInts
);