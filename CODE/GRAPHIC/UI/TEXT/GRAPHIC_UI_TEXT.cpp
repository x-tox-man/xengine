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
#include "GRAPHIC_UI_TEXT_ADAPTER.h"

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
    
    SetAdapter( new GRAPHIC_UI_TEXT_ADAPTER );
    
    GRAPHIC_TEXTURE_BLOCK::PTR text_texture_block = new GRAPHIC_TEXTURE_BLOCK();
    text_texture_block->SetTexture( Text.GetFont()->GetTexture() );
    
    GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL();
    material->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, text_texture_block);
    
    RenderStyle = new GRAPHIC_UI_RENDER_STYLE;
    RenderStyle->SetColor( Color );
    RenderStyle->SetShape( &Text );
    
    GRAPHIC_SHADER_EFFECT::PTR ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderText"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    ui_textured_shader_effect->SetMaterial( material );
    ui_textured_shader_effect->Initialize(GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    Text.Initialize( &ui_textured_shader_effect->GetProgram() );
    
    TextRectangle.Size = Text.GetTextExtent();
    TextRectangle.Center = GetPosition();
    
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, RenderStyle );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, RenderStyle );
    SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, RenderStyle );
}

void GRAPHIC_UI_TEXT::UpdateText( const char * text ) {
    
    Text.UpdateText( text );
    
    TextRectangle.Size = Text.GetTextExtent();
    TextRectangle.Center = GetPosition();
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_TEXT::Contains( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( TextRectangle.Contains(cursor_position) ){
        
        return this;
    }
    
    return NULL;
}
