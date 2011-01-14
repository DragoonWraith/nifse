#include "Commands_NiTexturingProperty.h"

#include "obj/NiTexturingProperty.h"
#include "gen/TexDesc.h"
#include "obj/NiSourceTexture.h"

static bool Cmd_NiTexturingPropertyGetTextureCount_Execute(COMMAND_ARGS) {
	*result = -1;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureCount","Getting the texture count of NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						try {
							*result = texPr->GetTextureCount();
							dPrintAndLog("NiTexturingPropertyGetTextureCount","Returning "+UIntToString(*result)+".\n");
						}
						catch (std::exception e) {
							*result = -1;
							dPrintAndLog("NiTexturingPropertyGetTextureCount","Exception \""+string(e.what())+"\" thrown.\n");
						}
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureCount","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureCount","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureCount","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureCount","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureCount","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureCount,
	NiTexPropGetTexCount,
	"Returns the number of texture slots used by the property. Does not guarantee that every slot is filled.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureCount_Execute(COMMAND_ARGS) {
	*result = 0;

	int texCount = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texCount, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureCount","Setting the texture count of NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		if ( Niflib::BASE_MAP <= texCount && texCount <= Niflib::DECAL_3_MAP ) {
			NifFile* nifPtr = NULL;
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
							if ( texPr ) {
								try {
									texPr->SetTextureCount(texCount);
									*result = 1;
									dPrintAndLog("NiTexturingPropertySetTextureCount","Texture count set.\n");
									nifPtr->logChange(blockID, kNiflibType_NiTexturingProperty, kNiTexingPropAct_SetTexCount, UIntToString(texCount), true);
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiTexturingPropertySetTextureCount","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureCount","Not a NiTexturingProperty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureCount","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureCount","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureCount","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureCount","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureCount","Impossible texture count; must be between 0 and 11, inclusive.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureCount","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureCount,
	NiTexPropSetTexCount,
	"Sets the number of texture slots used by the property. Does not require that every slot is filled.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyHasTexture_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyHasTexture","Getting whether texture slot #"+UIntToString(texSlot)+" is used by the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->HasTexture(texSlot);
								dPrintAndLog("NiTexturingPropertyHasTexture","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiTexturingPropertyHasTexture","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyHasTexture","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyHasTexture","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyHasTexture","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyHasTexture","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyHasTexture","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyHasTexture","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyHasTexture,
	NiTexPropHasTex,
	"Gets whether there is a texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureSource_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureSource","Getting texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							if ( texPr->HasTexture(texSlot) ) {
								try {
									Niflib::TexDesc texDesc = texPr->GetTexture(texSlot);
									Niflib::NiSourceTextureRef texSrc = texDesc.source;
									if ( texSrc ) {
										*result = texSrc->internal_block_number;
										dPrintAndLog("NiTexturingPropertyGetTextureSource","Returning block #"+UIntToString(*result)+".\n");
									}
									else
										dPrintAndLog("NiTexturingPropertyGetTextureSource","Bad texture source.\n");
								}
								catch (std::exception e) {
									*result = -1;
									dPrintAndLog("NiTexturingPropertyGetTextureSource","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiTexturingPropertyGetTextureSource","Texture slot is empty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureSource","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureSource","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureSource","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureSource","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureSource","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureSource","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureSource,
	NiTexPropGetTex,
	"Gets the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyAddTextureSource_Execute(COMMAND_ARGS) {
	*result = 0;

	char file[kMaxMessageLength] = "";
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &file, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyAddTextureSource","Adding texture \""+string(file)+"\" to slot #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							if ( !(texPr->HasTexture(texSlot)) ) {
								Niflib::TexDesc desc;
								desc.source = Niflib::DynamicCast<Niflib::NiSourceTexture>(Niflib::NiSourceTexture::Create());
								if ( desc.source ) {
									try {
										desc.source->SetExternalTexture(string("textures\\")+file);
										desc.source->internal_block_number = nifPtr->nifList.size();
										texPr->SetTexture(texSlot, desc);
										nifPtr->nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(desc.source));
										nifPtr->logChange(texPr->internal_block_number, kNiflibType_NiTexturingProperty, kNiTexingPropAct_AddTex, UIntToString(texSlot)+logValType+file);
										*result = desc.source->internal_block_number;
										dPrintAndLog("NiTexturingPropertyAddTextureSource","Added new texture.\n");
									}
									catch (std::exception e) {
										*result = -1;
										dPrintAndLog("NiTexturingPropertyAddTextureSource","Exception \""+string(e.what())+"\" thrown.\n");
									}
								}
								else
									dPrintAndLog("NiTexturingPropertyAddTextureSource","Could not create new texture source block.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertyAddTextureSource","Texture slot already filled.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertyAddTextureSource","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyAddTextureSource","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyAddTextureSource","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyAddTextureSource","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyAddTextureSource","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyAddTextureSource","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyAddTextureSource,
	NiTexPropAddTex,
	"Adds a texture in the property's texture slot.",
	0,
	kParams_OneString_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyDeleteTextureSource_Execute(COMMAND_ARGS) {
	*result = 0;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Deleting a texture from slot #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							if ( texPr->HasTexture(texSlot) ) {
								try {
									texPr->ClearTexture(texSlot);
									*result = 1;
									dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Texture source deleted.\n");
									nifPtr->logChange(blockID, kNiflibType_NiTexturingProperty, kNiTexingPropAct_DelTex, UIntToString(texSlot));
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Texture slot empty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyDeleteTextureSource","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyDeleteTextureSource,
	NiTexPropDelTex,
	"Deletes a texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureClampMode_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Getting the clamp mode of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->GetTexture(texSlot).clampMode;
								dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Returning "+UIntToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureClampMode,
	NiTexPropGetTexClamp,
	"Gets the clamp mode of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureFilterMode_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Getting the filter mode of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->GetTexture(texSlot).filterMode;
								dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Returning "+UIntToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureFilterMode,
	NiTexPropGetTexFilter,
	"Gets the filter mode of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureUVSet_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Getting the UV set on texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->GetTexture(texSlot).uvSet;
								dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Returning "+UIntToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureUVSet,
	NiTexPropGetTexUV,
	"Gets the UV set of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyTextureHasTransform_Execute(COMMAND_ARGS) {
	*result = -1;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyTextureHasTransform","Getting whether transform applies to texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->GetTexture(texSlot).hasTextureTransform;
								dPrintAndLog("NiTexturingPropertyTextureHasTransform","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
							}
							catch (std::exception e) {
								*result = -1;
								dPrintAndLog("NiTexturingPropertyTextureHasTransform","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyTextureHasTransform","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyTextureHasTransform","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyTextureHasTransform","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyTextureHasTransform","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyTextureHasTransform","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyTextureHasTransform","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyTextureHasTransform,
	NiTexPropTexHasTransf,
	"Gets whether the texture in the property's texture slot has a transform applied.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureTranslation_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Getting the translation of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								map<string,OBSEElement> omap;
								omap[string("u")] = texPr->GetTexture(texSlot).translation.u;
								omap[string("v")] = texPr->GetTexture(texSlot).translation.v;
								arr = StringMapFromStdMap(omap, scriptObj);
							}
							catch (std::exception e) {
								arr = NULL;
								dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Exception \""+string(e.what())+"\" thrown.");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Texture slot out of range.");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Not a NiTexturingProperty.");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Block index out of range.");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Nif root bad.");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Could not find Nif.");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Returning TexturingProperty's translation.\n");
	else
		dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureTranslation,
	NiTexPropGetTexTransl,
	"Gets the translation of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureTiling_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Getting the tiling of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								map<string,OBSEElement> omap;
								omap[string("u")] = texPr->GetTexture(texSlot).tiling.u;
								omap[string("v")] = texPr->GetTexture(texSlot).tiling.v;
								arr = StringMapFromStdMap(omap, scriptObj);
							}
							catch (std::exception e) {
								arr = NULL;
								dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Exception \""+string(e.what())+"\" thrown.");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureTiling","Texture slot out of range.");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureTiling","Not a NiTexturingProperty.");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureTiling","Block index out of range.");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureTiling","Nif root bad.");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureTiling","Could not find Nif.");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Returning TexturingProperty's tiling.\n");
	else
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureTiling,
	NiTexPropGetTexTiling,
	"Gets the center offset of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureRotation_Execute(COMMAND_ARGS) {
	*result = 0;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureRotation","Getting the rotation on texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								*result = texPr->GetTexture(texSlot).wRotation;
								dPrintAndLog("NiTexturingPropertyGetTextureRotation","Returning "+FloatToString(*result)+".\n");
							}
							catch (std::exception e) {
								*result = 0;
								dPrintAndLog("NiTexturingPropertyGetTextureRotation","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureRotation","Texture slot out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureRotation","Not a NiTexturingProperty.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureRotation","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureRotation","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureRotation","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureRotation","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureRotation,
	NiTexPropGetTexRot,
	"Gets the rotation of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureCenterOffset_Execute(COMMAND_ARGS) {
	*result = 0;
	OBSEArray* arr = NULL;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Getting the center offset of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							try {
								map<string,OBSEElement> omap;
								omap[string("u")] = texPr->GetTexture(texSlot).centerOffset.u;
								omap[string("v")] = texPr->GetTexture(texSlot).centerOffset.v;
								arr = StringMapFromStdMap(omap, scriptObj);
							}
							catch (std::exception e) {
								arr = NULL;
								dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Exception \""+string(e.what())+"\" thrown.\n");
							}
						}
						else
							dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Texture slot out of range.");
					}
					else
						dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Not a NiTexturingProperty.");
				}
				else
					dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Block index out of range.");
			}
			else
				dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Nif root bad.");
		}
		else
			dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Could not find Nif.");
	}
	else
		dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Error extracting arguments.");

	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Returning TexturingProperty's center offset.\n");
	else
		dPrintAndLog("NiTexturingPropertyGetTextureCenterOffset","Failed to create and return array.\n");
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureCenterOffset,
	NiTexPropGetTexCenOff,
	"Gets the center offset of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureClampMode_Execute(COMMAND_ARGS) {
	*result = 0;

	int clampMode = -1;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &clampMode, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureClampMode","Setting the clamp mode of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( Niflib::CLAMP_S_CLAMP_T <= clampMode && clampMode <= Niflib::WRAP_S_WRAP_T ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
							if ( texPr ) {
								if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
									try {
										Niflib::TexDesc desc = texPr->GetTexture(texSlot);
										desc.clampMode = (Niflib::TexClampMode)clampMode;
										texPr->SetTexture(texSlot, desc);
										*result = 1;
										nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetClampMode,UIntToString(texSlot)+logValType+UIntToString(clampMode),true);
										dPrintAndLog("NiTexturingPropertySetTextureClampMode","Clamp mode set.\n");
									}
									catch (std::exception e) {
										*result = 0;
										dPrintAndLog("NiTexturingPropertySetTextureClampMode","Exception \""+string(e.what())+"\" thrown.\n");
									}
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureClampMode","Texture slot out of range.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureClampMode","Not a NiTexturingProperty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureClampMode","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureClampMode","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureClampMode","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureClampMode","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureClampMode","Bad clamp mode; clamp mode must be from 0-3, inclusive.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureClampMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureClampMode,
	NiTexPropSetTexClamp,
	"Sets the clamp mode of the texture in the property's texture slot.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureFilterMode_Execute(COMMAND_ARGS) {
	*result = 0;

	int filterMode = -1;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &filterMode, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Setting the filter mode of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( Niflib::FILTER_NEAREST <= filterMode && filterMode <= Niflib::FILTER_BILERP_MIPNEAREST ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
							if ( texPr ) {
								if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
									try {
										Niflib::TexDesc desc = texPr->GetTexture(texSlot);
										desc.filterMode = (Niflib::TexFilterMode)filterMode;
										texPr->SetTexture(texSlot, desc);
										*result = 1;
										nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetFilterMode,UIntToString(texSlot)+logValType+UIntToString(filterMode),true);
										dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Filter mode set.\n");
									}
									catch (std::exception e) {
										*result = 0;
										dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Exception \""+string(e.what())+"\" thrown.\n");
									}
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Texture slot out of range.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Not a NiTexturingProperty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Bad filter mode.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureFilterMode","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureFilterMode,
	NiTexPropSetTexFilter,
	"Sets the filter mode of the texture in the property's texture slot.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureUVSet_Execute(COMMAND_ARGS) {
	*result = 0;

	int uvSet = -1;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &uvSet, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureUVSet","Setting the UV set on texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( uvSet >= 0 ) {
			if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
				if ( nifPtr->root ) {
					if ( nifPtr->editable ) {
						if ( blockID < nifPtr->nifList.size() ) {
							Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
							if ( texPr ) {
								if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
									try {
										Niflib::TexDesc desc = texPr->GetTexture(texSlot);
										desc.uvSet = uvSet;
										texPr->SetTexture(texSlot, desc);
										*result = 1;
										nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetUVSet,UIntToString(texSlot)+logValType+UIntToString(uvSet),true);
										dPrintAndLog("NiTexturingPropertySetTextureUVSet","UV Set set.\n");
									}
									catch (std::exception e) {
										*result = 0;
										dPrintAndLog("NiTexturingPropertySetTextureUVSet","Exception \""+string(e.what())+"\" thrown.\n");
									}
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureUVSet","Texture slot out of range.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureUVSet","Not a NiTexturingProperty.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureUVSet","Block index out of range.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureUVSet","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureUVSet","Nif root bad.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureUVSet","Could not find Nif.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureUVSet","Bad UV set.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureUVSet","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureUVSet,
	NiTexPropSetTexUV,
	"Sets the UV set of the texture in the property's texture slot.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureHasTransform_Execute(COMMAND_ARGS) {
	*result = 0;

	int hasTransf = -1;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &hasTransf, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Setting whether transform applies to texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
						if ( texPr ) {
							if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
								try {
									Niflib::TexDesc desc = texPr->GetTexture(texSlot);
									desc.hasTextureTransform = (hasTransf!=0);
									texPr->SetTexture(texSlot, desc);
									*result = 1;
									nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetHasTransf,UIntToString(texSlot)+logValType+UIntToString(hasTransf),true);
									dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Transform use set.\n");
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Texture slot out of range.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Not a NiTexturingProperty.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureHasTransform","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureHasTransform,
	NiTexPropSetTexHasTransf,
	"Sets whether the texture in the property's texture slot has a transform applied.",
	0,
	kParams_ThreeInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureTranslation_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureTranslation","Setting the translation of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 2 ) {
				NifFile* nifPtr = NULL;
				if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
					if ( nifPtr->editable ) {
						if ( nifPtr->root ) {
							if ( blockID < nifPtr->nifList.size() ) {
								Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
								if ( texPr ) {
									if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
										try {
											OBSEElement ele;
											arrInterface->GetElement(arr, (double)0, ele);
											double u = ele.Number();
											arrInterface->GetElement(arr, (double)1, ele);
											double v = ele.Number();
											texPr->GetTexture(texSlot).translation.Set(u, v);
											*result = 1;
											nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetTransl,UIntToString(texSlot)+logValType+VectorToString(texPr->GetTexture(texSlot).translation),true);
											dPrintAndLog("NiTexturingPropertySetTextureTranslation","Texture translation set.\n");
										}
										catch (std::exception e) {
											*result = 0;
											dPrintAndLog("NiTexturingPropertySetTextureTranslation","Exception \""+string(e.what())+"\" thrown.\n");
										}
									}
									else
										dPrintAndLog("NiTexturingPropertySetTextureTranslation","Texture slot out of range.\n");
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureTranslation","Not a NiTexturingProperty.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureTranslation","Block index out of range.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureTranslation","Nif root bad.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureTranslation","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureTranslation","Could not find Nif.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureTranslation","Array size must be 2.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureTranslation","Array not found.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureTranslation","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureTranslation,
	NiTexPropSetTexTransl,
	"Sets the translation of the texture in the property's texture slot.",
	0,
	kParams_OneArray_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureTiling_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureTiling","Setting the tiling of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 2 ) {
				NifFile* nifPtr = NULL;
				if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
					if ( nifPtr->editable ) {
						if ( nifPtr->root ) {
							if ( blockID < nifPtr->nifList.size() ) {
								Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
								if ( texPr ) {
									if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
										try {
											OBSEElement ele;
											arrInterface->GetElement(arr, (double)0, ele);
											double u = ele.Number();
											arrInterface->GetElement(arr, (double)1, ele);
											double v = ele.Number();
											texPr->GetTexture(texSlot).tiling.Set(u, v);
											*result = 1;
											nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetTiling,UIntToString(texSlot)+logValType+VectorToString(texPr->GetTexture(texSlot).translation),true);
											dPrintAndLog("NiTexturingPropertySetTextureTiling","Texture tiling set.\n");
										}
										catch (std::exception e) {
											*result = 0;
											dPrintAndLog("NiTexturingPropertySetTextureTiling","Exception \""+string(e.what())+"\" thrown.\n");
										}
									}
									else
										dPrintAndLog("NiTexturingPropertySetTextureTiling","Texture slot out of range.\n");
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureTiling","Not a NiTexturingProperty.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureTiling","Block index out of range.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureTiling","Nif root bad.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureTiling","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureTiling","Could not find Nif.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureTiling","Array size must be 2.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureTiling","Array not found.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureTiling","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureTiling,
	NiTexPropSetTexTiling,
	"Sets the center offset of the texture in the property's texture slot.",
	0,
	kParams_OneArray_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureRotation_Execute(COMMAND_ARGS) {
	*result = 0;

	float rotation = 0;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &rotation, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureRotation","Setting the rotation on texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
						if ( texPr ) {
							if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
								try {
									Niflib::TexDesc desc = texPr->GetTexture(texSlot);
									desc.wRotation = rotation;
									texPr->SetTexture(texSlot, desc);
									*result = 1;
									nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetRot,UIntToString(texSlot)+logValType+FloatToString(rotation),true);
									dPrintAndLog("NiTexturingPropertySetTextureRotation","Texture rotation set.\n");
								}
								catch (std::exception e) {
									*result = 0;
									dPrintAndLog("NiTexturingPropertySetTextureRotation","Exception \""+string(e.what())+"\" thrown.\n");
								}
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureRotation","Texture slot out of range.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureRotation","Not a NiTexturingProperty.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureRotation","Block index out of range.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureRotation","Nif not editable.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureRotation","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureRotation","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureRotation","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureRotation,
	NiTexPropSetTexRot,
	"Sets the rotation of the texture in the property's texture slot.",
	0,
	kParams_OneFloat_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertySetTextureCenterOffset_Execute(COMMAND_ARGS) {
	*result = 0;

	OBSEArray* arr = NULL;
	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &arr, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Setting the center offset of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		if ( arr ) {
			UInt32 arrSize = arrInterface->GetArraySize(arr);
			if ( arrSize == 2 ) {
				NifFile* nifPtr = NULL;
				if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
					if ( nifPtr->editable ) {
						if ( nifPtr->root ) {
							if ( blockID < nifPtr->nifList.size() ) {
								Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
								if ( texPr ) {
									if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
										try {
											OBSEElement ele;
											arrInterface->GetElement(arr, (double)0, ele);
											double u = ele.Number();
											arrInterface->GetElement(arr, (double)1, ele);
											double v = ele.Number();
											texPr->GetTexture(texSlot).centerOffset.Set(u, v);
											*result = 1;
											nifPtr->logChange(blockID,kNiflibType_NiTexturingProperty,kNiTexingPropAct_SetCenOff,UIntToString(texSlot)+logValType+VectorToString(texPr->GetTexture(texSlot).translation),true);
											dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Texture center offset set.\n");
										}
										catch (std::exception e) {
											*result = 0;
											dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Exception \""+string(e.what())+"\" thrown.\n");
										}
									}
									else
										dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Texture slot out of range.\n");
								}
								else
									dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Not a NiTexturingProperty.\n");
							}
							else
								dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Block index out of range.\n");
						}
						else
							dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Nif root bad.\n");
					}
					else
						dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Nif not editable.\n");
				}
				else
					dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Could not find Nif.\n");
			}
			else
				dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Array size must be 2.\n");
		}
		else
			dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Array not found.\n");
	}
	else
		dPrintAndLog("NiTexturingPropertySetTextureCenterOffset","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertySetTextureCenterOffset,
	NiTexPropSetTexCenOff,
	"Sets the center offset of the texture in the property's texture slot.",
	0,
	kParams_OneArray_TwoInts_OneOptionalInt
);

void NifFile::loadChNiTexturingProperty(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifList[block]);
		if ( texPr ) {
			switch (act) {
				case kNiTexingPropAct_SetTexCount:
					{
						UInt32 texCount = StringToUInt(val);
						texPr->SetTextureCount(texCount);
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture count change loaded.");
					break;

				case kNiTexingPropAct_SetClampMode:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).clampMode = Niflib::TexClampMode(StringToUInt(val.substr(i+1)));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture clamp mode change loaded.");
					break;

				case kNiTexingPropAct_SetFilterMode:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).filterMode = Niflib::TexFilterMode(StringToUInt(val.substr(i+1)));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture filter mode change loaded.");
					break;

				case kNiTexingPropAct_SetUVSet:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).uvSet = StringToUInt(val.substr(i+1));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture UV set change loaded.");
					break;

				case kNiTexingPropAct_SetHasTransf:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).hasTextureTransform = (StringToUInt(val.substr(i+1))!=0);
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture transform bool change loaded.");
					break;

				case kNiTexingPropAct_SetTransl:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).translation = StringToVectorT(val.substr(i+1));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture translation change loaded.");
					break;

				case kNiTexingPropAct_SetTiling:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).tiling = StringToVectorT(val.substr(i+1));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture tiling change loaded.");
					break;

				case kNiTexingPropAct_SetRot:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).wRotation = StringToFloat(val.substr(i+1));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture rotation change loaded.");
					break;

				case kNiTexingPropAct_SetCenOff:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						texPr->GetTexture(texSlot).centerOffset = StringToVectorT(val.substr(i+1));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture center offset change loaded.");
					break;

				case kNiTexingPropAct_AddTex:
					{
						string::size_type i = val.find(logValType);
						UInt32 texSlot = StringToUInt(val.substr(0, i));
						string file = val.substr(i+1);
						if ( !(texPr->HasTexture(texSlot)) ) {
							Niflib::TexDesc desc;
							desc.source = Niflib::DynamicCast<Niflib::NiSourceTexture>(Niflib::NiSourceTexture::Create());
							if ( desc.source ) {
								desc.source->SetExternalTexture(file);
								desc.source->internal_block_number = nifList.size();
								texPr->SetTexture(texSlot, desc);
								nifList.push_back(Niflib::StaticCast<Niflib::NiObject>(desc.source));
								dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture addition loaded.");
							}
							else
								dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tCould not create new texture source block! Loaded nif will be incorrect!\n");
						}
						else
							dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tTexture slot already filled! Loaded nif may be incorrect!\n");
					}
					break;

				case kNiTexingPropAct_DelTex:
					{
						UInt32 texSlot = StringToUInt(val);
						if ( texPr->HasTexture(texSlot) ) {
							texPr->ClearTexture(texSlot);
							dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture deletion loaded.");
						}
						else
							dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tTexture slot empty! Loaded nif will be incorrect!\n");
					}
					break;

				default:
					dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tIndicated block is not a NiTexturingProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiTexturingProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
