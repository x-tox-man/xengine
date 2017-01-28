//
//  GRAPHIC_UI_FRAME_LIST_ADAPTER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"


// TODO : Refactor this to inherit from a scrollView

GRAPHIC_UI_FRAME_LIST_ADAPTER::GRAPHIC_UI_FRAME_LIST_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template ) :
    GRAPHIC_UI_FRAME_ADAPTER(),
    Frame( frame ),
    UITemplate( ui_template ),
    VisibleItemsTable(),
    VisibleItemsCount( 0 ),
    Spacing(),
    TotalScrollOffset(CORE_MATH_VECTOR::Zero),
    CellDimension(CORE_MATH_VECTOR::Zero),
    OverallFrameDimension(CORE_MATH_VECTOR::Zero) {
    
}

GRAPHIC_UI_FRAME_LIST_ADAPTER::~GRAPHIC_UI_FRAME_LIST_ADAPTER() {
    
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnResize( GRAPHIC_UI_ELEMENT * item ) {
    
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnCollectionChanged() {
    
    OnLayoutItems(Frame);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnLayoutItems( GRAPHIC_UI_FRAME * frame ) {
    
    int itemsOffset = VisibleItemsCount;
    CellDimension = UITemplate->GetSize();
    VisibleItemsCount = CalculateItemsCount(frame);
    OverallFrameDimension = CalculateListViewDimension();
    
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
    
    UpdateOffsetAndCheckBounds(frame, CORE_MATH_VECTOR::Zero, true);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnDragged(GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & drag_offset) {
    
    UpdateOffsetAndCheckBounds(frame, drag_offset);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::OnScrolled(GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & scroll_offset) {
    
    UpdateOffsetAndCheckBounds(frame, scroll_offset);
}

void GRAPHIC_UI_FRAME_LIST_ADAPTER::UpdateOffsetAndCheckBounds( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force) {
    
    Spacing = GetSpacing();
    
    float scrollZone = (OverallFrameDimension.Y() - frame->GetSize().Y());
    bool scroll_changed = false;
    
    //if we can scroll
    if ( scrollZone > 0.0f ) {
        
        TotalScrollOffset.Y(fminf(scrollZone,(offset.Y() + TotalScrollOffset.Y())));
        
        scroll_changed = true;
    }
    
    if( scroll_changed || force ) {
        
        int base_offset = ceil(TotalScrollOffset.Y() / CellDimension.Y());
        
        CORE_MATH_VECTOR position_offset = TotalScrollOffset;
        
        for(int i = 0; i < VisibleItemsCount && i < GetItemsCount(); i++ ) {

            VisibleItemsTable[i]->SetPosition(position_offset);
            position_offset.Y(position_offset.Y() - (CellDimension.Y() +Spacing));
            ConfigureItemLayoutFor(base_offset++, VisibleItemsTable[i]);
        }
    }
}

CORE_MATH_VECTOR GRAPHIC_UI_FRAME_LIST_ADAPTER::CalculateListViewDimension() {
    
    return CellDimension * GetItemsCount();
}

int GRAPHIC_UI_FRAME_LIST_ADAPTER::CalculateItemsCount(GRAPHIC_UI_FRAME * frame) {
    
    return (int) fmin( ceil(frame->GetSize().Y() / CellDimension.Y()), GetItemsCount());
}
