#include "NiflibTypes.h"

#include "obj/ATextureRenderData.h"
#include "obj/AvoidNode.h"
#include "obj/bhkAabbPhantom.h"
#include "obj/bhkBlendCollisionObject.h"
#include "obj/bhkBlendController.h"
#include "obj/bhkBoxShape.h"
#include "obj/bhkBreakableConstraint.h"
#include "obj/bhkBvTreeShape.h"
#include "obj/bhkCapsuleShape.h"
#include "obj/bhkCollisionObject.h"
#include "obj/bhkConstraint.h"
#include "obj/bhkConvexListShape.h"
#include "obj/bhkConvexShape.h"
#include "obj/bhkConvexTransformShape.h"
#include "obj/bhkConvexVerticesShape.h"
#include "obj/bhkEntity.h"
#include "obj/bhkHingeConstraint.h"
#include "obj/bhkLimitedHingeConstraint.h"
#include "obj/bhkLiquidAction.h"
#include "obj/bhkListShape.h"
#include "obj/bhkMalleableConstraint.h"
#include "obj/bhkMoppBvTreeShape.h"
#include "obj/bhkMultiSphereShape.h"
#include "obj/bhkNiCollisionObject.h"
#include "obj/bhkNiTriStripsShape.h"
#include "obj/bhkOrientHingedBodyAction.h"
#include "obj/bhkPackedNiTriStripsShape.h"
#include "obj/bhkPCollisionObject.h"
#include "obj/bhkPhantom.h"
#include "obj/bhkPrismaticConstraint.h"
#include "obj/bhkRagdollConstraint.h"
#include "obj/bhkRefObject.h"
#include "obj/bhkRigidBody.h"
#include "obj/bhkRigidBodyT.h"
#include "obj/bhkSerializable.h"
#include "obj/bhkShape.h"
#include "obj/bhkShapeCollection.h"
#include "obj/bhkShapePhantom.h"
#include "obj/bhkSimpleShapePhantom.h"
#include "obj/bhkSPCollisionObject.h"
#include "obj/bhkSphereRepShape.h"
#include "obj/bhkSphereShape.h"
#include "obj/bhkStiffSpringConstraint.h"
#include "obj/bhkTransformShape.h"
#include "obj/bhkWorldObject.h"
#include "obj/BSAnimNotes.h"
#include "obj/BSBlastNode.h"
#include "obj/BSBound.h"
#include "obj/BSDamageStage.h"
#include "obj/BSDebrisNode.h"
#include "obj/BSDecalPlacementVectorExtraData.h"
#include "obj/BSDismemberSkinInstance.h"
#include "obj/BSDistantTreeShaderProperty.h"
#include "obj/BSFadeNode.h"
#include "obj/BSFrustumFOVController.h"
#include "obj/BSFurnitureMarker.h"
#include "obj/BSKeyframeController.h"
#include "obj/BSMasterParticleSystem.h"
#include "obj/BSMaterialEmittanceMultController.h"
#include "obj/BSMultiBound.h"
#include "obj/BSMultiBoundAABB.h"
#include "obj/BSMultiBoundData.h"
#include "obj/BSMultiBoundNode.h"
#include "obj/BSMultiBoundSphere.h"
#include "obj/BSOrderedNode.h"
#include "obj/BSParentVelocityModifier.h"
#include "obj/BSPSysArrayEmitter.h"
#include "obj/BSPSysMultiTargetEmitterCtlr.h"
#include "obj/BSPSysSimpleColorModifier.h"
#include "obj/BSPSysStripUpdateModifier.h"
#include "obj/BSRefractionFirePeriodController.h"
#include "obj/BSRefractionStrengthController.h"
#include "obj/BSSegmentedTriShape.h"
#include "obj/BSShaderLightingProperty.h"
#include "obj/BSShaderNoLightingProperty.h"
#include "obj/BSShaderPPLightingProperty.h"
#include "obj/BSShaderProperty.h"
#include "obj/BSShaderTextureSet.h"
#include "obj/BSStripParticleSystem.h"
#include "obj/BSStripPSysData.h"
#include "obj/BSTreadTransfInterpolator.h"
#include "obj/BSValueNode.h"
#include "obj/BSWArray.h"
#include "obj/BSWindModifier.h"
#include "obj/BSXFlags.h"
#include "obj/DistantLODShaderProperty.h"
#include "obj/FxButton.h"
#include "obj/FxRadioButton.h"
#include "obj/FxWidget.h"
#include "obj/HairShaderProperty.h"
#include "obj/hkPackedNiTriStripsData.h"
#include "obj/Lighting30ShaderProperty.h"
#include "obj/Ni3dsAlphaAnimator.h"
#include "obj/Ni3dsAnimationNode.h"
#include "obj/Ni3dsColorAnimator.h"
#include "obj/Ni3dsMorphShape.h"
#include "obj/Ni3dsParticleSystem.h"
#include "obj/Ni3dsPathController.h"
#include "obj/NiAdditionalGeometryData.h"
#include "obj/NiAlphaController.h"
#include "obj/NiAlphaProperty.h"
#include "obj/NiAmbientLight.h"
#include "obj/NiArkAnimationExtraData.h"
#include "obj/NiArkImporterExtraData.h"
#include "obj/NiArkShaderExtraData.h"
#include "obj/NiArkTextureExtraData.h"
#include "obj/NiArkViewportInfoExtraData.h"
#include "obj/NiAutoNormalParticles.h"
#include "obj/NiAutoNormalParticlesData.h"
#include "obj/NiAVObject.h"
#include "obj/NiAVObjectPalette.h"
#include "obj/NiBezierMesh.h"
#include "obj/NiBezierTriangle4.h"
#include "obj/NiBillboardNode.h"
#include "obj/NiBinaryExtraData.h"
#include "obj/NiBinaryVoxelData.h"
#include "obj/NiBinaryVoxelExtraData.h"
#include "obj/NiBlendBoolInterpolator.h"
#include "obj/NiBlendFloatInterpolator.h"
#include "obj/NiBlendInterpolator.h"
#include "obj/NiBlendPoint3Interpolator.h"
#include "obj/NiBlendTransformInterpolator.h"
#include "obj/NiBone.h"
#include "obj/NiBoneLODController.h"
#include "obj/NiBoolData.h"
#include "obj/NiBooleanExtraData.h"
#include "obj/NiBoolInterpController.h"
#include "obj/NiBoolInterpolator.h"
#include "obj/NiBoolTimelineInterpolator.h"
#include "obj/NiBSAnimationNode.h"
#include "obj/NiBSBoneLODController.h"
#include "obj/NiBSPArrayController.h"
#include "obj/NiBSParticleNode.h"
#include "obj/NiBSplineBasisData.h"
#include "obj/NiBSplineCompFloatInterpolator.h"
#include "obj/NiBSplineCompPoint3Interpolator.h"
#include "obj/NiBSplineCompTransformInterpolator.h"
#include "obj/NiBSplineData.h"
#include "obj/NiBSplineFloatInterpolator.h"
#include "obj/NiBSplineInterpolator.h"
#include "obj/NiBSplinePoint3Interpolator.h"
#include "obj/NiBSplineTransformInterpolator.h"
#include "obj/NiCamera.h"
#include "obj/NiClod.h"
#include "obj/NiClodData.h"
#include "obj/NiClodSkinInstance.h"
#include "obj/NiCollisionData.h"
#include "obj/NiCollisionObject.h"
#include "obj/NiColorData.h"
#include "obj/NiColorExtraData.h"
#include "obj/NiControllerManager.h"
#include "obj/NiControllerSequence.h"
#include "obj/NiDefaultAVObjectPalette.h"
#include "obj/NiDirectionalLight.h"
#include "obj/NiDitherProperty.h"
#include "obj/NiDynamicEffect.h"
#include "obj/NiEnvMappedTriShape.h"
#include "obj/NiEnvMappedTriShapeData.h"
#include "obj/NiExtraData.h"
#include "obj/NiExtraDataController.h"
#include "obj/NiFlipController.h"
#include "obj/NiFloatData.h"
#include "obj/NiFloatExtraData.h"
#include "obj/NiFloatExtraDataController.h"
#include "obj/NiFloatInterpController.h"
#include "obj/NiFloatInterpolator.h"
#include "obj/NiFloatsExtraData.h"
#include "obj/NiFogProperty.h"
#include "obj/NiGeometry.h"
#include "obj/NiGeometryData.h"
#include "obj/NiGeomMorpherController.h"
#include "obj/NiGravity.h"
#include "obj/NiImage.h"
#include "obj/NiIntegerExtraData.h"
#include "obj/NiIntegersExtraData.h"
#include "obj/NiInterpController.h"
#include "obj/NiInterpolator.h"
#include "obj/NiKeyBasedInterpolator.h"
#include "obj/NiKeyframeController.h"
#include "obj/NiKeyframeData.h"
#include "obj/NiLight.h"
#include "obj/NiLightColorController.h"
#include "obj/NiLightDimmerController.h"
#include "obj/NiLightIntensityController.h"
#include "obj/NiLines.h"
#include "obj/NiLinesData.h"
#include "obj/NiLODData.h"
#include "obj/NiLODNode.h"
#include "obj/NiLookAtController.h"
#include "obj/NiLookAtInterpolator.h"
#include "obj/NiMaterialColorController.h"
#include "obj/NiMaterialProperty.h"
#include "obj/NiMeshParticleSystem.h"
#include "obj/NiMeshPSysData.h"
#include "obj/NiMorphController.h"
#include "obj/NiMorphData.h"
#include "obj/NiMorpherController.h"
#include "obj/NiMultiTargetTransformController.h"
#include "obj/NiMultiTextureProperty.h"
#include "obj/NiNode.h"
#include "obj/NiObject.h"
#include "obj/NiObjectNET.h"
#include "obj/NiPalette.h"
#include "obj/NiParticleBomb.h"
#include "obj/NiParticleColorModifier.h"
#include "obj/NiParticleGrowFade.h"
#include "obj/NiParticleMeshes.h"
#include "obj/NiParticleMeshesData.h"
#include "obj/NiParticleMeshModifier.h"
#include "obj/NiParticleModifier.h"
#include "obj/NiParticleRotation.h"
#include "obj/NiParticles.h"
#include "obj/NiParticlesData.h"
#include "obj/NiParticleSystem.h"
#include "obj/NiParticleSystemController.h"
#include "obj/NiPathController.h"
#include "obj/NiPathInterpolator.h"
#include "obj/NiPersistentSrcTextureRendererData.h"
#include "obj/NiPhysXActorDesc.h"
#include "obj/NiPhysXBodyDesc.h"
#include "obj/NiPhysXD6JointDesc.h"
#include "obj/NiPhysXKinematicSrc.h"
#include "obj/NiPhysXMaterialDesc.h"
#include "obj/NiPhysXMeshDesc.h"
#include "obj/NiPhysXProp.h"
#include "obj/NiPhysXPropDesc.h"
#include "obj/NiPhysXShapeDesc.h"
#include "obj/NiPhysXTransformDest.h"
#include "obj/NiPixelData.h"
#include "obj/NiPlanarCollider.h"
#include "obj/NiPoint3InterpController.h"
#include "obj/NiPoint3Interpolator.h"
#include "obj/NiPointLight.h"
#include "obj/NiPortal.h"
#include "obj/NiPosData.h"
#include "obj/NiProperty.h"
#include "obj/NiPSysAgeDeathModifier.h"
#include "obj/NiPSysAirFieldModifier.h"
#include "obj/NiPSysBombModifier.h"
#include "obj/NiPSysBoundUpdateModifier.h"
#include "obj/NiPSysBoxEmitter.h"
#include "obj/NiPSysCollider.h"
#include "obj/NiPSysColliderManager.h"
#include "obj/NiPSysColorModifier.h"
#include "obj/NiPSysCylinderEmitter.h"
#include "obj/NiPSysData.h"
#include "obj/NiPSysDragFieldModifier.h"
#include "obj/NiPSysDragModifier.h"
#include "obj/NiPSysEmitter.h"
#include "obj/NiPSysEmitterCtlr.h"
#include "obj/NiPSysEmitterCtlrData.h"
#include "obj/NiPSysEmitterDeclinationCtlr.h"
#include "obj/NiPSysEmitterDeclinationVarCtlr.h"
#include "obj/NiPSysEmitterInitialRadiusCtlr.h"
#include "obj/NiPSysEmitterLifeSpanCtlr.h"
#include "obj/NiPSysEmitterSpeedCtlr.h"
#include "obj/NiPSysFieldMagnitudeCtlr.h"
#include "obj/NiPSysFieldModifier.h"
#include "obj/NiPSysGravityFieldModifier.h"
#include "obj/NiPSysGravityModifier.h"
#include "obj/NiPSysGravityStrengthCtlr.h"
#include "obj/NiPSysGrowFadeModifier.h"
#include "obj/NiPSysMeshEmitter.h"
#include "obj/NiPSysMeshUpdateModifier.h"
#include "obj/NiPSysModifier.h"
#include "obj/NiPSysModifierActiveCtlr.h"
#include "obj/NiPSysModifierBoolCtlr.h"
#include "obj/NiPSysModifierCtlr.h"
#include "obj/NiPSysModifierFloatCtlr.h"
#include "obj/NiPSysPlanarCollider.h"
#include "obj/NiPSysPositionModifier.h"
#include "obj/NiPSysResetOnLoopCtlr.h"
#include "obj/NiPSysRotationModifier.h"
#include "obj/NiPSysSpawnModifier.h"
#include "obj/NiPSysSphereEmitter.h"
#include "obj/NiPSysSphericalCollider.h"
#include "obj/NiPSysTrailEmitter.h"
#include "obj/NiPSysTurbulenceFieldModifier.h"
#include "obj/NiPSysUpdateCtlr.h"
#include "obj/NiPSysVolumeEmitter.h"
#include "obj/NiPSysVortexFieldModifier.h"
#include "obj/NiRangeLODData.h"
#include "obj/NiRawImageData.h"
#include "obj/NiRollController.h"
#include "obj/NiRoom.h"
#include "obj/NiRoomGroup.h"
#include "obj/NiRotatingParticles.h"
#include "obj/NiRotatingParticlesData.h"
#include "obj/NiScreenElements.h"
#include "obj/NiScreenElementsData.h"
#include "obj/NiScreenLODData.h"
#include "obj/NiSequence.h"
#include "obj/NiSequenceStreamHelper.h"
#include "obj/NiShadeProperty.h"
#include "obj/NiSingleInterpController.h"
#include "obj/NiSkinData.h"
#include "obj/NiSkinInstance.h"
#include "obj/NiSkinPartition.h"
#include "obj/NiSortAdjustNode.h"
#include "obj/NiSourceCubeMap.h"
#include "obj/NiSourceTexture.h"
#include "obj/NiSpecularProperty.h"
#include "obj/NiSphericalCollider.h"
#include "obj/NiSpotLight.h"
#include "obj/NiStencilProperty.h"
#include "obj/NiStringExtraData.h"
#include "obj/NiStringPalette.h"
#include "obj/NiStringsExtraData.h"
#include "obj/NiSwitchNode.h"
#include "obj/NiTextKeyExtraData.h"
#include "obj/NiTexture.h"
#include "obj/NiTextureEffect.h"
#include "obj/NiTextureModeProperty.h"
#include "obj/NiTextureProperty.h"
#include "obj/NiTextureTransformController.h"
#include "obj/NiTexturingProperty.h"
#include "obj/NiTimeController.h"
#include "obj/NiTransformController.h"
#include "obj/NiTransformData.h"
#include "obj/NiTransformInterpolator.h"
#include "obj/NiTransparentProperty.h"
#include "obj/NiTriBasedGeom.h"
#include "obj/NiTriBasedGeomData.h"
#include "obj/NiTriShape.h"
#include "obj/NiTriShapeData.h"
#include "obj/NiTriShapeSkinController.h"
#include "obj/NiTriStrips.h"
#include "obj/NiTriStripsData.h"
#include "obj/NiUVController.h"
#include "obj/NiUVData.h"
#include "obj/NiVectorExtraData.h"
#include "obj/NiVertexColorProperty.h"
#include "obj/NiVertWeightsExtraData.h"
#include "obj/NiVisController.h"
#include "obj/NiVisData.h"
#include "obj/NiWireframeProperty.h"
#include "obj/NiZBufferProperty.h"
#include "RefObject.h"
#include "obj/RootCollisionNode.h"
#include "obj/SkyShaderProperty.h"
#include "obj/TallGrassShaderProperty.h"
#include "obj/TileShaderProperty.h"
#include "obj/VolumetricFogShaderProperty.h"
#include "obj/WaterShaderProperty.h"

