#pragma once

#include "obse/PluginAPI.h"
#include "obse/GameAPI.h"
#include "obse/GameData.h"

#include <list>
using std::list;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include <exception>
using std::exception;

#include <iostream>
#include <fstream>
using std::iostream;
#include <sstream>

#include "BSA Browser\include\tes_bsa.h"
#include "BSA Browser\include\tes4_bsa.h"
using TES_BSA::TES4BSA_Archive;

// This is the folder in which NifSE will keep all of its dynamically-generated .nifs
// must be within Meshes. Folder name can be changed, keep it to 4 chars or less for efficiency's sake. MUST be all-lowercase
static char s_nifScriptFullPath[] = "meshes\\ni\\";	
static char s_nifScriptPath[] = "ni\\";											

static UInt32 s_nifScriptFullPathLen = sizeof(s_nifScriptFullPath) - 1;	// don't count the null terminator
static UInt32 s_nifScriptPathLen = sizeof(s_nifScriptPath) - 1;

// list of BSA files that is constructed on load; used later to find BSA'd files and read them
static list<string> BSAlist;
static list<string>::iterator BSAit;

list<string> GetBSAfiles();

// Utility function, determines if Nif is (0) missing, (1) in a folder, or (2) in an archive
UInt32 CheckFileLocation(string path);

// Utility function for reading nif out of BSA archive
void WriteNifToStream(string path, UInt32& loc, std::iostream* stream);

// Printer utility functions
void PrintAndLog(string func);
void PrintAndLog(string func, string msg);
void dPrintAndLog(string func);
void dPrintAndLog(string func, string msg);

// Utility function
string UIntToString(UInt32 uint);
UInt32 StringToUInt(string str);

string FloatToString(float flt);
float StringToFloat(string str);

string VectorToString(vector<float> vec);
vector<float> StringToVector(string str);

string MatrixToString(vector< vector<float> > mat);
vector< vector<float> > StringToMatrix(string str);

// Legacy code for old tag system.
string ToggleTag(string path, string element, string newVal);

// Legacy utility functions for copying Nifs.
int CopyNif(string oriPath, string altPath);
int CopyNif(string path);