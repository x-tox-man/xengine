//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_SYSTEM.h"

GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT() {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetSahderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::~GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM() {

}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::Apply( GRAPHIC_RENDERER & renderer ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer );
    
    GRAPHIC_SHADER_ATTRIBUTE & attr_bloom_intensity = Program.getShaderAttribute( BloomIntensityIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_base_intensity = Program.getShaderAttribute( BaseIntensityIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_bloom_saturation = Program.getShaderAttribute( BloomSaturationIdentifier );
    GRAPHIC_SHADER_ATTRIBUTE & attr_base_saturation = Program.getShaderAttribute( BaseSaturationIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( attr_bloom_intensity.AttributeValue.Value.FloatValue, attr_bloom_intensity );
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( attr_base_intensity.AttributeValue.Value.FloatValue, attr_base_intensity );
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( attr_bloom_saturation.AttributeValue.Value.FloatValue, attr_bloom_saturation );
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( attr_base_saturation.AttributeValue.Value.FloatValue, attr_base_saturation );
}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::BindAttributes() {
    
    GRAPHIC_SHADER_EFFECT::BindAttributes();
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), BloomIntensityIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BloomIntensityIdentifier;
        attribute->AttributeValue.Value.FloatValue = 0.7f;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), BaseIntensityIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BaseIntensityIdentifier;
        attribute->AttributeValue.Value.FloatValue = 1.0f;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), BloomSaturationIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BloomSaturationIdentifier;
        attribute->AttributeValue.Value.FloatValue = 0.7f;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), BaseSaturationIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BaseSaturationIdentifier;
        attribute->AttributeValue.Value.FloatValue = 1.0f;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::BloomIntensityIdentifier( "BloomIntensity" ),
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::BaseIntensityIdentifier( "BaseIntensity" ),
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::BloomSaturationIdentifier( "BloomSaturation" ),
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::BaseSaturationIdentifier( "BaseSaturation" );
