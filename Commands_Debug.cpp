#include "Commands_Debug.h"

#ifdef _DEBUG
static bool Cmd_NifWriteToDisk_Execute(COMMAND_ARGS) {
	*result = 0;

	char filename[kMaxMessageLength] = " ";
	UInt32 nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &filename, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifWriteToDisk","Writing nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" to disk as \""+string(filename)+"\".");
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(modID,nifID,nifPtr);
		if ( nifPtr->root ) {
			Niflib::WriteNifTree(GetOblivionDirectory()+"Data\\Meshes\\ni\\"+filename,DynamicCast<Niflib::NiObject>(nifPtr->root),nifPtr->headerInfo);
			*result = 1;
			dPrintAndLog("NifWriteToDisk","Nif written to disk.\n");
		}
		else
			dPrintAndLog("NifWriteToDisk","Nif not found.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifWriteToDisk,
	"Writes the nif to disk permanently. For testing only!",
	0,
	2,
	kParams_OneString_OneInt
);
#endif