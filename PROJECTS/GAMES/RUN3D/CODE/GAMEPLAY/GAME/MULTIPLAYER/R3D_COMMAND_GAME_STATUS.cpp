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

typedef std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_COMMAND_PLAYER_UPDATE > PLAYER_UPDATE_TYPE;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_COMMAND_GAME_STATUS )
    XS_DEFINE_ClassMember( "Tick", unsigned int, Tick )
    XS_DEFINE_ClassMember( "PlayersUpdates", PLAYER_UPDATE_TYPE, PlayersUpdates )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation( R3D_COMMAND_GAME_STATUS, GAMEPLAY_ACTION_TYPE_Custom_1 )

R3D_COMMAND_GAME_STATUS::R3D_COMMAND_GAME_STATUS() :
    GAMEPLAY_ACTION(),
    Tick( 0 ),
    PlayersUpdates() {
    
}

R3D_COMMAND_GAME_STATUS::R3D_COMMAND_GAME_STATUS( const R3D_COMMAND_GAME_STATUS & other ) :
    GAMEPLAY_ACTION(),
    Tick( 0 ),
    PlayersUpdates() {
    
    abort();
}

void R3D_COMMAND_GAME_STATUS::Apply() {
    
    auto players = ((R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::PTR) R3D_APP_PTR->GetGame()->GetDelegate())->GetPlayers();
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_COMMAND_PLAYER_UPDATE >::iterator it = PlayersUpdates.begin();
    
    while ( it != PlayersUpdates.end() ) {
        
        
        (*players)[it->first]->GetShip()->ApplyInputParamters( it->second.Thrust, it->second.Orientation );
        
        it++;
    }
}
