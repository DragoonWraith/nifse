#include "Commands_NiProperty.h"

#include "NiProperties.h"

#include "gen/TexDesc.h"
#include "obj/NiSourceTexture.h"

static bool Cmd_NiTexturingPropertyGetTextureCount_Execute(COMMAND_ARGS) {
	*result = 0;

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
						*result = texPr->GetTextureCount();
						dPrintAndLog("NiTexturingPropertyGetTextureCount","Returning "+UIntToString(*result)+".\n");
					}
				}
			}
		}
	}
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
								texPr->SetTextureCount(texCount);
								*result = 1;
								dPrintAndLog("NiTexturingPropertySetTextureCount","Texture count set.\n");
								nifPtr->logChange(blockID, kNiflibType_NiTexturingProperty, kNiTexingPropAct_SetTexCount, UIntToString(texCount), true);
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
	NiTexturingPropertySetTextureCount,
	NiTexPropSetTexCount,
	"Sets the number of texture slots used by the property. Does not require that every slot is filled.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyHasTexture_Execute(COMMAND_ARGS) {
	*result = 0;

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
							*result = texPr->HasTexture(texSlot);
							dPrintAndLog("NiTexturingPropertyHasTexture","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
						}
					}
				}
			}
		}
	}
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
	*result = 0;

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
								Niflib::TexDesc texDesc = texPr->GetTexture(texSlot);
								Niflib::NiSourceTextureRef texSrc = texDesc.source;
								if ( texSrc ) {
									*result = texSrc->internal_block_number;
									dPrintAndLog("NiTexturingPropertyGetTextureSource","Returning block #"+UIntToString(*result)+".\n");
								}
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
	NiTexturingPropertyGetTextureSource,
	NiTexPropGetTex,
	"Gets the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureClampMode_Execute(COMMAND_ARGS) {
	*result = 0;

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
							*result = texPr->GetTexture(texSlot).clampMode;
							dPrintAndLog("NiTexturingPropertyGetTextureClampMode","Returning "+UIntToString(*result)+".\n");
						}
					}
				}
			}
		}
	}
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
	*result = 0;

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
							*result = texPr->GetTexture(texSlot).filterMode;
							dPrintAndLog("NiTexturingPropertyGetTextureFilterMode","Returning "+UIntToString(*result)+".\n");
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureFilterMode,
	NiTexPropGetTexFilter,
	"Gets the filter mode of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureFlags_Execute(COMMAND_ARGS) {
	*result = 0;

	int texSlot = -1;
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &texSlot, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiTexturingPropertyGetTextureFlags","Getting the flags on texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							*result = texPr->GetTexture(texSlot).flags;
							dPrintAndLog("NiTexturingPropertyGetTextureFlags","Returning "+UIntToString(*result)+".\n");
						}
					}
				}
			}
		}
	}
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiTexturingPropertyGetTextureFlags,
	NiTexPropGetTexFlags,
	"Gets the flags of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

static bool Cmd_NiTexturingPropertyGetTextureUVSet_Execute(COMMAND_ARGS) {
	*result = 0;

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
							*result = texPr->GetTexture(texSlot).uvSet;
							dPrintAndLog("NiTexturingPropertyGetTextureUVSet","Returning "+UIntToString(*result)+".\n");
						}
					}
				}
			}
		}
	}
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
	*result = 0;

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
							*result = texPr->GetTexture(texSlot).hasTextureTransform;
							dPrintAndLog("NiTexturingPropertyTextureHasTransform","Returning "+string((*result)!=0?"TRUE":"FALSE")+".\n");
						}
					}
				}
			}
		}
	}
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
							map<string,OBSEElement> omap;
							omap[string("u")] = texPr->GetTexture(texSlot).translation.u;
							omap[string("v")] = texPr->GetTexture(texSlot).translation.v;
							arr = StringMapFromStdMap(omap, scriptObj);
						}
					}
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiTexturingPropertyGetTextureTranslation","Returning ExtraData's array.\n");
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
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Getting the center offset of texture #"+UIntToString(texSlot)+" of the NiTexturingProperty (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiTexturingPropertyRef texPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(nifPtr->nifList[blockID]);
					if ( texPr ) {
						if ( Niflib::BASE_MAP <= texSlot && texSlot <= texPr->GetTextureCount() ) {
							map<string,OBSEElement> omap;
							omap[string("u")] = texPr->GetTexture(texSlot).tiling.u;
							omap[string("v")] = texPr->GetTexture(texSlot).tiling.v;
							arr = StringMapFromStdMap(omap, scriptObj);
						}
					}
				}
			}
		}
	}
	if ( arrInterface->AssignCommandResult(arr, result) )
		dPrintAndLog("NiTexturingPropertyGetTextureTiling","Returning ExtraData's array.\n");
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
							*result = texPr->GetTexture(texSlot).wRotation;
							dPrintAndLog("NiTexturingPropertyGetTextureRotation","Returning "+FloatToString(*result)+".\n");
						}
					}
				}
			}
		}
	}
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
							map<string,OBSEElement> omap;
							omap[string("u")] = texPr->GetTexture(texSlot).centerOffset.u;
							omap[string("v")] = texPr->GetTexture(texSlot).centerOffset.v;
							arr = StringMapFromStdMap(omap, scriptObj);
						}
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
	NiTexturingPropertyGetTextureCenterOffset,
	NiTexPropGetTexCenOff,
	"Gets the center offset of the texture in the property's texture slot.",
	0,
	kParams_TwoInts_OneOptionalInt
);

void NifFile::loadChNiProperty(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiPropertyRef pr = Niflib::DynamicCast<Niflib::NiProperty>(nifList[block]);
		if ( pr ) {
			switch (act) {
				case kNiTexingPropAct_SetTexCount:
					{
						Niflib::NiTexturingPropertyRef texingPr = Niflib::DynamicCast<Niflib::NiTexturingProperty>(texingPr);
						texingPr->SetTextureCount(StringToUInt(val));
					}
					dPrintAndLog("NifLoad - NiTexturingProperty","NiTexturingProperty texture count change loaded.");
					break;

				case kNiTexingPropAct_AddTex:
				case kNiTexingPropAct_SetClampMode:
				case kNiTexingPropAct_SetFilterMode:
				case kNiTexingPropAct_SetFlags:
				case kNiTexingPropAct_SetUVSet:
				case kNiTexingPropAct_SetHasTransf:
				case kNiTexingPropAct_SetTransl:
				case kNiTexingPropAct_SetRot:
				case kNiTexingPropAct_SetCenOff:
					dPrintAndLog("NifLoad - NiProperty","\n\n\t\tThis version of NifSE does not support these changes! Loaded nif will be incorrect!\n");

				default:
					dPrintAndLog("NifLoad - NiProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiProperty","\n\n\t\tIndicated block is not a NiProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
