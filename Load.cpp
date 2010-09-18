#include "Load.h"

extern std::map<const char*, const char*>* FunctionDocMap (NULL);

void MessageHandler(OBSEMessagingInterface::Message* msg) {
	switch (msg->type) {
		case OBSEMessagingInterface::kMessage_PostLoad:
			_MESSAGE("Game loaded: Creating ni\\ directory.\n");
			CreateDirectory((GetOblivionDirectory()+"Data\\"+s_nifSEFullPath).c_str(), NULL);
			break;

		case OBSEMessagingInterface::kMessage_ExitGame:
		case OBSEMessagingInterface::kMessage_ExitGame_Console:
			_MESSAGE("Game quit: Deleting ni\\ directory.");
			RemoveDirectory((GetOblivionDirectory()+"Data\\"+s_nifSEFullPath).c_str());
			break;
	}
}

void EditorMessageHandler(OBSEMessagingInterface::Message* msg) {
	switch (msg->type) {
		case OBSEMessagingInterface::kMessage_PostLoad:
			msgInterface->RegisterListener(g_pluginHandle, "CSE", EditorMessageHandler);
			_MESSAGE("OBSE Plugins loaded. Listening for CSE dispatches.");
			break;

		case 'CSEL':
			_MESSAGE("\nDocumenting functions for CSE.");
			FunctionDocMap = new std::map<const char*, const char*>;
			doc("NifGetAltGrip");
			doc("NifGetOffHand");
			doc("NifGetBackShield");
			doc("NifOpen");
			doc("NifClose");
			doc("NifGetPath");
			doc("NifGetOriginalPath");
			doc("NifGetNumExtraData");
			doc("NifAddExtraData");
			doc("NifDeleteNthExtraData");
			doc("NifGetNthExtraDataName");
			doc("NifSetNthExtraDataName");
			doc("NifGetExtraDataIndexByName");
			doc("NifGetNthExtraDataType");
			doc("NifGetNthExtraDataString");
			doc("NifSetNthExtraDataString");
			doc("NifGetNumChildren");
			doc("NifDeleteNthChild");
			doc("NifGetNthChildName");
			doc("NifSetNthChildName");
			doc("NifGetChildIndexByName");
			doc("NifGetNthChildType");
			doc("NifGetNthChildLocalTransform");
			doc("NifGetNthChildLocalTranslation");
			doc("NifGetNthChildLocalRotation");
			doc("NifGetNthChildLocalScale");
			doc("NifSetNthChildLocalScale");
			doc("NifSetNthChildLocalTransformTEMP");
			doc("NifSetNthChildLocalTranslationTEMP");
			doc("NifSetNthChildLocalRotationTEMP");
			doc("NifNthChildHasMaterial");
			doc("NifGetNthChildMaterial");
			doc("NifSetNthChildMaterial");
			doc("NifNthChildHasTexturingProp");
			doc("NifNthChildHasBaseTexture");
			doc("NifGetNthChildBaseTexture");
			doc("NifSetNthChildBaseTexture");
			msgInterface->Dispatch(g_pluginHandle, 'CSEL', FunctionDocMap, sizeof(&FunctionDocMap), "CSE");
			_MESSAGE("CSE Documentation dispatched.");
			break;
	}
}

string ReadString(UInt32 length) {
	char* tempStr = new char[length+1];
	serInterface->ReadRecordData(tempStr, length);
	tempStr[length] = '\0';
	string changes = string(tempStr);
	delete[] tempStr;
	return changes;
}

void LoadChangelog(string &changes, UInt32 &chNode, UInt32 &chType, UInt32 &chAct, string &chVal) {
	string::size_type posS;
	string::size_type posF;

	posS = 0;
	posF = changes.find(logNode,posS);
	chNode = StringToUInt(changes.substr(posS,posF-posS));
	dPrintAndLog("LoadChangelog","Change node: \""+changes.substr(posS,posF-posS)+"\".");

	posS = posF+1;
	posF = changes.find(logType,posS);
	chType = StringToUInt(changes.substr(posS,posF-posS));
	dPrintAndLog("LoadChangelog","Change type: \""+changes.substr(posS,posF-posS)+"\".");

	posS = posF+1;
	posF = changes.find(logAction,posS);
	chAct = StringToUInt(changes.substr(posS,posF-posS));
	dPrintAndLog("LoadChangelog","Change action: \""+changes.substr(posS,posF-posS)+"\".");
	
	posS = posF+1;
	posF = changes.find(logValue,posS);
	chVal = changes.substr(posS,posF-posS);
	dPrintAndLog("LoadChangelog","Change value: \""+chVal+"\".");

	changes.erase(0,posF+1);
}

