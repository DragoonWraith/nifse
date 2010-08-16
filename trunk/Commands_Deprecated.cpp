#include "Commands_Deprecated.h"

// for easily switching between two versions of a mesh - modified and original
string ToggleTag(string path, string element, string newVal) {
	if ( path.find("NifScript") != string::npos ) { // already tagged with something
		if ( path.find(element) != string::npos ) { // already tagged with THIS element
			if ( path.find(element+newVal) != string::npos ) { // element has been changed to appropriate value, want to remove change
				path.erase(path.find(element+newVal)-1,(element+newVal).length()+1); // 1's to account for the prefixed '.'
				if ( !_stricmp(path.substr(path.length()-14,14).c_str(),".NifScript.nif") ) { // only tag in this path
					dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged correctly, only tag in path, removing all tags and returning original mesh!");
					if ( !_stricmp(path.substr(0, s_nifSEPathLen).c_str(), s_nifSEPath) ) {
						NifFile* nifPtr = NULL;
						NifFile::getRegNif(path.substr(s_nifSEPathLen), nifPtr);
						if ( nifPtr )
							path = nifPtr->basePath;
						else
							throw std::exception("Registered nif not found in registry.");
					}
					else
						path.erase(path.find(".NifScript"),10);
				}
				else
					dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged correctly, removing this tag. Other tags remain.");
			}
			else { // already changed this element, but changing it to a new value
				string::size_type oldValPos = path.find(element)+element.length();
				string::size_type oldValLen = path.find(".",oldValPos)-oldValPos;
				path.replace(oldValPos,oldValLen,newVal);
				dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged, value changed to \""+newVal+"\".");
			}
		}
		else { // tagged, but this element's new
			path.insert(path.length()-4,"."+element+newVal);
			dPrintAndLog("ToggleTag","Element \""+element+"\" added to existing tags with value \""+newVal+"\".");
		}
	}
	else { // completely untagged
		path.insert(path.length()-4,".NifScript."+element+newVal);
		dPrintAndLog("ToggleTag","Element \""+element+"\" first tag in path. Set with value \""+newVal+"\".");
	}
	return path;
}

static bool Cmd_NifGetAltGrip_Execute(COMMAND_ARGS) { // returns path to model using opposite number of hands
	dPrintAndLog("NifGetAltGrip");
	TESForm* form = NULL;

	if (ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form))
	{
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESObjectWEAP* weapon = (TESObjectWEAP*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESObjectWEAP, 0);
			if ( weapon ) { // only weapons have handedness
				dPrintAndLog("NifGetAltGrip","Weapon: "+string(weapon->fullName.name.m_data));
				if ( weapon->type <= 3 ) { // only works on blades/blunt weapons
					TESModel* model = (TESModel*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESModel, 0);
					string oriPath = model->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","AltWeapon");
					if ( CheckFileLocation(altPath) == 0 ) {
						NifFile* alt = new NifFile(oriPath, altPath);
						if ( alt->root ) {
							list<Niflib::NiExtraDataRef>::size_type edID = alt->getEDIndexByName("Prn");
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt->findExtraData(edID));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetAltGrip","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "SideWeapon" ) { // one-handed according to Nif
									Prn->SetData("BackWeapon");
									dPrintAndLog("NifGetAltGrip","Weapon switched from 1h to 2h! Prn = "+Prn->GetData());
									alt->extraDataChanges += changeLog(edID, ED_Str, Act_ED_SetValue, "BackWeapon");
								}
								else if ( Prn->GetData() == "BackWeapon" ) { // two-handed according to Nif
									Prn->SetData("SideWeapon");
									dPrintAndLog("NifGetAltGrip","Weapon switched from 2h to 1h! Prn = "+Prn->GetData());
									alt->extraDataChanges += changeLog(edID, ED_Str, Act_ED_SetValue, "SideWeapon");
								}
								else {
									PrintAndLog("NifGetAltGrip","Unknown weapon type! Prn = "+Prn->GetData());
									return true;
								}
								dPrintAndLog("NifGetAltGrip","New Alt-Grip Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetAltGrip","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else {
							PrintAndLog("NifGetAltGrip","Nif could not be read!");
							return true;
						}
					}

					// return the new mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetAltGrip","Alt grip model path returned to Oblivion! path = \""+altPath+"\".\n");
				}
				else // weapon->type > 3
					PrintAndLog("NifGetAltGrip","Invalid weapon type!\n");
			}
			else // !weapon
				PrintAndLog("NifGetAltGrip","Argument not weapon!\n");
		}
		else // !form
			PrintAndLog("NifGetAltGrip","Invalid argument!\n");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetAltGrip","Failed to determine passed argument!\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetAltGrip,"Returns the opposite handed version of a weapon mesh. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);

