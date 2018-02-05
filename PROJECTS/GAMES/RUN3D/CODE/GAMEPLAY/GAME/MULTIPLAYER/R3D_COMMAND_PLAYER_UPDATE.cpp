
//
//  R3D_COMMAND_PLAYER_UPDATE.cpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_COMMAND_PLAYER_UPDATE.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_COMMAND_PLAYER_UPDATE )
    XS_DEFINE_ClassMember( "Tick", unsigned int, Tick )
    XS_DEFINE_ClassMember( "Thrust", float, Thrust )
    XS_DEFINE_ClassMember( "Orientation", float, Orientation )
    XS_DEFINE_ClassMember( "UniqueId", CORE_HELPERS_UNIQUE_IDENTIFIER, UniqueId )
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( R3D_COMMAND_PLAYER_UPDATE )
XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( R3D_COMMAND_PLAYER_UPDATE, CORE_HELPERS_UNIQUE_IDENTIFIER )

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
    
    ((R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::PTR) R3D_APP_PTR->GetGame()->GetDelegate())->SetPlayerUpdate( this );
}

void R3D_COMMAND_PLAYER_UPDATE::Set( const R3D_COMMAND_PLAYER_UPDATE & other ) {
    
    Tick = other.Tick;
    Thrust = other.Thrust;
    Orientation = other.Orientation;
    UniqueId = other.UniqueId;
}

void R3D_COMMAND_PLAYER_UPDATE::operator=(const R3D_COMMAND_PLAYER_UPDATE &other) {
    
    Tick = other.Tick;
    Thrust = other.Thrust;
    Orientation = other.Orientation;
    UniqueId = other.UniqueId;
}
