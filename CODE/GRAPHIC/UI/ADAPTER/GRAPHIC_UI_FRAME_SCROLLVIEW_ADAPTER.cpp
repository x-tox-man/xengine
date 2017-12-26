//
//  GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"

GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER() :
    TotalScrollOffset( CORE_MATH_VECTOR::Zero ),
    ScrollZone( CORE_MATH_VECTOR::Zero ),
    DragOffset( CORE_MATH_VECTOR::Zero ),
    OverallFrameDimension( CORE_MATH_VECTOR::Zero ),
    Horizontal( false ){
    
}

GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::~GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER() {
    
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * ) {
    
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnLayoutFrame( GRAPHIC_UI_FRAME * frame ) {
    
    OverallFrameDimension = CalculateFrameContentDimension( (GRAPHIC_UI_ELEMENT *) frame );
    
    if ( Horizontal ) {
        
        ScrollZone.X( OverallFrameDimension.X() - frame->GetSize().X());
    }
    else {
        
        ScrollZone.Y( OverallFrameDimension.Y() - frame->GetSize().Y());
    }
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnDragEnd() {
    
    DragOffset = CORE_MATH_VECTOR::Zero;
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnDragged(GRAPHIC_UI_ELEMENT * element, const CORE_MATH_VECTOR & offset ) {
    
    if ( DragOffset == CORE_MATH_VECTOR::Zero ) {
        
        if (  Horizontal ) {
            
            DragOffset.X( offset.X() );
            DragOffset.Y( 0.0f );
        }
        else {
            
            DragOffset.X( 0.0f );
            DragOffset.Y( offset.Y() );
        }
    }
    
    if (  Horizontal ) {
        
        CORE_MATH_VECTOR current_offset(offset.X() - DragOffset.X(), 0.0f );
        
        UpdateOffset( element, current_offset, false );
        
        DragOffset.X( offset.X() );
    }
    else {
        
        CORE_MATH_VECTOR current_offset( 0.0f, offset.Y() - DragOffset.Y() );
        
        UpdateOffset( element, current_offset, false );
        
        DragOffset.Y( offset.Y() );
    }
    
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnScrolled(GRAPHIC_UI_ELEMENT * element, const CORE_MATH_VECTOR & offset ) {
    
    UpdateOffset( element, offset, false );
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force) {
    
    if (  Horizontal ) {
        
        if ( ScrollZone.X() > 0.0f ) {
            
            auto fr = ( GRAPHIC_UI_FRAME * ) frame;
            
            TotalScrollOffset.X(fminf(ScrollZone.X(),(offset.X() + TotalScrollOffset.X())));
            
            fr->SetOffset( TotalScrollOffset );
        }
    }
    else {
        
        if ( ScrollZone.Y() > 0.0f ) {
            
            auto fr = ( GRAPHIC_UI_FRAME * ) frame;
            
            TotalScrollOffset.Y(fminf(ScrollZone.Y(),(offset.Y() + TotalScrollOffset.Y())));
            
            fr->SetOffset( TotalScrollOffset );
        }
    }
}
