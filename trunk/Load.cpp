#include "Load.h"

extern std::map<const char*, const char*>* FunctionDocMap (NULL);

void MessageHandler(OBSEMessagingInterface::Message* msg) {
	switch (msg->type) {
		case OBSEMessagingInterface::kMessage_PostLoad:
			_MESSAGE("Game loaded: Creating ni\\ directory.\n");
			CreateDirectory(string(GetOblivionDirectory()+"Data\\"+s_nifSEFullPath).c_str(), NULL);
			break;

		case OBSEMessagingInterface::kMessage_ExitGame:
			_MESSAGE("Game quit: Deleting ni\\ directory.");
			RemoveDirectory(string(GetOblivionDirectory()+"Data\\"+s_nifSEFullPath).c_str());
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

void LoadChangelog(string &changes, string &chNode, UInt32 &chType, UInt32 &chAct, string &chVal) {
	string::size_type posS;
	string::size_type posF;

	posS = 0;
	posF = changes.find(logNode,posS);
	chNode = changes.substr(posS,posF-posS);
	dPrintAndLog("LoadChangelog","Change node: \""+chNode+"\".");

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
	dPrintAndLog("NifLoad","loading saved NifFiles");
	UInt32 type, version, length;

	UInt32 modID;
	bool modLoaded;
	UInt32 nifSEv = getV(0x0001,0x00,0x0,0x3);
	UInt8 testInt;
	UInt32 nifID;
	string nifPath;

	string changes;
	string chNode;
	UInt32 chType;
	UInt32 chAct;
	string chVal;

	NiExtraDataRef edNode;
	Niflib::NiStringExtraDataRef edStrNode;

	NiAVObjectRef avNode;
	vector<float> vvector;
	vector< vector<float> > vmatrix;
	Niflib::Vector3 nvector3;
	Niflib::Matrix33 nmatrix33;
	Niflib::Matrix44 nmatrix44;

	NifFile* nifPtr = NULL;

	dPrintAndLog("NifLoad","Clearing previous RegList.");
	for ( map<UInt8, map<UInt32, NifFile*> >::iterator RegListIter = NifFile::RegList.begin(); RegListIter != NifFile::RegList.end(); ++RegListIter )
		for ( map<UInt32, NifFile*>::iterator NifListIter = RegListIter->second.begin(); NifListIter != RegListIter->second.end(); ++NifListIter )
			std::remove(NifListIter->second->filePath.c_str());
	NifFile::RegList.clear();

	dPrintAndLog("NifLoad","Previous RegList cleared.");
	while( serInterface->GetNextRecordInfo(&type, &version, &length) ) {
		dPrintAndLog("NifLoad",string("Type '")+((char*)&type)[3]+((char*)&type)[2]+((char*)&type)[1]+((char*)&type)[0]+"'\tVersion "+UIntToString(version)+"\tLength "+UIntToString(length));
		switch (type) {
			case 'test':
				dPrintAndLog("NifLoad","'test' record.");
				serInterface->ReadRecordData(&testInt, sizeof(UInt8));
				dPrintAndLog("NifLoad","Saved test number = "+UIntToString(testInt));
				break;

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

			case 'niED':
				dPrintAndLog("NifLoad","'niED' record - new ExtraData changes.");
				if ( modLoaded ) {
					changes = ReadString(length);
					dPrintAndLog("NifLoad","ExtraData changelog loaded.");
					edNode = NULL;
					edStrNode = NULL;
					while ( changes.length() != 0 ) {
						LoadChangelog(changes, chNode, chType, chAct, chVal);
						dPrintAndLog("NifLoad","Changes loaded.");
						switch (chAct) {
							case Act_Add:
								dPrintAndLog("NifLoad","Adding new ExtraData node.");
								switch (chType) {
									case ED_ExtraData:
										dPrintAndLog("NifLoad","Adding NiExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiExtraData::Create()));
										break;

									case ED_Bound:
										dPrintAndLog("NifLoad","Adding BSBound node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSBound::Create()));
										break;

									case ED_Furniture:
										dPrintAndLog("NifLoad","Adding BSFurnitureMarker node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSFurnitureMarker::Create()));
										break;

									case ED_Binary:
										dPrintAndLog("NifLoad","Adding NiBinaryExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBinaryExtraData::Create()));
										break;

									case ED_BinaryVoxel:
										dPrintAndLog("NifLoad","Adding NiBinaryVoxelData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBinaryVoxelData::Create()));
										break;

									case ED_Boolean:
										dPrintAndLog("NifLoad","Adding NiBooleanExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiBooleanExtraData::Create()));
										break;

									case ED_Color:
										dPrintAndLog("NifLoad","Adding NiColorExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiColorExtraData::Create()));
										break;

									case ED_Float:
										dPrintAndLog("NifLoad","Adding NiFloatExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiFloatExtraData::Create()));
										break;

									case ED_Floats:
										dPrintAndLog("NifLoad","Adding NiFloatsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiFloatsExtraData::Create()));
										break;

									case ED_Int:
										dPrintAndLog("NifLoad","Adding NiIntegerExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiIntegerExtraData::Create()));
										break;

									case ED_BSXFlags:
										dPrintAndLog("NifLoad","Adding BSXFlags node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::BSXFlags::Create()));
										break;

									case ED_Ints:
										dPrintAndLog("NifLoad","Adding NiIntegersExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiIntegersExtraData::Create()));
										break;

									case ED_Str:
										dPrintAndLog("NifLoad","Adding NiStringExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiStringExtraData::Create()));
										break;

									case ED_Strs:
										dPrintAndLog("NifLoad","Adding NiStringsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiStringsExtraData::Create()));
										break;

									case ED_TextKey:
										dPrintAndLog("NifLoad","Adding NiTextKeyExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiTextKeyExtraData::Create()));
										break;

									case ED_Vector:
										dPrintAndLog("NifLoad","Adding NiVectorExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiVectorExtraData::Create()));
										break;

									case ED_VertWeights:
										dPrintAndLog("NifLoad","Adding NiVertWeightsExtraData node.");
										edNode = DynamicCast<Niflib::NiExtraData>(NiObjectRef(Niflib::NiVertWeightsExtraData::Create()));
										break;

									default:
										dPrintAndLog("Unknown ExtraData type.");
								}
								if ( edNode ) {
									edNode->SetName(chVal);
									nifPtr->root->AddExtraData(edNode, nifPtr->nifVersion);
									dPrintAndLog("NifLoad","ED node \""+chVal+"\" added.");
								}
								break;

							default:
								if ( chNode[0] == logNumber && StringToUInt(chNode.substr(1,chNode.length()-1)) < nifPtr->root->GetExtraData().size() )
									edNode = nifPtr->findExtraData(StringToUInt(chNode.substr(1,chNode.length()-1)));
								else
									edNode = nifPtr->getEDByName(chNode);

								if ( !edNode ) {
									dPrintAndLog("NifLoad","ExtraData node does not exist.");
									break;
								}
								else
									dPrintAndLog("NifLoad","ExtraData node found.");

								switch (chType) {
									case ED_ExtraData:
										dPrintAndLog("NifLoad","Changing ExtraData node.");
										switch (chAct) {
											case Act_Remove:
												nifPtr->root->RemoveExtraData(edNode);
												dPrintAndLog("NifLoad","ED node removed.");
												break;

											case Act_SetName:
												edNode->SetName(chVal);
												dPrintAndLog("NifLoad","ED node renamed \""+chVal+"\".");
												break;

											default:
												dPrintAndLog("NifLoad","Unknown ED node operation.");
										}
										break;

									case ED_Str:
										dPrintAndLog("NifLoad","Changing ExtraStringDataNode.");
										edStrNode = DynamicCast<NiStringExtraData>(edNode);
										if ( edStrNode ) {
											switch (chAct) {
												case Act_ED_SetValue:
													dPrintAndLog("NifLoad","Setting String data to \""+chVal+"\".");
													edStrNode->SetData(chVal);
													break;

												default:
													dPrintAndLog("NifLoad","Unknown ED String node operation.");
											}
										}
										else
											dPrintAndLog("NifLoad","ED String node failed.");
										break;

									case ED_Bound:
									case ED_Furniture:
									case ED_Binary:
									case ED_BinaryVoxel:
									case ED_Boolean:
									case ED_Color:
									case ED_Float:
									case ED_Floats:
									case ED_Int:
									case ED_BSXFlags:
									case ED_Ints:
									case ED_Strs:
									case ED_TextKey:
									case ED_Vector:
									case ED_VertWeights:
										dPrintAndLog("NifLoad","Changes to this ED node type are unsupported.");
										break;

									default:
										dPrintAndLog("NifLoad","Unknown node type.");
								}
						}
					}
				}
				break;

			case 'niCo':
				dPrintAndLog("NifLoad","'niCo' record - Collision changes not supported.");
				break;

			case 'niCh':
				dPrintAndLog("NifLoad","'niCh' record - new Children changes.");
				if ( modLoaded ) {
					changes = ReadString(length);
					dPrintAndLog("NifLoad","Children changelog loaded.");
					avNode = NULL;
					while ( changes.length() != 0 ) {
						LoadChangelog(changes, chNode, chType, chAct, chVal);
						if ( chNode[0] == logNumber )
							avNode = nifPtr->root->GetChildren()[StringToUInt(chNode.substr(1,chNode.length()-1))];
						else
							avNode = nifPtr->getChildByName(chNode);
						
						switch (chType) {
							case Ch_AVObj:
								dPrintAndLog("NifLoad","Changing AVObject node.");
								switch (chAct) {
									case Act_Remove:
										nifPtr->root->RemoveChild(avNode);
										dPrintAndLog("NifLoad","AV node removed.");
										break;

									case Act_SetName:
										avNode->SetName(chVal);
										dPrintAndLog("NifLoad","AV node renamed \""+chVal+"\".");
										break;

									case Act_AV_SetLocTransform:
										vmatrix = StringToMatrix(chVal);
										if ( vmatrix.size() == 4 ) {
											if ( vmatrix[0].size() == 4 && vmatrix[1].size() == 4 && vmatrix[2].size() == 4 && vmatrix[3].size() == 4 ) {
												nmatrix44 = Niflib::Matrix44(vmatrix[0][0], vmatrix[0][1], vmatrix[0][2], vmatrix[0][3],
																			 vmatrix[1][0], vmatrix[1][1], vmatrix[1][2], vmatrix[1][3],
																			 vmatrix[2][0], vmatrix[2][1], vmatrix[2][2], vmatrix[2][3],
																			 vmatrix[3][0], vmatrix[3][1], vmatrix[3][2], vmatrix[3][3]);
												avNode->SetLocalTransform(nmatrix44);
												dPrintAndLog("NifLoad","AV node Local Transform set.");
											}
											else
												dPrintAndLog("NifLoad","Transform matrix missized: Is "+UIntToString(vmatrix.size())+" wide, should be 4.");
										}
										else
											dPrintAndLog("NifLoad","Transform matrix missized: Is "+UIntToString(vmatrix.size())+" tall, should be 4.");
										break;

									case Act_AV_SetLocTranslation:
										vvector = StringToVector(chVal);
										if ( vvector.size() == 3 ) {
											nvector3 = Niflib::Vector3(vvector[0], vvector[1], vvector[2]);
											avNode->SetLocalTranslation(nvector3);
											dPrintAndLog("NifLoad","AV node Local Translation set.");
										}
										else
											dPrintAndLog("NifLoad","Translation vector missized: Is "+UIntToString(vvector.size())+", should be 3.");
										break;

									case Act_AV_SetLocRotation:
										vmatrix = StringToMatrix(chVal);
										if ( vmatrix.size() == 3 ) {
											if ( vmatrix[0].size() == 3 && vmatrix[1].size() == 3 && vmatrix[2].size() == 3 ) {
												nmatrix33 = Niflib::Matrix33(vmatrix[0][0], vmatrix[0][1], vmatrix[0][2],
																			 vmatrix[1][0], vmatrix[1][1], vmatrix[1][2],
																			 vmatrix[2][0], vmatrix[2][1], vmatrix[2][2]);
												avNode->SetLocalRotation(nmatrix33);
												dPrintAndLog("NifLoad","AV node Local Rotation set.");
											}
											else
												dPrintAndLog("NifLoad","Rotation matrix missized: Is "+UIntToString(vmatrix.size())+" wide, should be 3.");
										}
										else
											dPrintAndLog("NifLoad","Rotation matrix missized: Is "+UIntToString(vmatrix.size())+" tall, should be 3.");
										break;

									case Act_AV_PropMat_SetName:
										dPrintAndLog("NifLoad","Child material changed to \""+chVal+"\".");
										avNode->GetPropertyByType(Niflib::NiMaterialProperty::TYPE)->SetName(chVal);
										break;

									case Act_AV_PropTex_SetBaseMap:
										dPrintAndLog("NifLoad","Child base texture set to \""+chVal+"\".");
										DynamicCast<Niflib::NiTexturingProperty>(avNode->GetPropertyByType(Niflib::NiTexturingProperty::TYPE))->GetTexture(Niflib::BASE_MAP).source->SetExternalTexture(chVal);
										break;

									default:
										dPrintAndLog("NifLoad","Unknown AV node operation.");
								}
								break;

							case Ch_NiCam:
							case Ch_NiGeom:
							case Ch_NiParticles:
							case Ch_NiAutoNormParticles:
							case Ch_NiParticleMeshes:
							case Ch_NiParticleSystem:
							case Ch_NiMeshParticleSystem:
							case Ch_NiRotParticles:
							case Ch_NiTriBasedGeom:
							case Ch_NiClod:
							case Ch_NiTriShape:
							case Ch_NiTriStrips:
							case Ch_NiNode:
							case Ch_AvoidNode:
							case Ch_FxWidget:
							case Ch_FxButton:
							case Ch_FxRadioButton:
							case Ch_NiBillboard:
							case Ch_NiBone:
							case Ch_NiBSAnim:
							case Ch_NiBSParticle:
							case Ch_NiSwitch:
							case Ch_NiLOD:
							case Ch_RootCol:
								dPrintAndLog("NifLoad","Child node type changes unsupported.");
								break;

							default:
								dPrintAndLog("NifLoad","Unknown node type.");
						}
					}
				}
				break;

			case 'niEf':
				dPrintAndLog("NifLoad","'niEf' record - Effects changes not supported.");
				break;

			default:
				dPrintAndLog("NifLoad","Unknown record type.");
		}
	}
	dPrintAndLog("NifLoad","Load complete.\n");
}
