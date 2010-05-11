#pragma once

#include "Utilities.h"

#include "niflib.h"
#include "obj\NiObject.h"
#include "obj\NiNode.h"
#include "obj\NiExtraData.h"
#include "obj\BSBound.h"
#include "obj\BSFurnitureMarker.h"
#include "obj\NiBinaryExtraData.h"
#include "obj\NiBinaryVoxelData.h"
#include "obj\NiBooleanExtraData.h"
#include "obj\NiColorExtraData.h"
#include "obj\NiFloatExtraData.h"
#include "obj\NiFloatsExtraData.h"
#include "obj\NiIntegerExtraData.h"
#include "obj\BSXFlags.h"
#include "obj\NiIntegersExtraData.h"
#include "obj\NiStringExtraData.h"
#include "obj\NiStringsExtraData.h"
#include "obj\NiTextKeyExtraData.h"
#include "obj\NiVectorExtraData.h"
#include "obj\NiVertWeightsExtraData.h"
#include "obj\NiAVObject.h"
#include "obj\NiMaterialProperty.h"
#include "obj\NiTextureProperty.h"
#include "obj\NiTexturingProperty.h"
#include "obj\NiSourceTexture.h"
#include "obj\NiImage.h"
#include "obj\NiCollisionObject.h"
#include "obj\bhkNiCollisionObject.h"
#include "obj\bhkRigidBodyT.h"
#include "obj\NiDynamicEffect.h"
//using Niflib::NiObject;
//using Niflib::NiNode;
//using Niflib::NiAVObject;

using Niflib::GetNifVersion;
using Niflib::Ref;
using Niflib::NiObjectRef;
using Niflib::NiNodeRef;
using Niflib::NifInfo;
//using Niflib::NiExtraData;
using Niflib::NiExtraDataRef;
using Niflib::NiStringExtraData;
using Niflib::NiStringExtraDataRef;
using Niflib::NiAVObjectRef;
using Niflib::NiCollisionObject;
using Niflib::bhkNiCollisionObject;
using Niflib::bhkNiCollisionObjectRef;
using Niflib::bhkRigidBodyT;
using Niflib::NiDynamicEffect;
using Niflib::DynamicCast;
using Niflib::StaticCast;
using Niflib::ReadNifTree;

class NifFile{
public:
	string filePath; // actual file for this modified Nif relative to Oblivion\Data\Meshes
	UInt32 loc;
	unsigned int nifVersion;

	bool editable;	 // whether or not the Nif is to be edited (and therefore needs a unique copy)
	string basePath; // file it is based on, also relative to Oblivion\Data\Meshes
	UInt32 baseLoc;

	UInt8 modID;
	SInt64 nifID;

	NiNodeRef root;  // in-memory understanding of the mesh
	NifInfo headerInfo;
	
	string extraDataChanges;
	string collisionChanges;
	string childrenChanges;
	string effectChanges;

	bhkNiCollisionObjectRef collision;

	std::list<Niflib::NiExtraDataRef>::iterator extraDataIt;
	vector<Niflib::NiAVObjectRef>::iterator childIt;
	vector<Niflib::NiDynamicEffectRef>::iterator effectIt;

	NifFile();
	NifFile(const string& file, UInt8 modIndex, UInt32 nifIndex, bool editable);
	NifFile(const string& file, UInt8 modIndex = 255, bool editable = false);
	NifFile(const NifFile&);
	~NifFile();
	SInt64 reg();												// defined in main.cpp to use RegList
	SInt64 reg(UInt8 modIndex, UInt32 nifIndex);				// defined in main.cpp to use RegList
	bool isreg();												// defined in main.cpp to use RegList
	void dereg();												// defined in main.cpp to use RegList
	string getAbsPath() const;
	string getAbsBasePath() const;
	string getVersion() const;
	NiExtraDataRef NifFile::findExtraData(std::list<Niflib::NiExtraDataRef>::size_type i) const;
	void setRoot(const string& newPath);
	void setRoot();
	Niflib::NiExtraDataRef getEDByName(string name);
	list<Niflib::NiExtraDataRef>::size_type getEDIndexByName(string name);
	Niflib::NiAVObjectRef getChildByName(string name);
	vector<Niflib::NiAVObjectRef>::size_type getChildIndexByName(string name);
	Niflib::NiDynamicEffectRef getEffectByName(string name);
	vector<Niflib::NiDynamicEffectRef>::size_type getEffectIndexByName(string name);
	void commitChanges();
	string getIDstring() const;
};

