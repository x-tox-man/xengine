//
//  R3D_GARAGE_SHIPS_ADAPTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GARAGE_SHIPS_ADAPTER.h"
#include "GRAPHIC_UI_HELPER.h"
#include "UI_GARAGE_SHIP_CELL.h"
#include "UI_GARAGE.h"
#include "R3D_GAUGE.h"
#include "GRAPHIC_UI_SYSTEM.h"

R3D_GARAGE_SHIPS_ADAPTER::R3D_GARAGE_SHIPS_ADAPTER( GRAPHIC_UI_FRAME * frame ) :
    GRAPHIC_UI_FRAME_LIST_STEPPER_ADAPTER( frame, CreateTemplate() ),
    PlayerShips( NULL ) {
    
}

R3D_GARAGE_SHIPS_ADAPTER::~R3D_GARAGE_SHIPS_ADAPTER() {
    
}

int R3D_GARAGE_SHIPS_ADAPTER::GetItemsCount() {
    
    if ( PlayerShips ) {
        return (int) PlayerShips->size();
    }
    
    return 0;
}

int R3D_GARAGE_SHIPS_ADAPTER::GetSpacing() {
    
    return 64;
}

void R3D_GARAGE_SHIPS_ADAPTER::ConfigureItemLayoutFor( int row, GRAPHIC_UI_ELEMENT * item) {
    
    UI_GARAGE_SHIP_CELL * cell = (UI_GARAGE_SHIP_CELL*) item;
}

GRAPHIC_UI_ELEMENT::PTR R3D_GARAGE_SHIPS_ADAPTER::CreateTemplate() {
    
    GRAPHIC_UI_FRAME::PTR template_element = GRAPHIC_UI_HELPER::CreateFrame( "ship_template" );
    
    return template_element;
}

void R3D_GARAGE_SHIPS_ADAPTER::OnBaseIndexChanged( int index ) {
    
    if ( index > 0 ) {
        
        auto frame = (R3D_UI_FRAME::PTR) GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().GetCurrentNavigationItem()->GetFrame();
        auto stats = (GRAPHIC_UI_FRAME::PTR) frame->GetObjectForIdentifier( UI_GARAGE::Stats );
        auto g1 = (R3D_GAUGE::PTR) stats->GetObjectAtIndex( 0 );
        auto g2 = (R3D_GAUGE::PTR) stats->GetObjectAtIndex( 1 );
        auto g3 = (R3D_GAUGE::PTR) stats->GetObjectAtIndex( 2 );
        
        g1->SetPercentAnimated( (rand() % 100 ) * 0.01f );
        g2->SetPercentAnimated( (rand() % 100 ) * 0.01f );
        g3->SetPercentAnimated( (rand() % 100 ) * 0.01f );
    }
}
