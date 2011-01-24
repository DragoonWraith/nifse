#include "changeLog.h"

#include "NifFile.h"

changeLog::changeLog(UInt8 modID, UInt32 nifID, string filePath, string basePath, UInt32 version, bool editable, UInt32 typeID, UInt32 blockID, UInt32 actID, string valStr)
					:mod(modID), nif(nifID), path(filePath), base(basePath), ver(version), edit(editable), type(typeID), block(blockID), act(actID), val(valStr), required(vector<NifFile*>()) {
}

void changeLog::saveMod() const {
	serInterface->WriteRecord('MOD ', g_pluginVersion, (void *)(&mod), sizeof(UInt8));
}

void changeLog::saveNif() const {
	NifFile* nifPtr;
	if ( NifFile::getRegNif(mod, nif, nifPtr) || !required.empty() || act == kBasicAct_Close ) {
		serInterface->WriteRecord('niID', g_pluginVersion, (void *)(&nif), sizeof(UInt32));
		serInterface->WriteRecord('nSEV', g_pluginVersion, (void *)(&ver), sizeof(UInt32));
		if ( edit ) {
			switch (ver) {
				case VERSION(0, 0, 1, F): // NifScript beta
					serInterface->WriteRecord('niRo', g_pluginVersion, (void *)(base.c_str()), base.length());
					serInterface->WriteRecord('niRa', g_pluginVersion, (void *)(path.substr(s_nifSEPathLen).c_str()), path.length()-s_nifSEPathLen);
					break;

				default: // NifSE
					serInterface->WriteRecord('niRe', g_pluginVersion, (void *)(base.c_str()), base.length());
					break;
			}
		}
		else { // constant
			serInterface->WriteRecord('niRc', g_pluginVersion, (void *)(path.c_str()), path.length());
		}
	}
	else
		dPrintAndLog("NifSave","Unnecessary save.");
}

void changeLog::saveCh() const {
	string saveStr = UIntToString(block)+logNode+UIntToString(type)+logType+UIntToString(act)+logAction+val+logValue;
	serInterface->WriteRecordData((void *) saveStr.c_str(), saveStr.length());
}
