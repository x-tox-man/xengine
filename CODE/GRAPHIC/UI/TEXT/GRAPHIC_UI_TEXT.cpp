//
//  GRAPHIC_UI_TEXT.cpp
//  GAME-ENGINE
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
    Text( NULL ) {
}

GRAPHIC_UI_TEXT::~GRAPHIC_UI_TEXT() {
    
    CORE_MEMORY_ObjectSafeDeallocation( Text );
}

void GRAPHIC_UI_TEXT::Initialize() {
    
    SetAdapter( new GRAPHIC_UI_TEXT_ADAPTER );
    
    TextRectangle.Size = Text->GetTextExtent();
    GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( GetPlacement().GetRelativePosition().X() - (Text->GetTextExtent().X() / Text->GetFont()->GetSize()) * 0.5f, GetPlacement().GetRelativePosition().Y() - (Text->GetTextExtent().Y() ) * 0.33f ) );
    TextRectangle.Center = GetPosition();
}

void GRAPHIC_UI_TEXT::UpdateText( const CORE_DATA_UTF8_TEXT & text ) {
    
    Text->UpdateText( text );
    
    TextRectangle.Size = Text->GetTextExtent();
    GetPlacement().SetRelativePosition( CORE_MATH_VECTOR( GetPlacement().GetRelativePosition().X() - (Text->GetTextExtent().X() / Text->GetFont()->GetSize()) * 0.5f, GetPlacement().GetRelativePosition().Y() - (Text->GetTextExtent().Y() ) * 0.33f ) );
    TextRectangle.Center = GetPosition();
}

GRAPHIC_UI_ELEMENT * GRAPHIC_UI_TEXT::Contains( const CORE_MATH_VECTOR & cursor_position ) {
    
    if ( TextRectangle.Contains(cursor_position) ){
        
        return this;
    }
    
    return NULL;
}