const char logNode = ':';
const char logNumber = '#';
const char logType = '-';
const char logAction = '=';
const char logValue = '\n';

void clearPrevChange(string &log, const UInt32 &Node, const UInt32 &Type, const UInt32 &Action);
void clearPrevChange(string &log, const string &Node, const UInt32 &Type, const UInt32 &Action);

string changeLog(UInt32 Node, UInt32 Type, UInt32 Action, string Value = "");
string changeLog(string Node, UInt32 Type, UInt32 Action, string Value = "");

enum {
	ED_ExtraData,
	ED_Bound,
	ED_Furniture,
	ED_Binary,
	ED_BinaryVoxel,
	ED_Boolean,
	ED_Color,
	ED_Float,
	ED_Floats,
	ED_Int,
	ED_BSXFlags,
	ED_Ints,
	ED_Str,
	ED_Strs,
	ED_TextKey,
	ED_Vector,
	ED_VertWeights,

	Co_bhkNiColObj = 100,
	Co_ColData,
	Co_bhkColObj,
	Co_bhkBlendColObj,
	Co_bhkPColObj,
	Co_bhkSPColObj,

	Ch_AVObj = 200,
	Ch_NiCam,
	Ch_NiGeom,
	Ch_NiParticles,
	Ch_NiAutoNormParticles,
	Ch_NiParticleMeshes,
	Ch_NiParticleSystem,
	Ch_NiMeshParticleSystem,
	Ch_NiRotParticles,
	Ch_NiTriBasedGeom,
	Ch_NiClod,
	Ch_NiTriShape,
	Ch_NiTriStrips,
	Ch_NiNode,
	Ch_AvoidNode,
	Ch_FxWidget,
	Ch_FxButton,
	Ch_FxRadioButton,
	Ch_NiBillboard,
	Ch_NiBone,
	Ch_NiBSAnim,
	Ch_NiBSParticle,
	Ch_NiSwitch,
	Ch_NiLOD,
	Ch_RootCol,

	Ef_Effect = 300,
	Ef_Light,
	Ef_AmbLight,
	Ef_DirLight,
	Ef_PntLight,
	Ef_SpotLight,
	Ef_TexEff,
	Ef_Remove,
};

enum {
	Act_Add = 1,
	Act_Remove,
	Act_SetName,

	Act_ED_SetValue = 50,

	Act_AV_ClearBoundingBox = 150,
	Act_AV_SetBoundingBox,
	Act_AV_ClearProps,
	Act_AV_SetFlags,
	Act_AV_SetLocTransform,
	Act_AV_SetLocTranslation,
	Act_AV_SetLocRotation,
	Act_AV_SetLocScale,
	Act_AV_SetVelocity,
	Act_AV_SetVisibility,
	Act_AV_SetColObj,
	Act_AV_SetColMode,

	Act_AV_PropMat_Add = 200,
	Act_AV_PropMat_Remove,
	Act_AV_PropMat_SetName,

	Act_AV_PropTex_Add = 250,
	Act_AV_PropTex_Remove,
	Act_AV_PropTex_SetBaseMap,
	Act_AV_PropTex_SetDarkMap,
	Act_AV_PropTex_SetDetailMap,
	Act_AV_PropTex_SetGlossMap,
	Act_AV_PropTex_SetGlowMap,
	Act_AV_PropTex_SetBumpMap,
	Act_AV_PropTex_SetDecal0Map,
	Act_AV_PropTex_SetDecal1Map,
};

bool getRegNif(UInt8 modID, UInt32 nifID, NifFile* &nifPtr);	// defined in main.cpp to use RegList
bool getRegNif(string filename, NifFile* &nifPtr);				// defined in main.cpp to use RegList