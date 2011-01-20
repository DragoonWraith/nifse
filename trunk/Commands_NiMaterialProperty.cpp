#include "Commands_NiMaterialProperty.h"

#include "obj/NiMaterialProperty.h"

static bool Cmd_NiMaterialPropertyGetTransparency_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetTransparency","Getting the transparency setting of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							*result = matPr->GetTransparency();
							dPrintAndLog("NiMaterialPropertyGetTransparency","Returning "+FloatToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetTransparency","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetTransparency","Not a NiMaterialProperty.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetTransparency","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetTransparency","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetTransparency","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetTransparency","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetTransparency,
	NiMatPropGetTransp,
	"Returns the transparency setting of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertyGetAmbientColor_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetAmbientColor","Getting the ambient color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							Niflib::Color3 color = matPr->GetAmbientColor();
							const char* keys[3] = { "r", "g", "b" };
							OBSEElement values[3] = { color.r, color.g, color.b };
							arr = arrInterface->CreateStringMap(keys, values, 3, scriptObj);
							if ( arr )
								dPrintAndLog("NiMaterialPropertyGetAmbientColor","Returning "+VectorToString(color)+".");
							else
								dPrintAndLog("NiMaterialPropertyGetAmbientColor","Failed to create array.");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetAmbientColor","Exception \""+string(e.what())+"\" thrown.");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetAmbientColor","Not a NiMaterialProperty.");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetAmbientColor","Block index out of range.");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetAmbientColor","Nif root bad.");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetAmbientColor","Could not find Nif.");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetAmbientColor","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiMaterialPropertyGetAmbientColor","Returning ExtraData's array.\n");
	else
		dPrintAndLog("NiMaterialPropertyGetAmbientColor","Failed to return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetAmbientColor,
	NiMatPropGetAmbColor,
	"Returns the ambient color of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertyGetDiffuseColor_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Getting the diffuse color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							Niflib::Color3 color = matPr->GetDiffuseColor();
							const char* keys[3] = { "r", "g", "b" };
							OBSEElement values[3] = { color.r, color.g, color.b };
							arr = arrInterface->CreateStringMap(keys, values, 3, scriptObj);
							if ( arr )
								dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Returning "+VectorToString(color)+".");
							else
								dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Failed to create array.");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Exception \""+string(e.what())+"\" thrown.");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Not a NiMaterialProperty.");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Block index out of range.");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Nif root bad.");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Could not find Nif.");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Returning ExtraData's array.\n");
	else
		dPrintAndLog("NiMaterialPropertyGetDiffuseColor","Failed to return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetDiffuseColor,
	NiMatPropGetDifColor,
	"Returns the diffuse color of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertyGetEmissiveColor_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Getting the emissive color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							Niflib::Color3 color = matPr->GetEmissiveColor();
							const char* keys[3] = { "r", "g", "b" };
							OBSEElement values[3] = { color.r, color.g, color.b };
							arr = arrInterface->CreateStringMap(keys, values, 3, scriptObj);
							if ( arr )
								dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Returning "+VectorToString(color)+".");
							else
								dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Failed to create array.");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Exception \""+string(e.what())+"\" thrown.");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Not a NiMaterialProperty.");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Block index out of range.");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Nif root bad.");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Could not find Nif.");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Returning ExtraData's array.\n");
	else
		dPrintAndLog("NiMaterialPropertyGetEmissiveColor","Failed to return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetEmissiveColor,
	NiMatPropGetEmiColor,
	"Returns the emissive color of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertyGetSpecularColor_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetSpecularColor","Getting the specular color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							Niflib::Color3 color = matPr->GetSpecularColor();
							const char* keys[3] = { "r", "g", "b" };
							OBSEElement values[3] = { color.r, color.g, color.b };
							arr = arrInterface->CreateStringMap(keys, values, 3, scriptObj);
							if ( arr )
								dPrintAndLog("NiMaterialPropertyGetSpecularColor","Returning "+VectorToString(color)+".");
							else
								dPrintAndLog("NiMaterialPropertyGetSpecularColor","Failed to create array.");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetSpecularColor","Exception \""+string(e.what())+"\" thrown.");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetSpecularColor","Not a NiMaterialProperty.");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetSpecularColor","Block index out of range.");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetSpecularColor","Nif root bad.");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetSpecularColor","Could not find Nif.");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetSpecularColor","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiMaterialPropertyGetSpecularColor","Returning ExtraData's array.\n");
	else
		dPrintAndLog("NiMaterialPropertyGetSpecularColor","Failed to return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetSpecularColor,
	NiMatPropGetSpecColor,
	"Returns the specular color of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertyGetGlossiness_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertyGetGlossiness","Getting the glossiness of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
					if ( matPr ) {
						try {
							*result = matPr->GetGlossiness();
							dPrintAndLog("NiMaterialPropertyGetGlossiness","Returning "+FloatToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = 0;
							dPrintAndLog("NiMaterialPropertyGetGlossiness","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiMaterialPropertyGetGlossiness","Not a NiMaterialProperty.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertyGetGlossiness","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertyGetGlossiness","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertyGetGlossiness","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertyGetGlossiness","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertyGetGlossiness,
	NiMatPropGetGloss,
	"Returns the glossiness of the given NiMaterialProperty.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetTransparency_Execute(COMMAND_ARGS) {
	*result = 0;

	float transp = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &transp, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetTransparency","Setting the transparency setting of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								matPr->SetTransparency(transp);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetTransp, FloatToString(transp), true);
								dPrintAndLog("NiMaterialPropertySetTransparency","Transparency set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetTransparency","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetTransparency","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetTransparency","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetTransparency","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetTransparency","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetTransparency","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetTransparency","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetTransparency,
	NiMatPropSetTransp,
	"Sets the transparency setting of the given NiMaterialProperty.",
	0,
	kParams_OneFloat_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetAmbientColor_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetAmbientColor","Setting the ambient color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								Niflib::Color3 color = Niflib::Color3();
								OBSEElement val = OBSEElement();
								if ( !arrInterface->GetElement(arr, "r", val) )
									if ( !arrInterface->GetElement(arr, (double)0, val ) )
										throw std::exception("Red value not found.");
								color.r = val.Number();
								if ( !arrInterface->GetElement(arr, "g", val) )
									if ( !arrInterface->GetElement(arr, (double)1, val ) )
										throw std::exception("Green value not found.");
								color.g = val.Number();
								if ( !arrInterface->GetElement(arr, "b", val) )
									if ( !arrInterface->GetElement(arr, (double)2, val ) )
										throw std::exception("Blue value not found.");
								color.b = val.Number();
								matPr->SetAmbientColor(color);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetAmbColor, VectorToString(color), true);
								dPrintAndLog("NiMaterialPropertySetAmbientColor","Ambient color set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetAmbientColor","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetAmbientColor","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetAmbientColor","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetAmbientColor","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetAmbientColor","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetAmbientColor","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetAmbientColor","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetAmbientColor,
	NiMatPropSetAmbColor,
	"Sets the ambient color of the given NiMaterialProperty.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetDiffuseColor_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetDiffuseColor","Setting the diffuse color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								Niflib::Color3 color = Niflib::Color3();
								OBSEElement val = OBSEElement();
								if ( !arrInterface->GetElement(arr, "r", val) )
									if ( !arrInterface->GetElement(arr, (double)0, val ) )
										throw std::exception("Red value not found.");
								color.r = val.Number();
								if ( !arrInterface->GetElement(arr, "g", val) )
									if ( !arrInterface->GetElement(arr, (double)1, val ) )
										throw std::exception("Green value not found.");
								color.g = val.Number();
								if ( !arrInterface->GetElement(arr, "b", val) )
									if ( !arrInterface->GetElement(arr, (double)2, val ) )
										throw std::exception("Blue value not found.");
								color.b = val.Number();
								matPr->SetDiffuseColor(color);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetDifColor, VectorToString(color), true);
								dPrintAndLog("NiMaterialPropertySetDiffuseColor","Diffuse color set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetDiffuseColor","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetDiffuseColor","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetDiffuseColor","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetDiffuseColor","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetDiffuseColor","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetDiffuseColor","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetDiffuseColor","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetDiffuseColor,
	NiMatPropSetDifColor,
	"Sets the diffuse color of the given NiMaterialProperty.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetEmissiveColor_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetEmissiveColor","Setting the emissive color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								Niflib::Color3 color = Niflib::Color3();
								OBSEElement val = OBSEElement();
								if ( !arrInterface->GetElement(arr, "r", val) )
									if ( !arrInterface->GetElement(arr, (double)0, val ) )
										throw std::exception("Red value not found.");
								color.r = val.Number();
								if ( !arrInterface->GetElement(arr, "g", val) )
									if ( !arrInterface->GetElement(arr, (double)1, val ) )
										throw std::exception("Green value not found.");
								color.g = val.Number();
								if ( !arrInterface->GetElement(arr, "b", val) )
									if ( !arrInterface->GetElement(arr, (double)2, val ) )
										throw std::exception("Blue value not found.");
								color.b = val.Number();
								matPr->SetEmissiveColor(color);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetEmiColor, VectorToString(color), true);
								dPrintAndLog("NiMaterialPropertySetEmissiveColor","Emissive color set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetEmissiveColor","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetEmissiveColor","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetEmissiveColor","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetEmissiveColor","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetEmissiveColor","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetEmissiveColor","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetEmissiveColor","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetEmissiveColor,
	NiMatPropSetEmiColor,
	"Sets the emissive color of the given NiMaterialProperty.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetSpecularColor_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetSpecularColor","Setting the specular color of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								Niflib::Color3 color = Niflib::Color3();
								OBSEElement val = OBSEElement();
								if ( !arrInterface->GetElement(arr, "r", val) )
									if ( !arrInterface->GetElement(arr, (double)0, val ) )
										throw std::exception("Red value not found.");
								color.r = val.Number();
								if ( !arrInterface->GetElement(arr, "g", val) )
									if ( !arrInterface->GetElement(arr, (double)1, val ) )
										throw std::exception("Green value not found.");
								color.g = val.Number();
								if ( !arrInterface->GetElement(arr, "b", val) )
									if ( !arrInterface->GetElement(arr, (double)2, val ) )
										throw std::exception("Blue value not found.");
								color.b = val.Number();
								matPr->SetSpecularColor(color);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetSpecColor, VectorToString(color), true);
								dPrintAndLog("NiMaterialPropertySetSpecularColor","Specular color set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetSpecularColor","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetSpecularColor","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetSpecularColor","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetSpecularColor","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetSpecularColor","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetSpecularColor","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetSpecularColor","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetSpecularColor,
	NiMatPropSetSpecColor,
	"Sets the specular color of the given NiMaterialProperty.",
	0,
	kParams_OneArray_OneInt_OneOptionalInt
);

static bool Cmd_NiMaterialPropertySetGlossiness_Execute(COMMAND_ARGS) {
	*result = 0;

	float gloss = 0;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &gloss, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiMaterialPropertySetGlossiness","Setting the glossiness of NiMaterialProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifPtr->nifList[blockID]);
						if ( matPr ) {
							try {
								matPr->SetGlossiness(gloss);
								*result = 1;
								nifPtr->logChange(blockID, kNiflibType_NiMaterialProperty, kNiMatPropAct_SetGloss, FloatToString(gloss), true);
								dPrintAndLog("NiMaterialPropertySetGlossiness","Glossiness set.\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiMaterialPropertySetGlossiness","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiMaterialPropertySetGlossiness","Not a NiMaterialProperty.\n");
					}
					else
						dPrintAndLog("NiMaterialPropertySetGlossiness","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiMaterialPropertySetGlossiness","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiMaterialPropertySetGlossiness","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiMaterialPropertySetGlossiness","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiMaterialPropertySetGlossiness","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiMaterialPropertySetGlossiness,
	NiMatPropSetGloss,
	"Sets the glossiness of the given NiMaterialProperty.",
	0,
	kParams_OneFloat_OneInt_OneOptionalInt
);

void NifFile::loadChNiMatProperty(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::NiMaterialPropertyRef matPr = Niflib::DynamicCast<Niflib::NiMaterialProperty>(nifList[block]);
		if ( matPr ) {
			switch (act) {
				case kNiMatPropAct_SetTransp:
					matPr->SetTransparency(StringToFloat(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty transparency change loaded.");
					break;

				case kNiMatPropAct_SetAmbColor:
					matPr->SetAmbientColor(StringToVectorC3(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty ambient color change loaded.");
					break;

				case kNiMatPropAct_SetDifColor:
					matPr->SetDiffuseColor(StringToVectorC3(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty diffuse color change loaded.");
					break;

				case kNiMatPropAct_SetEmiColor:
					matPr->SetEmissiveColor(StringToVectorC3(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty emissive color change loaded.");
					break;

				case kNiMatPropAct_SetSpecColor:
					matPr->SetSpecularColor(StringToVectorC3(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty specular color change loaded.");
					break;
					
				case kNiMatPropAct_SetGloss:
					matPr->SetGlossiness(StringToFloat(val));
					dPrintAndLog("NifLoad - NiMaterialProperty","NiMaterialProperty glossiness change loaded.");
					break;

				default:
					dPrintAndLog("NifLoad - NiMaterialProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiMaterialProperty","\n\n\t\tIndicated block is not a NiMaterialProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiMaterialProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