UInt32 getNiflibTypeIndex(const Niflib::Type& type) {
	if ( type.IsSameType(Niflib::RefObject::TYPE) )
		return kNiflibType_RefObject;

	if ( type.IsSameType(Niflib::NiObject::TYPE) )
		return kNiflibType_NiObject;

	if ( type.IsDerivedType(Niflib::NiObjectNET::TYPE) )
		if ( type.IsSameType(Niflib::NiAVObject::TYPE) )
			return kNiflibType_NiAVObject;
		else if ( type.IsSameType(Niflib::NiEnvMappedTriShape::TYPE) )
			return kNiflibType_NiEnvMappedTriShape;
		else if ( type.IsSameType(Niflib::NiPhysXProp::TYPE) )
			return kNiflibType_NiPhysXProp;
		else if ( type.IsSameType(Niflib::NiProperty::TYPE) )
			return kNiflibType_NiProperty;
		else if ( type.IsSameType(Niflib::NiSequenceStreamHelper::TYPE) )
			return kNiflibType_NiSequenceStreamHelper;
		else if ( type.IsSameType(Niflib::NiTexture::TYPE) )
			return kNiflibType_NiTexture;
		else if ( type.IsSameType(Niflib::NiSourceTexture::TYPE) )
			return kNiflibType_NiSourceTexture;
		else if ( type.IsSameType(Niflib::NiSourceCubeMap::TYPE) )
			return kNiflibType_NiSourceCubeMap;
		else if ( type.IsDerivedType(Niflib::NiAVObject::TYPE) )
			if ( type.IsSameType(Niflib::NiBezierMesh::TYPE) )
				return kNiflibType_NiBezierMesh;
			else if ( type.IsSameType(Niflib::NiCamera::TYPE) )
				return kNiflibType_NiCamera;
			else if ( type.IsSameType(Niflib::NiDynamicEffect::TYPE) )
				return kNiflibType_NiDynamicEffect;
			else if ( type.IsSameType(Niflib::NiLight::TYPE) )
				return kNiflibType_NiLight;
			else if ( type.IsSameType(Niflib::NiTextureEffect::TYPE) )
				return kNiflibType_NiTextureEffect;
			else if ( type.IsSameType(Niflib::NiGeometry::TYPE) )
				return kNiflibType_NiGeometry;
			else if ( type.IsSameType(Niflib::NiParticles::TYPE) )
				return kNiflibType_NiParticles;
			else if ( type.IsSameType(Niflib::NiTriBasedGeom::TYPE) )
				return kNiflibType_NiTriBasedGeom;
			else if ( type.IsSameType(Niflib::NiNode::TYPE) )
				return kNiflibType_NiNode;
			else if ( type.IsSameType(Niflib::NiPortal::TYPE) )
				return kNiflibType_NiPortal;
			else if (type.IsDerivedType(Niflib::NiLight::TYPE) )
				if ( type.IsSameType(Niflib::NiAmbientLight::TYPE) )
					return kNiflibType_NiAmbientLight;
				else if ( type.IsSameType(Niflib::NiDirectionalLight::TYPE) )
					return kNiflibType_NiDirectionalLight;
				else if ( type.IsSameType(Niflib::NiPointLight::TYPE) )
					return kNiflibType_NiPointLight;
				else if ( type.IsSameType(Niflib::NiSpotLight::TYPE) )
					return kNiflibType_NiSpotLight;
				else
					return kNiflibType_NiLight;

			else if ( type.IsDerivedType(Niflib::NiParticles::TYPE) )
				if ( type.IsSameType(Niflib::NiAutoNormalParticles::TYPE) )
					return kNiflibType_NiAutoNormalParticles;
				else if ( type.IsSameType(Niflib::NiParticleMeshes::TYPE) )
					return kNiflibType_NiParticleMeshes;
				else if ( type.IsSameType(Niflib::NiParticleSystem::TYPE) )
					return kNiflibType_NiParticleSystem;
				else if ( type.IsSameType(Niflib::BSStripParticleSystem::TYPE) )
					return kNiflibType_BSStripParticleSystem;
				else if ( type.IsSameType(Niflib::NiMeshParticleSystem::TYPE) )
					return kNiflibType_NiMeshParticleSystem;
				else if ( type.IsSameType(Niflib::NiRotatingParticles::TYPE) )
					return kNiflibType_NiRotatingParticles;
				else
					return kNiflibType_NiParticles;

			else if ( type.IsDerivedType(Niflib::NiTriBasedGeom::TYPE) )
				if ( type.IsSameType(Niflib::NiClod::TYPE) )
					return kNiflibType_NiClod;
				else if ( type.IsSameType(Niflib::NiLines::TYPE) )
					return kNiflibType_NiLines;
				else if ( type.IsSameType(Niflib::NiTriShape::TYPE) )
					return kNiflibType_NiTriShape;
				else if ( type.IsSameType(Niflib::BSSegmentedTriShape::TYPE) )
					return kNiflibType_BSSegmentedTriShape;
				else if ( type.IsSameType(Niflib::NiScreenElements::TYPE) )
					return kNiflibType_NiScreenElements;
				else if ( type.IsSameType(Niflib::NiTriStrips::TYPE) )
					return kNiflibType_NiTriStrips;
				else
					return kNiflibType_NiTriBasedGeom;

			else if ( type.IsDerivedType(Niflib::NiNode::TYPE) )
				if ( type.IsSameType(Niflib::AvoidNode::TYPE) )
					return kNiflibType_AvoidNode;
				else if ( type.IsSameType(Niflib::BSBlastNode::TYPE) )
					return kNiflibType_BSBlastNode;
				else if ( type.IsSameType(Niflib::BSDamageStage::TYPE) )
					return kNiflibType_BSDamageStage;
				else if ( type.IsSameType(Niflib::BSDebrisNode::TYPE) )
					return kNiflibType_BSDebrisNode;
				else if ( type.IsSameType(Niflib::BSFadeNode::TYPE) )
					return kNiflibType_BSFadeNode;
				else if ( type.IsSameType(Niflib::BSMasterParticleSystem::TYPE) )
					return kNiflibType_BSMasterParticleSystem;
				else if ( type.IsSameType(Niflib::BSMultiBoundNode::TYPE) )
					return kNiflibType_BSMultiBoundNode;
				else if ( type.IsSameType(Niflib::BSOrderedNode::TYPE) )
					return kNiflibType_BSOrderedNode;
				else if ( type.IsSameType(Niflib::BSValueNode::TYPE) )
					return kNiflibType_BSValueNode;
				else if ( type.IsSameType(Niflib::FxWidget::TYPE) )
					return kNiflibType_FxWidget;
				else if ( type.IsSameType(Niflib::FxButton::TYPE) )
					return kNiflibType_FxButton;
				else if ( type.IsSameType(Niflib::FxRadioButton::TYPE) )
					return kNiflibType_FxRadioButton;
				else if ( type.IsSameType(Niflib::NiBillboardNode::TYPE) )
					return kNiflibType_NiBillboardNode;
				else if ( type.IsSameType(Niflib::NiBone::TYPE) )
					return kNiflibType_NiBone;
				else if ( type.IsSameType(Niflib::NiBSAnimationNode::TYPE) )
					return kNiflibType_NiBSAnimationNode;
				else if ( type.IsSameType(Niflib::NiBSParticleNode::TYPE) )
					return kNiflibType_NiBSParticleNode;
				else if ( type.IsSameType(Niflib::NiRoom::TYPE) )
					return kNiflibType_NiRoom;
				else if ( type.IsSameType(Niflib::NiRoomGroup::TYPE) )
					return kNiflibType_NiRoomGroup;
				else if ( type.IsSameType(Niflib::NiSortAdjustNode::TYPE) )
					return kNiflibType_NiSortAdjustNode;
				else if ( type.IsSameType(Niflib::NiSwitchNode::TYPE) )
					return kNiflibType_NiSwitchNode;
				else if ( type.IsSameType(Niflib::NiLODNode::TYPE) )
					return kNiflibType_NiLODNode;
				else if ( type.IsSameType(Niflib::RootCollisionNode::TYPE) )
					return kNiflibType_RootCollisionNode;
				else
					return kNiflibType_NiNode;
			else
				return kNiflibType_NiAVObject;

		else if ( type.IsDerivedType(Niflib::NiProperty::TYPE) )
			if ( type.IsSameType(Niflib::BSShaderProperty::TYPE) )
				return kNiflibType_BSShaderProperty;
			else if ( type.IsSameType(Niflib::NiAlphaProperty::TYPE) )
				return kNiflibType_NiAlphaProperty;
			else if ( type.IsSameType(Niflib::NiDitherProperty::TYPE) )
				return kNiflibType_NiDitherProperty;
			else if ( type.IsSameType(Niflib::NiFogProperty::TYPE) )
				return kNiflibType_NiFogProperty;
			else if ( type.IsSameType(Niflib::NiMaterialProperty::TYPE) )
				return kNiflibType_NiMaterialProperty;
			else if ( type.IsSameType(Niflib::NiMultiTextureProperty::TYPE) )
				return kNiflibType_NiMultiTextureProperty;
			else if ( type.IsSameType(Niflib::NiShadeProperty::TYPE) )
				return kNiflibType_NiShadeProperty;
			else if ( type.IsSameType(Niflib::NiSpecularProperty::TYPE) )
				return kNiflibType_NiSpecularProperty;
			else if ( type.IsSameType(Niflib::NiStencilProperty::TYPE) )
				return kNiflibType_NiStencilProperty;
			else if ( type.IsSameType(Niflib::NiTextureModeProperty::TYPE) )
				return kNiflibType_NiTextureModeProperty;
			else if ( type.IsSameType(Niflib::NiTextureProperty::TYPE) )
				return kNiflibType_NiTextureProperty;
			else if ( type.IsSameType(Niflib::NiTexturingProperty::TYPE) )
				return kNiflibType_NiTexturingProperty;
			else if ( type.IsSameType(Niflib::NiTransparentProperty::TYPE) )
				return kNiflibType_NiTransparentProperty;
			else if ( type.IsSameType(Niflib::NiVertexColorProperty::TYPE) )
				return kNiflibType_NiVertexColorProperty;
			else if ( type.IsSameType(Niflib::NiWireframeProperty::TYPE) )
				return kNiflibType_NiWireframeProperty;
			else if ( type.IsSameType(Niflib::NiZBufferProperty::TYPE) )
				return kNiflibType_NiZBufferProperty;
			else if ( type.IsDerivedType(Niflib::BSShaderProperty::TYPE) )
				if ( type.IsSameType(Niflib::BSDistantTreeShaderProperty::TYPE) )
					return kNiflibType_BSDistantTreeShaderProperty;
				else if ( type.IsSameType(Niflib::BSShaderLightingProperty::TYPE) )
					return kNiflibType_BSShaderLightingProperty;
				else if ( type.IsSameType(Niflib::DistantLODShaderProperty::TYPE) )
					return kNiflibType_DistantLODShaderProperty;
				else if ( type.IsSameType(Niflib::HairShaderProperty::TYPE) )
					return kNiflibType_HairShaderProperty;
				else if ( type.IsSameType(Niflib::SkyShaderProperty::TYPE) )
					return kNiflibType_SkyShaderProperty;
				else if ( type.IsSameType(Niflib::TallGrassShaderProperty::TYPE) )
					return kNiflibType_TallGrassShaderProperty;
				else if ( type.IsSameType(Niflib::VolumetricFogShaderProperty::TYPE) )
					return kNiflibType_VolumetricFogShaderProperty;
				else if ( type.IsSameType(Niflib::WaterShaderProperty::TYPE) )
					return kNiflibType_WaterShaderProperty;
				else if ( type.IsDerivedType(Niflib::BSShaderLightingProperty::TYPE) )
					if ( type.IsSameType(Niflib::BSShaderNoLightingProperty::TYPE) )
						return kNiflibType_BSShaderNoLightingProperty;
					else if ( type.IsSameType(Niflib::BSShaderPPLightingProperty::TYPE) )
						return kNiflibType_BSShaderPPLightingProperty;
					else if ( type.IsSameType(Niflib::Lighting30ShaderProperty::TYPE) )
						return kNiflibType_Lighting30ShaderProperty;
					else if ( type.IsSameType(Niflib::TileShaderProperty::TYPE) )
						return kNiflibType_TileShaderProperty;
					else
						return kNiflibType_BSShaderNoLightingProperty;
				else
					return kNiflibType_BSShaderProperty;
			else
				return kNiflibType_NiProperty;
		else
			return kNiflibType_NiObjectNET;

	else if ( type.IsDerivedType(Niflib::NiExtraData::TYPE) )
		if ( type.IsSameType(Niflib::BSBound::TYPE) )
			return kNiflibType_BSBound;
		else if ( type.IsSameType(Niflib::BSDecalPlacementVectorExtraData::TYPE) )
			return kNiflibType_BSDecalPlacementVectorExtraData;
		else if ( type.IsSameType(Niflib::BSFurnitureMarker::TYPE) )
			return kNiflibType_BSFurnitureMarker;
		else if ( type.IsSameType(Niflib::BSWArray::TYPE) )
			return kNiflibType_BSWArray;
		else if ( type.IsSameType(Niflib::NiArkAnimationExtraData::TYPE) )
			return kNiflibType_NiArkAnimationExtraData;
		else if ( type.IsSameType(Niflib::NiArkImporterExtraData::TYPE) )
			return kNiflibType_NiArkImporterExtraData;
		else if ( type.IsSameType(Niflib::NiArkShaderExtraData::TYPE) )
			return kNiflibType_NiArkShaderExtraData;
		else if ( type.IsSameType(Niflib::NiArkTextureExtraData::TYPE) )
			return kNiflibType_NiArkTextureExtraData;
		else if ( type.IsSameType(Niflib::NiArkViewportInfoExtraData::TYPE) )
			return kNiflibType_NiArkViewportInfoExtraData;
		else if ( type.IsSameType(Niflib::NiBinaryExtraData::TYPE) )
			return kNiflibType_NiBinaryExtraData;
		else if ( type.IsSameType(Niflib::NiBinaryVoxelExtraData::TYPE) )
			return kNiflibType_NiBinaryVoxelExtraData;
		else if ( type.IsSameType(Niflib::NiBooleanExtraData::TYPE) )
			return kNiflibType_NiBooleanExtraData;
		else if ( type.IsSameType(Niflib::NiColorExtraData::TYPE) )
			return kNiflibType_NiColorExtraData;
		else if ( type.IsSameType(Niflib::NiFloatExtraData::TYPE) )
			return kNiflibType_NiFloatExtraData;
		else if ( type.IsSameType(Niflib::NiFloatsExtraData::TYPE) )
			return kNiflibType_NiFloatsExtraData;
		else if ( type.IsSameType(Niflib::NiIntegerExtraData::TYPE) )
			return kNiflibType_NiIntegerExtraData;
		else if ( type.IsSameType(Niflib::BSXFlags::TYPE) )
			return kNiflibType_BSXFlags;
		else if ( type.IsSameType(Niflib::NiIntegersExtraData::TYPE) )
			return kNiflibType_NiIntegersExtraData;
		else if ( type.IsSameType(Niflib::NiStringExtraData::TYPE) )
			return kNiflibType_NiStringExtraData;
		else if ( type.IsSameType(Niflib::NiStringsExtraData::TYPE) )
			return kNiflibType_NiStringsExtraData;
		else if ( type.IsSameType(Niflib::NiTextKeyExtraData::TYPE) )
			return kNiflibType_NiTextKeyExtraData;
		else if ( type.IsSameType(Niflib::NiVectorExtraData::TYPE) )
			return kNiflibType_NiVectorExtraData;
		else if ( type.IsSameType(Niflib::NiVertWeightsExtraData::TYPE) )
			return kNiflibType_NiVertWeightsExtraData;
		else
			return kNiflibType_NiExtraData;

	if ( type.IsSameType(Niflib::ATextureRenderData::TYPE) )
		return kNiflibType_ATextureRenderData;
	else if ( type.IsSameType(Niflib::bhkRefObject::TYPE) )
		return kNiflibType_bhkRefObject;
	else if ( type.IsSameType(Niflib::BSAnimNotes::TYPE) )
		return kNiflibType_BSAnimNotes;
	else if ( type.IsSameType(Niflib::BSDismemberSkinInstance::TYPE) )
		return kNiflibType_BSDismemberSkinInstance;
	else if ( type.IsSameType(Niflib::BSMultiBound::TYPE) )
		return kNiflibType_BSMultiBound;
	else if ( type.IsSameType(Niflib::BSMultiBoundData::TYPE) )
		return kNiflibType_BSMultiBoundData;
	else if ( type.IsSameType(Niflib::BSMultiBoundAABB::TYPE) )
		return kNiflibType_BSMultiBoundAABB;
	else if ( type.IsSameType(Niflib::BSMultiBoundSphere::TYPE) )
		return kNiflibType_BSMultiBoundSphere;
	else if ( type.IsSameType(Niflib::BSShaderTextureSet::TYPE) )
		return kNiflibType_BSShaderTextureSet;
	else if ( type.IsSameType(Niflib::Ni3dsAlphaAnimator::TYPE) )
		return kNiflibType_Ni3dsAlphaAnimator;
	else if ( type.IsSameType(Niflib::Ni3dsAnimationNode::TYPE) )
		return kNiflibType_Ni3dsAnimationNode;
	else if ( type.IsSameType(Niflib::Ni3dsColorAnimator::TYPE) )
		return kNiflibType_Ni3dsColorAnimator;
	else if ( type.IsSameType(Niflib::Ni3dsMorphShape::TYPE) )
		return kNiflibType_Ni3dsMorphShape;
	else if ( type.IsSameType(Niflib::Ni3dsParticleSystem::TYPE) )
		return kNiflibType_Ni3dsParticleSystem;
	else if ( type.IsSameType(Niflib::Ni3dsPathController::TYPE) )
		return kNiflibType_Ni3dsPathController;
	else if ( type.IsSameType(Niflib::NiAdditionalGeometryData::TYPE) )
		return kNiflibType_NiAdditionalGeometryData;
	else if ( type.IsSameType(Niflib::NiAVObjectPalette::TYPE) )
		return kNiflibType_NiAVObjectPalette;
	else if ( type.IsSameType(Niflib::NiDefaultAVObjectPalette::TYPE) )
		return kNiflibType_NiDefaultAVObjectPalette;
	else if ( type.IsSameType(Niflib::NiBezierTriangle4::TYPE) )
		return kNiflibType_NiBezierTriangle4;
	else if ( type.IsSameType(Niflib::NiBinaryVoxelData::TYPE) )
		return kNiflibType_NiBinaryVoxelData;
	else if ( type.IsSameType(Niflib::NiBoolData::TYPE) )
		return kNiflibType_NiBoolData;
	else if ( type.IsSameType(Niflib::NiBSplineData::TYPE) )
		return kNiflibType_NiBSplineData;
	else if ( type.IsSameType(Niflib::NiClodSkinInstance::TYPE) )
		return kNiflibType_NiClodSkinInstance;
	else if ( type.IsSameType(Niflib::NiCollisionObject::TYPE) )
		return kNiflibType_NiCollisionObject;
	else if ( type.IsSameType(Niflib::NiColorData::TYPE) )
		return kNiflibType_NiColorData;
	else if ( type.IsSameType(Niflib::NiControllerSequence::TYPE) )
		return kNiflibType_NiControllerSequence;
	else if ( type.IsSameType(Niflib::NiExtraData::TYPE) )
		return kNiflibType_NiExtraData;
	else if ( type.IsSameType(Niflib::NiFloatData::TYPE) )
		return kNiflibType_NiFloatData;
	else if ( type.IsSameType(Niflib::NiGeometryData::TYPE) )
		return kNiflibType_NiGeometryData;
	else if ( type.IsSameType(Niflib::NiImage::TYPE) )
		return kNiflibType_NiImage;
	else if ( type.IsSameType(Niflib::NiInterpolator::TYPE) )
		return kNiflibType_NiInterpolator;
	else if ( type.IsSameType(Niflib::NiKeyframeData::TYPE) )
		return kNiflibType_NiKeyframeData;
	else if ( type.IsSameType(Niflib::NiLODData::TYPE) )
		return kNiflibType_NiLODData;
	else if ( type.IsSameType(Niflib::NiMorphData::TYPE) )
		return kNiflibType_NiMorphData;
	else if ( type.IsSameType(Niflib::NiObjectNET::TYPE) )
		return kNiflibType_NiObjectNET;
	else if ( type.IsSameType(Niflib::NiPalette::TYPE) )
		return kNiflibType_NiPalette;
	else if ( type.IsSameType(Niflib::NiParticleModifier::TYPE) )
		return kNiflibType_NiParticleModifier;
	else if ( type.IsSameType(Niflib::NiParticlesData::TYPE) )
		return kNiflibType_NiParticlesData;
	else if ( type.IsSameType(Niflib::NiPhysXActorDesc::TYPE) )
		return kNiflibType_NiPhysXActorDesc;
	else if ( type.IsSameType(Niflib::NiPhysXBodyDesc::TYPE) )
		return kNiflibType_NiPhysXBodyDesc;
	else if ( type.IsSameType(Niflib::NiPhysXD6JointDesc::TYPE) )
		return kNiflibType_NiPhysXD6JointDesc;
	else if ( type.IsSameType(Niflib::NiPhysXKinematicSrc::TYPE) )
		return kNiflibType_NiPhysXKinematicSrc;
	else if ( type.IsSameType(Niflib::NiPhysXMaterialDesc::TYPE) )
		return kNiflibType_NiPhysXMaterialDesc;
	else if ( type.IsSameType(Niflib::NiPhysXMeshDesc::TYPE) )
		return kNiflibType_NiPhysXMeshDesc;
	else if ( type.IsSameType(Niflib::NiPhysXPropDesc::TYPE) )
		return kNiflibType_NiPhysXPropDesc;
	else if ( type.IsSameType(Niflib::NiPhysXShapeDesc::TYPE) )
		return kNiflibType_NiPhysXShapeDesc;
	else if ( type.IsSameType(Niflib::NiPhysXTransformDest::TYPE) )
		return kNiflibType_NiPhysXTransformDest;
	else if ( type.IsSameType(Niflib::NiPersistentSrcTextureRendererData::TYPE) )
		return kNiflibType_NiPersistentSrcTextureRendererData;
	else if ( type.IsSameType(Niflib::NiPixelData::TYPE) )
		return kNiflibType_NiPixelData;
	else if ( type.IsSameType(Niflib::NiPosData::TYPE) )
		return kNiflibType_NiPosData;
	else if ( type.IsSameType(Niflib::NiPSysCollider::TYPE) )
		return kNiflibType_NiPSysCollider;
	else if ( type.IsSameType(Niflib::NiPSysEmitterCtlrData::TYPE) )
		return kNiflibType_NiPSysEmitterCtlrData;
	else if ( type.IsSameType(Niflib::NiPSysModifier::TYPE) )
		return kNiflibType_NiPSysModifier;
	else if ( type.IsSameType(Niflib::NiPSysPlanarCollider::TYPE) )
		return kNiflibType_NiPSysPlanarCollider;
	else if ( type.IsSameType(Niflib::NiPSysSphericalCollider::TYPE) )
		return kNiflibType_NiPSysSphericalCollider;
	else if ( type.IsSameType(Niflib::NiRangeLODData::TYPE) )
		return kNiflibType_NiRangeLODData;
	else if ( type.IsSameType(Niflib::NiRawImageData::TYPE) )
		return kNiflibType_NiRawImageData;
	else if ( type.IsSameType(Niflib::NiScreenLODData::TYPE) )
		return kNiflibType_NiScreenLODData;
	else if ( type.IsSameType(Niflib::NiSequence::TYPE) )
		return kNiflibType_NiSequence;
	else if ( type.IsSameType(Niflib::NiSkinData::TYPE) )
		return kNiflibType_NiSkinData;
	else if ( type.IsSameType(Niflib::NiSkinInstance::TYPE) )
		return kNiflibType_NiSkinInstance;
	else if ( type.IsSameType(Niflib::NiSkinPartition::TYPE) )
		return kNiflibType_NiSkinPartition;
	else if ( type.IsSameType(Niflib::NiStringPalette::TYPE) )
		return kNiflibType_NiStringPalette;
	else if ( type.IsSameType(Niflib::NiTimeController::TYPE) )
		return kNiflibType_NiTimeController;
	else if ( type.IsSameType(Niflib::NiTransformData::TYPE) )
		return kNiflibType_NiTransformData;
	else if ( type.IsSameType(Niflib::NiUVData::TYPE) )
		return kNiflibType_NiUVData;
	else if ( type.IsSameType(Niflib::NiVisData::TYPE) )
		return kNiflibType_NiVisData;

	if ( type.IsDerivedType(Niflib::bhkRefObject::TYPE) )
		if ( type.IsSameType(Niflib::bhkSerializable::TYPE) )
			return kNiflibType_bhkSerializable;
		else if ( type.IsSameType(Niflib::bhkConstraint::TYPE) )
			return kNiflibType_bhkConstraint;
		else if ( type.IsSameType(Niflib::bhkLiquidAction::TYPE) )
			return kNiflibType_bhkLiquidAction;
		else if ( type.IsSameType(Niflib::bhkOrientHingedBodyAction::TYPE) )
			return kNiflibType_bhkOrientHingedBodyAction;
		else if ( type.IsSameType(Niflib::bhkShape::TYPE) )
			return kNiflibType_bhkShape;
		else if ( type.IsSameType(Niflib::bhkWorldObject::TYPE) )
			return kNiflibType_bhkWorldObject;
		else if ( type.IsDerivedType(Niflib::bhkConstraint::TYPE) )
			if ( type.IsSameType(Niflib::bhkBreakableConstraint::TYPE) )
				return kNiflibType_bhkBreakableConstraint;
			else if ( type.IsSameType(Niflib::bhkHingeConstraint::TYPE) )
				return kNiflibType_bhkHingeConstraint;
			else if ( type.IsSameType(Niflib::bhkMalleableConstraint::TYPE) )
				return kNiflibType_bhkMalleableConstraint;
			else if ( type.IsSameType(Niflib::bhkPrismaticConstraint::TYPE) )
				return kNiflibType_bhkPrismaticConstraint;
			else if ( type.IsSameType(Niflib::bhkRagdollConstraint::TYPE) )
				return kNiflibType_bhkRagdollConstraint;
			else if ( type.IsSameType(Niflib::bhkStiffSpringConstraint::TYPE) )
				return kNiflibType_bhkStiffSpringConstraint;
			else
				return kNiflibType_bhkConstraint;

		else if ( type.IsDerivedType(Niflib::bhkShape::TYPE) )
			if ( type.IsSameType(Niflib::bhkBvTreeShape::TYPE) )
				return kNiflibType_bhkBvTreeShape;
			else if ( type.IsSameType(Niflib::bhkConvexListShape::TYPE) )
				return kNiflibType_bhkConvexListShape;
			else if ( type.IsSameType(Niflib::bhkShapeCollection::TYPE) )
				return kNiflibType_bhkShapeCollection;
			else if ( type.IsSameType(Niflib::bhkSphereRepShape::TYPE) )
				return kNiflibType_bhkSphereRepShape;
			else if ( type.IsSameType(Niflib::bhkTransformShape::TYPE) )
				return kNiflibType_bhkTransformShape;
			else if ( type.IsSameType(Niflib::bhkMoppBvTreeShape::TYPE) )
				return kNiflibType_bhkMoppBvTreeShape;
			else if ( type.IsSameType(Niflib::bhkConvexTransformShape::TYPE) )
				return kNiflibType_bhkConvexTransformShape;
			else if ( type.IsDerivedType(Niflib::bhkShapeCollection::TYPE) )
				if ( type.IsSameType(Niflib::bhkListShape::TYPE) )
					return kNiflibType_bhkListShape;
				else if ( type.IsSameType(Niflib::bhkNiTriStripsShape::TYPE) )
					return kNiflibType_bhkNiTriStripsShape;
				else if ( type.IsSameType(Niflib::bhkPackedNiTriStripsShape::TYPE) )
					return kNiflibType_bhkPackedNiTriStripsShape;
				else if ( type.IsSameType(Niflib::hkPackedNiTriStripsData::TYPE) )
					return kNiflibType_hkPackedNiTriStripsData;
				else
					return kNiflibType_bhkShapeCollection;

			else if ( type.IsDerivedType(Niflib::bhkSphereRepShape::TYPE) )
				if ( type.IsSameType(Niflib::bhkConvexShape::TYPE) )
					return kNiflibType_bhkConvexShape;
				else if ( type.IsSameType(Niflib::bhkMultiSphereShape::TYPE) )
					return kNiflibType_bhkMultiSphereShape;
				else if ( type.IsSameType(Niflib::bhkBoxShape::TYPE) )
					return kNiflibType_bhkBoxShape;
				else if ( type.IsSameType(Niflib::bhkCapsuleShape::TYPE) )
					return kNiflibType_bhkCapsuleShape;
				else if ( type.IsSameType(Niflib::bhkConvexVerticesShape::TYPE) )
					return kNiflibType_bhkConvexVerticesShape;
				else if ( type.IsSameType(Niflib::bhkSphereShape::TYPE) )
					return kNiflibType_bhkSphereShape;
				else
					return kNiflibType_bhkSphereRepShape;
			else
				return kNiflibType_bhkShape;

		else if ( type.IsDerivedType(Niflib::bhkWorldObject::TYPE) )
			if ( type.IsSameType(Niflib::bhkEntity::TYPE) )
				return kNiflibType_bhkEntity;
			else if ( type.IsSameType(Niflib::bhkPhantom::TYPE) )
				return kNiflibType_bhkPhantom;
			else if ( type.IsSameType(Niflib::bhkRigidBody::TYPE) )
				return kNiflibType_bhkRigidBody;
			else if ( type.IsSameType(Niflib::bhkRigidBodyT::TYPE) )
				return kNiflibType_bhkRigidBodyT;
			else if ( type.IsDerivedType(Niflib::bhkPhantom::TYPE) )
				if ( type.IsSameType(Niflib::bhkShapePhantom::TYPE) )
					return kNiflibType_bhkShapePhantom;
				else if ( type.IsSameType(Niflib::bhkAabbPhantom::TYPE) )
					return kNiflibType_bhkAabbPhantom;
				else if ( type.IsSameType(Niflib::bhkSimpleShapePhantom::TYPE) )
					return kNiflibType_bhkSimpleShapePhantom;
				else
					return kNiflibType_bhkPhantom;
			else
				return kNiflibType_bhkWorldObject;
		else
			return kNiflibType_bhkRefObject;

	else if ( type.IsDerivedType(Niflib::NiCollisionObject::TYPE) )
		if ( type.IsSameType(Niflib::bhkNiCollisionObject::TYPE) )
			return kNiflibType_bhkNiCollisionObject;
		else if ( type.IsSameType(Niflib::NiCollisionData::TYPE) )
			return kNiflibType_NiCollisionData;
		else if ( type.IsSameType(Niflib::bhkCollisionObject::TYPE) )
			return kNiflibType_bhkCollisionObject;
		else if ( type.IsSameType(Niflib::bhkPCollisionObject::TYPE) )
			return kNiflibType_bhkPCollisionObject;
		else if ( type.IsSameType(Niflib::bhkBlendCollisionObject::TYPE) )
			return kNiflibType_bhkBlendCollisionObject;
		else if ( type.IsSameType(Niflib::bhkSPCollisionObject::TYPE) )
			return kNiflibType_bhkSPCollisionObject;
		else
			return kNiflibType_NiCollisionObject;

	else if ( type.IsDerivedType(Niflib::NiGeometryData::TYPE) )
		if ( type.IsSameType(Niflib::NiLinesData::TYPE) )
			return kNiflibType_NiLinesData;
		else if ( type.IsSameType(Niflib::NiTriBasedGeomData::TYPE) )
			return kNiflibType_NiTriBasedGeomData;
		else if ( type.IsSameType(Niflib::NiClodData::TYPE) )
			return kNiflibType_NiClodData;
		else if ( type.IsSameType(Niflib::NiTriShapeData::TYPE) )
			return kNiflibType_NiTriShapeData;
		else if ( type.IsSameType(Niflib::NiTriStripsData::TYPE) )
			return kNiflibType_NiTriStripsData;
		else if ( type.IsSameType(Niflib::NiEnvMappedTriShapeData::TYPE) )
			return kNiflibType_NiEnvMappedTriShapeData;
		else if ( type.IsSameType(Niflib::NiScreenElementsData::TYPE) )
			return kNiflibType_NiScreenElementsData;
		else
			return kNiflibType_NiGeometryData;

	else if ( type.IsDerivedType(Niflib::NiParticleModifier::TYPE) )
		if ( type.IsSameType(Niflib::NiGravity::TYPE) )
			return kNiflibType_NiGravity;
		else if ( type.IsSameType(Niflib::NiParticleBomb::TYPE) )
			return kNiflibType_NiParticleBomb;
		else if ( type.IsSameType(Niflib::NiParticleColorModifier::TYPE) )
			return kNiflibType_NiParticleColorModifier;
		else if ( type.IsSameType(Niflib::NiParticleGrowFade::TYPE) )
			return kNiflibType_NiParticleGrowFade;
		else if ( type.IsSameType(Niflib::NiParticleMeshModifier::TYPE) )
			return kNiflibType_NiParticleMeshModifier;
		else if ( type.IsSameType(Niflib::NiParticleRotation::TYPE) )
			return kNiflibType_NiParticleRotation;
		else if ( type.IsSameType(Niflib::NiPlanarCollider::TYPE) )
			return kNiflibType_NiPlanarCollider;
		else if ( type.IsSameType(Niflib::NiSphericalCollider::TYPE) )
			return kNiflibType_NiSphericalCollider;
		else
			return kNiflibType_NiParticleModifier;

	else if ( type.IsDerivedType(Niflib::NiParticlesData::TYPE) )
		if ( type.IsSameType(Niflib::NiAutoNormalParticlesData::TYPE) )
			return kNiflibType_NiAutoNormalParticlesData;
		else if ( type.IsSameType(Niflib::NiRotatingParticlesData::TYPE) )
			return kNiflibType_NiRotatingParticlesData;
		else if ( type.IsSameType(Niflib::NiParticleMeshesData::TYPE) )
			return kNiflibType_NiParticleMeshesData;
		else if ( type.IsSameType(Niflib::NiPSysData::TYPE) )
			return kNiflibType_NiPSysData;
		else if ( type.IsSameType(Niflib::BSStripPSysData::TYPE) )
			return kNiflibType_BSStripPSysData;
		else if ( type.IsSameType(Niflib::NiMeshPSysData::TYPE) )
			return kNiflibType_NiMeshPSysData;
		else
			return kNiflibType_NiParticlesData;

	else if ( type.IsDerivedType(Niflib::NiInterpolator::TYPE) )
		return kNiflibType_NiInterpolator;

	else if ( type.IsDerivedType(Niflib::NiPSysModifier::TYPE) )
		return kNiflibType_NiPSysModifier;

	else if ( type.IsDerivedType(Niflib::NiTimeController::TYPE) )
		return kNiflibType_NiTimeController;

	return kNiflibType_UNKNOWN;
}

