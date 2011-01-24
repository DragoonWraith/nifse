#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiVertColorPropAct_SetVertMode,
	kNiVertColorPropAct_SetLightMode
};

extern CommandInfo kCommandInfo_NiVertexColorPropertyGetVertexMode;
extern CommandInfo kCommandInfo_NiVertexColorPropertyGetLightingMode;

extern CommandInfo kCommandInfo_NiVertexColorPropertySetVertexMode;
extern CommandInfo kCommandInfo_NiVertexColorPropertySetLightingMode;
