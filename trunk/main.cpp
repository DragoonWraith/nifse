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
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetAltGrip,					kRetnType_String); //0x24F0 T S L
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOffHand,					kRetnType_String); //0x24F1 T S L
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetBackShield,					kRetnType_String); //0x24F2   S L

	// ------------------------------------------------- NifSE v1.0 ------------------------------------------------- //

		// Debug Function //
#ifdef _DEBUG
		obse->RegisterCommand(		&kCommandInfo_NifWriteToDisk									); //0x25F3 T     D
#else
		obse->SetOpcodeBase(0x24F4);
#endif	
		// Basic Functions //
		obse->RegisterCommand(		&kCommandInfo_NifOpen											); //0x24F4 T S L D
		obse->RegisterCommand(		&kCommandInfo_NifClose											); //0x24F5 T     D

		obse->RegisterTypedCommand(	&kCommandInfo_NifGetPath,						kRetnType_String); //0x24F6 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NifGetOriginalPath,				kRetnType_String); //0x24F7 T     D

		obse->RegisterCommand(		&kCommandInfo_NifGetNumBlocks									); //0x24F8 T     D

		obse->RegisterCommand(		&kCommandInfo_GetNifTypeIndex									); //0x24F9 T     D

		// NiObject //
		obse->RegisterCommand(		&kCommandInfo_NiObjectGetType									); //0x24FA T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectGetTypeName,				kRetnType_String); //0x24FB T     D
		obse->RegisterCommand(		&kCommandInfo_NiObjectTypeDerivesFrom							); //0x24FC T     D

		// NiObjectNET //
		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectNETGetName,				kRetnType_String); //0x24FD T     D
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETSetName								); //0x24FE T S L D

		obse->RegisterCommand(		&kCommandInfo_NiObjectNETGetNumExtraData						); //0x24FF T     D

		/* 0x2500 out of range */	obse->SetOpcodeBase(0x2510);	// to 0x252F (inclusive)

		obse->RegisterTypedCommand(	&kCommandInfo_NiObjectNETGetExtraData,			kRetnType_Array	); //0x2510 T     D
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETGetExtraDataByName						); //0x2511 T     D
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETAddExtraData							); //0x2512 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiObjectNETDeleteExtraData						); //0x2513 T S L D

		// NiExtraData //
		obse->RegisterTypedCommand(	&kCommandInfo_NiExtraDataGetName,				kRetnType_String); //0x2514 T     D
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetName								); //0x2515 T S L D

		obse->RegisterCommand(		&kCommandInfo_NiExtraDataGetNumber								); //0x2516 T     D
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetNumber								); //0x2517 T S L D

		obse->RegisterTypedCommand(	&kCommandInfo_NiExtraDataGetString,				kRetnType_String); //0x2518 T     D
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetString								); //0x2519 T S L D

		obse->RegisterTypedCommand(	&kCommandInfo_NiExtraDataGetArray,				kRetnType_Array	); //0x251A T     D
		obse->RegisterCommand(		&kCommandInfo_NiExtraDataSetArray								); //0x251B T S L D

		// NiAVObject //
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalTransform,		kRetnType_Array	); //0x251C T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalTranslation,	kRetnType_Array	); //0x251D T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetLocalRotation,		kRetnType_Array	); //0x251E T     D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetLocalScale							); //0x251F T     D

		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTransform						); //0x2520 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalTranslation						); //0x2521 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalRotation						); //0x2522 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetLocalScale							); //0x2523 T S L D

		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetNumProperties						); //0x2524 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiAVObjectGetProperties,			kRetnType_Array	); //0x2525 T     D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetPropertyByType						); //0x2526 T     D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectAddProperty								); //0x2527 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectDeleteProperty							); //0x2528 T S L D

		// NiNode //
		obse->RegisterCommand(		&kCommandInfo_NiNodeGetNumChildren								); //0x2529 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiNodeGetChildren,				kRetnType_Array	); //0x252A T     D
		obse->RegisterCommand(		&kCommandInfo_NiNodeGetChildByName								); //0x252B T     D
		obse->RegisterCommand(		&kCommandInfo_NiNodeAddChild									); //0x252C T S L D
		obse->RegisterCommand(		&kCommandInfo_NiNodeDeleteChild									); //0x252D T S L D
		obse->RegisterCommand(		&kCommandInfo_NiNodeCopyChild									); //0x252E T S L D

		// NiTexturingProperty //
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureCount				); //0x252F T     D

		/* 0x2530 out of range */	obse->SetOpcodeBase(0x25C0);	// to 25CF (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureCount				); //0x25C0 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyHasTexture						); //0x25C1 T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureSource				); //0x25C2 T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyAddTextureSource				); //0x25C3 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyDeleteTextureSource			); //0x25C4 T S L D

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureClampMode			); //0x25C5 T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureFilterMode			); //0x25C6 T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureUVSet				); //0x25C7 T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyTextureHasTransform			); //0x25C8 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureTranslation,
																					kRetnType_Array	); //0x25C9 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureTiling,
																					kRetnType_Array	); //0x25CA T     D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertyGetTextureRotation				); //0x25CB T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiTexturingPropertyGetTextureCenterOffset,
																					kRetnType_Array	); //0x25CC T     D

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureClampMode			); //0x25CD T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureFilterMode			); //0x25CE T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureUVSet				); //0x26CF T S L D

		/* 0x25D0 out of range */	obse->SetOpcodeBase(0x2660);	// to 267F (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureHasTransform			); //0x2660 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureTranslation			); //0x2661 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureTiling				); //0x2662 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureRotation				); //0x2663 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiTexturingPropertySetTextureCenterOffset			); //0x2664 T S L D

		// NiSourceTexture //
		obse->RegisterCommand(		&kCommandInfo_NiSourceTextureIsExternal							); //0x2665 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiSourceTextureGetFile,			kRetnType_String); //0x2666 T     D
		obse->RegisterCommand(		&kCommandInfo_NiSourceTextureSetExternalTexture					); //0x2667 T S L D

		// NiAlphaProperty //
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetBlendState						); //0x2668 T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetSourceBlendFunction				); //0x2669 T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetDestinationBlendFunction		); //0x266A T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetTestState						); //0x266B T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetTestFunction					); //0x266C T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetTestThreshold					); //0x266D T     D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertyGetTriangleSortMode				); //0x266E T     D

		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetBlendState						); //0x266F T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetSourceBlendFunction				); //0x2670 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetDestinationBlendFunction		); //0x2671 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetTestState						); //0x2672 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetTestFunction					); //0x2673 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetTestThreshold					); //0x2674 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiAlphaPropertySetTriangleSortMode				); //0x2675 T S L D

		// NiMaterialProperty //
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertyGetTransparency					); //0x2676 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiMaterialPropertyGetAmbientColor, kRetnType_Array); //0x2677 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiMaterialPropertyGetDiffuseColor, kRetnType_Array); //0x2678 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiMaterialPropertyGetEmissiveColor,kRetnType_Array); //0x2679 T     D
		obse->RegisterTypedCommand(	&kCommandInfo_NiMaterialPropertyGetSpecularColor,kRetnType_Array); //0x267A T     D
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertyGetGlossiness					); //0x267B T     D
		
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetTransparency					); //0x267C T S L D
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetAmbientColor					); //0x267D T S L D
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetDiffuseColor					); //0x267E T S L D
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetEmissiveColor				); //0x267F T S L D

		/* 0x2680 out of range */	obse->SetOpcodeBase(0x26D0);	// to 26FF (inclusive)

		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetSpecularColor				); //0x2680 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiMaterialPropertySetGlossiness					); //0x2681 T S L D

		// NiStencilProperty //	
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetStencilState					); //0x26D2 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetStencilFunction				); //0x26D3 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetStencilRef					); //0x26D4 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetStencilMask					); //0x26D5 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetFailAction					); //0x26D6 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetZFailAction					); //0x26D7 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetPassAction					); //0x26D8 T     D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertyGetFaceDrawMode					); //0x26D9 T     D

		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetStencilState					); //0x26DA T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetStencilFunction				); //0x26DB T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetStencilRef					); //0x26DC T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetStencilMask					); //0x26DD T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetFailAction					); //0x26DE T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetZFailAction					); //0x26DF T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetPassAction					); //0x26E1 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiStencilPropertySetFaceDrawMode					); //0x26E2 T S L D

		// NiVertexColorProperty //
		obse->RegisterCommand(		&kCommandInfo_NiVertexColorPropertyGetVertexMode				); //0x26E3 T     D
		obse->RegisterCommand(		&kCommandInfo_NiVertexColorPropertyGetLightingMode				); //0x26E4 T     D
		
		obse->RegisterCommand(		&kCommandInfo_NiVertexColorPropertySetVertexMode				); //0x26E5 T S L D
		obse->RegisterCommand(		&kCommandInfo_NiVertexColorPropertySetLightingMode				); //0x26E6 T S L D

		// NiAVObject // (again)
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetCollisionMode						); //0x26E7       D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectSetCollisionMode						); //0x26E8   S L D

		obse->RegisterCommand(		&kCommandInfo_NiAVObjectGetCollisionObject						); //0x26E9       D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectClearCollisionObject					); //0x26EA   S L D
		obse->RegisterCommand(		&kCommandInfo_NiAVObjectCopyCollisionObject						); //0x26EB   S L D

		// set up serialization callbacks when running in the runtime
		if(!obse->isEditor)
		{
			BSAlist = GetBSAfiles();
			_MESSAGE("List of BSA files: (excluding BSA files known to contain non-NIF data)");
			for ( BSAit = BSAlist.begin(); BSAit != BSAlist.end(); ++BSAit ) {
				_MESSAGE(("\t"+(*BSAit)).c_str());
			}
			_MESSAGE(("\t\t"+UIntToString(BSAlist.size())+" total.").c_str());

			_MESSAGE("\nRegistering OBSE script interface.");
			scrInterface = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script);

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
