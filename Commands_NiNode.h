#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiNodeAct_AddChild,
	kNiNodeAct_DelChild,
	kNiNodeAct_AddEffect,
	kNiNodeAct_DelEffect,
	kNiNodeAct_AddSkin,
	kNiNodeAct_DelSkin,
	kNiNodeAct_SetSkinFlag
};

extern CommandInfo kCommandInfo_NiNodeGetNumChildren;
extern CommandInfo kCommandInfo_NiNodeGetChildren;
extern CommandInfo kCommandInfo_NiNodeGetChildByName;
extern CommandInfo kCommandInfo_NiNodeDeleteChild;