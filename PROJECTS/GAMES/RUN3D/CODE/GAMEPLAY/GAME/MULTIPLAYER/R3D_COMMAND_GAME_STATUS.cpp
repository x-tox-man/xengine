//
//  R3D_COMMAND_GAME_STATUS.cpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_COMMAND_GAME_STATUS.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_COMMAND_GAME_STATUS )
    XS_DEFINE_ClassMember( "Tick", int, Tick )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation( R3D_COMMAND_GAME_STATUS, GAMEPLAY_ACTION_TYPE_Custom_1 )

R3D_COMMAND_GAME_STATUS::R3D_COMMAND_GAME_STATUS() :
    GAMEPLAY_ACTION(),
    Tick( 0 ) {
    
}

R3D_COMMAND_GAME_STATUS::R3D_COMMAND_GAME_STATUS( const R3D_COMMAND_GAME_STATUS & other ) :
    GAMEPLAY_ACTION(),
    Tick( 0 ) {
    
        abort();
}

void R3D_COMMAND_GAME_STATUS::Apply() {
    
    abort();
}
