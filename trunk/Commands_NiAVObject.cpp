#include "Commands_NiAVObject.h"

#include "obj/NiObject.h"
#include "obj/NiObjectNET.h"
#include "obj/NiAVObject.h"
using Niflib::NiAVObjectRef;

#include "NiProperties.h"
#include "obj/NiCollisionObject.h"

#include "Command_Macros.h"

// gets the local transformation of the
// specified NiAVObject
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
						try {
							Niflib::Matrix44 nmatrix = avObj->GetLocalTransform();
							vector<vector<OBSEElement> > vrow;
							OBSEArray* orow = NULL;
							for ( int i = 0; i < 4; ++i ) {
								vrow.push_back(vector<OBSEElement>());
								for ( int j = 0; j < 4; ++j ) {
									vrow[i].push_back(nmatrix.rows[i][j]);
								}
								orow = ArrayFromStdVector(vrow[i], scriptObj);
								vmatrix.push_back(orow);
							}
							omatrix = ArrayFromStdVector(vmatrix, scriptObj);
						}
						catch (std::exception e) {
							omatrix = NULL;
							dPrintAndLog("NiAVObjectGetLocalTransform","Exception \""+string(e.what())+"\" thrown.");
						}
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
// specified NiAVObject
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
						try {
							Niflib::Vector3 ntransl = avObj->GetLocalTranslation();
							vector<OBSEElement> vtransl;
							vtransl.push_back(ntransl.x);
							vtransl.push_back(ntransl.y);
							vtransl.push_back(ntransl.z);
							arr = ArrayFromStdVector(vtransl, scriptObj);
						}
						catch (std::exception e) {
							arr = NULL;
							dPrintAndLog("NiAVObjectGetLocalTranslation","Exception \""+string(e.what())+"\" thrown.");
						}
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
// specified NiAVObject
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
						try {
							Niflib::Matrix33 nmatrix = avObj->GetLocalRotation();
							vector<vector<OBSEElement> > vrow;
							OBSEArray* orow = NULL;
							for ( int i = 0; i < 3; ++i ) {
								vrow.push_back(vector<OBSEElement>());
								for ( int j = 0; j < 3; ++j ) {
									vrow[i].push_back(nmatrix.rows[i][j]);
								}
								orow = ArrayFromStdVector(vrow[i], scriptObj);
								vmatrix.push_back(orow);
							}
							omatrix = ArrayFromStdVector(vmatrix, scriptObj);
						}
						catch (std::exception e) {
							omatrix = NULL;
							dPrintAndLog("NiAVObjectGetLocalRotation","Exception \""+string(e.what())+"\" thrown.");
						}
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
// specified NiAVObject
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
						try {
							*result = avObj->GetLocalScale();
							dPrintAndLog("NiAVObjectGetLocalScale","Returning "+FloatToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAVObjectGetLocalTransform","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiAVObjectGetLocalScale","Not NiAVObject.\n");
				}
				else
					dPrintAndLog("NiAVObjectGetLocalScale","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiAVObjectGetLocalScale","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiAVObjectGetLocalScale","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiAVObjectGetLocalScale","Error extracting arguments\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectGetLocalScale,
	NiAVObjGetLocScale,
	"Gets the local scale of the Nth Child of the given Nif.",
	0,
	kParams_OneInt_OneOptionalInt
);

// sets the local transformation of the
// specified NiAVObject
static bool Cmd_NiAVObjectSetLocalTransform_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalTransform","Setting local Transform of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 4 ) {
				vector<OBSEArray*> row = vector<OBSEArray*>();
				OBSEElement ele;
				arrInterface->GetElement(arr, (double)0, ele);
				row.push_back(ele.Array());
				arrInterface->GetElement(arr, (double)1, ele);
				row.push_back(ele.Array());
				arrInterface->GetElement(arr, (double)2, ele);
				row.push_back(ele.Array());
				arrInterface->GetElement(arr, (double)3, ele);
				row.push_back(ele.Array());
				if ( row[0] && row[1] && row[2] && row[3] ) {
					unsigned long row0Size = arrInterface->GetArraySize(row[0]);
					unsigned long row1Size = arrInterface->GetArraySize(row[1]);
					unsigned long row2Size = arrInterface->GetArraySize(row[2]);
					unsigned long row3Size = arrInterface->GetArraySize(row[3]);
					if ( row0Size == 4 && row1Size == 4 && row2Size ==4 && row3Size == 4 ) {
						NifFile* nifPtr = NULL;
						if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
							if ( nifPtr->root ) {
								if ( nifPtr->editable ) {
									if ( blockID < nifPtr->nifList.size() ) {
										NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
										if ( avObj ) {
											Niflib::Matrix44 newTransform (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
											for ( UInt32 i = 0; i < 4; ++i ) {
												for ( UInt32 j = 0; j < 4; ++j ) {
													arrInterface->GetElement(row[i], j, ele);
													if ( ele.GetType() == OBSEArrayVarInterface::Element::kType_Numeric )
														newTransform[i][j] = ele.Number();
													else {
														dPrintAndLog("NiAVObjectSetLocalTransform","Array element is not a number. Array must be a 4x4 matrix.\n");
														return true;
													}
												}
											}
											try {
												avObj->SetLocalTransform(newTransform);
												*result = 1;
												nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocTransf,MatrixToString(newTransform),true);
												dPrintAndLog("NiAVObjectSetLocalTransform","Local transform set.\n");
											}
											catch (std::exception e) {
												*result = 0;
												dPrintAndLog("NiAVObjectSetLocalTransform","Exception \""+string(e.what())+"\" thrown.\n");
											}
										}
										else
											dPrintAndLog("NiAVObjectSetLocalTransform","Not NiAVObject.\n");
									}
									else
										dPrintAndLog("NiAVObjectSetLocalTransform","Block index out of range.\n");
								}
								else
									dPrintAndLog("NiAVObjectSetLocalTransform","Nif is not editable.\n");
							}
							else
								dPrintAndLog("NiAVObjectSetLocalTransform","Nif root bad.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalTransform","Could not find Nif.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalTransform","Not every row has size 4. Array must be a 4x4 matrix.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalTransform","Array is not fully 2-dimensional. Array must be 4x4 matrix.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalTransform","Array does not have size 4. Array must be a 4x4 matrix.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalTransform","Array not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalTransform","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalTransform,
	NiAVObjSetLocTransf,
	"Sets the local transform of the Nth Child of the given Nif.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

// sets the local translation of the
// specified NiAVObject
static bool Cmd_NiAVObjectSetLocalTranslation_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalTranslation","Setting local Translation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 3 ) {
				NifFile* nifPtr = NULL;
				if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
					if ( nifPtr->root ) {
						if ( nifPtr->editable ) {
							if ( blockID < nifPtr->nifList.size() ) {
								NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
								if ( avObj ) {
									OBSEElement ele;
									Niflib::Vector3 newTranslation (0,0,0);
									for ( UInt32 i = 0; i < 3; ++i ) {
										arrInterface->GetElement(arr, i, ele);
										if ( ele.GetType() == OBSEElement::kType_Numeric ) {
											switch (i) {
												case 0:
													newTranslation.x = ele.Number();
													dPrintAndLog("NiAVObjectSetLocalTranslation","x translation set to "+FloatToString(newTranslation.x));
													break;
												case 1:
													newTranslation.y = ele.Number();
													dPrintAndLog("NiAVObjectSetLocalTranslation","y translation set to "+FloatToString(newTranslation.y));
													break;
												case 2:
													newTranslation.z = ele.Number();
													dPrintAndLog("NiAVObjectSetLocalTranslation","z translation set to "+FloatToString(newTranslation.z));
													break;
											}
										}
										else {
											dPrintAndLog("NiAVObjectSetLocalTranslation","Array element is not a number. Array must be a 3-vector.\n");
											return true;
										}
									}
									try {
										avObj->SetLocalTranslation(newTranslation);
										*result = 1;
										nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocTransl,VectorToString(newTranslation),true);
										dPrintAndLog("NiAVObjectSetLocalTranslation","Local translation set.\n");
									}
									catch (std::exception e) {
										*result = 0;
										dPrintAndLog("NiAVObjectSetLocalTranslation","Exception \""+string(e.what())+"\" thrown.\n");
									}
								}
								else
									dPrintAndLog("NiAVObjectSetLocalTranslation","Not NiAVObject.\n");
							}
							else
								dPrintAndLog("NiAVObjectSetLocalTranslation","Block index out of range.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalTranslation","Nif is not editable.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalTranslation","Nif root bad.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalTranslation","Could not find Nif.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalTranslation","Array does not have size 3. Array must be a 3-vector.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalTranslation","Array not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalTranslation","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalTranslation,
	NiAVObjSetLocTransl,
	"Sets the local translation of the Nth Child of the given Nif.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

// sets the local rotation of the
// specified NiAVObject
static bool Cmd_NiAVObjectSetLocalRotation_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int nifID = -1;
	UInt32 blockID = 0;
	UInt8 modID;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectSetLocalRotation","Setting local Rotation of Child #"+UIntToString(blockID)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 3 ) {
				vector<OBSEArray*> row = vector<OBSEArray*>();
				OBSEElement ele;
				arrInterface->GetElement(arr, (double)0, ele);
				row.push_back(ele.Array());
				arrInterface->GetElement(arr, (double)1, ele);
				row.push_back(ele.Array());
				arrInterface->GetElement(arr, (double)2, ele);
				row.push_back(ele.Array());
				if ( row[0] && row[1] && row[2] ) {
					unsigned long row0Size = arrInterface->GetArraySize(row[0]);
					unsigned long row1Size = arrInterface->GetArraySize(row[1]);
					unsigned long row2Size = arrInterface->GetArraySize(row[2]);
					if ( row0Size == 3 && row1Size == 3 && row2Size == 3 ) {
						NifFile* nifPtr = NULL;
						if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
							if ( nifPtr->root ) {
								if ( nifPtr->editable ) {
									if ( blockID < nifPtr->nifList.size() ) {
										NiAVObjectRef avObj = Niflib::DynamicCast<Niflib::NiAVObject>(nifPtr->nifList[blockID]);
										if ( avObj ) {
											Niflib::Matrix33 newRotation (0,0,0,0,0,0,0,0,0);
											for ( UInt32 i = 0; i < 3; ++i ) {
												for ( UInt32 j = 0; j < 3; ++j ) {
													if ( arrInterface->GetElement(row[i], j, ele) ) {
														if ( ele.GetType() == OBSEArrayVarInterface::Element::kType_Numeric )
															newRotation[i][j] = ele.Number();
														else {
															dPrintAndLog("NiAVObjectSetLocalRotation","Array element is not a number. Array must be a 3x3 matrix.\n");
															return true;
														}
													}
													else
														dPrintAndLog("NiAVObjectSetLocalRotation","Array element could not be gotten.\n");
												}
											}
											try {
												avObj->SetLocalRotation(newRotation);
												*result = 1;
												nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocRot,MatrixToString(newRotation),true);
												dPrintAndLog("NiAVObjectSetLocalRotation","Local rotation set.\n");
											}
											catch (std::exception e) {
												*result = 0;
												dPrintAndLog("NiAVObjectSetLocalRotation","Exception \""+string(e.what())+"\" thrown.\n");
											}
										}
										else
											dPrintAndLog("NiAVObjectSetLocalRotation","Child not found.\n");
									}
									else
										dPrintAndLog("NiAVObjectSetLocalRotation","Child index out of range.\n");
								}
								else
									dPrintAndLog("NiAVObjectSetLocalRotation","Nif not editable.\n");
							}
							else
								dPrintAndLog("NiAVObjectSetLocalRotation","Nif not found.\n");
						}
						else
							dPrintAndLog("NiAVObjectSetLocalRotation","Nif not found.\n");
					}
					else
						dPrintAndLog("NiAVObjectSetLocalRotation","Not every row has size 3. Array must be a 3x3 matrix.\n");
				}
				else
					dPrintAndLog("NiAVObjectSetLocalRotation","Array is not fully 2-dimensional. Array must be 3x3 matrix.\n");
			}
			else
				dPrintAndLog("NiAVObjectSetLocalRotation","Array does not have size 3. Array must be a 3x3 matrix.\n");
		}
		else
			dPrintAndLog("NiAVObjectSetLocalRotation","Array not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectSetLocalRotation","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectSetLocalRotation,
	NiAVObjSetLocRot,
	"Sets the local rotation of the Nth Child of the given Nif.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

// sets the local scale of the
// specified NiAVObject
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
							try {
								avObj->SetLocalScale(nuScale);
								*result = 1;
								nifPtr->logChange(blockID,kNiflibType_NiAVObject,kNiAVObjAct_SetLocScale,FloatToString(nuScale),true);
								dPrintAndLog("NiAVObjectSetLocalScale","Local scale set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiAVObjectSetLocalScale","Exception \""+string(e.what())+"\" thrown.\n");
							}
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

// gets the number of properties that the NiAVObject has
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
						try {
							*result = avObj->GetProperties().size();
							dPrintAndLog("NiAVObjectGetNumProperties","Returning "+UIntToString(*result)+".");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiAVObjectGetNumProperties","Exception \""+string(e.what())+"\" thrown.\n");
						}
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
						try {
							vector<OBSEElement> prvec = vector<OBSEElement>();
							vector<Niflib::NiPropertyRef> prs = avObj->GetProperties();
							for ( vector<Niflib::NiPropertyRef>::iterator i = prs.begin(); i != prs.end(); ++i )
								prvec.push_back((*i)->internal_block_number);
							arr = ArrayFromStdVector(prvec, scriptObj);
						}
						catch (std::exception e) {
							arr = NULL;
							dPrintAndLog("NiAVObjectGetProperties","Exception \""+string(e.what())+"\" thrown.");
						}
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
		dPrintAndLog("NiAVObjectGetProperties","Returning node's properties.\n");
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
						try {
							Niflib::NiPropertyRef prRef = avObj->GetPropertyByType(*(getNiflibType(prType)));
							if ( prRef ) {
								*result = prRef->internal_block_number;
								dPrintAndLog("NiAVObjectGetPropertyByType","Returning "+UIntToString(*result)+".\n");
							}
							else
								dPrintAndLog("NiAVObjectGetPropertyByType","NiAVObject does not have a property of this type.\n");
						}
						catch (std::exception e) {
							*result = -1;
							dPrintAndLog("NiAVObjectGetPropertyByType","Exception \""+string(e.what())+"\" thrown.\n");
						}
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
								nifPtr->logChange(avObj->internal_block_number,kNiflibType_NiAVObject,kNiAVObjAct_AddProp,UIntToString(typeID)+logValType+name);
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

STDNIFLIBGET(NiAVObject, GetCollisionMode, NiAVObjGetCollMode, UInt, collision mode);

STDNIFLIBSETUINTCAST(NiAVObject, SetCollisionMode, NiAVObjSetCollMode, kNiAVObjAct_SetCollMode, true, collision mode, Niflib::NiAVObject::CollisionType);

STDNIFLIBGETBLOCK(NiAVObject, GetCollisionObject(), NiAVObjectGetCollisionObject, NiAVObjGetCollObj, UInt, collision object);

static bool Cmd_NiAVObjectClearCollisionObject_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectClearCollisionObject", "Clearing the collision object of NiAVObject (nif " NIFIDSTR+").");
		try {
			GETBLOCK(NiAVObject, block);
			if ( block->GetCollisionObject() )
				block->GetCollisionObject()->SetTarget((Niflib::NiAVObject*)NULL);
			block->SetCollisionObject((Niflib::NiCollisionObject*)NULL);
			*result = 1;
			dPrintAndLog("NiAVObjectClearCollisionObject", "Collision object cleared.\n");
		} catch (std::exception e) {
			*result = 0;
			dPrintAndLog("NiAVObjectClearCollisionObject", "Exception \""+string(e.what())+"\" thrown.\n");
		}
	} else
		dPrintAndLog("NiAVObjectClearCollisionObject", "Error extracting arguments.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectClearCollisionObject,
	NiAVObjClrCollObj,
	"Clears the collision object of the given NiAVObject.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiAVObjectCopyCollisionObject_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifIDfrom = -1;
	int blockIDfrom = -1;
	int nifIDto = -1;
	UInt32 blockIDto = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifIDfrom, &blockIDfrom, &nifIDto, &blockIDto)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiAVObjectCopyCollisionObject","Copying NiCollisionObject (Nif #"+UIntToString(modID)+"-"+UIntToString(nifIDfrom)+" block #"+UIntToString(blockIDfrom)+" as the collision object of NiAVObject (Nif #"+UIntToString(modID)+"-"+UIntToString(nifIDto)+" block #"+UIntToString(blockIDto)+".");
		NifFile* nifFromPtr = NULL;
		NifFile* nifToPtr = NULL;
		if ( NifFile::getRegNif(modID, nifIDfrom, nifFromPtr) && NifFile::getRegNif(modID, nifIDto, nifToPtr) ) {
			try {
				*result = Util_NiAVObjectCopyCollision(nifFromPtr, blockIDfrom, nifToPtr, blockIDto);
				nifFromPtr->frzChange(nifToPtr);
				nifToPtr->logChange(blockIDto, kNiflibType_NiAVObject, kNiAVObjAct_CopyCollObj, UIntToString(nifIDfrom) +logValType+ UIntToString(blockIDfrom));
				dPrintAndLog("NiAVObjectCopyCollisionObject","Collision object successfully copied.\n");
			}
			catch (std::exception e) {
				*result = 0;
				dPrintAndLog("NiAVObjectCopyCollisionObject",e.what());
			}
		}
		else
			dPrintAndLog("NiAVObjectCopyCollisionObject","Nif to copy to not found.\n");
	}
	else
		dPrintAndLog("NiAVObjectCopyCollisionObject","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiAVObjectCopyCollisionObject,
	NiAVObjCopyCollObj,
	"Copies the collision object of the first Nif as the collision object of the NiAVObject of the second Nif.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

UInt32 Util_NiAVObjectAddProperty(NifFile* nifPtr, Niflib::NiAVObjectRef avObj, UInt32 typeID, const string& name) {
	Niflib::NiPropertyRef nuProp = Niflib::DynamicCast<Niflib::NiProperty>(getNiflibType(typeID)->Create());

	if ( nuProp ) {
		nuProp->SetName(name);
		nuProp->internal_block_number = nifPtr->nifList.size();
		avObj->AddProperty(nuProp);
		nifPtr->nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(nuProp));
		return nuProp->internal_block_number;
	}
	else
		throw std::exception("Passed type is not derived from NiProperty.");
}

UInt32 Util_NiAVObjectCopyCollision(NifFile* nifFromPtr, UInt32 blockIDfrom, NifFile* nifToPtr, UInt32 blockIDto) {
	try {
		if ( nifFromPtr->root && nifToPtr->root ) {
			if ( nifToPtr->editable ) {
				if ( blockIDfrom < nifFromPtr->nifList.size() && blockIDto < nifToPtr->nifList.size() ) {
					Niflib::NiNodeRef avObj = Niflib::DynamicCast<Niflib::NiNode>(nifToPtr->nifList[blockIDto]);
					Niflib::NiObjectRef coll = nifFromPtr->nifList[blockIDfrom];
					if ( avObj && coll && coll->GetType().IsDerivedType(Niflib::NiCollisionObject::TYPE) ) {
						std::stringstream* nifStream = new std::stringstream(std::ios::binary|std::ios::in|std::ios::out);
						Niflib::WriteNifTree(*nifStream, coll, *(nifFromPtr->headerInfo));
						vector<Niflib::NiObjectRef> copiedBranch = Niflib::ReadNifList(*nifStream, nifFromPtr->headerInfo);
						if ( !(copiedBranch.empty()) ) {
							Niflib::NiCollisionObjectRef collCopy = Niflib::DynamicCast<Niflib::NiCollisionObject>(copiedBranch[0]);
							if ( collCopy ) {
								UInt32 copiedStartIndex = nifToPtr->nifList.size();
								for ( vector<Niflib::NiObjectRef>::iterator i = copiedBranch.begin(); i != copiedBranch.end(); ++i ) {
									(*i)->internal_block_number = nifToPtr->nifList.size();
									nifToPtr->nifList.push_back(*i);
								}
								if ( avObj->GetCollisionObject() )
									avObj->GetCollisionObject()->SetTarget((Niflib::NiAVObject*)NULL);
								avObj->SetCollisionObject(collCopy);
								return copiedStartIndex;
							}
							else
								throw std::exception("Could not find copied collision object.");
						}
						else
							throw std::exception("Copied branch is empty.");
					}
					else
						throw std::exception("Not a NiAVObject.");
				}
				else
					throw std::exception("Nif block index out of bounds.");
			}
			else
				throw std::exception("Nif to copy to not editable.");
		}
		else
			throw std::exception("Nif not found.");
	}
	catch (std::exception e) {
		throw std::exception(("Exception \""+string(e.what())+"\" thrown\n").c_str());
	}
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

				case kNiAVObjAct_SetCollMode:
					avObj->SetCollisionMode((Niflib::NiAVObject::CollisionType)StringToUInt(val));
					dPrintAndLog("NifLoad - NiAVObject","NiAVObject collision mode change loaded.");
					break;

				case kNiAVObjAct_ClrCollObj:
					if ( avObj->GetCollisionObject() )
						avObj->GetCollisionObject()->SetTarget((Niflib::NiAVObject*)NULL);
					avObj->SetCollisionObject((Niflib::NiCollisionObject*)NULL);
					dPrintAndLog("NifLoad - NiAVObject","NiAVObject collision object cleared.");
					break;

				case kNiAVObjAct_CopyCollObj:
					try {
						string::size_type i = val.find(logValType);
						UInt32 nifIDfrom = StringToUInt(val.substr(0, i));
						NifFile* nifFromPtr = NULL;
						if ( NifFile::getRegNif(modID, nifIDfrom, nifFromPtr) ) {
							UInt32 blockIDfrom = StringToUInt(val.substr(i+1));
							Util_NiAVObjectCopyCollision(nifFromPtr, blockIDfrom, this, block);
							dPrintAndLog("NifLoad - NiAVObject","Collision object (block #"+UIntToString(blockIDfrom)+" of nif #"+UIntToString(modID)+"-"+UIntToString(nifIDfrom)+") copied.");
						}
						else
							dPrintAndLog("NifLoad - NiAVObject","\n\n\t\tNif to copy from not found! Loaded nif will be incorrect!\n");
					}
					catch (std::exception e) {
						dPrintAndLog("NifLoad - NiAVObject","\n\n\t\t"+string(e.what())+"\t\tLoaded nif will be incorrect!\n");
					}
					break;

				case kNiAVObjAct_SetFlags:
				case kNiAVObjAct_SetVel:
				case kNiAVObjAct_SetVis:
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
