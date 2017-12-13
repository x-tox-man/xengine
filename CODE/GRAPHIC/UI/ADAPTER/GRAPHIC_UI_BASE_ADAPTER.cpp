//
//  GRAPHIC_UI_BASE_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_BASE_ADAPTER.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_UI_FRAME.h"

GRAPHIC_UI_BASE_ADAPTER::GRAPHIC_UI_BASE_ADAPTER() {
    
}

GRAPHIC_UI_BASE_ADAPTER::~GRAPHIC_UI_BASE_ADAPTER() {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const CORE_DATA_UTF8_TEXT & text ) {
    
    GRAPHIC_TEXT * graphic_text = (GRAPHIC_TEXT * ) element->GetRenderStyleForState( element->GetCurrentState() )->GetShape();
    
    graphic_text->UpdateText( text );
}

void GRAPHIC_UI_BASE_ADAPTER::OnLayoutFrame( GRAPHIC_UI_FRAME * frame ) {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * ) {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnMove( GRAPHIC_UI_ELEMENT * ) {
    
}

CORE_MATH_VECTOR GRAPHIC_UI_BASE_ADAPTER::CalculateFrameContentDimension( GRAPHIC_UI_ELEMENT * element ) {
    
    CORE_MATH_VECTOR
        frame_rectangle,
        result;
    GRAPHIC_UI_FRAME
        * frame = (GRAPHIC_UI_FRAME *) element;
    
    std::vector<GRAPHIC_UI_ELEMENT *>::iterator it = frame->GetElementTable().begin();
    
    while (it != frame->GetElementTable().end() ) {
        
        auto elem = (*it);
        
        //TOP LEFT
        if ( frame_rectangle.X() > elem->GetPosition().X() - elem->GetPlacement().GetSize().X() * 0.5f )
        {
            frame_rectangle.X( elem->GetPosition().X() - elem->GetPlacement().GetSize().X() * 0.5f );
        }
        
        if ( frame_rectangle.Y() < elem->GetPosition().Y() + elem->GetPlacement().GetSize().Y() * 0.5f )
        {
            frame_rectangle.Y( elem->GetPosition().Y() + elem->GetPlacement().GetSize().Y() * 0.5f );
        }
        
        //BOTTOM RIGHT
        if ( frame_rectangle.Z() < elem->GetPosition().X() + elem->GetPlacement().GetSize().X() * 0.5f )
        {
            frame_rectangle.Z( elem->GetPosition().X() + elem->GetPlacement().GetSize().X() * 0.5f );
        }
        
        if ( frame_rectangle.W() > elem->GetPosition().Y() - elem->GetPlacement().GetSize().Y() * 0.5f )
        {
            frame_rectangle.W( elem->GetPosition().Y() - elem->GetPlacement().GetSize().Y() * 0.5f );
        }
        
        it++;
    }
    
    result.X( ( frame_rectangle.Z() - frame_rectangle.X() ) * 0.5f);
    result.Y( ( frame_rectangle.W() - frame_rectangle.Y() ) * 0.5f );
    result.Z( frame_rectangle.Z() - frame_rectangle.X() );
    result.W( frame_rectangle.Y() - frame_rectangle.W() );
    
    return result;
}

void GRAPHIC_UI_BASE_ADAPTER::OnDragEnd() {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnDragged(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) {
    
}

void GRAPHIC_UI_BASE_ADAPTER::OnScrolled(GRAPHIC_UI_ELEMENT *, const CORE_MATH_VECTOR & ) {
    
}
