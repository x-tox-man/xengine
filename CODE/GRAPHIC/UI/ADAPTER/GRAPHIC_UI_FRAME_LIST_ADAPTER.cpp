//
//  GRAPHIC_UI_FRAME_LIST_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"


// TODO : Refactor this to inherit from a scrollView

GRAPHIC_UI_FRAME_LIST_ADAPTER::GRAPHIC_UI_FRAME_LIST_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template ) :
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER(),
    Frame( frame ),
    UITemplate( ui_template ),
    VisibleItemsTable(),
    VisibleItemsCount( 0 ),
    Spacing(),
    CellDimension(CORE_MATH_VECTOR::Zero) {
    
}

GRAPHIC_UI_FRAME_LIST_ADAPTER::~GRAPHIC_UI_FRAME_LIST_ADAPTER() {
    
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * item ) {
    
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnCollectionChanged() {
    
    OnLayoutFrame(Frame);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnLayoutFrame( GRAPHIC_UI_FRAME * frame ) {
    
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnLayoutFrame( frame );
    
    int itemsOffset = VisibleItemsCount;
    CellDimension = UITemplate->GetSize();
    VisibleItemsCount = CalculateVisibleItemsCount(frame);
    
    itemsOffset = VisibleItemsCount - itemsOffset;
    
    if ( itemsOffset ) {
        VisibleItemsTable.clear();
        VisibleItemsTable.resize(VisibleItemsCount);
    }
    
    if ( itemsOffset > 0)
    {
        ((GRAPHIC_UI_FRAME*)frame)->RemoveObjects();
        
        for (int i = 0; i < VisibleItemsCount; i++) {
            
            if( VisibleItemsTable[i] == NULL ) {
                
                VisibleItemsTable[i] = UITemplate->Copy();
                ((GRAPHIC_UI_FRAME*)frame)->AddObject(VisibleItemsTable[i]);
            }
        }
    }
    
    UpdateOffset(frame, CORE_MATH_VECTOR::Zero, true);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnDragEnd() {
    
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnDragged(GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & drag_offset) {
    
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnDragged( frame, drag_offset );
    
    UpdateOffset(frame, drag_offset);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnScrolled(GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & scroll_offset) {
 
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::OnScrolled(frame, scroll_offset);
    
    UpdateOffset(frame, scroll_offset);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force) {
    
    Spacing = GetSpacing();
    
    bool scroll_changed = false;
    
    //if we can scroll
    if ( GetScrollZone().Y() > 0.0f ) {
        
        GetTotalScrollOffset().Y(fminf(GetScrollZone().Y(),(offset.Y() + GetTotalScrollOffset().Y())));
        
        scroll_changed = true;
    }
    
    if( scroll_changed || force ) {
        
        int base_offset = ceil(GetTotalScrollOffset().Y() / CellDimension.Y());
        
        CORE_MATH_VECTOR position_offset = GetTotalScrollOffset();
        
        for(int i = 0; i < VisibleItemsCount && i < GetItemsCount(); i++ ) {

            VisibleItemsTable[i]->SetPosition(position_offset);
            position_offset.Y(position_offset.Y() - (CellDimension.Y() +Spacing));
            ConfigureItemLayoutFor(base_offset++, VisibleItemsTable[i]);
        }
    }
}

CORE_MATH_VECTOR GRAPHIC_UI_FRAME_LIST_ADAPTER::CalculateFrameContentDimension( GRAPHIC_UI_ELEMENT * ) {
    
    return CellDimension * GetItemsCount();
}

int GRAPHIC_UI_FRAME_LIST_ADAPTER::CalculateVisibleItemsCount(GRAPHIC_UI_FRAME * frame) {
    
    return (int) fmin( ceil(frame->GetSize().Y() / CellDimension.Y()), GetItemsCount());
}
