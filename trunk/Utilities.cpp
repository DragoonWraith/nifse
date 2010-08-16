#include "Utilities.h"

extern string						g_pluginName	("NifSE");
extern IDebugLog					g_Log			((g_pluginName+".log").c_str());
extern UInt32						g_pluginVersion	(getV(0x0001,0x00,0x0,0x4));
extern PluginHandle					g_pluginHandle	(kPluginHandle_Invalid);

extern OBSEArrayVarInterface*		arrInterface	(NULL);
extern OBSEMessagingInterface*		msgInterface	(NULL);
extern OBSESerializationInterface*	serInterface	(NULL);
extern OBSEStringVarInterface*		strInterface	(NULL);

UInt8  getAlphaV(const UInt32 ver) { return (ver & 0x0000000F) >> alpha; }
void setAlphaV(UInt8 a, UInt32 ver) { ver = (ver & 0xFFFFFFF0) | ((a & 0xF) << alpha); }
bool isAlpha(const UInt32 ver) { return !(getAlphaV(ver) == 0xF); }

UInt8   getBetaV(const UInt32 ver) { return (ver & 0x000000F0) >> beta; }
void setBetaV(UInt8 b, UInt32 ver) { ver = (ver & 0xFFFFFF0F) | ((b & 0xF) << beta); }
bool isBeta(const UInt32 ver) { return !(getBetaV(ver) == 0xF); }

UInt8  getMinorV(const UInt32 ver) { return (ver & 0x0000FF00) >> minor; }
void setMinorV(UInt8 m, UInt32 ver) { ver = (ver & 0xFFFF00FF) | (m << minor); }

UInt16 getMajorV(const UInt32 ver) { return (ver & 0xFFFF0000) >> major; }
void setMajorV(UInt16 M, UInt32 ver) { ver = (ver & 0x0000FFFF) | (M << major); }

UInt32 getV(const UInt16 majorV, const UInt8 minorV, const UInt8 betaV, const UInt8 alphaV) {
	return majorV<<major | minorV<<minor | betaV<<beta | alphaV<<alpha;
}

// some utility functions because I got tired of writing the same stuff for all my debug code
void PrintAndLog(string func) {
	Console_Print("");
	Console_Print(("NifSE::"+func+" called!").c_str());
	_MESSAGE(("\n\n"+func+" called!").c_str());
}

void PrintAndLog(string func, string msg) {
	Console_Print("");
	Console_Print(("NifSE::"+func+" - "+msg).c_str());
	_MESSAGE((func+" - "+msg).c_str());
}

void dPrintAndLog(string msg) {
#ifdef _DEBUG
	Console_Print(msg.c_str());
#endif
	_MESSAGE(msg.c_str());
}

void dPrintAndLog(string func, string msg) {
#ifdef _DEBUG
	Console_Print(("NifSE::"+func+" - "+msg).c_str());
#endif
	_MESSAGE((func+" - "+msg).c_str());
}

// helper function for creating an OBSE StringMap from a std::map<std::string, OBSEElement>
OBSEArray* StringMapFromStdMap(const map<string, OBSEElement>& data, Script* callingScript) {
	// create empty string map
	OBSEArray* arr = arrInterface->CreateStringMap(NULL, NULL, 0, callingScript);

	// add each key-value pair
	for (std::map<std::string, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		arrInterface->SetElement(arr, iter->first.c_str(), iter->second);
	}

	return arr;
}

// helper function for creating an OBSE Map from a std::map<double, OBSEElement>
OBSEArray* MapFromStdMap(const map<double, OBSEElement>& data, Script* callingScript) {
	OBSEArray* arr = arrInterface->CreateMap(NULL, NULL, 0, callingScript);
	for (std::map<double, OBSEElement>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		arrInterface->SetElement(arr, iter->first, iter->second);
	}

	return arr;
}

// helper function for creating OBSE Array from std::vector<OBSEElement>
OBSEArray* ArrayFromStdVector(const vector<OBSEElement>& data, Script* callingScript) {
	OBSEArray* arr = arrInterface->CreateArray(&(data[0]), data.size(), callingScript);
	return arr;
}

