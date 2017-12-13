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
    TotalScrollOffset(CORE_MATH_VECTOR::Zero),
    ScrollZone(CORE_MATH_VECTOR::Zero),
    DragOffset(CORE_MATH_VECTOR::Zero),
    OverallFrameDimension(CORE_MATH_VECTOR::Zero) {
    
}

GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::~GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER() {
    
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * ) {
    
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnLayoutFrame( GRAPHIC_UI_FRAME * frame ) {
    
    OverallFrameDimension = CalculateFrameContentDimension( (GRAPHIC_UI_ELEMENT *) frame );
    
    ScrollZone.Y( OverallFrameDimension.W() - frame->GetSize().Y());
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnDragEnd() {
    
    DragOffset = CORE_MATH_VECTOR::Zero;
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnDragged(GRAPHIC_UI_ELEMENT * element, const CORE_MATH_VECTOR & offset ) {
    
    if ( DragOffset == CORE_MATH_VECTOR::Zero ) {
        
        DragOffset.Y( offset.Y() );
    }
    
    CORE_MATH_VECTOR current_offset(0.0f, offset.Y() - DragOffset.Y() );
    
    printf( "%f\n", PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().GetPreviousScreenCoordinates().Y() );
    
    UpdateOffset( element, current_offset, false );
    
    DragOffset.Y( offset.Y() );
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnScrolled(GRAPHIC_UI_ELEMENT * element, const CORE_MATH_VECTOR & offset ) {
    
    UpdateOffset( element, offset, false );
}

void GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force) {
    
    if ( ScrollZone.Y() > 0.0f ) {
        
        auto fr = ( GRAPHIC_UI_FRAME * ) frame;
        
        TotalScrollOffset.Y(fminf(ScrollZone.Y(),(offset.Y() + TotalScrollOffset.Y())));
        
        fr->SetOffset( TotalScrollOffset );
    }
}
