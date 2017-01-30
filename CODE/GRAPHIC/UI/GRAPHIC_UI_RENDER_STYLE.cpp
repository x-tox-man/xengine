//
//  GRAPHIC_UI_RENDER_STYLE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"

GRAPHIC_UI_RENDER_STYLE::GRAPHIC_UI_RENDER_STYLE() :
    Color( 0.0f, 0.0f, 0.0f, 1.0f),
    Shape( NULL ),
    DecoratingShape( NULL ),
    TextureBlock( NULL ),
    DecoratingTextureBlock( NULL ) {
    
}

GRAPHIC_UI_RENDER_STYLE::GRAPHIC_UI_RENDER_STYLE( GRAPHIC_OBJECT_SHAPE * shape, GRAPHIC_TEXTURE_BLOCK * texture_block, const CORE_HELPERS_COLOR & color, GRAPHIC_OBJECT_SHAPE * decorating_shape, GRAPHIC_TEXTURE_BLOCK * decorating_texture_block ) :
    Color( color ),
    Shape( shape ),
    DecoratingShape( decorating_shape ),
    TextureBlock( texture_block ),
    DecoratingTextureBlock( decorating_texture_block ) {

}

GRAPHIC_UI_RENDER_STYLE::~GRAPHIC_UI_RENDER_STYLE() {

}

void GRAPHIC_UI_RENDER_STYLE::Apply( const GRAPHIC_RENDERER & renderer, const GRAPHIC_UI_PLACEMENT & placement, float opacity ) {
    
    if ( Shape ) {
        
        Shape->SetPosition( placement.GetAbsolutePosition() );
        Shape->SetScaleFactor( placement.GetSize() );
        
        if ( TextureBlock ) {
            
            Shape->SetTextureBlock( TextureBlock );
        }
        
        GRAPHIC_SHADER_ATTRIBUTE & color_attribute = Shape->GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
        
        color_attribute.AttributeValue.Value.FloatArray4[0] = Color[0] * opacity;
        color_attribute.AttributeValue.Value.FloatArray4[1] = Color[1] * opacity;
        color_attribute.AttributeValue.Value.FloatArray4[2] = Color[2] * opacity;
        color_attribute.AttributeValue.Value.FloatArray4[3] = Color[3] * opacity;
        
        Shape->Render( renderer );
    }
    
    if ( DecoratingShape && DecoratingTextureBlock) {
        
        DecoratingShape->SetPosition( placement.GetAbsolutePosition() );
        DecoratingShape->SetScaleFactor( placement.GetSize() );
        DecoratingShape->SetTextureBlock( DecoratingTextureBlock );
        GRAPHIC_SHADER_ATTRIBUTE & color_attribute = DecoratingShape->GetShaderTable()[0]->getShaderAttribute( GRAPHIC_SHADER_PROGRAM::GeometryColor );
        
        color_attribute.AttributeValue.Value.FloatArray4[0] = Color[0];
        color_attribute.AttributeValue.Value.FloatArray4[1] = Color[1];
        color_attribute.AttributeValue.Value.FloatArray4[2] = Color[2];
        color_attribute.AttributeValue.Value.FloatArray4[3] = Color[3];
        
        DecoratingShape->Render( renderer );
    }
}