// Extended version of FindFile that also checks RegList.
// Also does some double-checking that may be unnecessary.
// To avoid going through RegList twice, can store the nif
// in a pointer, if passed.
UInt32 CheckFileLocation(string path, NifFile* nifPtr) {
	UInt32 loc = (*g_FileFinder)->FindFile(("Data\\Meshes\\"+path).c_str(),0,0,-1);
	if ( loc == 0 ) {
		if ( !_stricmp(path.substr(0, s_nifSEPathLen).c_str(), s_nifSEPath) )
			if ( NifFile::getRegNif(path, nifPtr) )
				if ( nifPtr->root )
					loc = 3;
				else
					dPrintAndLog("CheckFileLocation","Nif root bad!");
	}
	dPrintAndLog("CheckFileLocation","File \""+path+"\" "+(loc==0?("not found!"):(loc==1?("found in folders!"):(loc==2?("found in BSA!"):(loc==3?("found in RegList!"):("returned unknown location!"))))));
	return loc;
}

void WriteNifToStream(string path, UInt32& loc, std::iostream* stream) {
	loc = CheckFileLocation(path);
	if ( loc == 0 ) {
		throw exception(string("Nif \""+path+"\" not found.").c_str());
	}
	else if ( loc == 1 ) {
		std::ifstream file ((GetOblivionDirectory()+"Data\\Meshes\\"+path).c_str(), std::ios::in|std::ios::out|std::ios::binary);
		if ( file.is_open() )
			*stream << file.rdbuf();
		else
			dPrintAndLog("WriteNifToStream","File \""+path+"\" could not be read.");
		file.close();
	}
	else if ( loc == 2 ) {
		UInt32 fileNum = 0;
		UInt32 size = 0;
		TES4BSA_Archive * BSA = NULL;
		char* buf = NULL;
		for ( BSAit = BSAlist.begin(); BSAit != BSAlist.end(); ++BSAit ) {
			try {
				BSA = new TES4BSA_Archive((*BSAit).c_str());
				if ( BSA->GetFileCount() > 0 ) {
					try {
						fileNum = BSA->FindFileNumber(("Meshes\\"+path).c_str());
						try {
							size = BSA->GetFileSize(fileNum);
							buf = new char[size];
							try {
								BSA->GetFileData(fileNum, buf);
								stream->write(buf, size);
								dPrintAndLog("WriteNifToStream","Successfully read nif data in BSA \""+(*BSAit)+"\". Buffer length is "+UIntToString(size)+".");
							}
							catch (exception& except) {
								dPrintAndLog("WriteNifToStream","Failed to read nif data in BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
								continue;
							}
							delete [] buf;
							break;
						}
						catch (exception& except) {
							dPrintAndLog("WriteNifToStream","Failed to determine nif file size in BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
							continue;
						}
					}
					catch (...) {
						continue;
					}
				}
				else
					continue;
				delete BSA;
			}
			catch (exception& except) {
				dPrintAndLog("WriteNifToStream","Failed to open BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
				continue;
			}
		}
		if ( size == 0 )
			throw exception("Nif not found in BSAs.");
	}
	else if ( loc == 3 ) {
		NifFile* nifPtr = NULL;
		NifFile::getRegNif(path, nifPtr);
		if ( nifPtr->root ) {
			std::stringstream ostr (std::ios::binary|std::ios::in|std::ios::out);
			try { Niflib::WriteNifTree(ostr, nifPtr->root, nifPtr->headerInfo); } catch (std::exception except) { throw except; }
			std::ofstream newFile ((GetOblivionDirectory()+"Data\\Meshes\\DW\\NifSE\\"+path).c_str(), std::ios::binary|std::ios::out);
			*stream << ostr.str();
		}
		else
			throw exception("Nif root bad!");
	}
	else
		throw exception(string("Nif location unknown. CheckLocation return value is "+UIntToString(loc)+".").c_str());
}

string UIntToString(UInt32 uint) {
	std::stringstream buf;
	buf << uint;
	return buf.str();
}

UInt32 StringToUInt(string str) {
	UInt32 uint = 0;
	for (int i = 0; i < str.length(); ++i ) {
		switch (str[i]) {
			case '0':
				uint = uint * 10;
				break;

			case '1':
				uint = uint * 10 + 1;
				break;

			case '2':
				uint = uint * 10 + 2;
				break;

			case '3':
				uint = uint * 10 + 3;
				break;

			case '4':
				uint = uint * 10 + 4;
				break;

			case '5':
				uint = uint * 10 + 5;
				break;

			case '6':
				uint = uint * 10 + 6;
				break;

			case '7':
				uint = uint * 10 + 7;
				break;

			case '8':
				uint = uint * 10 + 8;
				break;

			case '9':
				uint = uint * 10 + 9;
				break;
		}
	}
	return uint;
}

string FloatToString(float flt) {
	std::stringstream buf;
	buf << flt;
	return buf.str();
}

float StringToFloat(string str) {
	float flt = 0;
	std::stringstream buf (str);
	buf >> flt;
	return flt;
}

string VectorToString(vector<float> vec) {
	string str = "[";
	for ( unsigned int i = 0; i < vec.size(); ++i )
		str += FloatToString(vec[i])+"|";
	return str;
}

string VectorToString(Niflib::Vector3 vec) {
	return "["+FloatToString(vec.x)+"|"+FloatToString(vec.y)+"|"+FloatToString(vec.z)+"|";
}

vector<float> StringToVector(string str) {
	vector<float> vec = vector<float>();
	string::size_type posS = 1;
	string::size_type posF = str.find("|");
	while ( posS < str.size() ) {
		posF = str.find("|", posS);
		vec.push_back(StringToFloat(str.substr(posS,posF-posS)));
		posS = posF + 1;
	}
	return vec;
}

string MatrixToString(vector< vector <float> > mat) {
	string str = "";
	for ( unsigned int i = 0; i < mat.size(); ++i ) {
		str += "[";
		for ( unsigned int j = 0; j < mat[i].size(); ++j )
			str += FloatToString(mat[i][j])+"|";
	}
	return str;
}

string MatrixToString(Niflib::Matrix33 mat) {
	float matArr[3][3];
	mat.AsFloatArr(matArr);
	return   "["+FloatToString(matArr[0][0])+"|"+FloatToString(matArr[0][1])+"|"+FloatToString(matArr[0][2])+
			"|["+FloatToString(matArr[1][0])+"|"+FloatToString(matArr[1][1])+"|"+FloatToString(matArr[1][2])+
			"|["+FloatToString(matArr[2][0])+"|"+FloatToString(matArr[2][1])+"|"+FloatToString(matArr[2][2])+"|";
}

string MatrixToString(Niflib::Matrix44 mat) {
	float matArr[4][4];
	mat.AsFloatArr(matArr);
	return   "["+FloatToString(matArr[0][0])+"|"+FloatToString(matArr[0][1])+"|"+FloatToString(matArr[0][2])+"|"+FloatToString(matArr[0][3])+
			"|["+FloatToString(matArr[1][0])+"|"+FloatToString(matArr[1][1])+"|"+FloatToString(matArr[1][2])+"|"+FloatToString(matArr[1][3])+
			"|["+FloatToString(matArr[2][0])+"|"+FloatToString(matArr[2][1])+"|"+FloatToString(matArr[2][2])+"|"+FloatToString(matArr[2][3])+
			"|["+FloatToString(matArr[3][0])+"|"+FloatToString(matArr[3][1])+"|"+FloatToString(matArr[3][2])+"|"+FloatToString(matArr[3][3])+"|";
}

vector< vector<float> > StringToMatrix(string str) {
	vector< vector<float> > mat = vector< vector<float> >();
	string::size_type posS = 1;
	string::size_type posF = str.find("|");
	mat.push_back(vector<float>());
	unsigned int i = 0;
	while ( posS < str.size() ) {
		if ( str[posS] == '[' ) {
			mat.push_back(vector<float>());
			++posS;
			++i;
		}
		posF = str.find("|", posS);
		mat[i].push_back(StringToFloat(str.substr(posS,posF-posS)));
		posS = posF + 1;
	}
	return mat;
}

string changeLog(UInt32 Node, UInt32 Type, UInt32 Action, string Value) {
	return changeLog(logNumber+UIntToString(Node),Type,Action,Value);
}

string changeLog(string Node, UInt32 Type, UInt32 Action, string Value) {
	return Node+logNode+UIntToString(Type)+logType+UIntToString(Action)+logAction+Value+logValue;
}

void clearPrevChange(string &log, const UInt32 &Node, const UInt32 &Type, const UInt32 &Action) {
	clearPrevChange(log, logNumber+UIntToString(Node), Type, Action);
}

void clearPrevChange(string &log, const string &Node, const UInt32 &Type, const UInt32 &Action) {
	UInt32 changePos = log.find(Node+logNode+UIntToString(Type)+logType+UIntToString(Action)+logAction);
	if ( changePos != log.npos )
		log.erase(changePos, log.find(logValue,changePos)+1-changePos);
}

extern list<string> BSAlist = list<string>();
extern list<string>::iterator BSAit = list<string>::iterator();
