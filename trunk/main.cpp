#include "main.h"

extern "C" {

	bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
	{
#ifdef _DEBUG
		_MESSAGE("NifSE v%u.%0*u b:%x a:%x", getMajorV(), 2, getMinorV(), getBetaV(), getAlphaV());
#else
		if ( isAlpha() )
			_MESSAGE("NifSE v%u.%0*u a:%x", getMajorV(), 2, getMinorV(), getAlphaV());
		else if ( isBeta() )
			_MESSAGE("NifSE v%u.%0*u b:%x", getMajorV(), 2, getMinorV(), getBetaV());
		else
			_MESSAGE("NifSE v%u.%0*u", getMajorV(), 2, getMinorV());
#endif
		_MESSAGE("\n\tquery");

		// fill out the info structure
		info->name = g_pluginName.c_str();
		info->version = g_pluginVersion;
		info->infoVersion = PluginInfo::kInfoVersion;

		// version checks
		if(!obse->isEditor)
		{
			if(obse->obseVersion < OBSE_VERSION_INTEGER)
			{
				_ERROR("OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
				return true;
			}

			if(obse->oblivionVersion != OBLIVION_VERSION)
			{
				_ERROR("Incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
				return true;
			}

			strInterface = (OBSEStringVarInterface*)obse->QueryInterface(kInterface_StringVar);
			if(!strInterface)
			{
				_ERROR("string_var Interface not found");
				return false;
			}

			if(strInterface->version < OBSEStringVarInterface::kVersion)
			{
				_ERROR("Incorrect string_var version found (got %08X need %08X)", strInterface->version, OBSESerializationInterface::kVersion);
				return false;
			}

			serInterface = (OBSESerializationInterface *)obse->QueryInterface(kInterface_Serialization);
			if(!serInterface)
			{
				_ERROR("Serialization Interface not found");
				return false;
			}

			if(serInterface->version < OBSESerializationInterface::kVersion)
			{
				_ERROR("Incorrect Serialization version found (got %08X need %08X)", serInterface->version, OBSESerializationInterface::kVersion);
				return false;
			}

			arrInterface = (OBSEArrayVarInterface*)obse->QueryInterface(kInterface_ArrayVar);
			if (!arrInterface)
			{
				_ERROR("Array interface not found");
				return false;
			}
		}
		msgInterface = (OBSEMessagingInterface*)obse->QueryInterface(kInterface_Messaging);
		if(!msgInterface)
		{
			_ERROR("Messaging Interface not found");
			return false;
		}

		if(msgInterface->version < OBSEMessagingInterface::kVersion)
		{
			_ERROR("Incorrect messaging version found (got %08X need %08X)", msgInterface->version, OBSEMessagingInterface::kVersion);
			return false;
		}

		// version checks pass

		return true;
	}

	bool OBSEPlugin_Load(const OBSEInterface * obse)
	{
		_MESSAGE("\tload\n");

		g_pluginHandle = obse->GetPluginHandle();

		// register commands
		obse->SetOpcodeBase(0x25CF);
#ifdef _DEBUG
		obse->RegisterCommand(		&kCommandInfo_NifWriteToDisk									); //0x2000
#endif
		obse->SetOpcodeBase(0x24F0); // to 0x24FF (inclusive)

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetAltGrip,					kRetnType_String); //0x24F0 T
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOffHand,					kRetnType_String); //0x24F1 T
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetBackShield,					kRetnType_String); //0x24F2 T
		// ------------------------------------- End of Deprecated Functions ------------------------------------- //

		obse->RegisterCommand(		&kCommandInfo_NifOpen											); //0x24F3 T S L
		obse->RegisterCommand(		&kCommandInfo_NifClose											); //0x24F4 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetPath,						kRetnType_String); //0x24F5 T
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOriginalPath,				kRetnType_String); //0x24F6 T

		obse->RegisterCommand(		&kCommandInfo_NifGetNumExtraData								); //0x24F7 T
		obse->RegisterCommand(		&kCommandInfo_NifAddExtraData									); //0x24F8 T S L ?
		obse->RegisterCommand(		&kCommandInfo_NifDeleteNthExtraData								); //0x24F9 T S L ?

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataName,			kRetnType_String); //0x24FA T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthExtraDataName							); //0x24FB T S L
		obse->RegisterCommand(		&kCommandInfo_NifGetExtraDataIndexByName						); //0x24FC T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataType,			kRetnType_String); //0x24FE T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthExtraDataString,			kRetnType_String); //0x24FD T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthExtraDataString							); //0x24FF T S L
		// ----------------------------------------- 0x2450 out of range ----------------------------------------- //

		obse->SetOpcodeBase(0x2510); // to 0x252F (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NifGetNumChildren									); //0x2510 T
		obse->RegisterCommand(		&kCommandInfo_NifDeleteNthChild									); //0x2511 T S L

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildName,				kRetnType_String); //0x2512 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildName								); //0x2513   S L
		obse->RegisterCommand(		&kCommandInfo_NifGetChildIndexByName							); //0x2514 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildType,				kRetnType_String); //0x2515 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalTransform,		kRetnType_Array	); //0x2516 T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTransform						); //0x2517 

		obse->SetOpcodeBase(0x2518);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalTranslation,	kRetnType_Array	); //0x2518 T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTranslation					); //0x2519 

		obse->SetOpcodeBase(0x251A);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildLocalRotation,		kRetnType_Array	); //0x251A T
