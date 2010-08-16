#pragma once

#include "niflib.h"
#include "obj/NiObject.h"
#include "obj/NiNode.h"
#include "obj/NiExtraData.h"
#include "obj/BSBound.h"
#include "obj/BSFurnitureMarker.h"
#include "obj/NiBinaryExtraData.h"
#include "obj/NiBinaryVoxelData.h"
#include "obj/NiBooleanExtraData.h"
#include "obj/NiColorExtraData.h"
#include "obj/NiFloatExtraData.h"
#include "obj/NiFloatsExtraData.h"
#include "obj/NiIntegerExtraData.h"
#include "obj/BSXFlags.h"
#include "obj/NiIntegersExtraData.h"
#include "obj/NiStringExtraData.h"
#include "obj/NiStringsExtraData.h"
#include "obj/NiTextKeyExtraData.h"
#include "obj/NiVectorExtraData.h"
#include "obj/NiVertWeightsExtraData.h"
#include "obj/NiAVObject.h"
#include "obj/NiMaterialProperty.h"
#include "obj/NiTextureProperty.h"
#include "obj/NiTexturingProperty.h"
#include "obj/NiSourceTexture.h"
#include "obj/NiImage.h"
#include "obj/NiCollisionObject.h"
#include "obj/bhkNiCollisionObject.h"
#include "obj/bhkRigidBodyT.h"
#include "obj/NiDynamicEffect.h"
#include "obj/NiTriStrips.h"

using Niflib::GetNifVersion;
using Niflib::Ref;
using Niflib::NiObjectRef;
using Niflib::NiNodeRef;
using Niflib::NifInfo;
//using Niflib::NiExtraData;
using Niflib::NiExtraDataRef;
using Niflib::NiStringExtraData;
using Niflib::NiStringExtraDataRef;
using Niflib::NiAVObjectRef;
using Niflib::NiCollisionObject;
using Niflib::bhkNiCollisionObject;
using Niflib::bhkNiCollisionObjectRef;
using Niflib::bhkRigidBodyT;
using Niflib::NiDynamicEffect;
using Niflib::DynamicCast;
using Niflib::StaticCast;
using Niflib::ReadNifTree;

class NifFile;
#include "NifFile.h"

#include "Param_Infos.h"

#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"
#include "obse/GameAPI.h"
#include "obse/GameData.h"
#include "obse/GameForms.h"
#include "obse/GameObjects.h"
#include "obse/ParamInfos.h"
#include "obse/Utilities.h"
#include "obse/Script.h"

#include <list>
using std::list;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include <exception>
using std::exception;

#include <iostream>
#include <fstream>
using std::iostream;
#include <sstream>

#include "BSA Browser\include\tes_bsa.h"
#include "BSA Browser\include\tes4_bsa.h"
using TES_BSA::TES4BSA_Archive;

extern string				g_pluginName;
extern IDebugLog			g_Log;
extern UInt32				g_pluginVersion;
extern PluginHandle			g_pluginHandle;

static const UInt8 alpha = 0;
static const UInt8 beta = 4;
static const UInt8 minor = 8;
static const UInt8 major = 16;

UInt8  getAlphaV(const UInt32 ver = g_pluginVersion);
void setAlphaV(UInt8 a, UInt32 ver = g_pluginVersion);
bool isAlpha(const UInt32 ver = g_pluginVersion);

UInt8   getBetaV(const UInt32 ver = g_pluginVersion);
void setBetaV(UInt8 b, UInt32 ver = g_pluginVersion);
bool isBeta(const UInt32 ver = g_pluginVersion);

UInt8  getMinorV(const UInt32 ver = g_pluginVersion);
void setMinorV(UInt8 m, UInt32 ver = g_pluginVersion);

UInt16 getMajorV(const UInt32 ver = g_pluginVersion);
void setMajorV(UInt16 M, UInt32 ver = g_pluginVersion);

UInt32 getV(const UInt16 major, const UInt8 minor, const UInt8 beta = 0xF, const UInt8 alpha = 0xF);

// various OBSE interfaces
extern OBSEArrayVarInterface* arrInterface;
extern OBSEMessagingInterface* msgInterface;
extern OBSESerializationInterface* serInterface;
extern OBSEStringVarInterface* strInterface;

// type definitions
typedef OBSEArrayVarInterface::Array	OBSEArray;
typedef OBSEArrayVarInterface::Element	OBSEElement;

// helper functions to creating OBSE Arrays
OBSEArray* StringMapFromStdMap(const map<string, OBSEElement>& data, Script* callingScript);
OBSEArray* MapFromStdMap(const map<double, OBSEElement>& data, Script* callingScript);
OBSEArray* ArrayFromStdVector(const vector<OBSEElement>& data, Script* callingScript);

// This is the folder in which NifSE will keep all of its dynamically-generated .nifs
// must be within Meshes. Folder name can be changed, keep it to 4 chars or less for efficiency's sake. MUST be all-lowercase
static const char s_nifSEFullPath[] = "meshes\\ni\\";
static const char s_nifSEPath[] = "ni\\";

static UInt32 s_nifSEFullPathLen = sizeof(s_nifSEFullPath) - 1;	// don't count the null terminator
static UInt32 s_nifSEPathLen = sizeof(s_nifSEPath) - 1;

// Utility function, determines if Nif is (0) missing, (1) in a folder, (2) in an archive, or (3) in RegList
UInt32 CheckFileLocation(string path, NifFile* nifPtr = NULL);

// Utility function for reading nif out of BSA archive
void WriteNifToStream(string path, UInt32& loc, std::iostream* stream);

// Printer utility functions
void PrintAndLog(string func);
void PrintAndLog(string func, string msg);
void dPrintAndLog(string func);
void dPrintAndLog(string func, string msg);

// Utility conversion functions
string UIntToString(UInt32 uint);
UInt32 StringToUInt(string str);

string FloatToString(float flt);
float StringToFloat(string str);

string VectorToString(vector<float> vec);
string VectorToString(Niflib::Vector3 vec);
vector<float> StringToVector(string str);

string MatrixToString(vector< vector<float> > mat);
string MatrixToString(Niflib::Matrix33 mat);
string MatrixToString(Niflib::Matrix44 mat);
vector< vector<float> > StringToMatrix(string str);

const char logNode = ':';
const char logNumber = '#';
const char logType = '-';
const char logAction = '=';
const char logValue = '\n';

string changeLog(UInt32 Node, UInt32 Type, UInt32 Action, string Value = "");
string changeLog(string Node, UInt32 Type, UInt32 Action, string Value = "");

void clearPrevChange(string &log, const UInt32 &Node, const UInt32 &Type, const UInt32 &Action);
void clearPrevChange(string &log, const string &Node, const UInt32 &Type, const UInt32 &Action);

// list of BSA files that is constructed on load; used later to find BSA'd files and read them
extern list<string> BSAlist;
extern list<string>::iterator BSAit;
