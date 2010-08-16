#include "Save.h"

void NifSE_SaveCallback(void * reserved) {
	dPrintAndLog("NifSave","Saving registered nifs");
	UInt8 modIndex;
	UInt32 nifIndex;
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = NifFile::RegList.begin(); RegListIter != NifFile::RegList.end(); ++RegListIter ) {
		modIndex = RegListIter->first;
		dPrintAndLog("NifSave","Saving Nifs associated with mod #"+UIntToString(modIndex)+".");
		serInterface->WriteRecord('MOD ', g_pluginVersion, (void *)(&modIndex), sizeof(UInt8));
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter ) {
			nifIndex = NifListIter->first;
			dPrintAndLog("NifSave","Nif #"+UIntToString(modIndex)+"-"+UIntToString(nifIndex)+" found.");
			if ( NifListIter->second->root ) {
				dPrintAndLog("NifSave","Saving Nif #"+UIntToString(RegListIter->first)+"-"+UIntToString(NifListIter->first)+".");
				serInterface->WriteRecord('niID', g_pluginVersion, (void *)(&nifIndex), sizeof(UInt32));

				dPrintAndLog("NifSave","Saving NifSE version.");
				serInterface->WriteRecord('nSEV', g_pluginVersion, (void *)(&(NifListIter->second->nifSEversion)), sizeof(UInt32));

				if ( NifListIter->second->editable ) {
					switch (NifListIter->second->nifSEversion) {
						case 0x0000001F: // NifScript beta
							dPrintAndLog("NifSave","Saving deprecated nif! Original filepath \""+NifListIter->second->basePath+"\" and new filepath \""+NifListIter->second->filePath+"\".");
							serInterface->WriteRecord('niRo', g_pluginVersion, (void *)(NifListIter->second->basePath.c_str()), NifListIter->second->basePath.length());
							serInterface->WriteRecord('niRa', g_pluginVersion, (void *)(NifListIter->second->filePath.substr(s_nifSEPathLen).c_str()), NifListIter->second->filePath.length()-s_nifSEPathLen);
							break;

						case 0x00010003: // NifSE v1.0 a"1.3"
						case 0x0001001F: // NifSE v1.0 b1
						default:
							dPrintAndLog("NifSave","Saving filepath \""+NifListIter->second->basePath+"\" ("+UIntToString(NifListIter->second->filePath.length())+"); editable nif.");
							serInterface->WriteRecord('niRe', g_pluginVersion, (void *)(NifListIter->second->basePath.c_str()), NifListIter->second->basePath.length());
							break;
					}
				}
				else { // constant
					dPrintAndLog("NifSave","Saving filepath \""+NifListIter->second->filePath+"\" ("+UIntToString(NifListIter->second->filePath.length())+"); constant nif.");
					serInterface->WriteRecord('niRc', g_pluginVersion, (void *)(NifListIter->second->filePath.c_str()), NifListIter->second->filePath.length());
				}

				if ( NifListIter->second->extraDataChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving ExtraData changes.");
					serInterface->WriteRecord('niED', g_pluginVersion, (void *)(NifListIter->second->extraDataChanges.c_str()), NifListIter->second->extraDataChanges.length());
				}

				if ( NifListIter->second->collisionChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Collision changes.");
					serInterface->WriteRecord('niCo', g_pluginVersion, (void *)(NifListIter->second->collisionChanges.c_str()), NifListIter->second->collisionChanges.length());
				}

				if ( NifListIter->second->childrenChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Children changes.");
					serInterface->WriteRecord('niCh', g_pluginVersion, (void *)(NifListIter->second->childrenChanges.c_str()), NifListIter->second->childrenChanges.length());
				}

				if ( NifListIter->second->effectChanges.length() > 0 ) {
					dPrintAndLog("NifSave","Saving Effect changes.");
					serInterface->WriteRecord('niEf', g_pluginVersion, (void *)(NifListIter->second->effectChanges.c_str()), NifListIter->second->effectChanges.length());
				}
			}
		}
	}
	dPrintAndLog("NifSave","Save complete.\n");
}
