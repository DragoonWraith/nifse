#include "Commands_Basic.h"

// creates a NifFile from given file in folders or archives.
// returns nifID of the NifFile.
static bool Cmd_NifOpen_Execute(COMMAND_ARGS) {
	*result = -1;

	char oriPath[kMaxMessageLength] = " ";
	int forEdit = 0;
	if (!ExtractArgs(PASS_EXTRACT_ARGS, &oriPath, &forEdit)) return true;
	dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" opened"+(forEdit!=0?(" for editing."):(" for reading.")));

	try {
		NifFile* nifPtr = new NifFile(string(oriPath), scriptObj->GetModIndex(), (forEdit!=0));
		if ( nifPtr ) {
			if ( nifPtr->nifID >= 0 ) {
				*result = nifPtr->nifID;
				dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" registered as #"+UIntToString(nifPtr->modID)+"-"+UIntToString(*result)+".\n");
			}
			else
				dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" failed to register!\n");
		}
		else
			dPrintAndLog("NifOpen", "\""+string(oriPath)+"\" failed to register!\n");
	}
	catch (exception& except) {
		dPrintAndLog("NifOpen","Failed to create NifFile; exception \""+string(except.what())+"\" thrown.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifOpen,
	"Registers a nif for a mod to read or modify. Optional second argument is a boolean for editing - default is const.",
	0,
	2,
	kParams_OneString_OneOptionalBool
);

// deregisters and deletes NifFile of given nifID
static bool Cmd_NifClose_Execute(COMMAND_ARGS) {
	*result = 0;

	UInt32 nifID = 0;
	if (!ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) return true;

	UInt8 modID = scriptObj->GetModIndex();
	dPrintAndLog("NifClose","Closing nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
	NifFile* nifPtr = NULL;
	if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
		delete nifPtr;
		dPrintAndLog("NifClose","NifFile successfully closed.\n");
	}
	else
		dPrintAndLog("NifClose","Nif not found.\n");
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifClose,
	"Deletes the given NifFile, and if an editable file, deletes the file itself as well",
	0,
	1,
	kParams_OneInt
);

// returns the path where NifFile associated with the given nifID can be found
// for editable nifs, does not actually exist until called for by Oblivion
// but Oblivion needs to be calling the correct filename.
static bool Cmd_NifGetPath_Execute(COMMAND_ARGS) {
	*result = 0;
	string pathStr = " ";

	int nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetPath","Getting the path to nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				pathStr = nifPtr->filePath;
				dPrintAndLog("NifGetPath","Returning \""+pathStr+"\".\n");
			}
			else
				dPrintAndLog("NifGetPath","Root bad.\n");
		}
		else
			dPrintAndLog("NifGetPath","Nif not found.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, pathStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetPath,
	"Returns the path of a given registered Nif",
	0,
	1,
	kParams_OneInt
);

// returns the path where the path to the originally opened nif file
// can be found. For uneditable nif's, this is the same as the path.
static bool Cmd_NifGetOriginalPath_Execute(COMMAND_ARGS) {
	*result = 0;
	string pathStr = " ";

	int nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetOriginalPath","Getting the original path to nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				pathStr = nifPtr->basePath;
				dPrintAndLog("NifGetOriginalPath","Returning \""+pathStr+"\".\n");
			}
			else
				dPrintAndLog("NifGetOriginalPath","Root bad.\n");
		}
		else
			dPrintAndLog("NifGetOriginalPath","Nif not found.\n");
	}
	strInterface->Assign(PASS_COMMAND_ARGS, pathStr.c_str());
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetOriginalPath,
	"Returns the original path of a given registered Nif",
	0,
	1,
	kParams_OneInt
);

// returns the total number of blocks in a nif.
static bool Cmd_NifGetNumBlocks_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NifGetNumBlocks","Getting the number of blocks in nif #"+UIntToString(modID)+"-"+UIntToString(nifID));
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				*result = nifPtr->nifList.size();
				dPrintAndLog("NifGetNumBlocks","Returning "+UIntToString(nifPtr->nifList.size())+".\n");
			}
			else
				dPrintAndLog("NifGetNumBlocks","Root bad.\n");
		}
		else
			dPrintAndLog("NifGetNumBlocks","Nif not found.\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	NifGetNumBlocks,
	"Returns the number of blocks in a given registered Nif",
	0,
	1,
	kParams_OneInt
);

static bool Cmd_GetNifTypeIndex_Execute(COMMAND_ARGS) {
	*result = -1;

	char typeName[kMaxMessageLength];
	if (ExtractArgs(PASS_EXTRACT_ARGS, &typeName)) {
		dPrintAndLog("GetNifTypeIndex","Getting the code for Nif block type \""+string(typeName)+"\".");
		*result = getNiflibTypeIndex(typeName);
		dPrintAndLog("GetNifTypeIndex","Returning "+UIntToString(*result)+".\n");
	}
	return true;
}

DEFINE_COMMAND_PLUGIN(
	GetNifTypeIndex,
	"Returns code for the passed type name",
	0,
	1,
	kParams_OneString
);
