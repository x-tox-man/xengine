//
//  GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/01/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"

GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER::GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template ) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, ui_template ) {
    
}

void GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER::UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force ) {
    
    float spacing = GetSpacing();
    
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::UpdateOffset( frame, offset, force );
    
    if ( !IsHorizontal() ) {
        
        int base_offset = ceil(GetTotalScrollOffset().Y() / GetCellDimension().Y());
        
        if ( BaseIndex != base_offset ) {
            
            BaseIndex = base_offset;
            
            OnBaseIndexChanged( BaseIndex );
        }
        
        const CORE_MATH_VECTOR & ttl_off = GetTotalScrollOffset();
        CORE_MATH_VECTOR position_offset = ttl_off;
        
        position_offset.Y( GetCellDimension().Y() );
        CORE_MATH_VECTOR to( 0.0f, GetCellDimension().Y() * base_offset );
        
        auto fr = ( GRAPHIC_UI_FRAME * ) GetFrame();
        fr->SetOffset( to );
        
        for(int i = 0; i < GetVisibleItemsCount() && i < GetItemsCount(); i++ ) {
            
            GetVisibleItemsTable()[i]->SetPosition(position_offset);
            position_offset.Y(position_offset.Y() - ( GetCellDimension().Y() + spacing));
            ConfigureItemLayoutFor( base_offset++, GetVisibleItemsTable()[i]);
        }
    }
    else {
        
        int base_offset = ceil(GetTotalScrollOffset().X() / GetCellDimension().X());
        
        if ( BaseIndex != base_offset ) {
            
            BaseIndex = base_offset;
            
            OnBaseIndexChanged( BaseIndex );
        }
        
        const CORE_MATH_VECTOR & ttl_off = GetTotalScrollOffset();
        CORE_MATH_VECTOR position_offset = ttl_off;
        
        position_offset.X( GetCellDimension().X() );
        CORE_MATH_VECTOR to( GetCellDimension().X() * base_offset, 0.0f );

        auto fr = ( GRAPHIC_UI_FRAME * ) GetFrame();
        fr->SetOffset( to );
        
        for(int i = 0; i < GetVisibleItemsCount() && i < GetItemsCount(); i++ ) {
            
            GetVisibleItemsTable()[i]->SetPosition(position_offset);
            position_offset.X( position_offset.X() - ( GetCellDimension().X() + spacing ) );
            ConfigureItemLayoutFor( base_offset++, GetVisibleItemsTable()[i] );
        }
    }
}