UInt32 getNiflibTypeIndex(const string& typeStr) {
	UInt32 offset = kNiflibType_UNKNOWN;
	UInt32 limit = kNiflibType_WaterShaderProperty;
	switch (typeStr[0]) {
		case 'a':
		case 'A':
			if ( typeStr[1] == 'T' )
				return kNiflibType_ATextureRenderData;
			else if ( typeStr[1] == 'v' )
				return kNiflibType_AvoidNode;
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'b':
		case 'B':
			if ( typeStr[1] == 'h' ) {
				offset = kNiflibType_bhkAabbPhantom;
				limit = kNiflibType_BSAnimNotes;
			}
			else if ( typeStr[1] == 'S' ) {
				offset = kNiflibType_BSAnimNotes;
				limit = kNiflibType_DistantLODShaderProperty;
			}
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'c':
		case 'C':
			return kNiflibType_UNKNOWN;
			break;

		case 'd':
		case 'D':
			return kNiflibType_DistantLODShaderProperty;
			break;

		case 'e':
		case 'E':
			return kNiflibType_UNKNOWN;
			break;

		case 'f':
		case 'F':
			if ( typeStr[2] == 'B' )
				return kNiflibType_FxButton;
			else if ( typeStr[2] == 'R' )
				return kNiflibType_FxRadioButton;
			else if ( typeStr[2] == 'W' )
				return kNiflibType_FxWidget;
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'g':
		case 'G':
			return kNiflibType_UNKNOWN;
			break;

		case 'h':
		case 'H':
			if ( typeStr[1] == 'a' )
				return kNiflibType_HairShaderProperty;
			else if ( typeStr[1] == 'k' )
				return kNiflibType_hkPackedNiTriStripsData;
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'i':
		case 'I':
		case 'j':
		case 'J':
		case 'k':
		case 'K':
			return kNiflibType_UNKNOWN;
			break;

		case 'l':
		case 'L':
			return kNiflibType_Lighting30ShaderProperty;
			break;

		case 'm':
		case 'M':
			return kNiflibType_UNKNOWN;
			break;

		case 'n':
		case 'N':
			if ( typeStr[1] == 'i' ) {
				switch (typeStr[2]) {
					case '3':
						offset = kNiflibType_Ni3dsAlphaAnimator;
						limit = kNiflibType_NiAdditionalGeometryData;
						break;

					case 'a':
					case 'A':
						offset = kNiflibType_NiAdditionalGeometryData;
						limit = kNiflibType_NiBezierMesh;
						break;

					case 'b':
					case 'B':
						offset = kNiflibType_NiBezierMesh;
						limit = kNiflibType_NiCamera;
						break;

					case 'c':
					case 'C':
						offset = kNiflibType_NiCamera;
						limit = kNiflibType_NiDefaultAVObjectPalette;
						break;

					case 'd':
					case 'D':
						offset = kNiflibType_NiDefaultAVObjectPalette;
						limit = kNiflibType_NiEnvMappedTriShape;
						break;

					case 'e':
					case 'E':
						offset = kNiflibType_NiEnvMappedTriShape;
						limit = kNiflibType_NiFlipController;
						break;

					case 'f':
					case 'F':
						offset = kNiflibType_NiFlipController;
						limit = kNiflibType_NiGeometry;
						break;

					case 'g':
					case 'G':
						offset = kNiflibType_NiGeometry;
						limit = kNiflibType_NiImage;
						break;

					case 'h':
					case 'H':
						return kNiflibType_UNKNOWN;
						break;

					case 'i':
					case 'I':
						offset = kNiflibType_NiImage;
						limit = kNiflibType_NiKeyBasedInterpolator;
						break;

					case 'j':
					case 'J':
						return kNiflibType_UNKNOWN;
						break;

					case 'k':
					case 'K':
						offset = kNiflibType_NiKeyBasedInterpolator;
						limit = kNiflibType_NiLight;
						break;

					case 'l':
					case 'L':
						offset = kNiflibType_NiLight;
						limit = kNiflibType_NiMaterialColorController;
						break;

					case 'm':
					case 'M':
						offset = kNiflibType_NiMaterialColorController;
						limit = kNiflibType_NiNode;
						break;

					case 'n':
					case 'N':
						return kNiflibType_NiNode;
						break;

					case 'o':
					case 'O':
						if ( typeStr.size() == 8 )
							return kNiflibType_NiObject;
						else if ( typeStr.size() == 11 )
							return kNiflibType_NiObjectNET;
						else
							return kNiflibType_UNKNOWN;
						break;

					case 'p':
					case 'P':
						offset = kNiflibType_NiPalette;
						limit = kNiflibType_NiRangeLODData;
						break;

					case 'q':
					case 'Q':
						return kNiflibType_UNKNOWN;
						break;

					case 'r':
					case 'R':
						offset = kNiflibType_NiRangeLODData;
						limit = kNiflibType_NiScreenElements;
						break;

					case 's':
					case 'S':
						offset = kNiflibType_NiScreenElements;
						limit = kNiflibType_NiTextKeyExtraData;
						break;

					case 't':
					case 'T':
						offset = kNiflibType_NiTextKeyExtraData;
						limit = kNiflibType_NiUVController;
						break;

					case 'u':
					case 'U':
						if ( typeStr[3] == 'V' )
							if ( typeStr[4] == 'C' )
								return kNiflibType_NiUVController;
							else if ( typeStr[4] == 'D' )
								return kNiflibType_NiUVData;
							else
								return kNiflibType_UNKNOWN;
						else
							return kNiflibType_UNKNOWN;
						break;

					case 'v':
					case 'V':
						offset = kNiflibType_NiVectorExtraData;
						limit = kNiflibType_NiWireframeProperty;
						break;

					case 'w':
					case 'W':
						return kNiflibType_NiWireframeProperty;
						break;

					case 'x':
					case 'X':
					case 'y':
					case 'Y':
						return kNiflibType_UNKNOWN;
						break;

					case 'z':
					case 'Z':
						return kNiflibType_NiZBufferProperty;
						break;

					default:
						return kNiflibType_UNKNOWN;
				}
			}
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'o':
		case 'O':
		case 'p':
		case 'P':
		case 'q':
		case 'Q':
			return kNiflibType_UNKNOWN;
			break;

		case 'r':
		case 'R':
			if ( typeStr[1] == 'e' )
				return kNiflibType_RefObject;
			else if ( typeStr[1] == 'o' )
				return kNiflibType_RootCollisionNode;
			else
				return kNiflibType_UNKNOWN;
			break;

		case 's':
		case 'S':
			return kNiflibType_SkyShaderProperty;
			break;

		case 't':
		case 'T':
			if ( typeStr[1] == 'a' )
				return kNiflibType_TallGrassShaderProperty;
			else if ( typeStr[1] == 'i' )
				return kNiflibType_TileShaderProperty;
			else
				return kNiflibType_UNKNOWN;
			break;

		case 'u':
		case 'U':
			return kNiflibType_UNKNOWN;
			break;

		case 'v':
		case 'V':
			return kNiflibType_VolumetricFogShaderProperty;
			break;

		case 'w':
		case 'W':
			return kNiflibType_WaterShaderProperty;
			break;

		case 'x':
		case 'X':
		case 'y':
		case 'Y':
		case 'z':
		case 'Z':
		default:
			return kNiflibType_UNKNOWN;
			break;
	}

	if ( offset > limit ) {
		UInt32 temp = offset;
		offset = limit;
		limit = temp;
	}
	else if ( offset == limit )
		return offset;

	Niflib::Type type = getNiflibType(offset);
	for ( UInt32 i = offset; i < limit; ++i ) {
		if ( i != offset )
			type = getNiflibType(i);
		if ( type.GetTypeName().compare(typeStr) == 0 )
			return i;
	}
	return kNiflibType_UNKNOWN;
}