static bool Cmd_NifGetOffHand_Execute(COMMAND_ARGS) {
	dPrintAndLog("NifGetOffHand");

	TESForm* form = NULL;
	if (ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form))
	{
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESObjectWEAP* weapon = (TESObjectWEAP*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESObjectWEAP, 0);
			if ( weapon ) { // only weapons can be wielded off-hand
				dPrintAndLog("NifGetOffHand","Weapon: "+string(weapon->fullName.name.m_data));
				if ( weapon->type <= 3 ) { // only works on blades/blunt weapons
					TESModel* model = (TESModel*)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESModel, 0);
					string oriPath = model->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","Torch");
					if ( CheckFileLocation(altPath) == 0 ) {
						NifFile* alt = new NifFile(oriPath, altPath);
						if ( alt->root ) {
							list<Niflib::NiExtraDataRef>::size_type edID = alt->getEDIndexByName("Prn");
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt->findExtraData(edID));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetOffHand","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "SideWeapon" || Prn->GetData() == "BackWeapon" ) { // one of two weapon values
									Prn->SetData("Torch");
									dPrintAndLog("NifGetOffHand","Weapon switched to Shield! Prn = "+Prn->GetData());
									alt->extraDataChanges += changeLog(edID, ED_Str, Act_ED_SetValue, "Torch");
								}
								else {
									PrintAndLog("NifGetOffHand","Unknown weapon type! Prn = "+Prn->GetData());
									return true;
								}
								vector<Niflib::NiAVObjectRef>::size_type chID = alt->getChildIndexByName("Scb");
								NiAVObjectRef Scabbard = alt->root->GetChildren()[chID];
								if ( Scabbard != NULL ) {
									dPrintAndLog("NifGetOffHand","Removing scabbard!");
									alt->root->RemoveChild(Scabbard);
									alt->childrenChanges += changeLog(chID, Ch_AVObj, Act_Remove);
								}
								else
									dPrintAndLog("NifGetOffHand","No scabbard to remove!");
								dPrintAndLog("NifGetOffHand","New off-hand Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetOffHand","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else { // !alt->root
							PrintAndLog("NifGetOffHand","Nif could not be read!");
							return true;
						}
					}

					// return the mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetOffHand","Off hand model path returned to Oblivion! path = \""+altPath+"\".\n");
				}
				else // weapon->type > 3
					PrintAndLog("NifGetOffHand","Invalid weapon type!\n");
			}
			else // !weapon
				PrintAndLog("NifGetOffHand","Argument not weapon!\n");
		}
		else // !form
			PrintAndLog("NifGetOffHand","Invalid argument!\n");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetOffHand","Failed to determine passed argument!\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetOffHand,"Returns the off-hand version of a weapon mesh. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);

