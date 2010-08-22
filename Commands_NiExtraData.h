#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiEDAct_SetNum,
	kNiEDAct_SetStr,
	kNiEDAct_SetArr,
	kNiEDAct_SetBSBound,
};

extern CommandInfo kCommandInfo_NiExtraDataGetNumber;
extern CommandInfo kCommandInfo_NiExtraDataSetNumber;

extern CommandInfo kCommandInfo_NiExtraDataGetString;
extern CommandInfo kCommandInfo_NiExtraDataSetString;

extern CommandInfo kCommandInfo_NiExtraDataGetArray;
