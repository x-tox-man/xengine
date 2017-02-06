//
//  GRAPHIC_UI_TEXT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_TEXT.h"
#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GRAPHIC_UI_TEXT::GRAPHIC_UI_TEXT() :
    GRAPHIC_UI_ELEMENT(),
    Text(),
    Color( CORE_COLOR_White ) {
}

GRAPHIC_UI_TEXT::~GRAPHIC_UI_TEXT() {
    
}

void GRAPHIC_UI_TEXT::Initialize() {
    
    GRAPHIC_UI_RENDER_STYLE * text_render_style = new GRAPHIC_UI_RENDER_STYLE;
    GRAPHIC_TEXTURE_BLOCK * text_texture_block = new GRAPHIC_TEXTURE_BLOCK;
    
    text_texture_block->SetTexture( Text.GetFont()->Texture );
    text_render_style->SetColor( Color );
    text_render_style->SetShape( &Text );
    text_render_style->SetTextureBlock( text_texture_block );
    
    GRAPHIC_SHADER_EFFECT::PTR ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
    
    Text.Initialize( &ui_textured_shader_effect->GetProgram() );
    
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, text_render_style );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, text_render_style );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, text_render_style );
}
