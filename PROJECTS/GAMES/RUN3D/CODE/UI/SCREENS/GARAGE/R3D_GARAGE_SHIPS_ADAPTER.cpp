//
//  R3D_GARAGE_SHIPS_ADAPTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GARAGE_SHIPS_ADAPTER.h"
#include "GRAPHIC_UI_HELPER.h"

R3D_GARAGE_SHIPS_ADAPTER::R3D_GARAGE_SHIPS_ADAPTER( GRAPHIC_UI_FRAME * frame ) :
    GRAPHIC_UI_FRAME_LIST_ADAPTER( frame, CreateTemplate() ) {
    
}

R3D_GARAGE_SHIPS_ADAPTER::~R3D_GARAGE_SHIPS_ADAPTER() {
    
}

int R3D_GARAGE_SHIPS_ADAPTER::GetItemsCount() {
    
    return 10;
}

int R3D_GARAGE_SHIPS_ADAPTER::GetSpacing() {
    
    return 20;
}

void R3D_GARAGE_SHIPS_ADAPTER::ConfigureItemLayoutFor(int , GRAPHIC_UI_ELEMENT *) {
    
}

GRAPHIC_UI_ELEMENT::PTR R3D_GARAGE_SHIPS_ADAPTER::CreateTemplate() {
    
    GRAPHIC_UI_FRAME::PTR template_element = GRAPHIC_UI_HELPER::CreateFrame( "ship_template" );
    
    return template_element;
}
