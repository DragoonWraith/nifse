#pragma once

#include "NifFile.h"
#include "Param_Infos.h"

extern CommandInfo kCommandInfo_NiObjectGetType;
extern CommandInfo kCommandInfo_NiObjectGetTypeName;
extern CommandInfo kCommandInfo_NiObjectTypeDerivesFrom;

extern vector<Niflib::NiObjectRef> Util_CopyBranch(Niflib::NiObjectRef branchRoot, Niflib::NifInfo* headerInfoPtr);
extern vector<Niflib::NiObjectRef> Util_CopyBranch(Niflib::NiObjectRef branchRoot, Niflib::NifInfo* headerInfoPtr, Niflib::NiObjectRef destRoot);
