#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiMatPropAct_SetTransp,
	kNiMatPropAct_SetAmbColor,
	kNiMatPropAct_SetDifColor,
	kNiMatPropAct_SetEmiColor,
	kNiMatPropAct_SetSpecColor,
	kNiMatPropAct_SetGloss
};

extern CommandInfo kCommandInfo_NiMaterialPropertyGetTransparency;
extern CommandInfo kCommandInfo_NiMaterialPropertyGetAmbientColor;
extern CommandInfo kCommandInfo_NiMaterialPropertyGetDiffuseColor;
extern CommandInfo kCommandInfo_NiMaterialPropertyGetEmissiveColor;
extern CommandInfo kCommandInfo_NiMaterialPropertyGetSpecularColor;
extern CommandInfo kCommandInfo_NiMaterialPropertyGetGlossiness;

extern CommandInfo kCommandInfo_NiMaterialPropertySetTransparency;
extern CommandInfo kCommandInfo_NiMaterialPropertySetAmbientColor;
extern CommandInfo kCommandInfo_NiMaterialPropertySetDiffuseColor;
extern CommandInfo kCommandInfo_NiMaterialPropertySetEmissiveColor;
extern CommandInfo kCommandInfo_NiMaterialPropertySetSpecularColor;
extern CommandInfo kCommandInfo_NiMaterialPropertySetGlossiness;
