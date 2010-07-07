#pragma once
#include "obse/CommandTable.h"

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
