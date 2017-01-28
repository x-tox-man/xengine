//
//  GRAPHIC_UI_BASE_ADAPTER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_BASE_ADAPTER.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_TEXT.h"

GRAPHIC_UI_BASE_ADAPTER::GRAPHIC_UI_BASE_ADAPTER() {
    
}

GRAPHIC_UI_BASE_ADAPTER::~GRAPHIC_UI_BASE_ADAPTER() {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const char * text ) {
    
    GRAPHIC_TEXT * graphic_text = (GRAPHIC_TEXT * ) element->GetRenderStyleForState( element->GetCurrentState() )->GetShape();
    
    graphic_text->UpdateText( text );
}

void GRAPHIC_UI_BASE_ADAPTER::OnLayoutItems( GRAPHIC_UI_FRAME * ) {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * ) {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnMove( GRAPHIC_UI_ELEMENT * ) {
    
}
