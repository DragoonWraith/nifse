#include "Commands_NiVertexColorProperty.h"

#include "obj/NiVertexColorProperty.h"
#include "Command_Macros.h"

STDNIFLIBGET(NiVertexColorProperty, GetVertexMode, NiVertColorPropGetVertMode, UInt, vertex mode);

STDNIFLIBGET(NiVertexColorProperty, GetLightingMode, NiVertColorPropGetLightMode, UInt, lighting mode);

STDNIFLIBSETUINTCAST(NiVertexColorProperty, SetVertexMode, NiVertColorPropSetVertMode, kNiVertColorPropAct_SetVertMode, true, vertex mode, Niflib::VertMode);

STDNIFLIBSETUINTCAST(NiVertexColorProperty, SetLightingMode, NiVertColorPropSetLightMode, kNiVertColorPropAct_SetLightMode, true, lighting mode, Niflib::LightMode);

void NifFile::loadChNiVertColorProperty(UInt32 block, UInt32 act, string& val) {
	if ( block < nifList.size() ) {
		Niflib::NiVertexColorPropertyRef verColPr = Niflib::DynamicCast<Niflib::NiVertexColorProperty>(nifList[block]);
		if ( verColPr ) {
			switch (act) {
				case kNiVertColorPropAct_SetVertMode:
					verColPr->SetVertexMode((Niflib::VertMode)StringToUInt(val));
					dPrintAndLog("NifLoad - NiVertexColorProperty","Vertex Mode change loaded.");
					break;
					
				case kNiVertColorPropAct_SetLightMode:
					verColPr->SetLightingMode((Niflib::LightMode)StringToUInt(val));
					dPrintAndLog("NifLoad - NiVertexColorProperty","Lighting Mode change loaded.");
					break;

				default:
					dPrintAndLog("NifLoad - NiVertexColorProperty","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiVertexColorProperty","\n\n\t\tIndicated block is not a NiVertexColorProperty! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiVertexColorProperty","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
