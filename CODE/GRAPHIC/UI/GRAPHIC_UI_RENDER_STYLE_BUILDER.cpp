//
//  GRAPHIC_UI_RENDER_STYLE_BUILDER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_RENDER_STYLE_BUILDER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "GRAPHIC_OBJECT_SHAPE_FRAME.h"

GRAPHIC_UI_RENDER_STYLE_BUILDER & GRAPHIC_UI_RENDER_STYLE_BUILDER::NewStyle() {
    
#if DEBUG
    assert( Style == NULL );
#endif
    
    Style = new GRAPHIC_UI_RENDER_STYLE;
    
    return ThisBuilder;
}

GRAPHIC_UI_RENDER_STYLE_BUILDER & GRAPHIC_UI_RENDER_STYLE_BUILDER::CreateStyle( const CORE_HELPERS_UNIQUE_IDENTIFIER & texture_name, const CORE_HELPERS_COLOR & color ) {
    
    auto material = new GRAPHIC_MATERIAL;
    material->SetDiffuse( color );
    material->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( GRAPHIC_TEXTURE::GetResourceForIdentifier( texture_name ) ) );
    
    Style->SetShape( ( GRAPHIC_OBJECT_SHAPE * ) GRAPHIC_OBJECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::UIPlanShape ) );
    Style->SetEffect( GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::TexturedShaderIdentifier ) );
    Style->SetMaterial( material );
    
    return ThisBuilder;
}

GRAPHIC_UI_RENDER_STYLE_BUILDER & GRAPHIC_UI_RENDER_STYLE_BUILDER::CreateStyle( const char * texture_name, const CORE_HELPERS_COLOR & color ) {
    
    auto material = new GRAPHIC_MATERIAL;
    material->SetDiffuse( color );
    material->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( GRAPHIC_TEXTURE::GetResourceForIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ) ) ) );
    
    Style->SetShape( ( GRAPHIC_OBJECT_SHAPE * ) GRAPHIC_OBJECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::UIPlanShape ) );
    Style->SetEffect( GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::TexturedShaderIdentifier ) );
    Style->SetMaterial( material );
    
    return ThisBuilder;
}

GRAPHIC_UI_RENDER_STYLE_BUILDER & GRAPHIC_UI_RENDER_STYLE_BUILDER::CreateStyle( const CORE_HELPERS_COLOR & color ) {
    
    auto material = new GRAPHIC_MATERIAL;
    material->SetDiffuse( color );
    
    Style->SetShape( ( GRAPHIC_OBJECT_SHAPE * ) GRAPHIC_OBJECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::UIPlanShape ) );
    Style->SetEffect( GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::ColoredShaderIdentifier ) );
    Style->SetMaterial( material );
    
    return ThisBuilder;
}

GRAPHIC_UI_RENDER_STYLE_BUILDER & GRAPHIC_UI_RENDER_STYLE_BUILDER::CreateDecoratingFrameBorder( const CORE_MATH_VECTOR & frame_size, const CORE_HELPERS_UNIQUE_IDENTIFIER & texture_name, const CORE_HELPERS_COLOR & color ) {
    
    auto tex = GRAPHIC_TEXTURE::GetResourceForIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( texture_name ) );
                                                         
    auto material = new GRAPHIC_MATERIAL;
    material->SetDiffuse( color );
    
    material->SetTexture( GRAPHIC_SHADER_PROGRAM::ColorTexture, new GRAPHIC_TEXTURE_BLOCK( tex ) );
    Style->SetDecoratingEffect( GRAPHIC_SHADER_EFFECT::GetResourceForIdentifier( GRAPHIC_UI_SYSTEM::TexturedShaderIdentifier ) );
    
    Style->SetDecoratingShape( CreateFrameBorder( tex->GetTextureInfo().Height / ( frame_size.Y() * 3.0f), tex->GetTextureInfo().Width / ( frame_size.X()  * 3.0f) ) );
    Style->SetDecoratingMaterial( material );
    
    return ThisBuilder;
}

GRAPHIC_UI_RENDER_STYLE * GRAPHIC_UI_RENDER_STYLE_BUILDER::Build() {
    
    auto tmp = Style;
    Style = NULL;
    
    return tmp;
}

GRAPHIC_OBJECT_SHAPE * GRAPHIC_UI_RENDER_STYLE_BUILDER::CreateFrameBorder( float height_offset, float width_offset ) {
    
    auto frame = new GRAPHIC_OBJECT_SHAPE_FRAME;
    
    frame->SetBorderSize( height_offset, width_offset);
    frame->InitializeShape();
    
    return frame;
}

GRAPHIC_UI_RENDER_STYLE * GRAPHIC_UI_RENDER_STYLE_BUILDER::Style = NULL;
GRAPHIC_UI_RENDER_STYLE_BUILDER GRAPHIC_UI_RENDER_STYLE_BUILDER::ThisBuilder;

