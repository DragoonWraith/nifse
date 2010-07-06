#include "NifFile.h"

NifFile::NifFile() : filePath(""), basePath(""), root(NULL), modID(255), nifID(-1) {
	dPrintAndLog("NifFile c'tor","Default constructor");
}

NifFile::NifFile(const string& file, UInt8 modIndex, UInt32 nifIndex, bool forEdit) : filePath(file), editable(forEdit), modID(modIndex), nifID(nifIndex) {
	dPrintAndLog("NifFile c'tor","Load constructor");
	setRoot();
	if ( root )
		reg(modID,nifID);
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const string& file, UInt8 modIndex, bool forEdit) : filePath(file), basePath(""), editable(forEdit), modID(modIndex), nifID(0) {
	dPrintAndLog("NifFile c'tor","NifFile created"+string(editable?" for editing.":" without editing."));
	setRoot();
	if ( root )
		reg();
	else
		throw exception("Nif root not set; construction failed.");
}

NifFile::NifFile(const NifFile& copied) {
	if ( copied.root ) {
		filePath = copied.filePath;
		dPrintAndLog("NifFile c'tor","Copying \""+copied.filePath+"\".");
		basePath = copied.basePath;
		loc = copied.loc;
		baseLoc = copied.baseLoc;
		modID = copied.modID;
		nifID = copied.nifID;
	}
}

NifFile::~NifFile() {
	dPrintAndLog("NifFile d'tor","Nif "+UIntToString(modID)+"-"+UIntToString(nifID)+" deleted.\n");
	dereg();
}

// registers a nif in the next available index for its modID
SInt64 NifFile::reg() {
	dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList.");
	if ( modID != 255 ) {
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8,map<UInt32,NifFile*> >(modID,map<UInt32,NifFile*>()) );
		UInt32 i = 0;
		while ( !((RegList[modID].insert(pair<UInt32, NifFile*>(i, this))).second) )
			++i;
		nifID = i;
		if ( editable ) {
			basePath = filePath;
			filePath = string("ni\\") + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
			RegListByFilename[filePath.substr(s_nifScriptPathLen,filePath.length()-s_nifScriptPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
		}
		else
			RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
		dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(i)+".");
		return nifID;
	}
	return nifID = -1;
}

