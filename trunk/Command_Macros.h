#pragma once

#define GETBLOCK(blockType, varName) \
	NifFile* nifPtr = NULL; \
	Niflib:: ## blockType ## Ref varName = getNifBlock<Niflib:: ## blockType ## >(nifPtr, modID, nifID, blockID)

#define GETEDITBLOCK(blockType, varName) \
	NifFile* nifPtr = NULL; \
	Niflib:: ## blockType ## Ref varName = getNifBlock<Niflib:: ## blockType ## >(nifPtr, modID, nifID, blockID, true)

#define NIFIDSTR "#"+UIntToString(modID)+"-"+UIntToString(nifID)

#define STDNIFLIBGETCMD(blockType, funcName, cmdName, alias, retnType, desc) \
	static bool Cmd_ ## cmdName ## _Execute(COMMAND_ARGS) { \
		*result = 0; \
		\
		int nifID = -1; \
		UInt32 blockID = 0; \
		if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) { \
			UInt8 modID = scriptObj->GetModIndex(); \
			dPrintAndLog( #cmdName, "Getting the " #desc " of " #blockType " (nif " NIFIDSTR+")."); \
			try { \
				GETBLOCK(blockType, block); \
				*result = block-> ## funcName ## (); \
				dPrintAndLog( #cmdName, "Returning "+ ## retnType ## ToString(*result)+".\n"); \
			} catch (std::exception e) { \
				*result = 0; \
				dPrintAndLog( #cmdName, "Exception \""+string(e.what())+"\" thrown.\n"); \
			} \
		} else \
			dPrintAndLog( #cmdName, "Error extracting arguments.\n"); \
		return true; \
	} \
	DEFINE_CMD_PLUGIN_ALT( \
		cmdName, \
		alias, \
		"Gets the " #desc " of the given " #blockType ".", \
		0, \
		kParams_OneInt_OneOptionalInt \
	)

#define STDNIFLIBGETBLOCK(blockType, funcName, cmdName, alias, retnType, desc) \
	static bool Cmd_ ## cmdName ## _Execute(COMMAND_ARGS) { \
		*result = 0; \
		\
		int nifID = -1; \
		UInt32 blockID = 0; \
		if (ExtractArgs(PASS_EXTRACT_ARGS, &nifID, &blockID)) { \
			UInt8 modID = scriptObj->GetModIndex(); \
			dPrintAndLog( #cmdName, "Getting the " #desc " of " #blockType " (nif " NIFIDSTR+")."); \
			try { \
				GETBLOCK(blockType, block); \
				*result = block-> ## funcName ## ->internal_block_number; \
				dPrintAndLog( #cmdName, "Returning "+ ## retnType ## ToString(*result)+".\n"); \
			} catch (std::exception e) { \
				*result = 0; \
				dPrintAndLog( #cmdName, "Exception \""+string(e.what())+"\" thrown.\n"); \
			} \
		} else \
			dPrintAndLog( #cmdName, "Error extracting arguments.\n"); \
		return true; \
	} \
	DEFINE_CMD_PLUGIN_ALT( \
		cmdName, \
		alias, \
		"Gets the " #desc " of the given " #blockType ".", \
		0, \
		kParams_OneInt_OneOptionalInt \
	)

#define STDNIFLIBGET(blockType, funcName, alias, retnType, desc) \
	STDNIFLIBGETCMD(blockType, funcName, blockType ## funcName, alias, retnType, desc)

#define STDNIFLIBSETCMD(blockType, funcName, cmdName, alias, inType, inInit, inCast, valStr, act, ovr, params, desc) \
	static bool Cmd_ ## cmdName ## _Execute(COMMAND_ARGS) { \
		*result = 0; \
		\
		inType in = inInit; \
		int nifID = -1; \
		UInt32 blockID = 0; \
		if (ExtractArgs(PASS_EXTRACT_ARGS, &in, &nifID, &blockID)) { \
			UInt8 modID = scriptObj->GetModIndex(); \
			dPrintAndLog( #cmdName, "Getting the " #desc " of " #blockType " (nif " NIFIDSTR+")."); \
			try { \
				GETBLOCK(blockType, block); \
				block-> ## funcName ## (( ## inCast ## ) ## in); \
				*result = 1; \
				nifPtr->logChange(blockID, kNiflibType_ ## blockType, act, valStr ## (in), ovr); \
				dPrintAndLog( #cmdName, "Set " #desc ".\n"); \
			} catch (std::exception e) { \
				*result = 0; \
				dPrintAndLog( #cmdName, "Exception \""+string(e.what())+"\" thrown.\n"); \
			} \
		} else \
			dPrintAndLog( #cmdName, "Error extracting arguments.\n"); \
		return true; \
	} \
	DEFINE_CMD_PLUGIN_ALT( \
		cmdName, \
		alias, \
		"Sets the " #desc " of the given " #blockType ".", \
		0, \
		params \
	)

#define STDNIFLIBSETBOOL(blockType, funcName, alias, act, ovr, desc) \
	STDNIFLIBSETCMD(blockType, funcName, blockType ## funcName, alias, int, 0, bool, UIntToString, act, ovr, kParams_TwoInts_OneOptionalInt, desc)

#define STDNIFLIBSETUINTCAST(blockType, funcName, alias, act, ovr, desc, cast) \
	STDNIFLIBSETCMD(blockType, funcName, blockType ## funcName, alias, UInt32, 0, cast, UIntToString, act, ovr, kParams_TwoInts_OneOptionalInt, desc)

#define STDNIFLIBSETUINT(blockType, funcName, alias, act, ovr, desc) \
	STDNIFLIBSETUINTCAST(blockType, funcName, alias, act, ovr, desc, UInt32)

#define STDNIFLIBSETFLOAT(blockType, funcName, alias, act, ovr, desc) \
	STDNIFLIBSETCMD(blockType, funcName, blockType ## funcName, alias, float, 0, float, FloatToString, act, ovr, kParams_OneFloat_OneInt_OneOptionalInt, desc)

#define STDNIFLIBSETSTRING(blockType, funcName, alias, act, ovr, desc) \
	STDNIFLIBSETCMD(blockType, funcName, blockType ## funcName, alias, string, "", string, string, act, ovr, kParams_OneString_OneInt_OneOptionalInt, desc)
