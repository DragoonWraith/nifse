#include "Save.h"

#include "changeLog.h"
#include "NifFile.h"

void NifSE_SaveCallback(void * reserved) {
	dPrintAndLog("NifSave","Saving registered nifs");
	UInt8 prevMod = 0;
	UInt32 prevNif = 0;
	bool prevOpen = false;
	bool diffMod = false;
	bool diffNif = false;

	for ( vector<changeLog>::iterator i = NifFile::delta.begin(); i != NifFile::delta.end(); ++i ) {
		dPrintAndLog("NifSave","Saving nif #"+UIntToString(i->mod)+"-"+UIntToString(i->nif)+" change to block #"+UIntToString(i->block)+".");
		if ( prevMod != i->mod ) {
			i->saveMod();
			diffMod = true;
		}
		if ( prevNif != i->nif || diffMod ) {
			i->saveNif();
			diffNif = true;
		}
		if ( i->type == kNiflibType_NifFile && i->act == kBasicAct_Open )
			prevOpen = true;
		else {
			if ( diffNif || prevOpen )
					serInterface->OpenRecord('niCh', g_pluginVersion);
			i->saveCh();
			prevOpen = false;
		}
		prevMod = i->mod;
		prevNif = i->nif;
		diffNif = false;
	}
	dPrintAndLog("NifSave","Save complete.\n");
}
