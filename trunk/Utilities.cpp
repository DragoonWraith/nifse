#include "Utilities.h"

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

// for easily switching between two versions of a mesh - modified and original
string ToggleTag(string path, string element, string newVal) {
	if ( path.find("NifSE") != string::npos ) { // already tagged with something
		if ( path.find(element) != string::npos ) { // already tagged with THIS element
			if ( path.find(element+newVal) != string::npos ) { // element has been changed to appropriate value, want to remove change
				path.erase(path.find(element+newVal)-1,(element+newVal).length()+1); // 1's to account for the prefixed '.'
				if ( !_stricmp(&(path.c_str()[(path.length()>=14?path.length()-14:0)]),".NifSE.nif") ) { // only tag in this path
					dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged correctly, only tag in path, removing all tags and returning original mesh!");
					path.erase(path.find(".NifSE"),10);
				}
				else
					dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged correctly, removing this tag. Other tags remain.");
			}
			else { // already changed this element, but changing it to a new value
				string::size_type oldValPos = path.find(element)+element.length();
				string::size_type oldValLen = path.find(".",oldValPos)-oldValPos;
				path.replace(oldValPos,oldValLen,newVal);
				dPrintAndLog("ToggleTag","Element \""+element+"\" already tagged, value changed to \""+newVal+"\".");
			}
		}
		else { // tagged, but this element's new
			path.insert(path.length()-4,"."+element+newVal);
			dPrintAndLog("ToggleTag","Element \""+element+"\" added to existing tags with value \""+newVal+"\".");
		}
	}
	else { // completely untagged
		path.insert(path.length()-4,".NifSE."+element+newVal);
		dPrintAndLog("ToggleTag","Element \""+element+"\" first tag in path. Set with value \""+newVal+"\".");
	}
	return path;
}

// internal version of FindFile that does some double-checking
// not sure if this is still necessary
UInt32 CheckFileLocation(string path) {
	UInt32 loc = (*g_FileFinder)->FindFile(("Data\\Meshes\\"+path).c_str(),0,0,-1);
	if ( loc == 0 ) {
		std::ofstream file;
		file.open((GetOblivionDirectory()+"Data\\Meshes\\"+path).c_str(),std::ios::binary|std::ios::in);
		if ( file.is_open() )
			loc = 1;
		file.close();
	}
	dPrintAndLog("CheckFileLocation","File \""+path+"\" "+(loc==0?("not found!"):(loc==1?("found in folders!"):(loc==2?("found in BSA!"):("returned unknown location!")))));
	return loc;
}

void WriteNifToStream(string path, UInt32& loc, std::iostream* stream) {
	loc = CheckFileLocation(path);
	if ( loc == 0 )
		throw exception(string("Nif \""+path+"\" not found.").c_str());
	else if ( loc == 1 ) {
		std::ifstream file ((GetOblivionDirectory()+"Data\\Meshes\\"+path).c_str(), std::ios::in|std::ios::out|std::ios::binary);
		if ( file.is_open() )
			*stream << file.rdbuf();
		else
			dPrintAndLog("WriteNifToStream","File \""+path+"\" could not be read.");
		file.close();
	}
	else if ( loc == 2 ) {
		if ( BSAlist.size() == 0 )
			BSAlist = GetBSAfiles();
		UInt32 fileNum;
		UInt32 size;
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
								dPrintAndLog("GetNifStream","Successfully read nif data in BSA \""+(*BSAit)+"\". Buffer length is "+UIntToString(size)+".");
							}
							catch (exception& except) {
								dPrintAndLog("GetNifStream","Failed to read nif data in BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
								continue;
							}
							delete [] buf;
							break;
						}
						catch (exception& except) {
							dPrintAndLog("GetNifStream","Failed to determine nif file size in BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
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
				dPrintAndLog("GetNifStream","Failed to open BSA \""+(*BSAit)+"\". Exception \""+string(except.what())+"\" thrown.");
				continue;
			}
		}
		if ( size == 0 )
			throw exception("Nif not found in BSAs.");
	}
	else
		throw exception(string("Nif location unknown. CheckLocation return value is "+UIntToString(loc)+".").c_str());
}

// Copies the Nif-file to another file location.
// nothing Nif-specific here, just uses standard
// C++ file functions and BSA-reading code
int CopyNif(string oriPath, string altPath) {
	try {
		std::fstream nifbuf;
		unsigned int charIndex1 = 0;
		unsigned int charIndex2 = altPath.find_first_of("\\");
		string folder = GetOblivionDirectory()+"Data\\Meshes";
		while ( charIndex2 != string::npos ) {
			folder = folder+"\\"+altPath.substr(charIndex1,charIndex2-charIndex1);
			CreateDirectory(folder.c_str(),NULL);
			charIndex1 = charIndex2+1;
			charIndex2 = altPath.find_first_of("\\",charIndex1);
		}
		folder = GetOblivionDirectory()+"Data\\Meshes\\";
		nifbuf.open((folder+altPath).c_str(),std::ios::binary|std::ios::out);
		if ( nifbuf.is_open() ) {
			dPrintAndLog("CopyNif","Nif \""+folder+altPath+"\" created and opened.");
			UInt32 loc;
			WriteNifToStream(oriPath, loc, &nifbuf);
			nifbuf.close();
			return loc;
		}
		else {
			dPrintAndLog("CopyNif","Failed to create new file.");
			return -1;
		}
	}
	catch (exception& except) {
		dPrintAndLog("CopyNif","Failed to read Nif. Exception \""+string(except.what())+"\" thrown.");
		return -1;
	}
}

int CopyNif(string path) { // from BSA to folder, basically
	return CopyNif(path,path);
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

// constructs list of BSA files
std::list<string> GetBSAfiles() {
	std::list<string> BSAfiles;
	WIN32_FIND_DATA bsaSearch;
	HANDLE h;

	// build a list of BSA files
	// code adapted from that by Hammer on CProgramming.com
	// http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1046380353&id=1044780608
	h = FindFirstFile((GetOblivionDirectory()+"Data\\*.bsa").c_str(), &bsaSearch);
	if (h != INVALID_HANDLE_VALUE)
	{
		do {
			if ( !strncmp(bsaSearch.cFileName, "Oblivion", 8) ) {
				if ( !strcmp(bsaSearch.cFileName, "Oblivion - Meshes.bsa") )
					BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
			}
			else if ( !strncmp(bsaSearch.cFileName, "DLCShiveringIsles", 17) ) {
				if ( !strcmp(bsaSearch.cFileName, "DLCShiveringIsles - Meshes.bsa") )
					BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
			}
			else if ( strncmp(bsaSearch.cFileName, "ArchiveInvalidationInvalidated!.bsa", 34) )
				BSAfiles.push_back((GetOblivionDirectory()+"Data\\"+bsaSearch.cFileName));
		} while (FindNextFile(h, &bsaSearch));
		if (GetLastError() != ERROR_NO_MORE_FILES)
			PrintAndLog("GetBSAfiles","Unknown error during BSA search - some Nif files inside archives may be unaccessible.");
	}
	else
	{
		PrintAndLog("GetBSAfiles","No BSA files found!");
	}
	FindClose(h);
	return BSAfiles;
}