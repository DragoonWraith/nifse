#pragma once

#include "obse/CommandTable.h"
#include "obse/Utilities.h"

static ParamInfo kParams_OneString_OneInt_OneOptionalInt[3] =
{
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_TwoStrings_OneInt_OneOptionalInt[4] =
{
	{	"string",	kParamType_String,	0 },
	{	"string",	kParamType_String,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};

static ParamInfo kParams_TwoInts_OneOptionalInt[3] =
{
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	0 },
	{	"integer",	kParamType_Integer,	1 },
};