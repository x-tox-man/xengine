//
//  GRAPHIC_SHADER_EFFECT_SPEEDBLUR.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_SHADER_EFFECT_SPEEDBLUR::GRAPHIC_SHADER_EFFECT_SPEEDBLUR( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_SPEEDBLUR::~GRAPHIC_SHADER_EFFECT_SPEEDBLUR() {

}

void GRAPHIC_SHADER_EFFECT_SPEEDBLUR::Apply( GRAPHIC_RENDERER & renderer, bool does_lighting, bool does_texturing ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer, does_lighting, does_texturing );
    
    GRAPHIC_SHADER_ATTRIBUTE & attr_view_ray = Program.getShaderAttribute( ViewRayIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_previous_view_mat = Program.getShaderAttribute( GRAPHIC_SHADER_PROGRAM::PreviousModelViewProjectionIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_current_inverse_view_mat = Program.getShaderAttribute( InverseCurrentModelViewIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeVector( renderer, attr_view_ray.AttributeValue.Value.FloatArray4, attr_view_ray );
    //GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( attr_previous_view_mat.AttributeValue.Value.FloatMatrix4x4, attr_previous_view_mat );
    GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( renderer, attr_current_inverse_view_mat.AttributeValue.Value.FloatMatrix4x4, attr_current_inverse_view_mat );
}

void GRAPHIC_SHADER_EFFECT_SPEEDBLUR::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;

#if OPENGL2PLUS
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), ViewRayIdentifier.GetTextValue() ); )
#elif X_VK
    #error "TODO IMPLEMENT"
#elif X_METAL
    //#error "TODO IMPLEMENT"
#else
    #error "TODO IMPLEMENT"
#endif
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ViewRayIdentifier;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;

#if OPENGL2PLUS
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), InverseCurrentModelViewIdentifier.GetTextValue() ); )
#elif X_VK
    #error "TODO IMPLEMENT"
#elif X_METAL
    //#error "TODO IMPLEMENT"
#else
    #error "TODO IMPLEMENT"
#endif
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = InverseCurrentModelViewIdentifier;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier( "InverseCurrentModelView" ),
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier( "ViewRay" );
