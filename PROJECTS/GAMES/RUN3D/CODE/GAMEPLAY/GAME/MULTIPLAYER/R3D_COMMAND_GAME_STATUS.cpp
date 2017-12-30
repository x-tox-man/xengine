//
//  R3D_COMMAND_GAME_STATUS.cpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_COMMAND_GAME_STATUS.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_COMMAND_GAME_STATUS )
    XS_DEFINE_ClassMember( "Tick", int, Tick )
    XS_DEFINE_ClassMember( "PlayersUpdates", std::vector< R3D_COMMAND_PLAYER_UPDATE >, PlayersUpdates )
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
    
    auto players = ((R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::PTR) R3D_APP_PTR->GetGame()->GetDelegate())->GetPlayers();
    
    for ( int i = 0; i < players->size(); i++ ) {

        (*players)[i]->GetShip()->ApplyInputParamters( PlayersUpdates[i].Thrust, PlayersUpdates[i].Orientation );
    }
}
