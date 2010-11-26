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

#include "Versioning.h"

extern string				g_pluginName;
extern IDebugLog			g_Log;
extern UInt32				g_pluginVersion;
extern PluginHandle			g_pluginHandle;

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
string VectorToString(vector<Niflib::byte> vec);
string VectorToString(vector<unsigned int> vec);
string VectorToString(vector<string> vec);
string VectorToString(Niflib::Vector3 vec);
string VectorToString(Niflib::TexCoord mat);
vector<float> StringToVector(string str);
vector<Niflib::byte> StringToVectorB(string str);
vector<unsigned int> StringToVectorU(string str);
vector<string> StringToVectorS(string str);
Niflib::Vector3 StringToVector3(string str);
Niflib::TexCoord StringToVectorT(string str);

string MatrixToString(vector< vector<float> > mat);
string MatrixToString(Niflib::Matrix33 mat);
string MatrixToString(Niflib::Matrix44 mat);
vector< vector<float> > StringToMatrix(string str);
Niflib::Matrix33 StringToMatrix33(string str);
Niflib::Matrix44 StringToMatrix44(string str);

string Color4ToString(Niflib::Color4 color);
Niflib::Color4 StringToColor4(string str);

// list of BSA files that is constructed on load; used later to find BSA'd files and read them
extern list<string> BSAlist;
extern list<string>::iterator BSAit;