// this function is not tested
static bool Cmd_NifGetBackShield_Execute(COMMAND_ARGS) {
	dPrintAndLog("NifGetBackShield");

	TESForm * form = NULL;
	if ( ExtractArgsEx(paramInfo, arg1, opcodeOffsetPtr, scriptObj, eventList, &form) ) {
		if ( !form )
			if ( thisObj )
				form = thisObj->baseForm;

		if ( form ) {
			TESBipedModelForm	* bip = (TESBipedModelForm *)Oblivion_DynamicCast(form, 0, RTTI_TESForm, RTTI_TESBipedModelForm, 0);
			if ( bip ) { // to be shield must be BipedModel
				dPrintAndLog("NifGetBackShield","Shield: "+string(form->GetFullName()->name.m_data));
				if ( bip->GetSlot() == TESBipedModelForm::kPart_Shield ) { // only works on shields
					string oriPath = bip->bipedModel->nifPath.m_data;
					string altPath = ToggleTag(oriPath,"Prn","Bip01 L Shoulder Helper");
					if ( CheckFileLocation(altPath) == 0 ) {
						NifFile* alt = new NifFile(oriPath, altPath);
						if ( alt->root ) {
							list<Niflib::NiExtraDataRef>::size_type edID = alt->getEDIndexByName("Prn");
							Niflib::NiStringExtraDataRef Prn = DynamicCast<Niflib::NiStringExtraData>(alt->findExtraData(edID));
							if ( Prn != NULL ) {
								dPrintAndLog("NifGetBackShield","Prn node found! Prn = "+Prn->GetData());
								if ( Prn->GetData() == "Bip01 L ForearmTwist" ) { // is a shield
									Prn->SetData("Bip01 L Shoulder Helper");
									dPrintAndLog("NifGetBackShield","Shield switched to shoulder! Prn = "+Prn->GetData());
									alt->extraDataChanges += changeLog(edID, ED_Str, Act_ED_SetValue, "Bip01 L ForearmTwist");
								}
								else {
									PrintAndLog("NifGetBackShield","Unknown shield type! Prn = "+Prn->GetData());
									return true;
								}
								vector<Niflib::NiAVObjectRef>::size_type chID = 0;
								for ( alt->childIt = alt->root->GetChildren().begin() ; alt->childIt != alt->root->GetChildren().end() ; ++(alt->childIt), ++chID ) {
									dPrintAndLog("NifGetBackShield",string("Shield \"")+form->GetFullName()->name.m_data+"\" Child \""+(*(alt->childIt))->GetName()+"\" translated and rotated!");
									Niflib::Vector3 nuTranslation = (*(alt->childIt))->GetLocalTranslation()+Niflib::Vector3(25,-11,-20);
									(*(alt->childIt))->SetLocalTranslation(nuTranslation);
									alt->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocTranslation,VectorToString(nuTranslation));
									Niflib::Matrix33 nuRotation = (*(alt->childIt))->GetLocalRotation()*Niflib::Matrix33(-0.9249,-0.1247,0.3593,-0.4966,0.9655,-0.1710,-0.3256,-0.2287,-0.9174);
									(*(alt->childIt))->SetLocalRotation(nuRotation);
									alt->childrenChanges += changeLog(chID,Ch_AVObj,Act_AV_SetLocRotation,MatrixToString(nuRotation));
								}
								dPrintAndLog("NifGetBackShield","New back shield Nif created!");
							}
							else { // Prn == NULL
								PrintAndLog("NifGetBackShield","NiStringExtraData \"Prn\" node not found!");
								return true;
							}
						}
						else { // !alt->root
							PrintAndLog("NifGetBackShield","Nif could not be read!");
							return true;
						}
					}

					// return the mesh.
					strInterface->Assign(PASS_COMMAND_ARGS, altPath.c_str());
					dPrintAndLog("NifGetBackShield","Back shield model path returned to Oblivion! path = \""+altPath+"\".\n");
				}
				else // shield->BipedModel.getSlot() != kPart_Shield
					PrintAndLog("NifGetBackShield","Invalid armor type (needs shield)!\n");
			}
			else // !shield
				PrintAndLog("NifGetBackShield","Argument not armor!\n");
		}
		else // !form
			PrintAndLog("NifGetBackShield","Invalid argument!\n");
	}
	else // !ExtractArgs
		PrintAndLog("NifGetBackShield","Failed to determine passed argument!\n");

	return true;
}

DEFINE_COMMAND_PLUGIN(NifGetBackShield,"Returns a version of a shield suitable for placing on one's back. Creates mesh if necessary. Deprecated.", 0, 1, kParams_OneOptionalInventoryObject);