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

		FunctionDocMap = new std::vector<string>;

		// register commands
		// also links documentation for CSE
		// T = tested
		// S = saves
		// L = is loaded
		// D = documented

		obse->SetOpcodeBase(0x24F0); // to 0x24FF (inclusive)

	// --------------------------------- NifScript Beta --------------------------------- //

		// Deprecated Functions //
		REGT(	NifGetAltGrip,								String  ); //0x24F0 T S L D
		REGT(	NifGetOffHand,								String  ); //0x24F1 T S L D
		obse->RegisterTypedCommand(&kCommandInfo_NifGetBackShield, kRetnType_String);
																	   //0x24F2   S L to remain undocumented.

	// ----------------------------------- NifSE v1.0 ----------------------------------- //

		// Debug Function //
#ifdef _DEBUG
		REG(	NifWriteToDisk										); //0x25F3 T     D
#else
		obse->SetOpcodeBase(0x24F4);
#endif	
		// Basic Functions //
		REG(	NifOpen												); //0x24F4 T S L D
		REG(	NifClose											); //0x24F5 T     D

		REGT(	NifGetPath,									String  ); //0x24F6 T     D
		REGT(	NifGetOriginalPath,							String  ); //0x24F7 T     D

		REG(	NifGetNumBlocks										); //0x24F8 T     D

		REG(	GetNifTypeIndex										); //0x24F9 T     D

		// NiObject //
		REG(	NiObjectGetType										); //0x24FA T     D
		REGT(	NiObjectGetTypeName,						String  ); //0x24FB T     D
		REG(	NiObjectTypeDerivesFrom								); //0x24FC T     D

		// NiObjectNET //
		REGT(	NiObjectNETGetName,							String  ); //0x24FD T     D
		REG(	NiObjectNETSetName									); //0x24FE T S L D

		REG(	NiObjectNETGetNumExtraData							); //0x24FF T     D

		/* 0x2500 out of range */	obse->SetOpcodeBase(0x2510);		//to 0x252F (inclusive)

		REGT(	NiObjectNETGetExtraData,					Array	); //0x2510 T     D
		REG(	NiObjectNETGetExtraDataByName						); //0x2511 T     D
		REG(	NiObjectNETAddExtraData								); //0x2512 T S L D
		REG(	NiObjectNETDeleteExtraData							); //0x2513 T S L D

		// NiExtraData //
		REGT(	NiExtraDataGetName,							String  ); //0x2514 T     D
		REG(	NiExtraDataSetName									); //0x2515 T S L D

		REG(	NiExtraDataGetNumber								); //0x2516 T     D
		REG(	NiExtraDataSetNumber								); //0x2517 T S L D

		REGT(	NiExtraDataGetString,						String  ); //0x2518 T     D
		REG(	NiExtraDataSetString								); //0x2519 T S L D

		REGT(	NiExtraDataGetArray,						Array	); //0x251A T     D
		REG(	NiExtraDataSetArray									); //0x251B T S L D

		// NiAVObject //
		REGT(	NiAVObjectGetLocalTransform,				Array	); //0x251C T     D
		REGT(	NiAVObjectGetLocalTranslation,				Array	); //0x251D T     D
		REGT(	NiAVObjectGetLocalRotation,					Array	); //0x251E T     D
		REG(	NiAVObjectGetLocalScale								); //0x251F T     D

		REG(	NiAVObjectSetLocalTransform							); //0x2520 T S L D
		REG(	NiAVObjectSetLocalTranslation						); //0x2521 T S L D
		REG(	NiAVObjectSetLocalRotation							); //0x2522 T S L D
		REG(	NiAVObjectSetLocalScale								); //0x2523 T S L D

		REG(	NiAVObjectGetNumProperties							); //0x2524 T     D
		REGT(	NiAVObjectGetProperties,					Array	); //0x2525 T     D
		REG(	NiAVObjectGetPropertyByType							); //0x2526 T     D
		REG(	NiAVObjectAddProperty								); //0x2527 T S L D
		REG(	NiAVObjectDeleteProperty							); //0x2528 T S L D

		// NiNode //
		REG(	NiNodeGetNumChildren								); //0x2529 T     D
		REGT(	NiNodeGetChildren,							Array	); //0x252A T     D
		REG(	NiNodeGetChildByName								); //0x252B T     D
		REG(	NiNodeAddChild										); //0x252C T S L D
		REG(	NiNodeDeleteChild									); //0x252D T S L D
		REG(	NiNodeCopyChild										); //0x252E T S L D

		// NiTexturingProperty //
		REG(	NiTexturingPropertyGetTextureCount					); //0x252F T     D

		/* 0x2530 out of range */	obse->SetOpcodeBase(0x25C0);		//to 0x25CF (inclusive)

		REG(	NiTexturingPropertySetTextureCount					); //0x25C0 T S L D
		REG(	NiTexturingPropertyHasTexture						); //0x25C1 T     D
		REG(	NiTexturingPropertyGetTextureSource					); //0x25C2 T     D
		REG(	NiTexturingPropertyAddTextureSource					); //0x25C3 T S L D
		REG(	NiTexturingPropertyDeleteTextureSource				); //0x25C4 T S L D

		REG(	NiTexturingPropertyGetTextureClampMode				); //0x25C5 T     D
		REG(	NiTexturingPropertyGetTextureFilterMode				); //0x25C6 T     D
		REG(	NiTexturingPropertyGetTextureUVSet					); //0x25C7 T     D
		REG(	NiTexturingPropertyTextureHasTransform				); //0x25C8 T     D
		REGT(	NiTexturingPropertyGetTextureTranslation,	Array	); //0x25C9 T     D
		REGT(	NiTexturingPropertyGetTextureTiling,		Array	); //0x25CA T     D
		REG(	NiTexturingPropertyGetTextureRotation				); //0x25CB T     D
		REGT(	NiTexturingPropertyGetTextureCenterOffset,	Array	); //0x25CC T     D

		REG(	NiTexturingPropertySetTextureClampMode				); //0x25CD T S L D
		REG(	NiTexturingPropertySetTextureFilterMode				); //0x25CE T S L D
		REG(	NiTexturingPropertySetTextureUVSet					); //0x26CF T S L D

		/* 0x25D0 out of range */	obse->SetOpcodeBase(0x2660);		//to 0x267F (inclusive)

		REG(	NiTexturingPropertySetTextureHasTransform			); //0x2660 T S L D
		REG(	NiTexturingPropertySetTextureTranslation			); //0x2661 T S L D
		REG(	NiTexturingPropertySetTextureTiling					); //0x2662 T S L D
		REG(	NiTexturingPropertySetTextureRotation				); //0x2663 T S L D
		REG(	NiTexturingPropertySetTextureCenterOffset			); //0x2664 T S L D

		// NiSourceTexture //
		REG(	NiSourceTextureIsExternal							); //0x2665 T     D
		REGT(	NiSourceTextureGetFile,						String  ); //0x2666 T     D
		REG(	NiSourceTextureSetExternalTexture					); //0x2667 T S L D

		// NiAlphaProperty //
		REG(	NiAlphaPropertyGetBlendState						); //0x2668 T     D
		REG(	NiAlphaPropertyGetSourceBlendFunction				); //0x2669 T     D
		REG(	NiAlphaPropertyGetDestinationBlendFunction			); //0x266A T     D
		REG(	NiAlphaPropertyGetTestState							); //0x266B T     D
		REG(	NiAlphaPropertyGetTestFunction						); //0x266C T     D
		REG(	NiAlphaPropertyGetTestThreshold						); //0x266D T     D
		REG(	NiAlphaPropertyGetTriangleSortMode					); //0x266E T     D

		REG(	NiAlphaPropertySetBlendState						); //0x266F T S L D
		REG(	NiAlphaPropertySetSourceBlendFunction				); //0x2670 T S L D
		REG(	NiAlphaPropertySetDestinationBlendFunction			); //0x2671 T S L D
		REG(	NiAlphaPropertySetTestState							); //0x2672 T S L D
		REG(	NiAlphaPropertySetTestFunction						); //0x2673 T S L D
		REG(	NiAlphaPropertySetTestThreshold						); //0x2674 T S L D
		REG(	NiAlphaPropertySetTriangleSortMode					); //0x2675 T S L D

		// NiMaterialProperty //
		REG(	NiMaterialPropertyGetTransparency					); //0x2676 T     D
		REGT(	NiMaterialPropertyGetAmbientColor,			Array	); //0x2677 T     D
		REGT(	NiMaterialPropertyGetDiffuseColor,			Array	); //0x2678 T     D
		REGT(	NiMaterialPropertyGetEmissiveColor,			Array	); //0x2679 T     D
		REGT(	NiMaterialPropertyGetSpecularColor,			Array	); //0x267A T     D
		REG(	NiMaterialPropertyGetGlossiness						); //0x267B T     D
		
		REG(	NiMaterialPropertySetTransparency					); //0x267C T S L D
		REG(	NiMaterialPropertySetAmbientColor					); //0x267D T S L D
		REG(	NiMaterialPropertySetDiffuseColor					); //0x267E T S L D
		REG(	NiMaterialPropertySetEmissiveColor					); //0x267F T S L D

		/* 0x2680 out of range */	obse->SetOpcodeBase(0x26D0);		//to 0x26FF (inclusive)

		REG(	NiMaterialPropertySetSpecularColor					); //0x2680 T S L D
		REG(	NiMaterialPropertySetGlossiness						); //0x2681 T S L D

		// NiStencilProperty //	
		REG(	NiStencilPropertyGetStencilState					); //0x26D2 T     D
		REG(	NiStencilPropertyGetStencilFunction					); //0x26D3 T     D
		REG(	NiStencilPropertyGetStencilRef						); //0x26D4 T     D
		REG(	NiStencilPropertyGetStencilMask						); //0x26D5 T     D
		REG(	NiStencilPropertyGetFailAction						); //0x26D6 T     D
		REG(	NiStencilPropertyGetZFailAction						); //0x26D7 T     D
		REG(	NiStencilPropertyGetPassAction						); //0x26D8 T     D
		REG(	NiStencilPropertyGetFaceDrawMode					); //0x26D9 T     D

		REG(	NiStencilPropertySetStencilState					); //0x26DA T S L D
		REG(	NiStencilPropertySetStencilFunction					); //0x26DB T S L D
		REG(	NiStencilPropertySetStencilRef						); //0x26DC T S L D
		REG(	NiStencilPropertySetStencilMask						); //0x26DD T S L D
		REG(	NiStencilPropertySetFailAction						); //0x26DE T S L D
		REG(	NiStencilPropertySetZFailAction						); //0x26DF T S L D
		REG(	NiStencilPropertySetPassAction						); //0x26E1 T S L D
		REG(	NiStencilPropertySetFaceDrawMode					); //0x26E2 T S L D

		// NiVertexColorProperty //
		REG(	NiVertexColorPropertyGetVertexMode					); //0x26E3 T     D
		REG(	NiVertexColorPropertyGetLightingMode				); //0x26E4 T     D
		
		REG(	NiVertexColorPropertySetVertexMode					); //0x26E5 T S L D
		REG(	NiVertexColorPropertySetLightingMode				); //0x26E6 T S L D

		// NiAVObject // (again)
		REG(	NiAVObjectGetCollisionMode							); //0x26E7 T     D
		REG(	NiAVObjectSetCollisionMode							); //0x26E8 T S L D

		REG(	NiAVObjectGetCollisionObject						); //0x26E9 T     D
		REG(	NiAVObjectClearCollisionObject						); //0x26EA T S L D
		REG(	NiAVObjectCopyCollisionObject						); //0x26EB T S L D

		// BSFurnitureMarker //
		REGT(	BSFurnitureMarkerGetPositionRefs,			Array	); //0x26EC T S L D
		REG(	BSFurnitureMarkerSetPositionRefs					); //0x26ED T S L D

		// set up serialization callbacks when running in the runtime
		if(!obse->isEditor)
		{
			BSAlist = GetBSAfiles();
			_MESSAGE("List of BSA files: (excluding BSA files known to contain non-NIF data)");
			for ( BSAit = BSAlist.begin(); BSAit != BSAlist.end(); ++BSAit ) {
				for ( UInt8 i = 0; i < BSAit->length(); ++i )
					if ( (*BSAit)[i] == '%' )
						BSAit->insert(++i, 1, '%');
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

			delete FunctionDocMap;
		}
		else {
			_MESSAGE("Listening to OBSE dispatches.");
			msgInterface->RegisterListener(g_pluginHandle, "OBSE", EditorMessageHandler);
		}

		_MESSAGE("\n\tInitialization complete.\n\n");

		return true;
	}

};
