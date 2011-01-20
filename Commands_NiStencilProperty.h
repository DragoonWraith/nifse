#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

enum {
	kNiStenPropAct_SetState,
	kNiStenPropAct_SetFunc,
	kNiStenPropAct_SetRef,
	kNiStenPropAct_SetMask,
	kNiStenPropAct_SetFailAct,
	kNiStenPropAct_SetZFailAct,
	kNiStenPropAct_SetPassAct,
	kNiStenPropAct_SetFaceDrawMode
};

extern CommandInfo kCommandInfo_NiStencilPropertyGetStencilState;
extern CommandInfo kCommandInfo_NiStencilPropertyGetStencilFunction;
extern CommandInfo kCommandInfo_NiStencilPropertyGetStencilRef;
extern CommandInfo kCommandInfo_NiStencilPropertyGetStencilMask;
extern CommandInfo kCommandInfo_NiStencilPropertyGetFailAction;
extern CommandInfo kCommandInfo_NiStencilPropertyGetZFailAction;
extern CommandInfo kCommandInfo_NiStencilPropertyGetPassAction;
extern CommandInfo kCommandInfo_NiStencilPropertyGetFaceDrawMode;

extern CommandInfo kCommandInfo_NiStencilPropertySetStencilState;
extern CommandInfo kCommandInfo_NiStencilPropertySetStencilFunction;
extern CommandInfo kCommandInfo_NiStencilPropertySetStencilRef;
extern CommandInfo kCommandInfo_NiStencilPropertySetStencilMask;
extern CommandInfo kCommandInfo_NiStencilPropertySetFailAction;
extern CommandInfo kCommandInfo_NiStencilPropertySetZFailAction;
extern CommandInfo kCommandInfo_NiStencilPropertySetPassAction;
extern CommandInfo kCommandInfo_NiStencilPropertySetFaceDrawMode;
