//
//  R3D_PLAYER_MODIFIER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 7/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_PLAYER_MODIFIER.h"
#include "R3D_PLAYER.h"

R3D_PLAYER_MODIFIER::R3D_PLAYER_MODIFIER() :
    ModifierValue( 1.0f ) ,
    ModifierIdentifier() {
    
}

void R3D_PLAYER_MODIFIER::Apply( R3D_PLAYER * player ) {
    
    abort();
}

void R3D_PLAYER_MODIFIER::Discard( R3D_PLAYER * player ) {
    
    abort();
}