//		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalRotation						); //0x251B 

		obse->SetOpcodeBase(0x251C);
		obse->RegisterCommand(		&kCommandInfo_NifGetNthChildLocalScale							); //0x251C T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalScale							); //0x251D T S L

		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTransformTEMP					); //0x251E T S L
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalTranslationTEMP				); //0x251F T S L
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildLocalRotationTEMP					); //0x2520 T S L

		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasMaterial							); //0x2521 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddMaterial							); //0x2522 
		obse->SetOpcodeBase(0x2523);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildMaterial,			kRetnType_String); //0x2523 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildMaterial							); //0x2524 T S L

		// ----------------------------------------- 0x2530 out of range ----------------------------------------- //

		obse->SetOpcodeBase(0x25C0); // to 25CF (inclusive)
		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasTexturingProp						); //0x25C0 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddTexturingProp						); //0x25C1 
		obse->SetOpcodeBase(0x25C2);
		obse->RegisterCommand(		&kCommandInfo_NifNthChildHasBaseTexture							); //0x25C2 T
//		obse->RegisterCommand(		&kCommandInfo_NifNthChildAddBaseTexture							); //0x25C3 
		obse->SetOpcodeBase(0x25C4);
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetNthChildBaseTexture,		kRetnType_String); //0x25C4 T
		obse->RegisterCommand(		&kCommandInfo_NifSetNthChildBaseTexture							); //0x25C5 T S L

		// ----------------------------------------- 0x25D0 out of range ----------------------------------------- //

		// set up serialization callbacks when running in the runtime
		if(!obse->isEditor)
		{
			BSAlist = GetBSAfiles();
			_MESSAGE("List of BSA files: (excluding BSA files known to contain non-NIF data)");
			for ( BSAit = BSAlist.begin(); BSAit != BSAlist.end(); ++BSAit ) {
				_MESSAGE(("\t"+(*BSAit)).c_str());
			}
			_MESSAGE(("\t\t"+UIntToString(BSAlist.size())+" total.").c_str());

			_MESSAGE("\nListening to OBSE dispatches.");
			msgInterface->RegisterListener(g_pluginHandle, "OBSE", MessageHandler);

			_MESSAGE("\nRegistering String Interface.");
			strInterface->Register(strInterface);

			_MESSAGE("\nSetting Serialization callbacks.");
			serInterface->SetSaveCallback(g_pluginHandle, NifSE_SaveCallback);
			serInterface->SetPreloadCallback(g_pluginHandle, NifSE_PreloadCallback);
			serInterface->SetNewGameCallback(g_pluginHandle, NifSE_NewCallback);

			_MESSAGE("\nInitializing NifSE Hooks.");
			Hooks_NifSE_Init();
		}
/*		else {
			_MESSAGE("Listening to OBSE dispatches.");
			msgInterface->RegisterListener(g_pluginHandle, "OBSE", EditorMessageHandler);
		}*/

		_MESSAGE("\n\tInitialization complete.\n\n");

		return true;
	}

};
