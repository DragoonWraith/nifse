#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

class NifFile;

struct changeLog {
	UInt8 mod;
	UInt32 nif;
	string path;
	string base;
	UInt32 ver;
	bool edit;
	UInt32 type;
	UInt32 block;
	UInt32 act;
	string val;

	vector<NifFile*> required;

	changeLog(UInt8 modID, UInt32 nifID, string filePath, string basePath, UInt32 ver, bool edit, UInt32 typeID, UInt32 blockID, UInt32 actID, string valStr);
	void saveMod() const;
	void saveNif() const;
	void saveCh() const;
};

const char logNode = ':';
const char logNumber = '#';
const char logType = '-';
const char logAction = '=';
const char logValType = '|';
const char logValue = '@';
