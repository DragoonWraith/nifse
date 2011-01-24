#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiAVObjAct_AddBoundingBox,
	kNiAVObjAct_DelBoundingBox,
	kNiAVObjAct_SetLocTransf,
	kNiAVObjAct_SetLocTransl,
	kNiAVObjAct_SetLocRot,
	kNiAVObjAct_SetLocScale,
	kNiAVObjAct_AddProp,
	kNiAVObjAct_DelProp,
	kNiAVObjAct_SetFlags,
	kNiAVObjAct_SetVel,
	kNiAVObjAct_SetVis,
	kNiAVObjAct_SetCollMode,
	kNiAVObjAct_ClrCollObj,
	kNiAVObjAct_CopyCollObj
};

extern CommandInfo kCommandInfo_NiAVObjectGetLocalTransform;
extern CommandInfo kCommandInfo_NiAVObjectGetLocalTranslation;
extern CommandInfo kCommandInfo_NiAVObjectGetLocalRotation;
extern CommandInfo kCommandInfo_NiAVObjectGetLocalScale;

extern CommandInfo kCommandInfo_NiAVObjectSetLocalTransform;
extern CommandInfo kCommandInfo_NiAVObjectSetLocalTranslation;
extern CommandInfo kCommandInfo_NiAVObjectSetLocalRotation;
extern CommandInfo kCommandInfo_NiAVObjectSetLocalScale;

extern CommandInfo kCommandInfo_NiAVObjectGetNumProperties;
extern CommandInfo kCommandInfo_NiAVObjectGetProperties;
extern CommandInfo kCommandInfo_NiAVObjectGetPropertyByType;
extern CommandInfo kCommandInfo_NiAVObjectAddProperty;
extern CommandInfo kCommandInfo_NiAVObjectDeleteProperty;

extern CommandInfo kCommandInfo_NiAVObjectGetCollisionMode;
extern CommandInfo kCommandInfo_NiAVObjectSetCollisionMode;

extern CommandInfo kCommandInfo_NiAVObjectGetCollisionObject;
extern CommandInfo kCommandInfo_NiAVObjectClearCollisionObject;
extern CommandInfo kCommandInfo_NiAVObjectCopyCollisionObject;

extern UInt32 Util_NiAVObjectAddProperty(NifFile* nifPtr, Niflib::NiAVObjectRef avObj, UInt32 typeID, const string& name);
extern UInt32 Util_NiAVObjectCopyCollision(NifFile* nifFromPtr, UInt32 blockIDfrom, NifFile* nifToPtr, UInt32 blockIDto);
