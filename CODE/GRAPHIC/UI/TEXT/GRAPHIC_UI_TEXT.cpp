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
    Color( CORE_COLOR_White ),
    RenderStyle( NULL ) {
}

GRAPHIC_UI_TEXT::~GRAPHIC_UI_TEXT() {
    
    CORE_MEMORY_ObjectSafeDeallocation( RenderStyle );
}

void GRAPHIC_UI_TEXT::Initialize() {
    
    if ( RenderStyle ) {
        
        delete RenderStyle;
    }
    
    RenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    RenderStyle->SetTextureBlock( new GRAPHIC_TEXTURE_BLOCK );
    
    auto text_texture_block = RenderStyle->GetTextureBlock();
    
    text_texture_block->SetTexture( Text.GetFont()->GetTexture() );
    RenderStyle->SetColor( Color );
    RenderStyle->SetShape( &Text );
    
    GRAPHIC_SHADER_EFFECT::PTR ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
    
    Text.Initialize( &ui_textured_shader_effect->GetProgram() );
    
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, RenderStyle );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, RenderStyle );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, RenderStyle );
}
