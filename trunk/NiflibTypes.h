#pragma once

#include <exception>

#include "NifFile.h"
#include "Niflib.h"
#include "Type.h"

enum {
	kNiflibType_UNKNOWN = 0,
	kNiflibType_ATextureRenderData = 1,
	kNiflibType_AvoidNode,
	kNiflibType_bhkAabbPhantom,
	kNiflibType_bhkBlendCollisionObject,
	kNiflibType_bhkBlendController,
	kNiflibType_bhkBoxShape,
	kNiflibType_bhkBreakableConstraint,
	kNiflibType_bhkBvTreeShape,
	kNiflibType_bhkCapsuleShape,
	kNiflibType_bhkCollisionObject,
	kNiflibType_bhkConstraint,
	kNiflibType_bhkConvexListShape,
	kNiflibType_bhkConvexShape,
	kNiflibType_bhkConvexTransformShape,
	kNiflibType_bhkConvexVerticesShape,
	kNiflibType_bhkEntity,
	kNiflibType_bhkHingeConstraint,
	kNiflibType_bhkLimitedHingeConstraint,
	kNiflibType_bhkLiquidAction,
	kNiflibType_bhkListShape,
	kNiflibType_bhkMalleableConstraint,
	kNiflibType_bhkMoppBvTreeShape,
	kNiflibType_bhkMultiSphereShape,
	kNiflibType_bhkNiCollisionObject,
	kNiflibType_bhkNiTriStripsShape,
	kNiflibType_bhkOrientHingedBodyAction,
	kNiflibType_bhkPackedNiTriStripsShape,
	kNiflibType_bhkPCollisionObject,
	kNiflibType_bhkPhantom,
	kNiflibType_bhkPrismaticConstraint,
	kNiflibType_bhkRagdollConstraint,
	kNiflibType_bhkRefObject,
	kNiflibType_bhkRigidBody,
	kNiflibType_bhkRigidBodyT,
	kNiflibType_bhkSerializable,
	kNiflibType_bhkShape,
	kNiflibType_bhkShapeCollection,
	kNiflibType_bhkShapePhantom,
	kNiflibType_bhkSimpleShapePhantom,
	kNiflibType_bhkSPCollisionObject,
	kNiflibType_bhkSphereRepShape,
	kNiflibType_bhkSphereShape,
	kNiflibType_bhkStiffSpringConstraint,
	kNiflibType_bhkTransformShape,
	kNiflibType_bhkWorldObject,
	kNiflibType_BSAnimNotes,
	kNiflibType_BSBlastNode,
	kNiflibType_BSBound,
	kNiflibType_BSDamageStage,
	kNiflibType_BSDebrisNode,
	kNiflibType_BSDecalPlacementVectorExtraData,
	kNiflibType_BSDismemberSkinInstance,
	kNiflibType_BSDistantTreeShaderProperty,
	kNiflibType_BSFadeNode,
	kNiflibType_BSFrustumFOVController,
	kNiflibType_BSFurnitureMarker,
	kNiflibType_BSKeyframeController,
	kNiflibType_BSMasterParticleSystem,
	kNiflibType_BSMaterialEmittanceMultController,
	kNiflibType_BSMultiBound,
	kNiflibType_BSMultiBoundAABB,
	kNiflibType_BSMultiBoundData,
	kNiflibType_BSMultiBoundNode,
	kNiflibType_BSMultiBoundSphere,
	kNiflibType_BSOrderedNode,
	kNiflibType_BSParentVelocityModifier,
	kNiflibType_BSPSysArrayEmitter,
	kNiflibType_BSPSysMultiTargetEmitterCtlr,
	kNiflibType_BSPSysSimpleColorModifier,
	kNiflibType_BSPSysStripUpdateModifier,
	kNiflibType_BSRefractionFirePeriodController,
	kNiflibType_BSRefractionStrengthController,
	kNiflibType_BSSegmentedTriShape,
	kNiflibType_BSShaderLightingProperty,
	kNiflibType_BSShaderNoLightingProperty,
	kNiflibType_BSShaderPPLightingProperty,
	kNiflibType_BSShaderProperty,
	kNiflibType_BSShaderTextureSet,
	kNiflibType_BSStripParticleSystem,
	kNiflibType_BSStripPSysData,
	kNiflibType_BSTreadTransfInterpolator,
	kNiflibType_BSValueNode,
	kNiflibType_BSWArray,
	kNiflibType_BSWindModifier,
	kNiflibType_BSXFlags,
	kNiflibType_DistantLODShaderProperty,
	kNiflibType_FxButton,
	kNiflibType_FxRadioButton,
	kNiflibType_FxWidget,
	kNiflibType_HairShaderProperty,
	kNiflibType_hkPackedNiTriStripsData,
	kNiflibType_Lighting30ShaderProperty,
	kNiflibType_Ni3dsAlphaAnimator,
	kNiflibType_Ni3dsAnimationNode,
	kNiflibType_Ni3dsColorAnimator,
	kNiflibType_Ni3dsMorphShape,
	kNiflibType_Ni3dsParticleSystem,
	kNiflibType_Ni3dsPathController,
	kNiflibType_NiAdditionalGeometryData,
	kNiflibType_NiAlphaController,
	kNiflibType_NiAlphaProperty,
	kNiflibType_NiAmbientLight,
	kNiflibType_NiArkAnimationExtraData,
	kNiflibType_NiArkImporterExtraData,
	kNiflibType_NiArkShaderExtraData,
	kNiflibType_NiArkTextureExtraData,
	kNiflibType_NiArkViewportInfoExtraData,
	kNiflibType_NiAutoNormalParticles,
	kNiflibType_NiAutoNormalParticlesData,
	kNiflibType_NiAVObject,
	kNiflibType_NiAVObjectPalette,
	kNiflibType_NiBezierMesh,
	kNiflibType_NiBezierTriangle4,
	kNiflibType_NiBillboardNode,
	kNiflibType_NiBinaryExtraData,
	kNiflibType_NiBinaryVoxelData,
	kNiflibType_NiBinaryVoxelExtraData,
	kNiflibType_NiBlendBoolInterpolator,
	kNiflibType_NiBlendFloatInterpolator,
	kNiflibType_NiBlendInterpolator,
	kNiflibType_NiBlendPoint3Interpolator,
	kNiflibType_NiBlendTransformInterpolator,
	kNiflibType_NiBone,
	kNiflibType_NiBoneLODController,
	kNiflibType_NiBoolData,
	kNiflibType_NiBooleanExtraData,
	kNiflibType_NiBoolInterpController,
	kNiflibType_NiBoolInterpolator,
	kNiflibType_NiBoolTimelineInterpolator,
	kNiflibType_NiBSAnimationNode,
	kNiflibType_NiBSBoneLODController,
	kNiflibType_NiBSPArrayController,
	kNiflibType_NiBSParticleNode,
	kNiflibType_NiBSplineBasisData,
	kNiflibType_NiBSplineCompFloatInterpolator,
	kNiflibType_NiBSplineCompPoint3Interpolator,
	kNiflibType_NiBSplineCompTransformInterpolator,
	kNiflibType_NiBSplineData,
	kNiflibType_NiBSplineFloatInterpolator,
	kNiflibType_NiBSplineInterpolator,
	kNiflibType_NiBSplinePoint3Interpolator,
	kNiflibType_NiBSplineTransformInterpolator,
	kNiflibType_NiCamera,
	kNiflibType_NiClod,
	kNiflibType_NiClodData,
	kNiflibType_NiClodSkinInstance,
	kNiflibType_NiCollisionData,
	kNiflibType_NiCollisionObject,
	kNiflibType_NiColorData,
	kNiflibType_NiColorExtraData,
	kNiflibType_NiControllerManager,
	kNiflibType_NiControllerSequence,
	kNiflibType_NiDefaultAVObjectPalette,
	kNiflibType_NiDirectionalLight,
	kNiflibType_NiDitherProperty,
	kNiflibType_NiDynamicEffect,
	kNiflibType_NiEnvMappedTriShape,
	kNiflibType_NiEnvMappedTriShapeData,
	kNiflibType_NiExtraData,
	kNiflibType_NiExtraDataController,
	kNiflibType_NiFlipController,
	kNiflibType_NiFloatData,
	kNiflibType_NiFloatExtraData,
	kNiflibType_NiFloatExtraDataController,
	kNiflibType_NiFloatInterpController,
	kNiflibType_NiFloatInterpolator,
	kNiflibType_NiFloatsExtraData,
	kNiflibType_NiFogProperty,
	kNiflibType_NiGeometry,
	kNiflibType_NiGeometryData,
	kNiflibType_NiGeomMorpherController,
	kNiflibType_NiGravity,
	kNiflibType_NiImage,
	kNiflibType_NiIntegerExtraData,
	kNiflibType_NiIntegersExtraData,
	kNiflibType_NiInterpController,
	kNiflibType_NiInterpolator,
	kNiflibType_NiKeyBasedInterpolator,
	kNiflibType_NiKeyframeController,
	kNiflibType_NiKeyframeData,
	kNiflibType_NiLight,
	kNiflibType_NiLightColorController,
	kNiflibType_NiLightDimmerController,
	kNiflibType_NiLightIntensityController,
	kNiflibType_NiLines,
	kNiflibType_NiLinesData,
	kNiflibType_NiLODData,
	kNiflibType_NiLODNode,
	kNiflibType_NiLookAtController,
	kNiflibType_NiLookAtInterpolator,
	kNiflibType_NiMaterialColorController,
	kNiflibType_NiMaterialProperty,
	kNiflibType_NiMeshParticleSystem,
	kNiflibType_NiMeshPSysData,
	kNiflibType_NiMorphController,
	kNiflibType_NiMorphData,
	kNiflibType_NiMorpherController,
	kNiflibType_NiMultiTargetTransformController,
	kNiflibType_NiMultiTextureProperty,
	kNiflibType_NiNode,
	kNiflibType_NiObject,
	kNiflibType_NiObjectNET,
	kNiflibType_NiPalette,
	kNiflibType_NiParticleBomb,
	kNiflibType_NiParticleColorModifier,
	kNiflibType_NiParticleGrowFade,
	kNiflibType_NiParticleMeshes,
	kNiflibType_NiParticleMeshesData,
	kNiflibType_NiParticleMeshModifier,
	kNiflibType_NiParticleModifier,
	kNiflibType_NiParticleRotation,
	kNiflibType_NiParticles,
	kNiflibType_NiParticlesData,
	kNiflibType_NiParticleSystem,
	kNiflibType_NiParticleSystemController,
	kNiflibType_NiPathController,
	kNiflibType_NiPathInterpolator,
	kNiflibType_NiPersistentSrcTextureRendererData,
	kNiflibType_NiPhysXActorDesc,
	kNiflibType_NiPhysXBodyDesc,
	kNiflibType_NiPhysXD6JointDesc,
	kNiflibType_NiPhysXKinematicSrc,
	kNiflibType_NiPhysXMaterialDesc,
	kNiflibType_NiPhysXMeshDesc,
	kNiflibType_NiPhysXProp,
	kNiflibType_NiPhysXPropDesc,
	kNiflibType_NiPhysXShapeDesc,
	kNiflibType_NiPhysXTransformDest,
	kNiflibType_NiPixelData,
	kNiflibType_NiPlanarCollider,
	kNiflibType_NiPoint3InterpController,
	kNiflibType_NiPoint3Interpolator,
	kNiflibType_NiPointLight,
	kNiflibType_NiPortal,
	kNiflibType_NiPosData,
	kNiflibType_NiProperty,
	kNiflibType_NiPSysAgeDeathModifier,
	kNiflibType_NiPSysAirFieldModifier,
	kNiflibType_NiPSysBombModifier,
	kNiflibType_NiPSysBoundUpdateModifier,
	kNiflibType_NiPSysBoxEmitter,
	kNiflibType_NiPSysCollider,
	kNiflibType_NiPSysColliderManager,
	kNiflibType_NiPSysColorModifier,
	kNiflibType_NiPSysCylinderEmitter,
	kNiflibType_NiPSysData,
	kNiflibType_NiPSysDragFieldModifier,
	kNiflibType_NiPSysDragModifier,
	kNiflibType_NiPSysEmitter,
	kNiflibType_NiPSysEmitterCtlr,
	kNiflibType_NiPSysEmitterCtlrData,
	kNiflibType_NiPSysEmitterDeclinationCtlr,
	kNiflibType_NiPSysEmitterDeclinationVarCtlr,
	kNiflibType_NiPSysEmitterInitialRadiusCtlr,
	kNiflibType_NiPSysEmitterLifeSpanCtlr,
	kNiflibType_NiPSysEmitterSpeedCtlr,
	kNiflibType_NiPSysFieldMagnitudeCtlr,
	kNiflibType_NiPSysFieldModifier,
	kNiflibType_NiPSysGravityFieldModifier,
	kNiflibType_NiPSysGravityModifier,
	kNiflibType_NiPSysGravityStrengthCtlr,
	kNiflibType_NiPSysGrowFadeModifier,
	kNiflibType_NiPSysMeshEmitter,
	kNiflibType_NiPSysMeshUpdateModifier,
	kNiflibType_NiPSysModifier,
	kNiflibType_NiPSysModifierActiveCtlr,
	kNiflibType_NiPSysModifierBoolCtlr,
	kNiflibType_NiPSysModifierCtlr,
	kNiflibType_NiPSysModifierFloatCtlr,
	kNiflibType_NiPSysPlanarCollider,
	kNiflibType_NiPSysPositionModifier,
	kNiflibType_NiPSysResetOnLoopCtlr,
	kNiflibType_NiPSysRotationModifier,
	kNiflibType_NiPSysSpawnModifier,
	kNiflibType_NiPSysSphereEmitter,
	kNiflibType_NiPSysSphericalCollider,
	kNiflibType_NiPSysTrailEmitter,
	kNiflibType_NiPSysTurbulenceFieldModifier,
	kNiflibType_NiPSysUpdateCtlr,
	kNiflibType_NiPSysVolumeEmitter,
	kNiflibType_NiPSysVortexFieldModifier,
	kNiflibType_NiRangeLODData,
	kNiflibType_NiRawImageData,
	kNiflibType_NiRollController,
	kNiflibType_NiRoom,
	kNiflibType_NiRoomGroup,
	kNiflibType_NiRotatingParticles,
	kNiflibType_NiRotatingParticlesData,
	kNiflibType_NiScreenElements,
	kNiflibType_NiScreenElementsData,
	kNiflibType_NiScreenLODData,
	kNiflibType_NiSequence,
	kNiflibType_NiSequenceStreamHelper,
	kNiflibType_NiShadeProperty,
	kNiflibType_NiSingleInterpController,
	kNiflibType_NiSkinData,
	kNiflibType_NiSkinInstance,
	kNiflibType_NiSkinPartition,
	kNiflibType_NiSortAdjustNode,
	kNiflibType_NiSourceCubeMap,
	kNiflibType_NiSourceTexture,
	kNiflibType_NiSpecularProperty,
	kNiflibType_NiSphericalCollider,
	kNiflibType_NiSpotLight,
	kNiflibType_NiStencilProperty,
	kNiflibType_NiStringExtraData,
	kNiflibType_NiStringPalette,
	kNiflibType_NiStringsExtraData,
	kNiflibType_NiSwitchNode,
	kNiflibType_NiTextKeyExtraData,
	kNiflibType_NiTexture,
	kNiflibType_NiTextureEffect,
	kNiflibType_NiTextureModeProperty,
	kNiflibType_NiTextureProperty,
	kNiflibType_NiTextureTransformController,
	kNiflibType_NiTexturingProperty,
	kNiflibType_NiTimeController,
	kNiflibType_NiTransformController,
	kNiflibType_NiTransformData,
	kNiflibType_NiTransformInterpolator,
	kNiflibType_NiTransparentProperty,
	kNiflibType_NiTriBasedGeom,
	kNiflibType_NiTriBasedGeomData,
	kNiflibType_NiTriShape,
	kNiflibType_NiTriShapeData,
	kNiflibType_NiTriShapeSkinController,
	kNiflibType_NiTriStrips,
	kNiflibType_NiTriStripsData,
	kNiflibType_NiUVController,
	kNiflibType_NiUVData,
	kNiflibType_NiVectorExtraData,
	kNiflibType_NiVertexColorProperty,
	kNiflibType_NiVertWeightsExtraData,
	kNiflibType_NiVisController,
	kNiflibType_NiVisData,
	kNiflibType_NiWireframeProperty,
	kNiflibType_NiZBufferProperty,
	kNiflibType_RefObject,
	kNiflibType_RootCollisionNode,
	kNiflibType_SkyShaderProperty,
	kNiflibType_TallGrassShaderProperty,
	kNiflibType_TileShaderProperty,
	kNiflibType_VolumetricFogShaderProperty,
	kNiflibType_WaterShaderProperty,
};

UInt32 getNiflibTypeIndex(const Niflib::Type& type);
UInt32 getNiflibTypeIndex(const string& typeStr);
Niflib::Type getNiflibType(UInt32 typeIndex);
