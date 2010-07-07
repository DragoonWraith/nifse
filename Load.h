#pragma once

#include "NifFile.h"

// map of where documentation for functions can be found; used by shadeMe's CSE
extern std::map<const char*, const char*>* FunctionDocMap;
static string url ("http://cs.elderscrolls.com/constwiki/index.php/");
static void doc(string func) {
	FunctionDocMap->insert(pair<const char*,const char*>(func.c_str(), (url+func).c_str()));
}

// Message handlers
void MessageHandler(OBSEMessagingInterface::Message* msg);
void EditorMessageHandler(OBSEMessagingInterface::Message* msg);

// Utilities for Load
string ReadString(UInt32 length);
void LoadChangelog(string &changes, string &chNode, UInt32 &chType, UInt32 &chAct, string &chVal);
list<string> GetBSAfiles();

// Preload callback
void NifSE_PreloadCallback(void * reserved);
