//
//  R3D_PLAYER_SHIP_GEAR.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER_SHIP_GEAR_STAGE.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_PLAYER_SHIP_GEAR_STAGE )
    XS_DEFINE_ClassMember( "Power", float, Power )
    XS_DEFINE_ClassMember( "Torque", float, Torque )
XS_END_INTERNAL_MEMORY_LAYOUT

R3D_PLAYER_SHIP_GEAR_STAGE::R3D_PLAYER_SHIP_GEAR_STAGE() {
    
}

R3D_PLAYER_SHIP_GEAR_STAGE::~R3D_PLAYER_SHIP_GEAR_STAGE() {
    
}
