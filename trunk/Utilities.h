#pragma once

#include "niflib.h"

#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"
#if OBLIVION
#include "obse/GameAPI.h"
#else
#include "obse_editor/EditorAPI.h"
#endif
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

// Printer utility functions
void PrintAndLog(string func);
void PrintAndLog(string func, string msg);
void dPrintAndLog(string func);
void dPrintAndLog(string func, string msg);

// Utility conversion functions
string UIntToString(UInt32 uint);
UInt32 StringToUInt(string str);

string SIntToString(SInt32 sint);
SInt32 StringToSInt(string str);

string FloatToString(float flt);
float StringToFloat(string str);

string VectorToString(vector<float> vec);
string VectorToString(Niflib::Vector3 vec);
vector<float> StringToVector(string str);

string MatrixToString(vector< vector<float> > mat);
string MatrixToString(Niflib::Matrix33 mat);
string MatrixToString(Niflib::Matrix44 mat);
vector< vector<float> > StringToMatrix(string str);

// list of BSA files that is constructed on load; used later to find BSA'd files and read them
extern list<string> BSAlist;
extern list<string>::iterator BSAit;
