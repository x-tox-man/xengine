//
//  GRAPHIC_SHADER_PROGRAM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_RENDERER.h"

GRAPHIC_SHADER_PROGRAM::GRAPHIC_SHADER_PROGRAM():
    ShaderTable(),
    ShaderAttributeTable()
#if X_METAL
    ,_pipelineStateDescriptor( NULL ),
    MetalPipelineStateCache()
#endif
{
    
};

GRAPHIC_SHADER_PROGRAM::~GRAPHIC_SHADER_PROGRAM() {

}

const CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_PROGRAM::ProjectionMatrix( "ProjectionMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ViewMatrix( "ViewMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ModelMatrix( "ModelMatrix" ),
    GRAPHIC_SHADER_PROGRAM::MVPMatrix( "MVPMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP1( "ShadowMapMVP1" ),
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP2( "ShadowMapMVP2" ),
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP3( "ShadowMapMVP3" ),
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP4( "ShadowMapMVP4" ),
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP5( "ShadowMapMVP5" ),
    GRAPHIC_SHADER_PROGRAM::CascadeEndClipSpace( "cascadeEndClipSpace" ),
    GRAPHIC_SHADER_PROGRAM::NormalMatrix( "normalMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture( "c_texture" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture1( "c_texture_1" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture2( "c_texture_2" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture3( "c_texture_3" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture4( "c_texture_4" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture5( "c_texture_5" ),
    GRAPHIC_SHADER_PROGRAM::ColorTextureOut( "o_texture" ),
    GRAPHIC_SHADER_PROGRAM::ColorTextureOut1( "o_texture_1" ),
    GRAPHIC_SHADER_PROGRAM::ColorTextureOut2( "o_texture_2" ),
    GRAPHIC_SHADER_PROGRAM::ColorTextureOut3( "o_texture_3" ),
    GRAPHIC_SHADER_PROGRAM::ColorTextureOut4( "o_texture_4" ),
    GRAPHIC_SHADER_PROGRAM::NormalTexture( "n_texture" ),
    GRAPHIC_SHADER_PROGRAM::DisplacementTexture( "t_texture" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture( "d_texture" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture1( "d_texture1" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture2( "d_texture2" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture3( "d_texture3" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture4( "d_texture4" ),
    GRAPHIC_SHADER_PROGRAM::ShadowDepthTexture1( "d_texture_shadow1" ),
    GRAPHIC_SHADER_PROGRAM::ShadowDepthTexture2( "d_texture_shadow2" ),
    GRAPHIC_SHADER_PROGRAM::ShadowDepthTexture3( "d_texture_shadow3" ),
    GRAPHIC_SHADER_PROGRAM::ShadowDepthTexture4( "d_texture_shadow4" ),
    GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable( "jointsMatrix" ),
    GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix( "attrBindShapeMatrix" ),
    GRAPHIC_SHADER_PROGRAM::GeometryColor( "geometryColor" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightColor( "directional_light.Color" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightDirection( "directional_light.Direction" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightAmbientIntensity( "directional_light.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightDiffuseIntensity( "directional_light.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::AmbientLightColor( "ambient_light.Color" ),
    GRAPHIC_SHADER_PROGRAM::AmbientLightAmbientIntensity( "ambient_light.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::AmbientLightDiffuseIntensity( "ambient_light.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLightColor( "point_light.Color" ),
    GRAPHIC_SHADER_PROGRAM::PointLightPosition( "point_light.Position" ),
    GRAPHIC_SHADER_PROGRAM::PointLightAmbientIntensity( "point_light.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLightDiffuseIntensity( "point_light.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLightConstant( "point_light.AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::PointLightLinear( "point_light.AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::PointLightExp( "point_light.AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0Color( "point_light_table[0].Color" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0Position( "point_light_table[0].Position" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0AmbientIntensity( "point_light_table[0].AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0DiffuseIntensity( "point_light_table[0].DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0Constant( "point_light_table[0].AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0Linear( "point_light_table[0].AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::PointLight0Exp( "point_light_table[0].AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1Color( "point_light_table[1].Color" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1Position( "point_light_table[1].Position" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1AmbientIntensity( "point_light_table[1].AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1DiffuseIntensity( "point_light_table[1].DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1Constant( "point_light_table[1].AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1Linear( "point_light_table[1].AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::PointLight1Exp( "point_light_table[1].AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightColor( "spot_light.Base.Color" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightPosition( "spot_light.Base.Position" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightDirection( "spot_light.Direction" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightCutoff( "spot_light.Cutoff" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightAmbientIntensity( "spot_light.Base.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightDiffuseIntensity( "spot_light.Base.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightConstant( "spot_light.Base.AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightLinear( "spot_light.Base.AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::SpotLightExp( "spot_light.Base.AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Color( "spot_light_table[0].Base.Color" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Position( "spot_light_table[0].Base.Position" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Direction( "spot_light_table[0].Direction" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Cutoff( "spot_light_table[0].Cutoff" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0AmbientIntensity( "spot_light_table[0].Base.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0DiffuseIntensity( "spot_light_table[0].Base.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Constant( "spot_light_table[0].Base.AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Linear( "spot_light_table[0].Base.AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight0Exp( "spot_light_table[0].Base.AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Color( "spot_light_table[1].Base.Color" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Position( "spot_light_table[1].Base.Position" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Direction( "spot_light_table[1].Direction" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Cutoff( "spot_light_table[1].Cutoff" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1AmbientIntensity( "spot_light_table[1].Base.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1DiffuseIntensity( "spot_light_table[1].Base.DiffuseIntensity" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Constant( "spot_light_table[1].Base.AttenuationConstant" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Linear( "spot_light_table[1].Base.AttenuationLinear" ),
    GRAPHIC_SHADER_PROGRAM::SpotLight1Exp( "spot_light_table[1].Base.AttenuationExp" ),
    GRAPHIC_SHADER_PROGRAM::AmbientLight( "AmbientLight" ),
    GRAPHIC_SHADER_PROGRAM::CameraWorldPosition( "CameraWorldPosition" ),
    GRAPHIC_SHADER_PROGRAM::LightSpecularPower( "LightSpecularPower" ),
    GRAPHIC_SHADER_PROGRAM::MaterialSpecularIntensity( "MaterialSpecularIntensity" ),
    GRAPHIC_SHADER_PROGRAM::TimeModulator( "TimeModulator" ),
    GRAPHIC_SHADER_PROGRAM::PreviousModelViewProjectionIdentifier( "PreviousModelViewProjectionIdentifier" ),
    GRAPHIC_SHADER_PROGRAM::SSAOProjectionMatrix( "SSAOProjectionMatrix" ),
    GRAPHIC_SHADER_PROGRAM::SSAOSampleRadFOVRatio( "SSAOSampleRadFOVRatio" ),
    GRAPHIC_SHADER_PROGRAM::SSAOKernel( "SSAOKernel" ),
    GRAPHIC_SHADER_PROGRAM::SSAOTexture( "SSAOTexture" ),
    GRAPHIC_SHADER_PROGRAM::SSAOViewProjectionMatrix( "SSAOViewProjectionMatrix" ),
    GRAPHIC_SHADER_PROGRAM::FOVRatio( "FOVRatio" ),
    GRAPHIC_SHADER_PROGRAM::SSAOViewMatrix( "SSAOViewMatrix" ),
    GRAPHIC_SHADER_PROGRAM::FrameResolution( "FrameResolution" );
