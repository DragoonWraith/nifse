#include "NifFile.h"
#include "BSfile.h"

map < UInt8, map < UInt32, NifFile* > > NifFile::RegList = map < UInt8, map < UInt32, NifFile* > >();
map <string, pair<UInt8, UInt32>* > NifFile::RegListByFilename = map <string, pair<UInt8, UInt32>* >();
vector<changeLog> NifFile::delta = vector<changeLog>();

NifFile::NifFile() : filePath(""), basePath(""), root(NULL), modID(255), nifID(-1) {
	dPrintAndLog("NifFile c'tor","Default constructor");
}

NifFile::NifFile(const string& file, UInt8 modIndex, bool forEdit) : filePath(file), basePath(""), nifSEversion(g_pluginVersion), editable(forEdit), modID(modIndex), nifID(0) {
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
		}
		else
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
		dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(i)+".");
	}
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const string& oriPath, const string& altPath) : filePath(oriPath), nifSEversion(0x0000001F), editable(true), modID(0xFF), nifID(0) {
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

NifFile::NifFile(const string& file, UInt8 modIndex, UInt32 nifIndex, bool forEdit, UInt32 nifSEv) : filePath(file), nifSEversion(nifSEv), editable(forEdit), modID(modIndex), nifID(nifIndex) {
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

NifFile::NifFile(const string& oriPath, const string& altPath, UInt32 nifIndex) : filePath(oriPath), nifSEversion(0x0000001F), editable(true), modID(0xFF), nifID(0) {
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
			RegList[modID][nifID] = NULL;
		}
		if ( RegList[modID].empty() )
			RegList.erase(modID);
	}
	if ( headerInfo )
		delete headerInfo;
}

// this calls readNif and then sets up the NifFile with the result
void NifFile::loadNif() {
	dPrintAndLog("NifFile.loadNif","Loading \""+filePath+"\"!");
	try {
		readNif();
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
}

// this actually reads the nif in.
void NifFile::readNif() {
	std::stringstream* stream = new std::stringstream(std::ios::binary|std::ios::in|std::ios::out);
	BSfile* nifBSfile = loadBSfile(("Data\\Meshes\\"+filePath).c_str(), 0, 0x2800);
	NifFile* nifPtr = NULL;
	std::exception* e = NULL;
	if ( nifBSfile ) {
		const char* buffer = NULL;
		try {
			UInt32 size = nifBSfile->GetSize();
			buffer = new const char[size];
			UInt32 readCount = nifBSfile->Read((void*)buffer, size);
			dPrintAndLog("NifFile.readNif", "Read "+UIntToString(readCount)+" of "+UIntToString(size)+" bytes.");
			stream->write(buffer, size);
		}
		catch (std::exception except) {
			e = new std::exception(except);
		}
		if ( nifBSfile )
			nifBSfile->Destructor(true);
		if ( buffer )
			delete [] buffer;
	}
	else if ( NifFile::getRegNif(filePath, nifPtr) ) {
		if ( nifPtr->root ) {
			try {
				Niflib::WriteNifTree(*stream, nifPtr->root, *(nifPtr->headerInfo));
				nifPtr->frzChange(this);
			}
			catch (std::exception except) {
				e = new std::exception(except);
			}
		}
		else {
			e = new std::exception("Nif root bad.");
		}
	}
	else {
		e = new std::exception("Nif not found.");
	}
	if ( e ) {
		std::exception except = *e;
		delete e;
		throw except;
	}
	try {
		nifList = Niflib::ReadNifList(*stream, headerInfo);
		nifSize = nifList.size();
	}
	catch (std::exception except) {
		throw except;
	}
}

// returns NifFile associated with given mod and index.
bool NifFile::getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr) {
	if ( RegList.find(modID) != RegList.end() ) {
		if ( RegList[modID].find(nifID) != RegList[modID].end() ) {
	//		if ( RegList[modID][nifID]->root ) {
	//			dPrintAndLog("NifFile::getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+"'s root is good.");
			if ( RegList[modID][nifID] ) {
				nifPtr = RegList[modID][nifID];
				return true;
			}
			else {
	//			dPrintAndLog("NifFile::getRegNif","Nif root is no good.");
				dPrintAndLog("NifFile::getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" has been deleted.");
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
			string folderPath = GetOblivionDirectory()+"Data\\Meshes\\"+path.substr(0,i+nifSEoff);
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
	NifFile::delta.push_back(changeLog(modID, nifID, filePath, basePath, nifSEversion, editable, type, block, action, value));
}

void NifFile::clrChange(const UInt32 &block, const UInt32 &type, const UInt32 &action) {
	for ( vector<changeLog>::iterator i = NifFile::delta.begin(); i != NifFile::delta.end(); ++i ) {
		if ( i->mod == modID && i->nif == nifID && i->block == block && i->type == type && i->act == action && i->required.empty() ) {
			NifFile::delta.erase(i);
			break;
		}
	}
}

void NifFile::frzChange(NifFile* depends) {
	for ( vector<changeLog>::iterator i = NifFile::delta.begin(); i!= NifFile::delta.end(); ++i )
		if ( i->mod == modID && i->nif == nifID )
			i->required.push_back(depends);
}

bool NifFile::delChange() {
	changeLog* logPtr = NULL;
	for ( vector<changeLog>::size_type i = NifFile::delta.size(); i > 0; --i ) {
		logPtr = &(NifFile::delta[i-1]);
		if ( logPtr->mod == modID && logPtr->nif == nifID ) {
			if ( logPtr->required.empty() )
				NifFile::delta.erase(NifFile::delta.begin()+i-1);
			else
				return false;
		}
		else if ( !logPtr->required.empty() ) {
			for ( vector<NifFile*>::size_type j = 0; j < logPtr->required.size(); ++j ) {
				if ( logPtr->required[j] == this ) {
					logPtr->required.erase(logPtr->required.begin()+j);
					--j;
				}
			}
		}
	}
	return true;
}
