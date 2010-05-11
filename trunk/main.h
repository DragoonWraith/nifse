#pragma once

#include "Utilities.h"
#include "NifFile.h"
#include "Hooks_NifSE.h"

#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"
#include "obse/GameAPI.h"
#include "obse/GameData.h"
#include "obse/GameForms.h"
#include "obse/GameObjects.h"
#include "obse/ParamInfos.h"
#include "obse/Utilities.h"
#include "obse/Script.h"

// directory of registered NifFiles.
// declared here so they can be used by serialization.
static std::map < UInt8, std::map < UInt32, NifFile* > > RegList;
static std::map <string, pair<UInt8, UInt32>* > RegListByFilename;

static std::map<const char*, const char*> FunctionDocMap;
static string url ("http://cs.elderscrolls.com/constwiki/index.php/");
static void doc(string func) {
	FunctionDocMap.insert(pair<const char*,const char*>(func.c_str(), (url+func).c_str()));
}

static ParamInfo kParams_OneString_OneOptionalBool[2] = 
{
	{	"string",	kParamType_String,	0 },
	{	"boolean",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneString_TwoInts[3] = 
{
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_TwoStrings_OneInt[3] =
{
	{	"string",	kParamType_String,	0 },
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_OneFloat_TwoInts[3] =
{
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_OneVector3_TwoInts[5] =
{
	{	"vector",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_OneMatrix33_TwoInts[5] =
{
	{	"matrix33",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_OneMatrix44_TwoInts[5] =
{
	{	"matrix44",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_Vector3f_TwoInts[5] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_Matrix33f_TwoInts[11] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer, 0 },
	{	"integer",	kParamType_Integer,	0 },
};

static ParamInfo kParams_Matrix44f_TwoInts[18] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer, 0 },
	{	"integer",	kParamType_Integer,	0 },
};