// constructs list of BSA files
std::list<string> GetBSAfiles() {
	std::list<string> BSAfiles;
	WIN32_FIND_DATA bsaSearch;
	HANDLE h;

	// build a list of BSA files
	// code adapted from that by Hammer on CProgramming.com
	// http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1046380353&id=1044780608
	h = FindFirstFile((GetOblivionDirectory()+"Data\\*.bsa").c_str(), &bsaSearch);
	if (h != INVALID_HANDLE_VALUE)
	{
		do {
			if ( !strncmp(bsaSearch.cFileName, "Oblivion", 8) ) {
				if ( !strcmp(bsaSearch.cFileName, "Oblivion - Meshes.bsa") )
					BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
			}
			else if ( !strncmp(bsaSearch.cFileName, "DLCShiveringIsles", 17) ) {
				if ( !strcmp(bsaSearch.cFileName, "DLCShiveringIsles - Meshes.bsa") )
					BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
			}
			else if ( strncmp(bsaSearch.cFileName, "ArchiveInvalidationInvalidated!.bsa", 34) )
				BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
		} while (FindNextFile(h, &bsaSearch));
		if (GetLastError() != ERROR_NO_MORE_FILES)
			PrintAndLog("GetBSAfiles","Unknown error during BSA search - some Nif files inside archives may be unaccessible.");
	}
	else
	{
		PrintAndLog("GetBSAfiles","No BSA files found!");
	}
	FindClose(h);
	return BSAfiles;
}

