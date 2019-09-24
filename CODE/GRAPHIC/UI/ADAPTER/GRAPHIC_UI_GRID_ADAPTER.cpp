//
//  GRAPHIC_UI_GRID_ADAPTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/01/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_GRID_ADAPTER.h"
#include "GRAPHIC_UI_FRAME.h"

GRAPHIC_UI_GRID_ADAPTER::GRAPHIC_UI_GRID_ADAPTER( GRAPHIC_UI_FRAME * frame, GRAPHIC_UI_ELEMENT * ui_template ) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, ui_template ),
    LineItemCount( 0 ){
    
}

GRAPHIC_UI_GRID_ADAPTER::~GRAPHIC_UI_GRID_ADAPTER() {
    
}

void GRAPHIC_UI_GRID_ADAPTER::UpdateOffset( GRAPHIC_UI_ELEMENT * frame, const CORE_MATH_VECTOR & offset, bool force ) {
    
    float spacing = GetSpacing();
    
    ComputeLineItemCount();
    
    GRAPHIC_UI_FRAME_SCROLLVIEW_ADAPTER::UpdateOffset( frame, offset, force );
    
    if ( IsHorizontal() ) {
        
        CORE_RUNTIME_Abort();
    }
    else {
        
        int
            i = 0,
            base_offset = ceil(GetTotalScrollOffset().X() / GetCellDimension().X());
        
        const CORE_MATH_VECTOR & ttl_off = GetTotalScrollOffset();
        CORE_MATH_VECTOR position_offset = ttl_off;
        
        position_offset.X( - GetFrame()->GetPlacement().GetSize().X() * 0.5 + GetCellDimension().X() - spacing );
        CORE_MATH_VECTOR to( GetCellDimension().X() * base_offset, 0.0f );
        
        auto fr = ( GRAPHIC_UI_FRAME * ) GetFrame();
        fr->SetOffset( to );
        
        while ( i < GetItemsCount() && i < GetVisibleItemsTable().size() ) {
            
            for (int j = 0; j < LineItemCount && i < GetVisibleItemsTable().size(); j++ ) {
                
                GetVisibleItemsTable()[i]->SetPosition( position_offset );
                position_offset.X( position_offset.X() + ( GetCellDimension().X() + spacing ) );
                ConfigureItemLayoutFor( base_offset++, GetVisibleItemsTable()[i] );
                
                i++;
            }
            
            position_offset.X( - GetFrame()->GetPlacement().GetSize().X() * 0.5 + GetCellDimension().X() - spacing );
            position_offset.Y( position_offset.Y() - spacing - GetCellDimension().Y() );
        }
    }
}

void GRAPHIC_UI_GRID_ADAPTER::ComputeLineItemCount() {
    
    LineItemCount = GetFrame()->GetSize().X() / (GetSpacing() + GetCellDimension().X() );
}

int GRAPHIC_UI_GRID_ADAPTER::CalculateVisibleItemsCount( GRAPHIC_UI_FRAME * frame ) {
    
    return 10;
}
