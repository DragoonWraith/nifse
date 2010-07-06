#pragma once

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
static char s_nifScriptFullPath[] = "meshes\\ni\\";	
static char s_nifScriptPath[] = "ni\\";											

static UInt32 s_nifScriptFullPathLen = sizeof(s_nifScriptFullPath) - 1;	// don't count the null terminator
static UInt32 s_nifScriptPathLen = sizeof(s_nifScriptPath) - 1;

// Utility function, determines if Nif is (0) missing, (1) in a folder, or (2) in an archive
UInt32 CheckFileLocation(string path);

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
vector<float> StringToVector(string str);

string MatrixToString(vector< vector<float> > mat);
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
