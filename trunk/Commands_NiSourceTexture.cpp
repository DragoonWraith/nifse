#include "Commands_NiSourceTexture.h"

#include "obj/NiSourceTexture.h"

#include <boost/algorithm/string/find.hpp>

static bool Cmd_NiSourceTextureIsExternal_Execute(COMMAND_ARGS) {
	*result = 0;

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiSourceTextureIsExternal","Getting whether an external texture is used by the NiSourceTexture (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiSourceTextureRef srcTex = Niflib::DynamicCast<Niflib::NiSourceTexture>(nifPtr->nifList[blockID]);
					if ( srcTex ) {
						*result = (srcTex->IsTextureExternal()?1:0);
						dPrintAndLog("NiSourceTextureIsExternal","Returning "+string(srcTex->IsTextureExternal()?"TRUE":"FALSE")+".\n");
					}
					else
						dPrintAndLog("NiSourceTextureIsExternal","Not NiSourceTexture.\n");
				}
				else
					dPrintAndLog("NiSourceTextureIsExternal","Block index out of range.\n");
			}
			else
				dPrintAndLog("NiSourceTextureIsExternal","Nif root bad.\n");
		}
		else
			dPrintAndLog("NiSourceTextureIsExternal","Could not find Nif.\n");
	}
	else
		dPrintAndLog("NiSourceTextureIsExternal","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiSourceTextureIsExternal,
	NiSrcTexIsExt,
	"Gets whether the source texture is an external file.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiSourceTextureGetFile_Execute(COMMAND_ARGS) {
	*result = 0;
	string file = " ";

	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiSourceTextureGetFile","Getting the filename of the texture used by the NiSourceTexture (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( blockID < nifPtr->nifList.size() ) {
					Niflib::NiSourceTextureRef srcTex = Niflib::DynamicCast<Niflib::NiSourceTexture>(nifPtr->nifList[blockID]);
					if ( srcTex ) {
						file = srcTex->GetTextureFileName();
						string fileSub = "";
						boost::iterator_range<string::iterator> fileRng (boost::ifind_first(file, "textures\\").end(), file.end());
						for ( string::iterator i = fileRng.begin(); i != fileRng.end(); ++i )
							fileSub += *i;
						file = fileSub;
						dPrintAndLog("NiSourceTextureGetFile","Returning \""+file+"\".\n");
					}
					else
						dPrintAndLog("NiSourceTextureGetFile","Block #"+UIntToString(blockID)+" is not NiSourceTexture.\n");
				}
				else
					dPrintAndLog("NiSourceTextureGetFile","Block #"+UIntToString(blockID)+" is out of range.\n");
			}
			else
				dPrintAndLog("NiSourceTextureGetFile","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiSourceTextureGetFile","Nif not found.\n");
	}
	else
		dPrintAndLog("Error extracting arguments.\n");

	strInterface->Assign(PASS_COMMAND_ARGS, file.c_str());
	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiSourceTextureGetFile,
	NiSrcTexGetFile,
	"Gets the source texture's filename.",
	0,
	kParams_OneInt_OneOptionalInt
);

static bool Cmd_NiSourceTextureSetExternalTexture_Execute(COMMAND_ARGS) {
	*result = 0;

	char newFile[kMaxMessageLength];
	int nifID = -1;
	UInt32 blockID = 0;
	if (ExtractArgs(PASS_EXTRACT_ARGS, &newFile, &nifID, &blockID)) {
		UInt8 modID = scriptObj->GetModIndex();
		dPrintAndLog("NiSourceTextureSetExternalTexture","Setting the filename of the texture used by the NiSourceTexture (nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" block #"+UIntToString(blockID)+").");
		NifFile* nifPtr = NULL;
		if ( NifFile::getRegNif(modID, nifID, nifPtr) ) {
			if ( nifPtr->root ) {
				if ( nifPtr->editable ) {
					if ( blockID < nifPtr->nifList.size() ) {
						Niflib::NiSourceTextureRef srcTex = Niflib::DynamicCast<Niflib::NiSourceTexture>(nifPtr->nifList[blockID]);
						if ( srcTex ) {
							*result = 1;
							srcTex->SetExternalTexture(string("textures\\")+newFile);
							nifPtr->logChange(blockID,kNiflibType_NiSourceTexture,kNiSrcTexAct_SetExtTex,newFile,true);
							dPrintAndLog("NiSourceTextureSetExternalTexture","Setting file name to \""+string(newFile)+"\".\n");
						}
						else
							dPrintAndLog("NiSourceTextureSetExternalTexture","Block #"+UIntToString(blockID)+" is not NiSourceTexture.\n");
					}
					else
						dPrintAndLog("NiSourceTextureSetExternalTexture","Block #"+UIntToString(blockID)+" is out of range.\n");
				}
				else
					dPrintAndLog("NiSourceTextureSetExternalTexture","Nif is not editable.\n");
			}
			else
				dPrintAndLog("NiSourceTextureSetExternalTexture","Nif root is bad.\n");
		}
		else
			dPrintAndLog("NiSourceTextureSetExternalTexture","Nif not found.\n");
	}
	else
		dPrintAndLog("NiSourceTextureSetExternalTexture","Error extracting arguments.\n");

	return true;
}

DEFINE_CMD_PLUGIN_ALT(
	NiSourceTextureSetExternalTexture,
	NiSrcTexSetExtTex,
	"Gets the source texture's filename.",
	0,
	kParams_OneString_OneInt_OneOptionalInt
);

void NifFile::loadChNiSourceTexture(UInt32 block, UInt32 act, std::string &val) {
	if ( block < nifList.size() ) {
		Niflib::NiSourceTextureRef srcTex = Niflib::DynamicCast<Niflib::NiSourceTexture>(nifList[block]);
		if ( srcTex ) {
			switch (act) {
				case kNiSrcTexAct_SetExtTex:
					srcTex->SetExternalTexture(string("textures\\")+val);
					dPrintAndLog("NifLoad - NiSourceTexture","External texture change loaded.");
					break;

				case kNiSrcTexAct_SetIntTex:
				case kNiSrcTexAct_SetPixLayout:
				case kNiSrcTexAct_SetMipMapFormat:
				case kNiSrcTexAct_SetAlphaFormat:
					dPrintAndLog("NifLoad - NiSourceTexture","\n\n\t\tThis version of NifSE does not support these changes! Loaded nif will be incorrect!\n");

				default:
					dPrintAndLog("NifLoad - NiSourceTexture","\n\n\t\tUnknown change type! Loaded nif will be incorrect!\n");
			}
		}
		else
			dPrintAndLog("NifLoad - NiSourceTexture","\n\n\t\tIndicated block is not a NiSourceTexture! Change cannot be loaded; loaded nif will be incorrect!\n");
	}
	else
		dPrintAndLog("NifLoad - NiSourceTexture","\n\n\t\tIndicated block index is out of range! Change cannot be loaded; loaded nif will be incorrect!\n");
}
