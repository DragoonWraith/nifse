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
		obse->SetOpcodeBase(0x24F0); // to 0x24FF (inclusive)

	// ----------------------------------------------- NifScript Beta ----------------------------------------------- //

		// Deprecated Functions //
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetAltGrip,					kRetnType_String); //0x24F0 T S
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOffHand,					kRetnType_String); //0x24F1 T S
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetBackShield,					kRetnType_String); //0x24F2   S

	// ------------------------------------------------- NifSE v1.0 ------------------------------------------------- //

		// Debug Function //
#ifdef _DEBUG
		obse->RegisterCommand(		&kCommandInfo_NifWriteToDisk									); //0x25F3
#else
		obse->SetOpcodeBase(0x24F4);
#endif	
		// Basic Functions //
		obse->RegisterCommand(		&kCommandInfo_NifOpen											); //0x24F4 T S L
		obse->RegisterCommand(		&kCommandInfo_NifClose											); //0x24F5 T

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetPath,						kRetnType_String); //0x24F6 T
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOriginalPath,				kRetnType_String); //0x24F7 T

		obse->RegisterCommand(		&kCommandInfo_NifGetNumBlocks									); //0x24F8

		obse->RegisterCommand(		&kCommandInfo_GetNifTypeIndex									); //0x24F9

		// NiObject //
		obse->RegisterCommand(		&kCommandInfo_NiObjectGetType									); //0x24FA
		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectGetTypeName,				kRetnType_String); //0x24FB
		obse->RegisterCommand(		&kCommandInfo_NiObjectTypeDerivesFrom							); //0x24FC

		// NiObjectNET //
		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectNETGetName,				kRetnType_String); //0x24FD T
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETSetName								); //0x24FE T S L

		obse->RegisterCommand(		&kCommandInfo_NiObjectNETGetNumExtraData						); //0x24FF

		/* 0x2450 out of range */	obse->SetOpcodeBase(0x2510);	// to 0x252F (inclusive)

		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectNETGetExtraData,			kRetnType_Array	); //0x2510
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETGetExtraDataByName						); //0x2511
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETAddExtraData							); //0x2512   S L
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETDeleteExtraData						); //0x2513   S L

		// NiExtraData //
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataGetNumber								); //0x2514
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetNumber								); //0x2515   S L

		obse->RegisterTypedCommand(	&kCommandInfo_NiExtraDataGetString,				kRetnType_String); //0x2516
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetString								); //0x2517   S L

		obse->RegisterTypedCommand(	&kCommandInfo_NiExtraDataGetArray,				kRetnType_Array	); //0x2518
/*		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetArray								); //0x2519   S L
*/		obse->SetOpcodeBase(0x251A);

		// NiAVObject //
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalTransform,		kRetnType_Array	); //0x251A 
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalTranslation,	kRetnType_Array	); //0x251B T
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalRotation,		kRetnType_Array	); //0x251C T
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetLocalScale							); //0x251D T

/*		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTransform						); //0x251E
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTranslation						); //0x251F
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalRotation						); //0x2520
*/		obse->SetOpcodeBase(0x2521);
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalScale							); //0x2521 T S L

		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTransformTEMP					); //0x2522 T S L
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTranslationTEMP					); //0x2523 T S L
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalRotationTEMP					); //0x2524 T S L

		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetNumProperties						); //0x2525
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetProperties,			kRetnType_Array	); //0x2526
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetPropertyByType						); //0x2527
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectAddProperty								); //0x2528   S L
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectDeleteProperty							); //0x2529   S L

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureCount				); //0x252A
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureCount				); //0x252B   S L

		obse->RegisterCommand(		&kCommandInfo_NiNodeGetNumChildren								); //0x252C
		obse->RegisterTypedCommand(	&kCommandInfo_NiNodeGetChildren,				kRetnType_Array	); //0x252D
		obse->RegisterCommand(		&kCommandInfo_NiNodeGetChildByName								); //0x252E
		obse->RegisterCommand(		&kCommandInfo_NiNodeDeleteChild									); //0x252F   S L

		/* 0x2530 out of range */	obse->SetOpcodeBase(0x25C0);	// to 25CF (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureSource				); //0x25C0
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureClampMode			); //0x25C1
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureFilterMode			); //0x25C2
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureFlags				); //0x25C3
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureUVSet				); //0x25C4
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyTextureHasTransform			); //0x25C5
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureTranslation,
																					kRetnType_Array	); //0x25C6
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureTiling,
																					kRetnType_Array	); //0x25C7
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureRotation				); //0x25C8
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureCenterOffset,
																					kRetnType_Array	); //0x25C9

		/* 0x25D0 out of range */	

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