#pragma once

#include "obse_common/SafeWrite.h"
#include "NifFile.h"

static const UInt32 kLoadFile_HookAddr = 0x006F9999;
static const UInt32 kLoadFile_RetnAddr = 0x006F999E;
static const UInt32 kLoadFile_CallAddr = 0x00748100;	// __cdecl BSFile* LoadFile(char* path, UInt32 arg1, UInt32 arg2)

static const UInt32 kFinishedWithFile_HookAddr = 0x004395A9;
static const UInt32 kFinishedWithFile_RetnAddr = 0x004395AE;

void Hooks_NifSE_Init(void);