#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

#include "Commands_NiExtraData.h"
#include "Commands_NiAVObject.h"
#include "Commands_NiNode.h"

// Legacy code for old tag system.
string ToggleTag(string path, string element, string newVal);

// Legacy utility functions for copying Nifs.
int CopyNif(string oriPath, string altPath);
int CopyNif(string path);

extern CommandInfo kCommandInfo_NifGetOffHand;
extern CommandInfo kCommandInfo_NifGetAltGrip;
extern CommandInfo kCommandInfo_NifGetBackShield;