Niflib::Type getNiflibType(UInt32 typeID) {
	switch (typeID) {
		case kNiflibType_ATextureRenderData:
			return Niflib::ATextureRenderData::TYPE;
		case kNiflibType_AvoidNode:
			return Niflib::AvoidNode::TYPE;
		case kNiflibType_bhkAabbPhantom:
			return Niflib::bhkAabbPhantom::TYPE;
		case kNiflibType_bhkBlendCollisionObject:
			return Niflib::bhkBlendCollisionObject::TYPE;
		case kNiflibType_bhkBlendController:
			return Niflib::bhkBlendController::TYPE;
		case kNiflibType_bhkBoxShape:
			return Niflib::bhkBoxShape::TYPE;
		case kNiflibType_bhkBreakableConstraint:
			return Niflib::bhkBreakableConstraint::TYPE;
		case kNiflibType_bhkBvTreeShape:
			return Niflib::bhkBvTreeShape::TYPE;
		case kNiflibType_bhkCapsuleShape:
			return Niflib::bhkCapsuleShape::TYPE;
		case kNiflibType_bhkCollisionObject:
			return Niflib::bhkCollisionObject::TYPE;
		case kNiflibType_bhkConstraint:
			return Niflib::bhkConstraint::TYPE;
		case kNiflibType_bhkConvexListShape:
			return Niflib::bhkConvexListShape::TYPE;
		case kNiflibType_bhkConvexShape:
			return Niflib::bhkConvexShape::TYPE;
		case kNiflibType_bhkConvexTransformShape:
			return Niflib::bhkConvexTransformShape::TYPE;
		case kNiflibType_bhkConvexVerticesShape:
			return Niflib::bhkConvexVerticesShape::TYPE;
		case kNiflibType_bhkEntity:
			return Niflib::bhkEntity::TYPE;
		case kNiflibType_bhkHingeConstraint:
			return Niflib::bhkHingeConstraint::TYPE;
		case kNiflibType_bhkLimitedHingeConstraint:
			return Niflib::bhkLimitedHingeConstraint::TYPE;
		case kNiflibType_bhkLiquidAction:
			return Niflib::bhkLiquidAction::TYPE;
		case kNiflibType_bhkListShape:
			return Niflib::bhkListShape::TYPE;
		case kNiflibType_bhkMalleableConstraint:
			return Niflib::bhkMalleableConstraint::TYPE;
		case kNiflibType_bhkMoppBvTreeShape:
			return Niflib::bhkMoppBvTreeShape::TYPE;
		case kNiflibType_bhkMultiSphereShape:
			return Niflib::bhkMultiSphereShape::TYPE;
		case kNiflibType_bhkNiCollisionObject:
			return Niflib::bhkNiCollisionObject::TYPE;
		case kNiflibType_bhkNiTriStripsShape:
			return Niflib::bhkNiTriStripsShape::TYPE;
		case kNiflibType_bhkOrientHingedBodyAction:
			return Niflib::bhkOrientHingedBodyAction::TYPE;
		case kNiflibType_bhkPackedNiTriStripsShape:
			return Niflib::bhkPackedNiTriStripsShape::TYPE;
		case kNiflibType_bhkPCollisionObject:
			return Niflib::bhkPCollisionObject::TYPE;
		case kNiflibType_bhkPhantom:
			return Niflib::bhkPhantom::TYPE;
		case kNiflibType_bhkPrismaticConstraint:
			return Niflib::bhkPrismaticConstraint::TYPE;
		case kNiflibType_bhkRagdollConstraint:
			return Niflib::bhkRagdollConstraint::TYPE;
		case kNiflibType_bhkRefObject:
			return Niflib::bhkRefObject::TYPE;
		case kNiflibType_bhkRigidBody:
			return Niflib::bhkRigidBody::TYPE;
		case kNiflibType_bhkRigidBodyT:
			return Niflib::bhkRigidBodyT::TYPE;
		case kNiflibType_bhkSerializable:
			return Niflib::bhkSerializable::TYPE;
		case kNiflibType_bhkShape:
			return Niflib::bhkShape::TYPE;
		case kNiflibType_bhkShapeCollection:
			return Niflib::bhkShapeCollection::TYPE;
		case kNiflibType_bhkShapePhantom:
			return Niflib::bhkShapePhantom::TYPE;
		case kNiflibType_bhkSimpleShapePhantom:
			return Niflib::bhkSimpleShapePhantom::TYPE;
		case kNiflibType_bhkSPCollisionObject:
			return Niflib::bhkSPCollisionObject::TYPE;
		case kNiflibType_bhkSphereRepShape:
			return Niflib::bhkSphereRepShape::TYPE;
		case kNiflibType_bhkSphereShape:
			return Niflib::bhkSphereShape::TYPE;
		case kNiflibType_bhkStiffSpringConstraint:
			return Niflib::bhkStiffSpringConstraint::TYPE;
		case kNiflibType_bhkTransformShape:
			return Niflib::bhkTransformShape::TYPE;
		case kNiflibType_bhkWorldObject:
			return Niflib::bhkWorldObject::TYPE;
		case kNiflibType_BSAnimNotes:
			return Niflib::BSAnimNotes::TYPE;
		case kNiflibType_BSBlastNode:
			return Niflib::BSBlastNode::TYPE;
		case kNiflibType_BSBound:
			return Niflib::BSBound::TYPE;
		case kNiflibType_BSDamageStage:
			return Niflib::BSDamageStage::TYPE;
		case kNiflibType_BSDebrisNode:
			return Niflib::BSDebrisNode::TYPE;
		case kNiflibType_BSDecalPlacementVectorExtraData:
			return Niflib::BSDecalPlacementVectorExtraData::TYPE;
		case kNiflibType_BSDismemberSkinInstance:
			return Niflib::BSDismemberSkinInstance::TYPE;
		case kNiflibType_BSDistantTreeShaderProperty:
			return Niflib::BSDistantTreeShaderProperty::TYPE;
		case kNiflibType_BSFadeNode:
			return Niflib::BSFadeNode::TYPE;
		case kNiflibType_BSFrustumFOVController:
			return Niflib::BSFrustumFOVController::TYPE;
		case kNiflibType_BSFurnitureMarker:
			return Niflib::BSFurnitureMarker::TYPE;
		case kNiflibType_BSKeyframeController:
			return Niflib::BSKeyframeController::TYPE;
		case kNiflibType_BSMasterParticleSystem:
			return Niflib::BSMasterParticleSystem::TYPE;
		case kNiflibType_BSMaterialEmittanceMultController:
			return Niflib::BSMaterialEmittanceMultController::TYPE;
		case kNiflibType_BSMultiBound:
			return Niflib::BSMultiBound::TYPE;
		case kNiflibType_BSMultiBoundAABB:
			return Niflib::BSMultiBoundAABB::TYPE;
		case kNiflibType_BSMultiBoundData:
			return Niflib::BSMultiBoundData::TYPE;
		case kNiflibType_BSMultiBoundNode:
			return Niflib::BSMultiBoundNode::TYPE;
		case kNiflibType_BSMultiBoundSphere:
			return Niflib::BSMultiBoundSphere::TYPE;
		case kNiflibType_BSOrderedNode:
			return Niflib::BSOrderedNode::TYPE;
		case kNiflibType_BSParentVelocityModifier:
			return Niflib::BSParentVelocityModifier::TYPE;
		case kNiflibType_BSPSysArrayEmitter:
			return Niflib::BSPSysArrayEmitter::TYPE;
		case kNiflibType_BSPSysMultiTargetEmitterCtlr:
			return Niflib::BSPSysMultiTargetEmitterCtlr::TYPE;
		case kNiflibType_BSPSysSimpleColorModifier:
			return Niflib::BSPSysSimpleColorModifier::TYPE;
		case kNiflibType_BSPSysStripUpdateModifier:
			return Niflib::BSPSysStripUpdateModifier::TYPE;
		case kNiflibType_BSRefractionFirePeriodController:
			return Niflib::BSRefractionFirePeriodController::TYPE;
		case kNiflibType_BSRefractionStrengthController:
			return Niflib::BSRefractionStrengthController::TYPE;
		case kNiflibType_BSSegmentedTriShape:
			return Niflib::BSSegmentedTriShape::TYPE;
		case kNiflibType_BSShaderLightingProperty:
			return Niflib::BSShaderLightingProperty::TYPE;
		case kNiflibType_BSShaderNoLightingProperty:
			return Niflib::BSShaderNoLightingProperty::TYPE;
		case kNiflibType_BSShaderPPLightingProperty:
			return Niflib::BSShaderPPLightingProperty::TYPE;
		case kNiflibType_BSShaderProperty:
			return Niflib::BSShaderProperty::TYPE;
		case kNiflibType_BSShaderTextureSet:
			return Niflib::BSShaderTextureSet::TYPE;
		case kNiflibType_BSStripParticleSystem:
			return Niflib::BSStripParticleSystem::TYPE;
		case kNiflibType_BSStripPSysData:
			return Niflib::BSStripPSysData::TYPE;
		case kNiflibType_BSTreadTransfInterpolator:
			return Niflib::BSTreadTransfInterpolator::TYPE;
		case kNiflibType_BSValueNode:
			return Niflib::BSValueNode::TYPE;
		case kNiflibType_BSWArray:
			return Niflib::BSWArray::TYPE;
		case kNiflibType_BSWindModifier:
			return Niflib::BSWindModifier::TYPE;
		case kNiflibType_BSXFlags:
			return Niflib::BSXFlags::TYPE;
		case kNiflibType_DistantLODShaderProperty:
			return Niflib::DistantLODShaderProperty::TYPE;
		case kNiflibType_FxButton:
			return Niflib::FxButton::TYPE;
		case kNiflibType_FxRadioButton:
			return Niflib::FxRadioButton::TYPE;
		case kNiflibType_FxWidget:
			return Niflib::FxWidget::TYPE;
		case kNiflibType_HairShaderProperty:
			return Niflib::HairShaderProperty::TYPE;
		case kNiflibType_hkPackedNiTriStripsData:
			return Niflib::hkPackedNiTriStripsData::TYPE;
		case kNiflibType_Lighting30ShaderProperty:
			return Niflib::Lighting30ShaderProperty::TYPE;
		case kNiflibType_Ni3dsAlphaAnimator:
			return Niflib::Ni3dsAlphaAnimator::TYPE;
		case kNiflibType_Ni3dsAnimationNode:
			return Niflib::Ni3dsAnimationNode::TYPE;
		case kNiflibType_Ni3dsColorAnimator:
			return Niflib::Ni3dsColorAnimator::TYPE;
		case kNiflibType_Ni3dsMorphShape:
			return Niflib::Ni3dsMorphShape::TYPE;
		case kNiflibType_Ni3dsParticleSystem:
			return Niflib::Ni3dsParticleSystem::TYPE;
		case kNiflibType_Ni3dsPathController:
			return Niflib::Ni3dsPathController::TYPE;
		case kNiflibType_NiAdditionalGeometryData:
			return Niflib::NiAdditionalGeometryData::TYPE;
		case kNiflibType_NiAlphaController:
			return Niflib::NiAlphaController::TYPE;
		case kNiflibType_NiAlphaProperty:
			return Niflib::NiAlphaProperty::TYPE;
		case kNiflibType_NiAmbientLight:
			return Niflib::NiAmbientLight::TYPE;
		case kNiflibType_NiArkAnimationExtraData:
			return Niflib::NiArkAnimationExtraData::TYPE;
		case kNiflibType_NiArkImporterExtraData:
			return Niflib::NiArkImporterExtraData::TYPE;
		case kNiflibType_NiArkShaderExtraData:
			return Niflib::NiArkShaderExtraData::TYPE;
		case kNiflibType_NiArkTextureExtraData:
			return Niflib::NiArkTextureExtraData::TYPE;
		case kNiflibType_NiArkViewportInfoExtraData:
			return Niflib::NiArkViewportInfoExtraData::TYPE;
		case kNiflibType_NiAutoNormalParticles:
			return Niflib::NiAutoNormalParticles::TYPE;
		case kNiflibType_NiAutoNormalParticlesData:
			return Niflib::NiAutoNormalParticlesData::TYPE;
		case kNiflibType_NiAVObject:
			return Niflib::NiAVObject::TYPE;
		case kNiflibType_NiAVObjectPalette:
			return Niflib::NiAVObjectPalette::TYPE;
		case kNiflibType_NiBezierMesh:
			return Niflib::NiBezierMesh::TYPE;
		case kNiflibType_NiBezierTriangle4:
			return Niflib::NiBezierTriangle4::TYPE;
		case kNiflibType_NiBillboardNode:
			return Niflib::NiBillboardNode::TYPE;
		case kNiflibType_NiBinaryExtraData:
			return Niflib::NiBinaryExtraData::TYPE;
		case kNiflibType_NiBinaryVoxelData:
			return Niflib::NiBinaryVoxelData::TYPE;
		case kNiflibType_NiBinaryVoxelExtraData:
			return Niflib::NiBinaryVoxelExtraData::TYPE;
		case kNiflibType_NiBlendBoolInterpolator:
			return Niflib::NiBlendBoolInterpolator::TYPE;
		case kNiflibType_NiBlendFloatInterpolator:
			return Niflib::NiBlendFloatInterpolator::TYPE;
		case kNiflibType_NiBlendInterpolator:
			return Niflib::NiBlendInterpolator::TYPE;
		case kNiflibType_NiBlendPoint3Interpolator:
			return Niflib::NiBlendPoint3Interpolator::TYPE;
		case kNiflibType_NiBlendTransformInterpolator:
			return Niflib::NiBlendTransformInterpolator::TYPE;
		case kNiflibType_NiBone:
			return Niflib::NiBone::TYPE;
		case kNiflibType_NiBoneLODController:
			return Niflib::NiBoneLODController::TYPE;
		case kNiflibType_NiBoolData:
			return Niflib::NiBoolData::TYPE;
		case kNiflibType_NiBooleanExtraData:
			return Niflib::NiBooleanExtraData::TYPE;
		case kNiflibType_NiBoolInterpController:
			return Niflib::NiBoolInterpController::TYPE;
		case kNiflibType_NiBoolInterpolator:
			return Niflib::NiBoolInterpolator::TYPE;
		case kNiflibType_NiBoolTimelineInterpolator:
			return Niflib::NiBoolTimelineInterpolator::TYPE;
		case kNiflibType_NiBSAnimationNode:
			return Niflib::NiBSAnimationNode::TYPE;
		case kNiflibType_NiBSBoneLODController:
			return Niflib::NiBSBoneLODController::TYPE;
		case kNiflibType_NiBSPArrayController:
			return Niflib::NiBSPArrayController::TYPE;
		case kNiflibType_NiBSParticleNode:
			return Niflib::NiBSParticleNode::TYPE;
		case kNiflibType_NiBSplineBasisData:
			return Niflib::NiBSplineBasisData::TYPE;
		case kNiflibType_NiBSplineCompFloatInterpolator:
			return Niflib::NiBSplineCompFloatInterpolator::TYPE;
		case kNiflibType_NiBSplineCompPoint3Interpolator:
			return Niflib::NiBSplineCompPoint3Interpolator::TYPE;
		case kNiflibType_NiBSplineCompTransformInterpolator:
			return Niflib::NiBSplineCompTransformInterpolator::TYPE;
		case kNiflibType_NiBSplineData:
			return Niflib::NiBSplineData::TYPE;
		case kNiflibType_NiBSplineFloatInterpolator:
			return Niflib::NiBSplineFloatInterpolator::TYPE;
		case kNiflibType_NiBSplineInterpolator:
			return Niflib::NiBSplineInterpolator::TYPE;
		case kNiflibType_NiBSplinePoint3Interpolator:
			return Niflib::NiBSplinePoint3Interpolator::TYPE;
		case kNiflibType_NiBSplineTransformInterpolator:
			return Niflib::NiBSplineTransformInterpolator::TYPE;
		case kNiflibType_NiCamera:
			return Niflib::NiCamera::TYPE;
		case kNiflibType_NiClod:
			return Niflib::NiClod::TYPE;
		case kNiflibType_NiClodData:
			return Niflib::NiClodData::TYPE;
		case kNiflibType_NiClodSkinInstance:
			return Niflib::NiClodSkinInstance::TYPE;
		case kNiflibType_NiCollisionData:
			return Niflib::NiCollisionData::TYPE;
		case kNiflibType_NiCollisionObject:
			return Niflib::NiCollisionObject::TYPE;
		case kNiflibType_NiColorData:
			return Niflib::NiColorData::TYPE;
		case kNiflibType_NiColorExtraData:
			return Niflib::NiColorExtraData::TYPE;
		case kNiflibType_NiControllerManager:
			return Niflib::NiControllerManager::TYPE;
		case kNiflibType_NiControllerSequence:
			return Niflib::NiControllerSequence::TYPE;
		case kNiflibType_NiDefaultAVObjectPalette:
			return Niflib::NiDefaultAVObjectPalette::TYPE;
		case kNiflibType_NiDirectionalLight:
			return Niflib::NiDirectionalLight::TYPE;
		case kNiflibType_NiDitherProperty:
			return Niflib::NiDitherProperty::TYPE;
		case kNiflibType_NiDynamicEffect:
			return Niflib::NiDynamicEffect::TYPE;
		case kNiflibType_NiEnvMappedTriShape:
			return Niflib::NiEnvMappedTriShape::TYPE;
		case kNiflibType_NiEnvMappedTriShapeData:
			return Niflib::NiEnvMappedTriShapeData::TYPE;
		case kNiflibType_NiExtraData:
			return Niflib::NiExtraData::TYPE;
		case kNiflibType_NiExtraDataController:
			return Niflib::NiExtraDataController::TYPE;
		case kNiflibType_NiFlipController:
			return Niflib::NiFlipController::TYPE;
		case kNiflibType_NiFloatData:
			return Niflib::NiFloatData::TYPE;
		case kNiflibType_NiFloatExtraData:
			return Niflib::NiFloatExtraData::TYPE;
		case kNiflibType_NiFloatExtraDataController:
			return Niflib::NiFloatExtraDataController::TYPE;
		case kNiflibType_NiFloatInterpController:
			return Niflib::NiFloatInterpController::TYPE;
		case kNiflibType_NiFloatInterpolator:
			return Niflib::NiFloatInterpolator::TYPE;
		case kNiflibType_NiFloatsExtraData:
			return Niflib::NiFloatsExtraData::TYPE;
		case kNiflibType_NiFogProperty:
			return Niflib::NiFogProperty::TYPE;
		case kNiflibType_NiGeometry:
			return Niflib::NiGeometry::TYPE;
		case kNiflibType_NiGeometryData:
			return Niflib::NiGeometryData::TYPE;
		case kNiflibType_NiGeomMorpherController:
			return Niflib::NiGeomMorpherController::TYPE;
		case kNiflibType_NiGravity:
			return Niflib::NiGravity::TYPE;
		case kNiflibType_NiImage:
			return Niflib::NiImage::TYPE;
		case kNiflibType_NiIntegerExtraData:
			return Niflib::NiIntegerExtraData::TYPE;
		case kNiflibType_NiIntegersExtraData:
			return Niflib::NiIntegersExtraData::TYPE;
		case kNiflibType_NiInterpController:
			return Niflib::NiInterpController::TYPE;
		case kNiflibType_NiInterpolator:
			return Niflib::NiInterpolator::TYPE;
		case kNiflibType_NiKeyBasedInterpolator:
			return Niflib::NiKeyBasedInterpolator::TYPE;
		case kNiflibType_NiKeyframeController:
			return Niflib::NiKeyframeController::TYPE;
		case kNiflibType_NiKeyframeData:
			return Niflib::NiKeyframeData::TYPE;
		case kNiflibType_NiLight:
			return Niflib::NiLight::TYPE;
		case kNiflibType_NiLightColorController:
			return Niflib::NiLightColorController::TYPE;
		case kNiflibType_NiLightDimmerController:
			return Niflib::NiLightDimmerController::TYPE;
		case kNiflibType_NiLightIntensityController:
			return Niflib::NiLightIntensityController::TYPE;
		case kNiflibType_NiLines:
			return Niflib::NiLines::TYPE;
		case kNiflibType_NiLinesData:
			return Niflib::NiLinesData::TYPE;
		case kNiflibType_NiLODData:
			return Niflib::NiLODData::TYPE;
		case kNiflibType_NiLODNode:
			return Niflib::NiLODNode::TYPE;
		case kNiflibType_NiLookAtController:
			return Niflib::NiLookAtController::TYPE;
		case kNiflibType_NiLookAtInterpolator:
			return Niflib::NiLookAtInterpolator::TYPE;
		case kNiflibType_NiMaterialColorController:
			return Niflib::NiMaterialColorController::TYPE;
		case kNiflibType_NiMaterialProperty:
			return Niflib::NiMaterialProperty::TYPE;
		case kNiflibType_NiMeshParticleSystem:
			return Niflib::NiMeshParticleSystem::TYPE;
		case kNiflibType_NiMeshPSysData:
			return Niflib::NiMeshPSysData::TYPE;
		case kNiflibType_NiMorphController:
			return Niflib::NiMorphController::TYPE;
		case kNiflibType_NiMorphData:
			return Niflib::NiMorphData::TYPE;
		case kNiflibType_NiMorpherController:
			return Niflib::NiMorpherController::TYPE;
		case kNiflibType_NiMultiTargetTransformController:
			return Niflib::NiMultiTargetTransformController::TYPE;
		case kNiflibType_NiMultiTextureProperty:
			return Niflib::NiMultiTextureProperty::TYPE;
		case kNiflibType_NiNode:
			return Niflib::NiNode::TYPE;
		case kNiflibType_NiObject:
			return Niflib::NiObject::TYPE;
		case kNiflibType_NiObjectNET:
			return Niflib::NiObjectNET::TYPE;
		case kNiflibType_NiPalette:
			return Niflib::NiPalette::TYPE;
		case kNiflibType_NiParticleBomb:
			return Niflib::NiParticleBomb::TYPE;
		case kNiflibType_NiParticleColorModifier:
			return Niflib::NiParticleColorModifier::TYPE;
		case kNiflibType_NiParticleGrowFade:
			return Niflib::NiParticleGrowFade::TYPE;
		case kNiflibType_NiParticleMeshes:
			return Niflib::NiParticleMeshes::TYPE;
		case kNiflibType_NiParticleMeshesData:
			return Niflib::NiParticleMeshesData::TYPE;
		case kNiflibType_NiParticleMeshModifier:
			return Niflib::NiParticleMeshModifier::TYPE;
		case kNiflibType_NiParticleModifier:
			return Niflib::NiParticleModifier::TYPE;
		case kNiflibType_NiParticleRotation:
			return Niflib::NiParticleRotation::TYPE;
		case kNiflibType_NiParticles:
			return Niflib::NiParticles::TYPE;
		case kNiflibType_NiParticlesData:
			return Niflib::NiParticlesData::TYPE;
		case kNiflibType_NiParticleSystem:
			return Niflib::NiParticleSystem::TYPE;
		case kNiflibType_NiParticleSystemController:
			return Niflib::NiParticleSystemController::TYPE;
		case kNiflibType_NiPathController:
			return Niflib::NiPathController::TYPE;
		case kNiflibType_NiPathInterpolator:
			return Niflib::NiPathInterpolator::TYPE;
		case kNiflibType_NiPersistentSrcTextureRendererData:
			return Niflib::NiPersistentSrcTextureRendererData::TYPE;
		case kNiflibType_NiPhysXActorDesc:
			return Niflib::NiPhysXActorDesc::TYPE;
		case kNiflibType_NiPhysXBodyDesc:
			return Niflib::NiPhysXBodyDesc::TYPE;
		case kNiflibType_NiPhysXD6JointDesc:
			return Niflib::NiPhysXD6JointDesc::TYPE;
		case kNiflibType_NiPhysXKinematicSrc:
			return Niflib::NiPhysXKinematicSrc::TYPE;
		case kNiflibType_NiPhysXMaterialDesc:
			return Niflib::NiPhysXMaterialDesc::TYPE;
		case kNiflibType_NiPhysXMeshDesc:
			return Niflib::NiPhysXMeshDesc::TYPE;
		case kNiflibType_NiPhysXProp:
			return Niflib::NiPhysXProp::TYPE;
		case kNiflibType_NiPhysXPropDesc:
			return Niflib::NiPhysXPropDesc::TYPE;
		case kNiflibType_NiPhysXShapeDesc:
			return Niflib::NiPhysXShapeDesc::TYPE;
		case kNiflibType_NiPhysXTransformDest:
			return Niflib::NiPhysXTransformDest::TYPE;
		case kNiflibType_NiPixelData:
			return Niflib::NiPixelData::TYPE;
		case kNiflibType_NiPlanarCollider:
			return Niflib::NiPlanarCollider::TYPE;
		case kNiflibType_NiPoint3InterpController:
			return Niflib::NiPoint3InterpController::TYPE;
		case kNiflibType_NiPoint3Interpolator:
			return Niflib::NiPoint3Interpolator::TYPE;
		case kNiflibType_NiPointLight:
			return Niflib::NiPointLight::TYPE;
		case kNiflibType_NiPortal:
			return Niflib::NiPortal::TYPE;
		case kNiflibType_NiPosData:
			return Niflib::NiPosData::TYPE;
		case kNiflibType_NiProperty:
			return Niflib::NiProperty::TYPE;
		case kNiflibType_NiPSysAgeDeathModifier:
			return Niflib::NiPSysAgeDeathModifier::TYPE;
		case kNiflibType_NiPSysAirFieldModifier:
			return Niflib::NiPSysAirFieldModifier::TYPE;
		case kNiflibType_NiPSysBombModifier:
			return Niflib::NiPSysBombModifier::TYPE;
		case kNiflibType_NiPSysBoundUpdateModifier:
			return Niflib::NiPSysBoundUpdateModifier::TYPE;
		case kNiflibType_NiPSysBoxEmitter:
			return Niflib::NiPSysBoxEmitter::TYPE;
		case kNiflibType_NiPSysCollider:
			return Niflib::NiPSysCollider::TYPE;
		case kNiflibType_NiPSysColliderManager:
			return Niflib::NiPSysColliderManager::TYPE;
		case kNiflibType_NiPSysColorModifier:
			return Niflib::NiPSysColorModifier::TYPE;
		case kNiflibType_NiPSysCylinderEmitter:
			return Niflib::NiPSysCylinderEmitter::TYPE;
		case kNiflibType_NiPSysData:
			return Niflib::NiPSysData::TYPE;
		case kNiflibType_NiPSysDragFieldModifier:
			return Niflib::NiPSysDragFieldModifier::TYPE;
		case kNiflibType_NiPSysDragModifier:
			return Niflib::NiPSysDragModifier::TYPE;
		case kNiflibType_NiPSysEmitter:
			return Niflib::NiPSysEmitter::TYPE;
		case kNiflibType_NiPSysEmitterCtlr:
			return Niflib::NiPSysEmitterCtlr::TYPE;
		case kNiflibType_NiPSysEmitterCtlrData:
			return Niflib::NiPSysEmitterCtlrData::TYPE;
		case kNiflibType_NiPSysEmitterDeclinationCtlr:
			return Niflib::NiPSysEmitterDeclinationCtlr::TYPE;
		case kNiflibType_NiPSysEmitterDeclinationVarCtlr:
			return Niflib::NiPSysEmitterDeclinationVarCtlr::TYPE;
		case kNiflibType_NiPSysEmitterInitialRadiusCtlr:
			return Niflib::NiPSysEmitterInitialRadiusCtlr::TYPE;
		case kNiflibType_NiPSysEmitterLifeSpanCtlr:
			return Niflib::NiPSysEmitterLifeSpanCtlr::TYPE;
		case kNiflibType_NiPSysEmitterSpeedCtlr:
			return Niflib::NiPSysEmitterSpeedCtlr::TYPE;
		case kNiflibType_NiPSysFieldMagnitudeCtlr:
			return Niflib::NiPSysFieldMagnitudeCtlr::TYPE;
		case kNiflibType_NiPSysFieldModifier:
			return Niflib::NiPSysFieldModifier::TYPE;
		case kNiflibType_NiPSysGravityFieldModifier:
			return Niflib::NiPSysGravityFieldModifier::TYPE;
		case kNiflibType_NiPSysGravityModifier:
			return Niflib::NiPSysGravityModifier::TYPE;
		case kNiflibType_NiPSysGravityStrengthCtlr:
			return Niflib::NiPSysGravityStrengthCtlr::TYPE;
		case kNiflibType_NiPSysGrowFadeModifier:
			return Niflib::NiPSysGrowFadeModifier::TYPE;
		case kNiflibType_NiPSysMeshEmitter:
			return Niflib::NiPSysMeshEmitter::TYPE;
		case kNiflibType_NiPSysMeshUpdateModifier:
			return Niflib::NiPSysMeshUpdateModifier::TYPE;
		case kNiflibType_NiPSysModifier:
			return Niflib::NiPSysModifier::TYPE;
		case kNiflibType_NiPSysModifierActiveCtlr:
			return Niflib::NiPSysModifierActiveCtlr::TYPE;
		case kNiflibType_NiPSysModifierBoolCtlr:
			return Niflib::NiPSysModifierBoolCtlr::TYPE;
		case kNiflibType_NiPSysModifierCtlr:
			return Niflib::NiPSysModifierCtlr::TYPE;
		case kNiflibType_NiPSysModifierFloatCtlr:
			return Niflib::NiPSysModifierFloatCtlr::TYPE;
		case kNiflibType_NiPSysPlanarCollider:
			return Niflib::NiPSysPlanarCollider::TYPE;
		case kNiflibType_NiPSysPositionModifier:
			return Niflib::NiPSysPositionModifier::TYPE;
		case kNiflibType_NiPSysResetOnLoopCtlr:
			return Niflib::NiPSysResetOnLoopCtlr::TYPE;
		case kNiflibType_NiPSysRotationModifier:
			return Niflib::NiPSysRotationModifier::TYPE;
		case kNiflibType_NiPSysSpawnModifier:
			return Niflib::NiPSysSpawnModifier::TYPE;
		case kNiflibType_NiPSysSphereEmitter:
			return Niflib::NiPSysSphereEmitter::TYPE;
		case kNiflibType_NiPSysSphericalCollider:
			return Niflib::NiPSysSphericalCollider::TYPE;
		case kNiflibType_NiPSysTrailEmitter:
			return Niflib::NiPSysTrailEmitter::TYPE;
		case kNiflibType_NiPSysTurbulenceFieldModifier:
			return Niflib::NiPSysTurbulenceFieldModifier::TYPE;
		case kNiflibType_NiPSysUpdateCtlr:
			return Niflib::NiPSysUpdateCtlr::TYPE;
		case kNiflibType_NiPSysVolumeEmitter:
			return Niflib::NiPSysVolumeEmitter::TYPE;
		case kNiflibType_NiPSysVortexFieldModifier:
			return Niflib::NiPSysVortexFieldModifier::TYPE;
		case kNiflibType_NiRangeLODData:
			return Niflib::NiRangeLODData::TYPE;
		case kNiflibType_NiRawImageData:
			return Niflib::NiRawImageData::TYPE;
		case kNiflibType_NiRollController:
			return Niflib::NiRollController::TYPE;
		case kNiflibType_NiRoom:
			return Niflib::NiRoom::TYPE;
		case kNiflibType_NiRoomGroup:
			return Niflib::NiRoomGroup::TYPE;
		case kNiflibType_NiRotatingParticles:
			return Niflib::NiRotatingParticles::TYPE;
		case kNiflibType_NiRotatingParticlesData:
			return Niflib::NiRotatingParticlesData::TYPE;
		case kNiflibType_NiScreenElements:
			return Niflib::NiScreenElements::TYPE;
		case kNiflibType_NiScreenElementsData:
			return Niflib::NiScreenElementsData::TYPE;
		case kNiflibType_NiScreenLODData:
			return Niflib::NiScreenLODData::TYPE;
		case kNiflibType_NiSequence:
			return Niflib::NiSequence::TYPE;
		case kNiflibType_NiSequenceStreamHelper:
			return Niflib::NiSequenceStreamHelper::TYPE;
		case kNiflibType_NiShadeProperty:
			return Niflib::NiShadeProperty::TYPE;
		case kNiflibType_NiSingleInterpController:
			return Niflib::NiSingleInterpController::TYPE;
		case kNiflibType_NiSkinData:
			return Niflib::NiSkinData::TYPE;
		case kNiflibType_NiSkinInstance:
			return Niflib::NiSkinInstance::TYPE;
		case kNiflibType_NiSkinPartition:
			return Niflib::NiSkinPartition::TYPE;
		case kNiflibType_NiSortAdjustNode:
			return Niflib::NiSortAdjustNode::TYPE;
		case kNiflibType_NiSourceCubeMap:
			return Niflib::NiSourceCubeMap::TYPE;
		case kNiflibType_NiSourceTexture:
			return Niflib::NiSourceTexture::TYPE;
		case kNiflibType_NiSpecularProperty:
			return Niflib::NiSpecularProperty::TYPE;
		case kNiflibType_NiSphericalCollider:
			return Niflib::NiSphericalCollider::TYPE;
		case kNiflibType_NiSpotLight:
			return Niflib::NiSpotLight::TYPE;
		case kNiflibType_NiStencilProperty:
			return Niflib::NiStencilProperty::TYPE;
		case kNiflibType_NiStringExtraData:
			return Niflib::NiStringExtraData::TYPE;
		case kNiflibType_NiStringPalette:
			return Niflib::NiStringPalette::TYPE;
		case kNiflibType_NiStringsExtraData:
			return Niflib::NiStringsExtraData::TYPE;
		case kNiflibType_NiSwitchNode:
			return Niflib::NiSwitchNode::TYPE;
		case kNiflibType_NiTextKeyExtraData:
			return Niflib::NiTextKeyExtraData::TYPE;
		case kNiflibType_NiTexture:
			return Niflib::NiTexture::TYPE;
		case kNiflibType_NiTextureEffect:
			return Niflib::NiTextureEffect::TYPE;
		case kNiflibType_NiTextureModeProperty:
			return Niflib::NiTextureModeProperty::TYPE;
		case kNiflibType_NiTextureProperty:
			return Niflib::NiTextureProperty::TYPE;
		case kNiflibType_NiTextureTransformController:
			return Niflib::NiTextureTransformController::TYPE;
		case kNiflibType_NiTexturingProperty:
			return Niflib::NiTexturingProperty::TYPE;
		case kNiflibType_NiTimeController:
			return Niflib::NiTimeController::TYPE;
		case kNiflibType_NiTransformController:
			return Niflib::NiTransformController::TYPE;
		case kNiflibType_NiTransformData:
			return Niflib::NiTransformData::TYPE;
		case kNiflibType_NiTransformInterpolator:
			return Niflib::NiTransformInterpolator::TYPE;
		case kNiflibType_NiTransparentProperty:
			return Niflib::NiTransparentProperty::TYPE;
		case kNiflibType_NiTriBasedGeom:
			return Niflib::NiTriBasedGeom::TYPE;
		case kNiflibType_NiTriBasedGeomData:
			return Niflib::NiTriBasedGeomData::TYPE;
		case kNiflibType_NiTriShape:
			return Niflib::NiTriShape::TYPE;
		case kNiflibType_NiTriShapeData:
			return Niflib::NiTriShapeData::TYPE;
		case kNiflibType_NiTriShapeSkinController:
			return Niflib::NiTriShapeSkinController::TYPE;
		case kNiflibType_NiTriStrips:
			return Niflib::NiTriStrips::TYPE;
		case kNiflibType_NiTriStripsData:
			return Niflib::NiTriStripsData::TYPE;
		case kNiflibType_NiUVController:
			return Niflib::NiUVController::TYPE;
		case kNiflibType_NiUVData:
			return Niflib::NiUVData::TYPE;
		case kNiflibType_NiVectorExtraData:
			return Niflib::NiVectorExtraData::TYPE;
		case kNiflibType_NiVertexColorProperty:
			return Niflib::NiVertexColorProperty::TYPE;
		case kNiflibType_NiVertWeightsExtraData:
			return Niflib::NiVertWeightsExtraData::TYPE;
		case kNiflibType_NiVisController:
			return Niflib::NiVisController::TYPE;
		case kNiflibType_NiVisData:
			return Niflib::NiVisData::TYPE;
		case kNiflibType_NiWireframeProperty:
			return Niflib::NiWireframeProperty::TYPE;
		case kNiflibType_NiZBufferProperty:
			return Niflib::NiZBufferProperty::TYPE;
		case kNiflibType_RefObject:
			return Niflib::RefObject::TYPE;
		case kNiflibType_RootCollisionNode:
			return Niflib::RootCollisionNode::TYPE;
		case kNiflibType_SkyShaderProperty:
			return Niflib::SkyShaderProperty::TYPE;
		case kNiflibType_TallGrassShaderProperty:
			return Niflib::TallGrassShaderProperty::TYPE;
		case kNiflibType_TileShaderProperty:
			return Niflib::TileShaderProperty::TYPE;
		case kNiflibType_VolumetricFogShaderProperty:
			return Niflib::VolumetricFogShaderProperty::TYPE;
		case kNiflibType_WaterShaderProperty:
			return Niflib::WaterShaderProperty::TYPE;
		default:
			throw std::exception("kNiflibType_UNKNOWN");
	}
}
