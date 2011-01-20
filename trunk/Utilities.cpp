#include "Utilities.h"

extern string						g_pluginName	("NifSE");
extern IDebugLog					g_Log			((g_pluginName+".log").c_str());
extern UInt32						g_pluginVersion	(CURRENT_VERSION);
extern PluginHandle					g_pluginHandle	(kPluginHandle_Invalid);

extern OBSEScriptInterface*			scrInterface	(NULL);
extern OBSEArrayVarInterface*		arrInterface	(NULL);
extern OBSEMessagingInterface*		msgInterface	(NULL);
extern OBSESerializationInterface*	serInterface	(NULL);
extern OBSEStringVarInterface*		strInterface	(NULL);

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

string BoolToString(bool b) {
	return b?"TRUE":"FALSE";
}

bool StringToBool(string str) {
	return str.compare("TRUE") == 0;
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

string VectorToString(vector<Niflib::byte> vec) {
	string str = "[";
	for ( unsigned int i = 0; i < vec.size(); ++i )
		str += UIntToString(vec[i])+"|";
	return str;
}

string VectorToString(vector<unsigned int> vec) {
	string str = "[";
	for ( unsigned int i = 0; i < vec.size(); ++i )
		str += UIntToString(vec[i])+"|";
	return str;
}

string VectorToString(vector<string> vec) {
	string str = "[";
	for ( unsigned int i = 0; i < vec.size(); ++i )
		str += vec[i]+"|";
	return str;
}

string VectorToString(Niflib::Vector3 vec) {
	return "["+FloatToString(vec.x)+"|"+FloatToString(vec.y)+"|"+FloatToString(vec.z)+"|";
}

string VectorToString(Niflib::TexCoord mat) {
	return "["+FloatToString(mat.u)+"|"+FloatToString(mat.v)+"|";
}

string VectorToString(Niflib::Color3 color) {
	return "["+FloatToString(color.r)+"|"+FloatToString(color.g)+"|"+FloatToString(color.b)+"|";
}

string VectorToString(Niflib::Color4 color) {
	return "["+FloatToString(color.r)+"|"+FloatToString(color.g)+"|"+FloatToString(color.b)+"|"+FloatToString(color.a)+"|";
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

vector<Niflib::byte> StringToVectorB(string str) {
	vector<Niflib::byte> vec = vector<Niflib::byte>();
	string::size_type posS = 1;
	string::size_type posF = str.find("|");
	while ( posS < str.size() ) {
		posF = str.find("|", posS);
		vec.push_back(StringToUInt(str.substr(posS,posF-posS)));
		posS = posF + 1;
	}
	return vec;
}

vector<unsigned int> StringToVectorU(string str) {
	vector<unsigned int> vec = vector<unsigned int>();
	string::size_type posS = 1;
	string::size_type posF = str.find("|");
	while ( posS < str.size() ) {
		posF = str.find("|", posS);
		vec.push_back(StringToUInt(str.substr(posS,posF-posS)));
		posS = posF + 1;
	}
	return vec;
}

vector<string> StringToVectorS(string str) {
	vector<string> vec = vector<string>();
	string::size_type posS = 1;
	string::size_type posF = str.find("|");
	while ( posS < str.size() ) {
		posF = str.find("|", posS);
		vec.push_back(str.substr(posS,posF-posS));
		posS = posF + 1;
	}
	return vec;
}

Niflib::Vector3 StringToVector3(string str) {
	Niflib::Vector3 vec;
	string::size_type posS = 1;
	string::size_type posF = str.find("|",1);
	vec.x = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	vec.y = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	vec.z = StringToFloat(str.substr(posS,posF-posS));
	return vec;
}

Niflib::TexCoord StringToVectorT(string str) {
	Niflib::TexCoord vec;
	string::size_type posS = 1;
	string::size_type posF = str.find("|",1);
	vec.u = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	vec.v = StringToFloat(str.substr(posS,posF-posS));
	return vec;
}

Niflib::Color3 StringToVectorC3(string str) {
	Niflib::Color3 color;
	string::size_type posS = 1;
	string::size_type posF = str.find("|",1);
	color.r = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|", posS);
	color.g = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|", posS);
	color.b = StringToFloat(str.substr(posS,posF-posS));
	return color;
}

Niflib::Color4 StringToVectorC4(string str) {
	Niflib::Color4 color;
	string::size_type posS = 1;
	string::size_type posF = str.find("|",1);
	color.r = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|", posS);
	color.g = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|", posS);
	color.b = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|", posS);
	color.a = StringToFloat(str.substr(posS,posF-posS));
	return color;
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

string Color4ToString(Niflib::Color4 color) {
	return "[" + FloatToString(color.r) + "|" + FloatToString(color.g) + "|" + FloatToString(color.b) + "|" + FloatToString(color.a) + "|";
}

Niflib::Color4 StringToColor4(string str) {
	Niflib::Color4 color;
	string::size_type posS = 1;
	string::size_type posF = str.find("|",1);
	color.r = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	color.g = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	color.b = StringToFloat(str.substr(posS,posF-posS));
	posS = posF+1;
	posF = str.find("|",posS);
	color.a = StringToFloat(str.substr(posS,posF-posS));
	return color;
}

extern list<string> BSAlist = list<string>();
extern list<string>::iterator BSAit = list<string>::iterator();
