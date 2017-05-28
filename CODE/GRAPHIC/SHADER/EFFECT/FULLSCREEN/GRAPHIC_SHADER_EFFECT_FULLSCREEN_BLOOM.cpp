//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"

GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM() :
    GRAPHIC_SHADER_EFFECT() {
    
}

GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::~GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM() {

}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::Apply( GRAPHIC_RENDERER & ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & attr_threshold = Program.getShaderAttribute( BloomThresholdIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( attr_threshold.AttributeValue.Value.FloatValue, attr_threshold );
}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::BindAttributes() {
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( Program.GetProgram()->GetShaderProgram(), BloomThresholdIdentifier.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BloomThresholdIdentifier;
        attribute->AttributeValue.Value.FloatValue = 0.7f;
        
        Program.setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::BloomThresholdIdentifier( "BloomThreshold" );
