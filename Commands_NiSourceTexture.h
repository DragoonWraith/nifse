#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiSrcTexAct_SetExtTex,
	kNiSrcTexAct_SetIntTex,
	kNiSrcTexAct_SetPixLayout,
	kNiSrcTexAct_SetMipMapFormat,
	kNiSrcTexAct_SetAlphaFormat
};

extern CommandInfo kCommandInfo_NiSourceTextureIsExternal;
extern CommandInfo kCommandInfo_NiSourceTextureGetFile;
extern CommandInfo kCommandInfo_NiSourceTextureSetExternalTexture;
