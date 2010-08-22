#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiObjNETAct_SetName,
	kNiObjNETAct_AddED,
	kNiObjNETAct_DelED,
	kNiObjNETAct_AddCtlr,
	kNiObjNETAct_DelCtlr,
};

extern CommandInfo kCommandInfo_NiObjectNETGetName;
extern CommandInfo kCommandInfo_NiObjectNETSetName;

extern CommandInfo kCommandInfo_NiObjectNETGetNumExtraData;
extern CommandInfo kCommandInfo_NiObjectNETGetExtraData;
extern CommandInfo kCommandInfo_NiObjectNETGetExtraDataByName;
extern CommandInfo kCommandInfo_NiObjectNETAddExtraData;
extern CommandInfo kCommandInfo_NiObjectNETDeleteExtraData;

UInt32 Util_NiObjectNETAddExtraData(NifFile* nifPtr, Niflib::NiObjectNETRef objNET, UInt32 typeID, const string& name);
