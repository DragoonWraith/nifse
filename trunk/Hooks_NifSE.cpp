#include "Hooks_NifSE.h"

// returns true if the filepath points to nifScript's folder. Lets us quickly & easily determine if NifSE is interested in this file or not
static bool IsNifSEFilePath(const char* path, bool bUseFullPath) {
	if (!path)
		return false;
	
	const char* nsPath = bUseFullPath ? s_nifSEFullPath : s_nifSEPath;
	UInt32 nsPathLen = bUseFullPath ? s_nifSEFullPathLen : s_nifSEPathLen;

	UInt32 i = 0;
	while (path[i] && i < nsPathLen)
	{
		if (tolower(path[i]) != nsPath[i])
			break;

		i++;
	}

	return (i == nsPathLen);
}

// this is called when FileFinder attempts to load a .nif which doesn't exist
// should create a .nif with the requested name/path on disk
// nifPath includes "meshes\\" prefix
// return true if nif created, false otherwise
// presumably all "dynamic" .nifs would go in a particular folder i.e. "meshes\ni" to allow
// you to easily distinguish between your .nifs and genuinely missing .nifs
// add code elsewhere to clean up .nif files after they've been loaded
static bool __stdcall CreateNifFile(const char* nifPath) {
	if (!IsNifSEFilePath(nifPath, true))
		return false;

	dPrintAndLog("CreateNifFile","FileFinder requesting nifScript file \""+string(nifPath)+"\".");
	
	// Create the .nif and save to disk
	NifFile* nifPtr = NULL;
	if ( NifFile::getRegNif(string(&(nifPath[s_nifSEFullPathLen])), nifPtr) ) {
		if ( nifPtr->editable ) {
			nifPtr->loc = 1;
			ofstream newNif (nifPtr->getAbsPath().c_str(), ios::out);
			if ( newNif.is_open() ) {
				newNif.close();
				nifPtr->commitChanges();
				dPrintAndLog("CreateNifFile","Nif created.\n");
			}
			else
				dPrintAndLog("CreateNifFile","Nif not created.\n");
			return true;
		}
		else {
			dPrintAndLog("CreateNifFile","Nif not editable.\n");
			return false;
		}
	}
	else {
		dPrintAndLog("CreateNifFile","Nif not registered.\n");
		return false;
	}
}

static __declspec(naked) void LoadFileHook(void) {
	static UInt32 s_path;

	__asm
	{
		mov	eax,		[esp]		// grab the first arg (nifPath)
		mov [s_path],	eax

		// does nif already exist?
		call	[kLoadFile_CallAddr]
		test	eax,	eax
		jnz		Done

		// nif doesn't exist, create it
		mov		eax,	[s_path]
		push	eax
		call	CreateNifFile
		test	al, al
		jnz		ReloadFile
		
		// CreateFile didn't create the file, so return NULL
		xor		eax,	eax
		jmp		Done
		
	ReloadFile:
		// ask FileFinder to load the nif we just created
		call	[kLoadFile_CallAddr]

	Done:
		jmp		[kLoadFile_RetnAddr]
	}
}

// This is called when QueuedModel is finished with .nif file
// if it's a nifscript file, you can safely delete the file
// nifPath does not include "meshes\\" prefix
static void __stdcall DeleteNifFile(const char* nifPath) {
	if (!IsNifSEFilePath(nifPath, false))
		return;

	dPrintAndLog("DeleteNifFile","FileFinder has finished with nifScript file \""+string(nifPath)+"\".");

	// delete the file
	NifFile* nifPtr = NULL;
	if ( NifFile::getRegNif(string(&(nifPath[s_nifSEPathLen])), nifPtr) ) {
		if ( nifPtr->editable ) {
			nifPtr->loc = 0;
			std::remove(nifPtr->getAbsPath().c_str());
			if ( nifPtr->nifSEversion == 0x0000001F ) {
				string::size_type i = nifPtr->filePath.length()-4;
				while ( (i = nifPtr->filePath.find_last_of("\\", i-1)) != string::npos )
					RemoveDirectory(nifPtr->filePath.substr(0,i).c_str());
			}
			dPrintAndLog("DeleteNifFile","Nif deleted.\n");
		}
		else
			dPrintAndLog("DeleteNifFile","Nif not editable.\n");
	}
	else
		dPrintAndLog("DeleteNifFile","Nif not registered.\n");
}

static __declspec(naked) void FinishedWithFileHook(void) {
	__asm
	{
		mov		eax,	[esi+0x20]		// filepath
		push	eax
		call	DeleteNifFile

		// overwritten code
		pop		ecx
		pop		edi
		pop		esi
		pop		ebp
		pop		ebx
		
		jmp		[kFinishedWithFile_RetnAddr]
	}
}

// Call this to install the hooks, presumably during plugin load
void Hooks_NifSE_Init(void) {
	WriteRelJump(kLoadFile_HookAddr, (UInt32)&LoadFileHook);
	WriteRelJump(kFinishedWithFile_HookAddr, (UInt32)&FinishedWithFileHook);
}