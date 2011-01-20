#include "Commands_NiStencilProperty.h"
#include "obj/NiStencilProperty.h"

#include "Command_Macros.h"

STDNIFLIBGET(NiStencilProperty, GetStencilState, NiStenPropGetState, Bool, stencil state);

STDNIFLIBGET(NiStencilProperty, GetStencilFunction, NiStenPropGetFunc, UInt, stencil function);

STDNIFLIBGET(NiStencilProperty, GetStencilRef, NiStenPropGetRef, UInt, stencil ref);

STDNIFLIBGET(NiStencilProperty, GetStencilMask, NiStenPropGetMask, UInt, stencil mask);

STDNIFLIBGET(NiStencilProperty, GetFailAction, NIStenPropGetFailAct, UInt, fail action);

STDNIFLIBGET(NiStencilProperty, GetZFailAction, NiStenPropGetZFailAct, UInt, Z fail action);

STDNIFLIBGET(NiStencilProperty, GetPassAction, NiStenPropGetPassAct, UInt, pass action);

STDNIFLIBGET(NiStencilProperty, GetFaceDrawMode, NiStenPropGetFaceDrawMode, UInt, face draw mode);

STDNIFLIBSETBOOL(NiStencilProperty, SetStencilState, NiStenPropSetState, kNiStenPropAct_SetState, true, stencil state);

STDNIFLIBSETUINTCAST(NiStencilProperty, SetStencilFunction, NiStenPropSetFunc, kNiStenPropAct_SetFunc, true, stencil function, Niflib::StencilCompareMode);

STDNIFLIBSETUINT(NiStencilProperty, SetStencilRef, NiStenPropSetRef, kNiStenPropAct_SetRef, true, stencil ref);

STDNIFLIBSETUINT(NiStencilProperty, SetStencilMask, NiStenPropSetMask, kNiStenPropAct_SetMask, true, stencil mask);

STDNIFLIBSETUINTCAST(NiStencilProperty, SetFailAction, NiStenPropSetFailAct, kNiStenPropAct_SetFailAct, true, fail action, Niflib::StencilAction);

STDNIFLIBSETUINTCAST(NiStencilProperty, SetZFailAction, NiStenPropSetZFailAct, kNiStenPropAct_SetZFailAct, true, Z fail action, Niflib::StencilAction);

STDNIFLIBSETUINTCAST(NiStencilProperty, SetPassAction, NiStenPropSetPassAct, kNiStenPropAct_SetPassAct, true, pass action, Niflib::StencilAction);

STDNIFLIBSETUINTCAST(NiStencilProperty, SetFaceDrawMode, NiStenPropSetFaceDrawMode, kNiStenPropAct_SetFaceDrawMode, true, face draw mode, Niflib::FaceDrawMode);

void NifFile::loadChNiStenProperty(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::NiStencilPropertyRef stenPr = Niflib::DynamicCast<Niflib::NiStencilProperty>(nifList[block]);
		UInt32 valInt = StringToUInt(val);
		if ( stenPr ) {
			switch (act) {
				case kNiStenPropAct_SetState:
					stenPr->SetStencilState(valInt!=0);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty stencil state change loaded.");
					break;

				case kNiStenPropAct_SetFunc:
					stenPr->SetStencilFunction((Niflib::StencilCompareMode)valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty stencil function change loaded.");
					break;

				case kNiStenPropAct_SetRef:
					stenPr->SetStencilRef(valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty stencil reference change loaded.");
					break;

				case kNiStenPropAct_SetMask:
					stenPr->SetStencilMask(valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty stencil mask change loaded.");
					break;

				case kNiStenPropAct_SetFailAct:
					stenPr->SetFailAction((Niflib::StencilAction)valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty fail action change loaded.");
					break;

				case kNiStenPropAct_SetZFailAct:
					stenPr->SetZFailAction((Niflib::StencilAction)valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty Z fail action change loaded.");
					break;

				case kNiStenPropAct_SetPassAct:
					stenPr->SetPassAction((Niflib::StencilAction)valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty pass action change loaded.");
					break;

				case kNiStenPropAct_SetFaceDrawMode:
					stenPr->SetFaceDrawMode((Niflib::FaceDrawMode)valInt);
					dPrintAndLog("NifLoad - NiStencilProperty","NiStencilProperty face draw mode change loaded.");
					break;

				default:
					dPrintAndLog("NifLoad - NiStencilProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiStencilProperty","\n\n\t\tIndicated block is not a NiStencilProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiStencilProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
