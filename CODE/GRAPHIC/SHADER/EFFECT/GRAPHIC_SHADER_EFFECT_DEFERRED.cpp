//
//  GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_DEFERRED.h"
#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"
#include "CORE_MATH.h"

GRAPHIC_SHADER_EFFECT_DEFERRED::GRAPHIC_SHADER_EFFECT_DEFERRED( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT(),
    PreviousCamera( NULL ) {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_DEFERRED::~GRAPHIC_SHADER_EFFECT_DEFERRED() {
    
}

void GRAPHIC_SHADER_EFFECT_DEFERRED::Apply( GRAPHIC_RENDERER & renderer, const char * material_name ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer, material_name );
    
    GRAPHIC_SHADER_ATTRIBUTE
        & attr_previous_camera_world_position = Program.GetShaderAttribute( PreviousCameraWorldPositionIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE
        & attr_previous_proj_mat = Program.GetShaderAttribute( PreviousrojectionIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE
        & fov_and_ratio = Program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::FOVRatio );
    
    assert( PreviousCamera != NULL );
    
    float v4[4];
    float TanHalfFOV = tanf( DEG_TO_RAD * (PreviousCamera->GetFov() / 2.0f));
    
    v4[0] = 0.0f;
    v4[1] = PreviousCamera->GetAspectRatio();;
    v4[2] = TanHalfFOV;
    v4[3] = 1.0f;
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeVector(renderer, v4, fov_and_ratio);
    GRAPHIC_SYSTEM::ApplyShaderAttributeVector( renderer, &PreviousCamera->GetPosition()[0],attr_previous_camera_world_position );
    GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( renderer, &PreviousCamera->GetProjectionMatrix()[0], attr_previous_proj_mat );
}

void GRAPHIC_SHADER_EFFECT_DEFERRED::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_DEFERRED::PreviousCameraWorldPositionIdentifier( "PreviousCameraWorldPosition" ),
    GRAPHIC_SHADER_EFFECT_DEFERRED::PreviousrojectionIdentifier( "PreviousProjection" );
