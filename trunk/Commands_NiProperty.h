#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiTexingPropAct_SetTexCount,
	kNiTexingPropAct_AddTex,
	kNiTexingPropAct_SetClampMode,
	kNiTexingPropAct_SetFilterMode,
	kNiTexingPropAct_SetFlags,
	kNiTexingPropAct_SetUVSet,
	kNiTexingPropAct_SetHasTransf,
	kNiTexingPropAct_SetTransl,
	kNiTexingPropAct_SetRot,
	kNiTexingPropAct_SetCenOff
};

extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureCount;
extern CommandInfo kCommandInfo_NiTexturingPropertySetTextureCount;
extern CommandInfo kCommandInfo_NiTexturingPropertyHasTexture;


extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureSource;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureClampMode;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureFilterMode;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureFlags;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureUVSet;
extern CommandInfo kCommandInfo_NiTexturingPropertyTextureHasTransform;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureTranslation;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureTiling;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureRotation;
extern CommandInfo kCommandInfo_NiTexturingPropertyGetTextureCenterOffset;
