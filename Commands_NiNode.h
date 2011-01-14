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
	kNiNodeAct_SetSkinFlag,
	kNiNodeAct_CopyChild
};

extern CommandInfo kCommandInfo_NiNodeGetNumChildren;
extern CommandInfo kCommandInfo_NiNodeGetChildren;
extern CommandInfo kCommandInfo_NiNodeGetChildByName;
extern CommandInfo kCommandInfo_NiNodeAddChild;
extern CommandInfo kCommandInfo_NiNodeDeleteChild;
extern CommandInfo kCommandInfo_NiNodeCopyChild;

extern UInt32 Util_NiNodeAddChild(NifFile* nifPtr, Niflib::NiNodeRef node, UInt32 typeID, const string& name);
extern UInt32 Util_NiNodeCopyChild(NifFile* nifFromPtr, UInt32 blockIDfrom, NifFile* nifToPtr, UInt32 blockIDto);
