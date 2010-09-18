#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiAlphaPropAct_SetBlendState,
	kNiAlphaPropAct_SetSrcBlendFunc,
	kNiAlphaPropAct_SetDestBlendFunc,
	kNiAlphaPropAct_SetTestState,
	kNiAlphaPropAct_SetTestFunc,
	kNiAlphaPropAct_SetTestThreshold,
	kNiAlphaPropAct_SetTriSort
};

extern CommandInfo kCommandInfo_NiAlphaPropertyGetBlendState;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetSourceBlendFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetDestinationBlendFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetTestState;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetTestFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetTestThreshold;
extern CommandInfo kCommandInfo_NiAlphaPropertyGetTriangleSortMode;
extern CommandInfo kCommandInfo_NiAlphaPropertySetBlendState;
extern CommandInfo kCommandInfo_NiAlphaPropertySetSourceBlendFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertySetDestinationBlendFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertySetTestState;
extern CommandInfo kCommandInfo_NiAlphaPropertySetTestFunction;
extern CommandInfo kCommandInfo_NiAlphaPropertySetTestThreshold;
extern CommandInfo kCommandInfo_NiAlphaPropertySetTriangleSortMode;
