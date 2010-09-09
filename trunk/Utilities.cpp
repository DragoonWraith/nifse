#include "Utilities.h"

extern string						g_pluginName	("NifSE");
extern IDebugLog					g_Log			((g_pluginName+".log").c_str());
extern UInt32						g_pluginVersion	(getV(0x0001,0x00,0x2,0xF));
extern PluginHandle					g_pluginHandle	(kPluginHandle_Invalid);

extern OBSEArrayVarInterface*		arrInterface	(NULL);
extern OBSEMessagingInterface*		msgInterface	(NULL);
extern OBSESerializationInterface*	serInterface	(NULL);
extern OBSEStringVarInterface*		strInterface	(NULL);

UInt8  getAlphaV(const UInt32 ver) { return (ver & 0x0000000F) >> alpha; }
void setAlphaV(UInt8 a, UInt32 ver) { ver = (ver & 0xFFFFFFF0) | ((a & 0xF) << alpha); }
bool isAlpha(const UInt32 ver) { return (getAlphaV(ver) != 0xF); }

UInt8   getBetaV(const UInt32 ver) { return (ver & 0x000000F0) >> beta; }
void setBetaV(UInt8 b, UInt32 ver) { ver = (ver & 0xFFFFFF0F) | ((b & 0xF) << beta); }
bool isBeta(const UInt32 ver) { return (getBetaV(ver) != 0xF) && !isAlpha(); }

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

string UIntToString(UInt32 uint) {
	std::stringstream buf;
	buf << uint;
	return buf.str();
}

UInt32 StringToUInt(string str) {
	UInt32 uint;
	std::stringstream buf (str);
	buf >> uint;
	return uint;
}

string SIntToString(SInt32 sint) {
	std::stringstream buf;
	buf << sint;
	return buf.str();
}

SInt32 StringToSInt(string str) {
	SInt32 sint;
	std::stringstream buf (str);
	buf >> sint;
	return sint;
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

extern list<string> BSAlist = list<string>();
extern list<string>::iterator BSAit = list<string>::iterator();
