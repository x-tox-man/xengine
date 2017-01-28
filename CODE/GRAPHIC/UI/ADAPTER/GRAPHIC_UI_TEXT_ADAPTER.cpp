//
//  GRAPHIC_UI_TEXT_ADAPTER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_TEXT_ADAPTER.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_UI_ELEMENT.h"

GRAPHIC_UI_TEXT_ADAPTER::GRAPHIC_UI_TEXT_ADAPTER() :
    GRAPHIC_UI_BASE_ADAPTER() {
    
}

GRAPHIC_UI_TEXT_ADAPTER::~GRAPHIC_UI_TEXT_ADAPTER() {
    
}

void GRAPHIC_UI_TEXT_ADAPTER::OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const char * text ) {
    
    GRAPHIC_TEXT * text_shape = (GRAPHIC_TEXT *) element->GetRenderStyleForState( element->GetCurrentState() )->GetShape();
    
    text_shape->UpdateText( text );
}

void GRAPHIC_UI_TEXT_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * ) {
    
}