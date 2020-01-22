//
//  ShaderTypes.h
//  TestMetalMac
//
//  Created by Christophe Bernard on 08/07/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

//
//  Header containing types and enum constants shared between Metal shaders and Swift/ObjC source
//
#ifndef ShaderTypes_h
#define ShaderTypes_h

#ifdef __METAL_VERSION__
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#define NSInteger metal::int32_t
#else
#import <Foundation/Foundation.h>
#endif

#include <simd/simd.h>

typedef NS_ENUM(NSInteger, BufferIndex)
{
    BufferIndexMeshPositions = 0,
    BufferIndexUniforms = 1,
    BufferIndexConstants = 2,
    BufferIndexDirectionalLightsConstants = 3,
    BufferIndexAmbientLightConstants = 4,
    BufferIndexPointLightsConstants = 5,
    BufferIndexSpotLightsConstants = 6,
    BufferIndexBloomThresholdConstants = 7,
    BufferIndexCameraUniforms = 8,
    SkinningMatrixBuffer = 9,
    MaterialUniforms = 10
};

typedef NS_ENUM(NSInteger, VertexAttribute)
{
    VertexAttributePosition  = 0,
    VertexAttributeNormal    = 1,
    VertexAttributeTexcoords  = 2,
    VertexAttributeTexcoords1  = 3,
    VertexAttributeSkinWeight = 4,
    VertexAttributeJointIndices = 5,
    VertexAttributeTangent = 6,
    VertexAttributeBitangent = 7,
    VertexAttributeCustomFloat = 8
};

typedef NS_ENUM(NSInteger, TextureIndex)
{
    TextureIndex1Color      = 0,
    TextureIndex2Color      = 1,
    TextureIndex3Color      = 2,
    TextureIndex4Color      = 3,
    TextureIndex5Color      = 4,
    TextureIndex6Color      = 5,
    TextureIndex7Color      = 6,
    TextureIndex8Color      = 7,
    TextureIndex1Normal     = 8,
    TextureIndex1Depth      = 9,
    TextureIndex2Depth      = 10,
    TextureIndex3Depth      = 11
};

typedef struct
{
    matrix_float4x4
        ModelMatrix,
        ViewMatrix,
        MVPMatrix;
} ObjectUniforms;

typedef struct {
    vector_float2
        FrameResolution;
    matrix_float4x4
        ModelMatrix,
        ViewMatrix,
        MVPMatrix,
        attrBindShapeMatrix;
} AnimatedObjectUniforms;

typedef struct {
    vector_float2
        FrameResolution;
    matrix_float4x4
        ModelMatrix,
        MVPMatrix;
} FullscreenGaussianObjectUniforms;

typedef struct {
    vector_float4
        Diffuse,
        Specular,
        Ambient;
    float
        SpecularIntensity,
        Shininess;
} Material;

/*
 ProjectionMatrix,
 ViewMatrix,
 ModelMatrix,
 MVPMatrix,
 ShadowMapMVP1,
 ShadowMapMVP2,
 ShadowMapMVP3,
 ShadowMapMVP4,
 ShadowMapMVP5,
 CascadeEndClipSpace,
 NormalMatrix,
 ColorTexture,
 ColorTexture1,
 ColorTexture2,
 ColorTexture3,
 ColorTexture4,
 ColorTexture5,
 ColorTextureOut,
 ColorTextureOut1,
 ColorTextureOut2,
 ColorTextureOut3,
 ColorTextureOut4,
 NormalTexture,
 DisplacementTexture,
 DepthTexture,
 DepthTexture1,
 DepthTexture2,
 DepthTexture3,
 DepthTexture4,
 SkinningMatrixTable,
 AttrBindShapeMatrix,
 GeometryColor,
 DirectionalLightColor,
 DirectionalLightDirection,
 DirectionalLightAmbientIntensity,
 DirectionalLightDiffuseIntensity,
 AmbientLightColor,
 AmbientLightAmbientIntensity,
 AmbientLightDiffuseIntensity,
 PointLightColor,
 PointLightPosition,
 PointLightAmbientIntensity,
 PointLightDiffuseIntensity,
 PointLightConstant,
 PointLightLinear,
 PointLightExp,
 PointLight0Color,
 PointLight0Position,
 PointLight0AmbientIntensity,
 PointLight0DiffuseIntensity,
 PointLight0Constant,
 PointLight0Linear,
 PointLight0Exp,
 PointLight1Color,
 PointLight1Position,
 PointLight1AmbientIntensity,
 PointLight1DiffuseIntensity,
 PointLight1Constant,
 PointLight1Linear,
 PointLight1Exp,
 SpotLightColor,
 SpotLightPosition,
 SpotLightDirection,
 SpotLightCutoff,
 SpotLightAmbientIntensity,
 SpotLightDiffuseIntensity,
 SpotLightConstant,
 SpotLightLinear,
 SpotLightExp,
 SpotLight0Color,
 SpotLight0Position,
 SpotLight0Direction,
 SpotLight0Cutoff,
 SpotLight0AmbientIntensity,
 SpotLight0DiffuseIntensity,
 SpotLight0Constant,
 SpotLight0Linear,
 SpotLight0Exp,
 SpotLight1Color,
 SpotLight1Position,
 SpotLight1Direction,
 SpotLight1Cutoff,
 SpotLight1AmbientIntensity,
 SpotLight1DiffuseIntensity,
 SpotLight1Constant,
 SpotLight1Linear,
 SpotLight1Exp,
 AmbientLight,
 CameraWorldPosition,
 LightSpecularPower,
 MaterialSpecularIntensity,
 TimeModulator,
 PreviousModelViewProjectionIdentifier,
 SSAOViewProjectionMatrix,
 SSAOViewMatrix,
 SSAOSampleRad,
 SSAOKernel,
 SSAOTexture,
 FrameResolution
 */

#endif /* ShaderTypes_h */