void NifSE_PreloadCallback(void * reserved) {
	UInt32 type, version, length;

	UInt32 modID;
	bool modLoaded;
	UInt32 nifSEv = getV(0x0001,0x00,0x0,0x3);
	UInt32 nifID;
	string nifPath;

	string changes;
	UInt32 chNode;
	UInt32 chType;
	UInt32 chAct;
	string chVal;

	NifFile* nifPtr = NULL;

	dPrintAndLog("NifLoad","Clearing previous RegList.");
	NifFile::RegList.clear();
	NifFile::RegListByFilename.clear();

	while( serInterface->GetNextRecordInfo(&type, &version, &length) ) {
		dPrintAndLog("NifLoad",string("Type '")+((char*)&type)[3]+((char*)&type)[2]+((char*)&type)[1]+((char*)&type)[0]+"'\tVersion "+UIntToString(version)+"\tLength "+UIntToString(length));
		switch (type) {
			case 'MOD ':
				dPrintAndLog("NifLoad","'MOD ' record - new mod's NifFiles.");
				serInterface->ReadRecordData(&modID, sizeof(UInt8));
				dPrintAndLog("NifLoad","Saved modID: "+UIntToString(modID)+".");
				if ( !(serInterface->ResolveRefID(modID << 24, &modID)) ) {
					modLoaded = false;
					dPrintAndLog("NifLoad","Mod no longer loaded.");
				}
				else {
					modLoaded = true;
					modID = modID >> 24;
					dPrintAndLog("NifLoad","modID resolved: "+UIntToString(modID)+".");
				}
				break;

			case 'niID':
				dPrintAndLog("NifLoad","'niID' record - new NifFile.");
				if ( modLoaded )
					serInterface->ReadRecordData(&nifID, sizeof(UInt32));
				nifPath = "";
				nifSEv = getV(0x0001,0x00,0x0,0x3); // defaults to v1.0 a"1.3", as this was the last version to not include version information
				dPrintAndLog("NifLoad","New NifFile #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
				break;

			case 'nSEV':
				dPrintAndLog("NifLoad","'nSEV' record - NifFile version.");
				serInterface->ReadRecordData(&nifSEv, sizeof(UInt32));
				dPrintAndLog("NifLoad","NifFile version #"+UIntToString(nifSEv)+".");
				break;

			case 'niRo': // deprecated "oriPath"
				dPrintAndLog("NifLoad","'niRo' record - new oriPath.");
				if ( modLoaded ) {
					if ( nifPath == "" ) {
						nifPath = ReadString(length);
						dPrintAndLog("NifLoad","oriPath is \""+nifPath+"\".");
					}
					else {
						nifPtr = new NifFile(ReadString(length), nifPath);
						dPrintAndLog("NifLoad","New deprecated nif created.");
					}
				}
				break;

			case 'niRa': // deprecated "altPath"
				dPrintAndLog("NifLoad","'niRa' record - new altPath.");
				if ( modLoaded ) {
					if ( nifPath == "" ) {
						nifPath = ReadString(length);
						dPrintAndLog("NifLoad","altPath is \""+nifPath+"\".");
					}
					else {
						nifPtr = new NifFile(nifPath, ReadString(length));
						dPrintAndLog("NifLoad","New deprecated nif created.");
					}
				}
				break;

			case 'niRe':
				dPrintAndLog("NifLoad","'niRe' record - new filename, editable.");
				if ( modLoaded ) {
					nifPath = ReadString(length);
					nifPtr = new NifFile(nifPath, modID, nifID, true, nifSEv);
					dPrintAndLog("NifLoad","Filename is \""+nifPath+"\".");
				}
				break;

			case 'niRc':
				dPrintAndLog("NifLoad","'niRc' record - new filename, const.");
				if ( modLoaded ) {
					nifPath = ReadString(length);
					nifPtr = new NifFile(nifPath, modID, nifID, false, nifSEv);
					dPrintAndLog("NifLoad","Filename is \""+nifPath+"\".");
				}
				break;

			case 'niCh':
				dPrintAndLog("NifLoad","'niCh' record - new changes.");
				if ( modLoaded ) {
					changes = ReadString(length);
					nifPtr->delta = changes;
					dPrintAndLog("NifLoad","ChangeLog loaded.");
					while ( changes.length() != 0 ) {
						LoadChangelog(changes, chNode, chType, chAct, chVal);
						dPrintAndLog("NifLoad","Changes loaded; parsing.");
						switch (chType) {
							case kNiflibType_NiExtraData:
							case kNiflibType_BSBound:
							case kNiflibType_BSDecalPlacementVectorExtraData:
							case kNiflibType_BSFurnitureMarker:
							case kNiflibType_BSWArray:
							case kNiflibType_NiArkAnimationExtraData:
							case kNiflibType_NiArkImporterExtraData:
							case kNiflibType_NiArkShaderExtraData:
							case kNiflibType_NiArkTextureExtraData:
							case kNiflibType_NiArkViewportInfoExtraData:
							case kNiflibType_NiBinaryExtraData:
							case kNiflibType_NiBinaryVoxelExtraData:
							case kNiflibType_NiBooleanExtraData:
							case kNiflibType_NiColorExtraData:
							case kNiflibType_NiFloatExtraData:
							case kNiflibType_NiFloatsExtraData:
							case kNiflibType_NiIntegerExtraData:
							case kNiflibType_BSXFlags:
							case kNiflibType_NiIntegersExtraData:
							case kNiflibType_NiStringExtraData:
							case kNiflibType_NiStringsExtraData:
							case kNiflibType_NiTextKeyExtraData:
							case kNiflibType_NiVectorExtraData:
							case kNiflibType_NiVertWeightsExtraData:
								nifPtr->loadChNiExtraData(chNode, chAct, chType, chVal);
								break;

							case kNiflibType_NiObjectNET:
								nifPtr->loadChNiObjectNET(chNode, chAct, chVal);
								break;

							case kNiflibType_NiAVObject:
								nifPtr->loadChNiAVObject(chNode, chAct, chVal);
								break;

							case kNiflibType_NiNode:
								nifPtr->loadChNiNode(chNode, chAct, chVal);
								break;

							case kNiflibType_NiAlphaProperty:
								nifPtr->loadChNiAlphaProperty(chNode, chAct, chVal);
								break;

							case kNiflibType_NiTexturingProperty:
								nifPtr->loadChNiTexturingProperty(chNode, chAct, chVal);
								break;

							case kNiflibType_NiSourceTexture:
								nifPtr->loadChNiSourceTexture(chNode, chAct, chVal);
								break;

							default:
								dPrintAndLog("NifLoad","\n\n\t\tBlock type is unsupported! Loaded nif will be incorrect!\n");
								break;
						}
					}
				}
				break;

			default:
				dPrintAndLog("NifLoad","Unknown record type.");
		}
	}
	dPrintAndLog("NifLoad","Load complete.\n");
}
