//
//  GRAPHIC_UI_HELPER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_HELPER.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GRAPHIC_UI_HELPER )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_HELPER, CreateElement, const CORE_HELPERS_IDENTIFIER & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_HELPER, CreateElement, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( GRAPHIC_UI_FRAME *, GRAPHIC_UI_HELPER, CreateFrame, const CORE_HELPERS_IDENTIFIER & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( GRAPHIC_UI_FRAME *, GRAPHIC_UI_HELPER, CreateFrame, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_2( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_HELPER, CreateTextElement, const CORE_HELPERS_IDENTIFIER &, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_2( GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_HELPER, CreateTextElement, const char *, const char * )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_2( GRAPHIC_UI_HELPER, AddElementToFrame, GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_FRAME * )


CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GRAPHIC_UI_HELPER )

GRAPHIC_UI_HELPER::GRAPHIC_UI_HELPER() {
    
}

GRAPHIC_UI_HELPER::~GRAPHIC_UI_HELPER() {
    
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_HELPER::CreateElement( const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    GRAPHIC_UI_ELEMENT * element = new GRAPHIC_UI_ELEMENT;
    
    GRAPHIC_UI_RENDER_STYLE * style = GRAPHIC_UI_HELPER::CreateDefaultRenderStyle( identifier.GetTextValue() );
    
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Disabled, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, style );
    
    element->SetIdentifier( identifier );
    
    return element;
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_HELPER::CreateElement( const char * identifier ) {
    
    return GRAPHIC_UI_HELPER::CreateElement( CORE_HELPERS_IDENTIFIER( identifier ) );
}

GRAPHIC_UI_FRAME * GRAPHIC_UI_HELPER::CreateFrame( const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    GRAPHIC_UI_FRAME * frame = new GRAPHIC_UI_FRAME;
    
    frame->SetIdentifier( identifier );
    
    return frame;
}

GRAPHIC_UI_FRAME * GRAPHIC_UI_HELPER::CreateFrame( const char * identifier ) {
    
    return GRAPHIC_UI_HELPER::CreateFrame( CORE_HELPERS_IDENTIFIER( identifier ) );
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_HELPER::CreateTextElement( const CORE_HELPERS_IDENTIFIER & identifier, const char * text ) {
    
    GRAPHIC_UI_ELEMENT * element = new GRAPHIC_UI_ELEMENT;
    GRAPHIC_TEXT * text_shape = new GRAPHIC_TEXT;
    
    GRAPHIC_UI_RENDER_STYLE * style = GRAPHIC_UI_HELPER::CreateTextRenderStyle( DefaultFont, text_shape );
    
    text_shape->Initialize( text, *DefaultFont, 1.0f, text_shape->GetShaderTable()[0] );
    
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Disabled, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Hovered, style );
    element->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Pressed, style );
    
    element->SetIdentifier( identifier );
    
    return element;
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_HELPER::CreateTextElement( const char * identifier, const char * text ) {
    
    return GRAPHIC_UI_HELPER::CreateTextElement( CORE_HELPERS_IDENTIFIER( identifier ), text );
}

void GRAPHIC_UI_HELPER::AddElementToFrame( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_FRAME * frame ) {
    
    frame->SetObjectForIdentifier(element->GetIdentifier(), element );
} 

GRAPHIC_UI_RENDER_STYLE * GRAPHIC_UI_HELPER::CreateDefaultRenderStyle( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_UI_RENDER_STYLE * render_style = new GRAPHIC_UI_RENDER_STYLE;
    
    render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f, 1.0f ) );
    render_style->SetShape( DefaultPlanShape );
    render_style->SetTextureBlock( &TextureAtlas->GetTextureBlock( identifier ) );
    
    return render_style;
}

GRAPHIC_UI_RENDER_STYLE * GRAPHIC_UI_HELPER::CreateTextRenderStyle( GRAPHIC_FONT * DefaultFont, GRAPHIC_TEXT *text_shape ) {
    
    GRAPHIC_UI_RENDER_STYLE * render_style = new GRAPHIC_UI_RENDER_STYLE;
    GRAPHIC_TEXTURE_BLOCK * text_texture_block = new GRAPHIC_TEXTURE_BLOCK;
    
    text_texture_block->SetTexture( DefaultFont->GetTexture() );
    
    render_style->SetColor( CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f, 1.0f ) );
    render_style->SetShape( text_shape );
    render_style->SetTextureBlock( text_texture_block );
    
    return render_style;
}

GRAPHIC_OBJECT_SHAPE_PLAN * GRAPHIC_UI_HELPER::DefaultPlanShape = NULL;
GRAPHIC_TEXTURE_ATLAS * GRAPHIC_UI_HELPER::TextureAtlas = NULL;
GRAPHIC_FONT * GRAPHIC_UI_HELPER::DefaultFont = NULL;
