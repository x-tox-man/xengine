//
//  GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING.h"
#include "GRAPHIC_SYSTEM.h"

GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::~GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING() {
    
}

void GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::Apply( GRAPHIC_RENDERER & renderer, bool does_lighting, bool does_texturing ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer, does_lighting, does_texturing );
    
    GRAPHIC_SHADER_ATTRIBUTE & attr_previous_view_mat = Program.getShaderAttribute( PreviousModelViewProjectionIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( attr_previous_view_mat.AttributeValue.Value.FloatMatrix4x4, attr_previous_view_mat );
}

void GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::PreviousModelViewProjectionIdentifier( "PreviousModelViewProjection" );
