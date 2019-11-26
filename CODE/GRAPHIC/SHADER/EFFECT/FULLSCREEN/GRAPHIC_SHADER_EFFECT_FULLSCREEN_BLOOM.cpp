//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::PTR effect ) :
    GRAPHIC_SHADER_EFFECT(),
    EffectInstance( effect ) {
    
    Program.SetProgram( effect->GetProgram().GetProgram() );
    Program.CopyAttributes();
    Bind = effect->GetShaderBind();
    MaterialCollection = effect->GetMaterialCollection();
}

GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::~GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM() {

}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::Apply( GRAPHIC_RENDERER & renderer, bool does_lighting, bool does_texturing ) {
    
    GRAPHIC_SHADER_EFFECT::Apply( renderer, does_lighting, does_texturing );
    GRAPHIC_SHADER_ATTRIBUTE & attr_threshold = EffectInstance->GetProgram().getShaderAttribute( BloomThresholdIdentifier );
    
    GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( renderer, attr_threshold.AttributeValue.Value.FloatValue, attr_threshold );
}

void GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::BindAttributes() {
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    #if OPENGL2PLUS
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( EffectInstance->GetProgram().GetProgram()->GetShaderProgram(), BloomThresholdIdentifier.GetTextValue() ); )
    #elif X_VK
        #error "TODO IMPLEMENT"
    #elif X_METAL
    //#error "TODO IMPLEMENT"
    #else
        #error "TODO IMPLEMENT"
    #endif
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = BloomThresholdIdentifier;
        attribute->AttributeValue.Value.FloatValue = 0.7f;
        
        EffectInstance->GetProgram().setShaderAttribute(*attribute);
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
}

CORE_HELPERS_IDENTIFIER
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::BloomThresholdIdentifier( "BloomThreshold" );
