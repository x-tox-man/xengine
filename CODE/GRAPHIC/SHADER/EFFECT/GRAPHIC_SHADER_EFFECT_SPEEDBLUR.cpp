//
//  GRAPHIC_SHADER_EFFECT_SPEEDBLUR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"

GRAPHIC_SHADER_EFFECT_SPEEDBLUR::GRAPHIC_SHADER_EFFECT_SPEEDBLUR() :
    GRAPHIC_SHADER_EFFECT() {
    
}

GRAPHIC_SHADER_EFFECT_SPEEDBLUR::~GRAPHIC_SHADER_EFFECT_SPEEDBLUR() {

}

void GRAPHIC_SHADER_EFFECT_SPEEDBLUR::Apply( GRAPHIC_RENDERER & ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & attr_view_ray = Program.getShaderAttribute( ViewRayIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_previous_view_mat = Program.getShaderAttribute( PreviousModelViewProjectionIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_current_inverse_view_mat = Program.getShaderAttribute( InverseCurrentModelViewIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeVector( attr_view_ray.AttributeValue.Value.FloatArray4, attr_view_ray );
    GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( attr_previous_view_mat.AttributeValue.Value.FloatMatrix4x4, attr_previous_view_mat );
    GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( attr_current_inverse_view_mat.AttributeValue.Value.FloatMatrix4x4, attr_current_inverse_view_mat );
}

void GRAPHIC_SHADER_EFFECT_SPEEDBLUR::BindAttributes() {
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), ViewRayIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ViewRayIdentifier;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), InverseCurrentModelViewIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = InverseCurrentModelViewIdentifier;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), PreviousModelViewProjectionIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PreviousModelViewProjectionIdentifier;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PreviousModelViewProjectionIdentifier( "PreviousModelViewProjection" ),
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::InverseCurrentModelViewIdentifier( "InverseCurrentModelView" ),
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::ViewRayIdentifier( "ViewRay" );