// registers nif in given modID and index; mostly for loading.
SInt64 NifFile::reg(UInt8 modIndex, UInt32 nifIndex) {
	dPrintAndLog("NifFile.reg","Registering \""+filePath+"\" on RegList as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
	if ( modIndex != modID )
		return nifID = -1;
	if ( modID != 255 ) {
		if ( RegList.find(modID) == RegList.end() )
			RegList.insert( pair<UInt8, map<UInt32, NifFile*> >(modID, map<UInt32, NifFile*>()));
		if ( (RegList[modID].insert(pair<UInt32, NifFile*>(nifIndex, this))).second ) {
			nifID = nifIndex;
			if ( editable ) {
				basePath = filePath;
				filePath = string("ni\\") + string((*g_dataHandler)->GetNthModName(modID)).substr(0,string((*g_dataHandler)->GetNthModName(modID)).length()-4) + string("_") + UIntToString(nifID) + ".nif";
				RegListByFilename[filePath.substr(s_nifScriptPathLen,filePath.length()-s_nifScriptPathLen)] = new pair<UInt8, UInt32>(modID, nifID);
			}
			else
				RegListByFilename[filePath] = new pair<UInt8, UInt32>(modID, nifID);
			dPrintAndLog("NifFile.reg","Registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
			return nifID;
		}
	}
	return nifID = -1;
}

// returns true if the given NifFile is on RegList
bool NifFile::isreg() {
	if ( RegList.find(modID) != RegList.end() )
		if ( RegList[modID].find(nifID) != RegList[modID].end() )
			return true;
	return false;
}

// removes given NifFile from RegList and does memory cleanup. Used in ~NifFile
void NifFile::dereg() {
	if ( isreg() ) {
//		delete RegListByFilename[RegList[modID][nifID]->filePath];
		RegListByFilename.erase(RegList[modID][nifID]->filePath);
//		delete RegList[modID][nifID];
		RegList[modID].erase(nifID);
	}
	if ( RegList[modID].empty() )
		RegList.erase(modID);
}

string NifFile::getAbsPath() const {
	return GetOblivionDirectory()+"Data\\Meshes\\"+filePath;
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

NiExtraDataRef NifFile::findExtraData(std::list<Niflib::NiExtraDataRef>::size_type i) const {
	list<Niflib::NiExtraDataRef>::iterator iter;
	list<Niflib::NiExtraDataRef>::size_type j = 0;
	list<Niflib::NiExtraDataRef> edlist = root->GetExtraData();
	for ( iter = edlist.begin(); (j < i) && (iter != edlist.end()); ++iter, ++j);
	if ( iter == edlist.end() )
		dPrintAndLog("NifFile.findExtraData","Index out of range.");
	return *iter;
}

void NifFile::setRoot(const string& newPath) {
	filePath = newPath;
	setRoot();
}

// this actually reads the Nif in.
void NifFile::setRoot() {
	dPrintAndLog("NifFile.setRoot","Setting root to root of \""+filePath+"\"!");
	try {
		std::stringstream nifStream (std::ios::binary|std::ios::in|std::ios::out);
		dPrintAndLog("NifFile.setRoot","nifStream initialized.");
		WriteNifToStream(filePath, loc, &nifStream);
		root = DynamicCast<Niflib::NiNode>(ReadNifTree(nifStream,&headerInfo));
		if ( root ) {
			dPrintAndLog("NifFile.setRoot","Nif read from stream of file \""+filePath+"\".");
			nifVersion = GetNifVersion(getAbsPath());
			collision = DynamicCast<Niflib::bhkNiCollisionObject>((DynamicCast<Niflib::NiAVObject>(root))->GetCollisionObject());
			dPrintAndLog("NifFile.setRoot","Nif is good; "+getVersion()+". Loaded "+UIntToString(root->GetExtraData().size())+" ExtraData nodes, "+(collision?string("collision, "):(""))+UIntToString(root->GetChildren().size())+" Children nodes, and "+UIntToString(root->GetEffects().size())+" Effects nodes.");
		}
		else {
			dPrintAndLog("NifFile.setRoot","Nif could not be read from stream of file \""+filePath+"\".");
			loc = 0;
		}
	}
	catch (exception& except) {
		dPrintAndLog("NifFile.setRoot","Nif cannot be read. Exception \""+string(except.what())+"\" thrown.");
		nifID = -1;
	}
}

// getExtraData
Niflib::NiExtraDataRef NifFile::getEDByName(string name) {
	dPrintAndLog("NifFile.getEDByName","Getting NiExtraData Node \""+name+"\".");
	list<NiExtraDataRef> edlist = root->GetExtraData();
	for ( extraDataIt = edlist.begin(); extraDataIt != edlist.end(); ++extraDataIt )
		if ( (*extraDataIt)->GetName() == name )
			return *extraDataIt;
	return NULL;
}

// getExtraData index
list<Niflib::NiExtraDataRef>::size_type NifFile::getEDIndexByName(string name) {
	dPrintAndLog("NifFile.getEDIndexByName","Getting NiExtraData Node \""+name+"\".");
	list<NiExtraDataRef> edlist = root->GetExtraData();
	list<NiExtraDataRef>::size_type i = 0;
	for ( extraDataIt = edlist.begin(); extraDataIt != edlist.end(); ++extraDataIt, ++i )
		if ( (*extraDataIt)->GetName() == name )
			return i;
	return edlist.size();
}

// getChild
Niflib::NiAVObjectRef NifFile::getChildByName(string name) {
	dPrintAndLog("NifFile.getChildByName","Getting NiAVObject Node \""+name+"\".");
	vector<Niflib::NiAVObjectRef> chvec = root->GetChildren();
	for ( childIt = chvec.begin(); childIt != chvec.end(); ++childIt )
		if ( (*childIt)->GetName() == name )
			return *childIt;
	return NULL;
}

// getChild index
vector<Niflib::NiAVObjectRef>::size_type NifFile::getChildIndexByName(string name) {
	dPrintAndLog("NifFile.getChildIndexByName","Getting NiAVObject Node \""+name+"\".");
	vector<Niflib::NiAVObjectRef>::size_type i = 0;
	vector<Niflib::NiAVObjectRef> chvec = root->GetChildren();
	for ( childIt = chvec.begin(); childIt != chvec.end(); ++childIt, ++i )
		if ( (*childIt)->GetName() == name )
			return i;
	return chvec.size();
}

// getEffect
Niflib::NiDynamicEffectRef NifFile::getEffectByName(string name) {
	dPrintAndLog("NifFile.getEffectByName","Getting NiDynamicEffects Node \""+name+"\".");
	vector<Niflib::NiDynamicEffectRef> efvec = root->GetEffects();
	for ( effectIt = efvec.begin(); effectIt != efvec.end(); ++effectIt )
		if ( (*effectIt)->GetName() == name )
			return *effectIt;
	return NULL;
}

// getEffect index
vector<Niflib::NiDynamicEffectRef>::size_type NifFile::getEffectIndexByName(string name) {
	dPrintAndLog("NifFile.getEffectIndexByName","Getting NiDynamicEffects Node \""+name+"\".");
	vector<Niflib::NiDynamicEffectRef>::size_type i = 0;
	vector<Niflib::NiDynamicEffectRef> efvec = root->GetEffects();
	for ( effectIt = efvec.begin(); effectIt != efvec.end(); ++effectIt, ++i )
		if ( (*effectIt)->GetName() == name )
			return i;
	return efvec.size();
}

// writes to the new Nif file
void NifFile::commitChanges() {
	if ( loc == 1 ) {
		dPrintAndLog("NifFile.commitChanges","Writing to \""+filePath+"\".");
		WriteNifTree(getAbsPath(),DynamicCast<Niflib::NiObject>(root),headerInfo);
	}
	else
		dPrintAndLog("NifFile.commitChanges","Failed to commit changes to Nif \""+filePath+"\".");
}

string NifFile::getIDstring() const {
	return "#"+UIntToString(modID)+"-"+UIntToString(nifID);
}

std::map < UInt8, std::map < UInt32, NifFile* > > NifFile::RegList;
std::map <string, pair<UInt8, UInt32>* > NifFile::RegListByFilename;

// returns NifFile associated with given mod and index.
bool NifFile::getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr) {
	dPrintAndLog("NifFile::getRegNif","Finding nif registered as #"+UIntToString(modID)+"-"+UIntToString(nifID)+".");
	if ( RegList.find(modID) != RegList.end() ) {
		if ( RegList[modID].find(nifID) != RegList[modID].end() ) {
			dPrintAndLog("NifFile::getRegNif","Nif #"+UIntToString(modID)+"-"+UIntToString(nifID)+" found.");
			if ( RegList[modID][nifID]->root ) {
				dPrintAndLog("NifFile::getRegNif","Nif root is good.");
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
	dPrintAndLog("getRefNif","Finding nif with filename \""+filename+"\".");
	if ( RegListByFilename.find(filename) != RegListByFilename.end() ) {
		pair<UInt8, UInt32> nifIDs = *(RegListByFilename[filename]);
		return NifFile::getRegNif(nifIDs.first, nifIDs.second, nifPtr);
	}
	dPrintAndLog("NifFile::getRegNif","Filename not registered.");
	return false;
}
