#pragma once

#include "NifFile.h"

// map of where documentation for functions can be found; used by shadeMe's CSE
extern std::vector<string>* FunctionDocMap;
static const string url ("http://cs.elderscrolls.com/constwiki/index.php/");

// Message handlers
void MessageHandler(OBSEMessagingInterface::Message* msg);
void EditorMessageHandler(OBSEMessagingInterface::Message* msg);

// Utilities for Load
string ReadString(UInt32 length);
void LoadChangelog(string &changes, string &chNode, UInt32 &chType, UInt32 &chAct, string &chVal);
list<string> GetBSAfiles();

// Preload callback
void NifSE_PreloadCallback(void * reserved);
