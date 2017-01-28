//
//  GRAPHIC_SHADER_PROGRAM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM.h"

GRAPHIC_SHADER_PROGRAM::GRAPHIC_SHADER_PROGRAM():
    ShaderTable(),
    ShaderAttributeTable() {
    
};

GRAPHIC_SHADER_PROGRAM::~GRAPHIC_SHADER_PROGRAM() {

}

const CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_PROGRAM::ProjectionMatrix( "ProjectionMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ModelViewMatrix( "modelViewMatrix" ) ,
    GRAPHIC_SHADER_PROGRAM::MVPMatrix( "MVPMatrix" ) ,
    GRAPHIC_SHADER_PROGRAM::ShadowMapMVP( "ShadowMapMVP" ) ,
    GRAPHIC_SHADER_PROGRAM::NormalMatrix( "normalMatrix" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture( "c_texture" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture1( "c_texture_1" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture2( "c_texture_2" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture3( "c_texture_3" ),
    GRAPHIC_SHADER_PROGRAM::ColorTexture4( "c_texture_4" ),
    GRAPHIC_SHADER_PROGRAM::NormalTexture( "n_texture" ),
    GRAPHIC_SHADER_PROGRAM::DepthTexture( "d_texture" ),
    GRAPHIC_SHADER_PROGRAM::SkinningMatrixTable( "jointsMatrix" ),
    GRAPHIC_SHADER_PROGRAM::AttrBindShapeMatrix( "attrBindShapeMatrix" ),
    GRAPHIC_SHADER_PROGRAM::GeometryColor( "geometryColor" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightColor( "directional_light.Color" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightDirection( "directional_light.Direction" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightAmbientIntensity( "directional_light.AmbientIntensity" ),
    GRAPHIC_SHADER_PROGRAM::DirectionalLightDiffuseIntensity( "directional_light.DiffuseIntensity" ),
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
    GRAPHIC_SHADER_PROGRAM::MaterialSpecularIntensity( "MaterialSpecularIntensity" );
