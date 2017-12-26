//
//  R3D_COMMAND_PLAYER_UPDATE.cpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_COMMAND_PLAYER_UPDATE.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_COMMAND_PLAYER_UPDATE )
    XS_DEFINE_ClassMember( "Tick", int, Tick )
    XS_DEFINE_ClassMember( "Thrust", float, Thrust )
    XS_DEFINE_ClassMember( "Orientation", float, Orientation )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation( R3D_COMMAND_PLAYER_UPDATE, GAMEPLAY_ACTION_TYPE_Custom_1 )

R3D_COMMAND_PLAYER_UPDATE::R3D_COMMAND_PLAYER_UPDATE() :
    GAMEPLAY_ACTION(),
    Tick( 0 ) {
    
}

R3D_COMMAND_PLAYER_UPDATE::R3D_COMMAND_PLAYER_UPDATE( const R3D_COMMAND_PLAYER_UPDATE & other ) :
    GAMEPLAY_ACTION(),
    Tick( 0 ) {
    
    abort();
}

void R3D_COMMAND_PLAYER_UPDATE::Apply() {
    
    abort();
}
