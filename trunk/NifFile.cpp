#include "NifFile.h"

map < UInt8, map < UInt32, NifFile* > > NifFile::RegList = map < UInt8, map < UInt32, NifFile* > >();
map <string, pair<UInt8, UInt32>* > NifFile::RegListByFilename = map <string, pair<UInt8, UInt32>* >();

NifFile::NifFile() : filePath(""), basePath(""), root(NULL), modID(255), nifID(-1), delta("") {
	dPrintAndLog("NifFile c'tor","Default constructor");
}

NifFile::NifFile(const string& file, UInt8 modIndex, bool forEdit) : filePath(file), basePath(""), nifSEversion(g_pluginVersion), editable(forEdit), modID(modIndex), nifID(0), delta("") {
	dPrintAndLog("NifFile c'tor","NifFile created"+string(editable?" for editing.":" without editing."));
	headerInfo = new Niflib::NifInfo();
	loadNif();
	if ( root ) {
		dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList.");
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8,map<UInt32,NifFile*> >(modID,map<UInt32,NifFile*>()) );
		UInt32 i = 0;
		while ( !((RegList[modID].insert(pair<UInt32, NifFile*>(i, this))).second) )
			++i;
		nifID = i;
		if ( editable ) {
			basePath = filePath;
			filePath = string(s_nifSEPath) + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
			RegListByFilename[filePath.substr(s_nifSEPathLen,filePath.length()-s_nifSEPathLen)] = new pair<UInt8, UInt32>(modID, nifID);

			string firstTest = filePath.substr(s_nifSEPathLen);
			firstTest.insert(firstTest.length()-4,"_first");
			Niflib::WriteNifTree(getAbsPath(firstTest),root,*headerInfo);
		}
		else
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
		dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(i)+".");
	}
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const string& oriPath, const string& altPath) : filePath(oriPath), nifSEversion(0x0000001F), editable(true), modID(0xFF), nifID(0), delta("") {
	dPrintAndLog("NifFile c'tor","NifFile created from deprecated function.");
	headerInfo = new Niflib::NifInfo();
	loadNif();
	if ( root ) {
		dPrintAndLog("NifFile.reg","Registering \""+altPath+"\" on RegList.");
		if ( RegList.find(0xFF) == RegList.end() )
			RegList.insert( pair<UInt8, map<UInt32, NifFile*> >(0xFF, map<UInt32, NifFile*>()) );
		UInt32 i = 0;
		while ( !((RegList[modID].insert(pair<UInt32, NifFile*>(i, this))).second) )
			++i;
		nifID = i;
		basePath = oriPath;
		filePath = altPath;
		if ( !_stricmp(filePath.substr(0, s_nifSEPathLen).c_str(), s_nifSEPath) ) {
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+" and \""+filePath.substr(s_nifSEPathLen)+"\".");
			RegListByFilename[filePath.substr(s_nifSEPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
		}
		else {
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+" and \""+filePath+"\".");
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
			filePath.insert(0,s_nifSEPath);
		}
	}
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const string& file, UInt8 modIndex, UInt32 nifIndex, bool forEdit, UInt32 nifSEv) : filePath(file), nifSEversion(nifSEv), editable(forEdit), modID(modIndex), nifID(nifIndex), delta("") {
	dPrintAndLog("NifFile c'tor","Load constructor");
	headerInfo = new Niflib::NifInfo();
	loadNif();
	if ( root ) {
		dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8, map<UInt32, NifFile*> >(modID, map<UInt32, NifFile*>()) );
		if ( (RegList[modID].insert(pair<UInt32, NifFile*>(nifIndex, this))).second ) {
			nifID = nifIndex;
			if ( editable ) {
				basePath = filePath;
				filePath = string(s_nifSEPath) + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
				RegListByFilename[filePath.substr(s_nifSEPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
			}
			else
				RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
		}
	}
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const string& oriPath, const string& altPath, UInt32 nifIndex) : filePath(oriPath), nifSEversion(0x0000001F), editable(true), modID(0xFF), nifID(0), delta("") {
	dPrintAndLog("NifFile c'tor","NifFile created from deprecated function.");
	headerInfo = new Niflib::NifInfo();
	loadNif();
	if ( root ) {
		dPrintAndLog("NifFile.reg","Registering \""+altPath+"\" on RegList.");
		if ( RegList.find(0xFF) == RegList.end() )
			RegList.insert( pair<UInt8, map<UInt32, NifFile*> >(0xFF, map<UInt32, NifFile*>()) );
		nifID = nifIndex;
		basePath = oriPath;
		filePath = altPath;
		if ( !_stricmp(filePath.substr(0, s_nifSEPathLen).c_str(), s_nifSEPath) ) {
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+" and \""+filePath.substr(s_nifSEPathLen)+"\".");
			RegListByFilename[filePath.substr(s_nifSEPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
		}
		else {
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+" and \""+filePath+"\".");
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
			filePath.insert(0,s_nifSEPath);
		}
	}
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::~NifFile() {
	dPrintAndLog("NifFile d'tor","Nif "+UIntToString(modID)+"-"+UIntToString(nifID)+" deleted.");
	if ( RegList.find(modID) != RegList.end() ) {
		if ( RegList[modID].find(nifID) != RegList[modID].end() ) {
			RegListByFilename.erase(RegList[modID][nifID]->filePath);
			RegList[modID].erase(nifID);
		}
		if ( RegList[modID].empty() )
			RegList.erase(modID);
	}
	if ( headerInfo )
		delete headerInfo;
}

// this actually reads the Nif in.
void NifFile::loadNif() {
	dPrintAndLog("NifFile.loadNif","Loading \""+filePath+"\"!");
	std::stringstream* nifStream = new std::stringstream(std::ios::binary|std::ios::in|std::ios::out);
	try {
		WriteNifToStream(filePath, loc, nifStream);
		nifList = Niflib::ReadNifList(*nifStream,headerInfo);
		nifSize = nifList.size();
		try {
			findRoot();
			nifVersion = headerInfo->version;
			dPrintAndLog("NifFile.loadNif","Nif is good; "+getVersion()+". Loaded "+UIntToString(nifSize)+" blocks.");
		}
		catch (exception e) {
			dPrintAndLog("NifFile.loadNif","Could not find root, exception \""+string(e.what())+"\" thrown.");
			loc = 0;
		}
	}
	catch (exception& except) {
		dPrintAndLog("NifFile.loadNif","Nif cannot be read. Exception \""+string(except.what())+"\" thrown.");
		nifID = -1;
	}
	delete nifStream;
}

// returns NifFile associated with given mod and index.
bool NifFile::getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr) {
	if ( RegList.find(modID) != RegList.end() ) {
		if ( RegList[modID].find(nifID) != RegList[modID].end() ) {
			if ( RegList[modID][nifID]->root ) {
				dPrintAndLog("NifFile::getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" found.");
				nifPtr = RegList[modID][nifID];
				return true;
			}
			else {
				dPrintAndLog("NifFile::getRegNif","Nif root is no good.");
				return false;
			}
		}
		else {
			dPrintAndLog("NifFile::getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" not found.");
			return false;
		}
	}
	else {
		dPrintAndLog("NifFile::getRegNif","Mod #"+UIntToString(modID)+" not found.");
		return false;
	}
}

// returns the modID and index of nif with given filename.
bool NifFile::getRegNif(string filename, NifFile* &nifPtr) {
	dPrintAndLog("NifFile::getRefNif","Finding nif with filename \""+filename+"\".");
	if ( filename.substr(0, s_nifSEPathLen).compare(s_nifSEPath) == 0 )
		filename = filename.substr(s_nifSEPathLen);
	if ( RegListByFilename.find(filename) != RegListByFilename.end() ) {
		pair<UInt8, UInt32> nifIDs = *(RegListByFilename[filename]);
		return NifFile::getRegNif(nifIDs.first, nifIDs.second, nifPtr);
	}
	else {
		dPrintAndLog("NifFile::getRegNif","Filename not registered.");
		return false;
	}
}

// from niflib.cpp
Niflib::NiNodeRef NifFile::findRoot() {
	//--Look for a NiNode that has no parents--//
	for (unsigned int i = 0; i < nifList.size(); ++i) {
		root = Niflib::DynamicCast<Niflib::NiNode>(nifList[i]);
		if ( root != NULL ) {
			break;
		}
	}

	//Make sure a node was found, if not return first node
	if ( root == NULL )
		throw std::exception("No nodes found.");

	//Move up the chain to the root node
	while ( root->GetParent() != NULL ) {
		root = root->GetParent();
	}

	return root;
}

string NifFile::getAbsPath() const {
	return GetOblivionDirectory()+"Data\\Meshes\\"+filePath;
}

string NifFile::getAbsPath(const string& path) const {
	return GetOblivionDirectory()+"Data\\Meshes\\"+path;
}

string NifFile::getAbsBasePath() const {
	return GetOblivionDirectory()+"Data\\Meshes\\"+basePath;
}

string NifFile::getVersion() const {
	switch (nifVersion) {
		case Niflib::VER_2_3:
			return "v2.3";
			break;
		case Niflib::VER_3_0:
			return "v3.0";
			break;
		case Niflib::VER_3_03:
			return "v3.03";
			break;
		case Niflib::VER_3_1:
			return "v3.1";
			break;
		case Niflib::VER_3_3_0_13:
			return "v3.3.0.13";
			break;
		case Niflib::VER_4_0_0_0:
			return "v4.0.0.0";
			break;
		case Niflib::VER_4_0_0_2:
			return "v4.0.0.2";
			break;
		case Niflib::VER_4_1_0_12:
			return "v4.1.0.12";
			break;
		case Niflib::VER_4_2_0_2:
			return "v4.2.0.2";
			break;
		case Niflib::VER_4_2_1_0:
			return "v4.2.1.0";
			break;
		case Niflib::VER_4_2_2_0:
			return "v4.2.2.0";
			break;
		case Niflib::VER_10_0_1_0:
			return "v10.0.1.0";
			break;
		case Niflib::VER_10_0_1_2:
			return "v10.0.1.2";
			break;
		case Niflib::VER_10_0_1_3:
			return "v10.0.1.3";
			break;
		case Niflib::VER_10_1_0_0:
			return "v10.1.0.0";
			break;
		case Niflib::VER_10_1_0_101:
			return "v10.1.0.101";
			break;
		case Niflib::VER_10_1_0_106:
			return "v10.1.0.106";
			break;
		case Niflib::VER_10_2_0_0:
			return "v10.2.0.0";
			break;
		case Niflib::VER_10_4_0_1:
			return "v10.4.0.1";
			break;
		case Niflib::VER_20_0_0_4:
			return "v20.0.0.4";
			break;
		case Niflib::VER_20_0_0_5:
			return "v20.0.0.5";
			break;
		case Niflib::VER_20_1_0_3:
			return "v20.1.0.3";
			break;
		case Niflib::VER_20_2_0_7:
			return "v20.2.0.7";
			break;
		case Niflib::VER_20_2_0_8:
			return "v20.2.0.8";
			break;
		case Niflib::VER_20_3_0_1:
			return "v20.3.0.1";
			break;
		case Niflib::VER_20_3_0_2:
			return "v20.3.0.2";
			break;
		case Niflib::VER_20_3_0_3:
			return "v20.3.0.3";
			break;
		case Niflib::VER_20_3_0_6:
			return "v20.3.0.6";
			break;
		case Niflib::VER_20_3_0_9:
			return "v20.3.0.9";
			break;
		case Niflib::VER_UNSUPPORTED:
			return "\"UNSUPPORTED VERSION\" ("+UIntToString(nifVersion)+")";
			break;
		case Niflib::VER_INVALID:
			return "\"INVALID VERSION\" ("+UIntToString(nifVersion)+")";
			break;
		default:
			return "\"UNKNOWN VERSION\" ("+UIntToString(nifVersion)+")";
			break;
	}
}

// writes to the new Nif file
void NifFile::write(string path) {
	if ( path.compare("") == 0 )
		path = filePath;
	if ( root ) {
		dPrintAndLog("NifFile.write","Writing to \""+path+"\".");
		string::size_type i = 0;
		UInt32 nifSEoff = (path.substr(0,s_nifSEPathLen).compare(s_nifSEPath)==0?s_nifSEPathLen:0);
		while ( (i = path.substr(nifSEoff).find_first_of("\\", i+1)) != string::npos ) {
			string folderPath = GetOblivionDirectory()+"Data\\"+path.substr(0,i);
			CreateDirectory(folderPath.c_str(), NULL);
		}
		try {
			Niflib::WriteNifTree(getAbsPath(path),root,*headerInfo);
		}
		catch (...) {
			throw;
		}
	}
	else
		throw std::exception("Nif root is bad.");
}

void NifFile::logChange(const UInt32 &block, const UInt32 &type, const UInt32 &action, const string &value, const bool &clrPrev) {
	if ( clrPrev )
		clrChange(block, type, action);
	delta += UIntToString(block)+logNode+UIntToString(type)+logType+UIntToString(action)+logAction+value+logValue;
}

void NifFile::clrChange(const UInt32 &block, const UInt32 &type, const UInt32 &action) {
	UInt32 changePos = delta.find(UIntToString(block)+logNode+UIntToString(type)+logType+UIntToString(action)+logAction);
	if ( changePos != delta.npos )
		delta.erase(changePos, delta.find(logValue,changePos)+1-changePos);
}

// Extended version of FindFile that also checks RegList.
// To avoid going through RegList twice, can store the nif
// in a pointer, if passed.
UInt32 CheckFileLocation(string path, NifFile* nifPtr) {
	UInt32 loc = (*g_FileFinder)->FindFile(("Data\\Meshes\\"+path).c_str(),0,0,-1);
	if ( loc == 0 ) {
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
			try { Niflib::WriteNifTree(ostr, nifPtr->root, *(nifPtr->headerInfo)); } catch (std::exception except) { throw except; }
			std::ofstream newFile ((GetOblivionDirectory()+"Data\\Meshes\\DW\\NifSE\\"+path).c_str(), std::ios::binary|std::ios::out);
			*stream << ostr.str();
		}
		else
			throw exception("Nif root bad!");
	}
	else
		throw exception(string("Nif location unknown. CheckLocation return value is "+UIntToString(loc)+".").c_str());
}
