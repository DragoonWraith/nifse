#pragma once

#include "NifFile.h"
#include "Hooks_NifSE.h"

#include "Commands_Basic.h"
#include "Commands_NiObject.h"
#include "Commands_NiObjectNET.h"
#include "Commands_NiExtraData.h"
#include "Commands_BSFurnitureMarker.h"
#include "Commands_NiAVObject.h"
#include "Commands_NiNode.h"
#include "Commands_NiAlphaProperty.h"
#include "Commands_NiMaterialProperty.h"
#include "Commands_NiStencilProperty.h"
#include "Commands_NiTexturingProperty.h"
#include "Commands_NiVertexColorProperty.h"
#include "Commands_NiSourceTexture.h"
#include "Commands_BSFurnitureMarker.h"
#include "Commands_Deprecated.h"

#ifdef _DEBUG
#include "Commands_Debug.h"
#endif

#include "New.h"
#include "Save.h"
#include "Load.h"

extern std::vector<string>* FunctionDocMap;

#define REG(cmd) \
	FunctionDocMap->push_back(string(#cmd)); \
	obse->RegisterCommand( &kCommandInfo_ ## cmd ## )

#define REGT(cmd, retn) \
	FunctionDocMap->push_back(string(#cmd)); \
	obse->RegisterTypedCommand( &kCommandInfo_ ## cmd ## , kRetnType_ ## retn ## )

