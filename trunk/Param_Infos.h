#pragma once

#include "obse/CommandTable.h"
#include "obse/Utilities.h"

#define DEFINE_CMD_PLUGIN_ALT(name, altName, description, refRequired, paramInfo) \
	CommandInfo (kCommandInfo_ ## name) = { \
	#name, \
	#altName, \
	0, \
	#description, \
	refRequired, \
	SIZEOF_ARRAY(paramInfo, ParamInfo), \
	paramInfo, \
	HANDLER(Cmd_ ## name ## _Execute), \
	NULL, \
	NULL, \
	0 \
};

static ParamInfo kParams_OneString_OneOptionalBool[2] = 
{
	{	"string",	kParamType_String,	0 },
	{	"boolean",	kParamType_Integer,	1 },
};

static ParamInfo kParams_TwoInts_OneOptionalInt[3] =
{
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneFloat_OneInt_OneOptionalInt[3] =
{
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneString_OneInt_OneOptionalInt[3] =
{
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_ThreeInts_OneOptionalInt[4] =
{
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneFloat_TwoInts_OneOptionalInt[4] =
{
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneString_TwoInts_OneOptionalInt[4] =
{
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneVector3_OneInt_OneOptionalInt[3] =
{
	{	"vector",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneMatrix33_OneInt_OneOptionalInt[3] =
{
	{	"matrix33",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_OneMatrix44_OneInt_OneOptionalInt[3] =
{
	{	"matrix44",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_Vector3f_OneInt_OneOptionalInt[5] =
{
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"float",	kParamType_Float,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_Matrix33f_OneInt_OneOptionalInt[11] =
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
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_Matrix44f_OneInt_OneOptionalInt[18] =
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
	{	"integer",	kParamType_Integer,	1 },
};
