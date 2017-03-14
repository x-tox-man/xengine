//
//  MULTIPLAYER_GAME_HUD_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "MULTIPLAYER_GAME_HUD_PRESENTER.h"
#include "MULTIPOLY_APPLICATION.h"
#include "GAMEPLAY_ACTION_COMMAND_START_GAME.h"

MULTIPLAYER_GAME_HUD_PRESENTER::MULTIPLAYER_GAME_HUD_PRESENTER() :
    GAME_HUD_PRESENTER() {

    CORE_HELPERS_CALLBACK
        callback( &Wrapper<MULTIPLAYER_GAME_HUD_PRESENTER, &MULTIPLAYER_GAME_HUD_PRESENTER::GameStartedServer>, this );
    
    if ( ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetServer() != NULL ) {
        
        std::vector< GAME_PLAYER_MODEL > players;
        
        std::array<NETWORK_PLAYER *, THIS_GAME_MAX_NETWORK_PLAYER_SIZE> * netork_players = NULL;
        
        netork_players = &((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetServer()->GetPlayerTable();
        
        for (int i = 0; i < THIS_GAME_MAX_NETWORK_PLAYER_SIZE; i++  ) {
            
            if ( (*netork_players)[i] != NULL ) {
                
                GAME_PLAYER_MODEL mod;
                mod.Name = (*netork_players)[i]->GetName();
                mod.Color = CORE_COLOR_White;
                mod.IsHuman = true;
                mod.IsMultiplayer = !( (*netork_players)[i]->GetUniqueId() == ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId() );
                players.push_back( mod );
            }
        }
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
            CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
                ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().SetPlayers( players );
            CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
        
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetServer()->SetGameStartedCallback( callback );
    }
}

MULTIPLAYER_GAME_HUD_PRESENTER::~MULTIPLAYER_GAME_HUD_PRESENTER() {
    
}

void MULTIPLAYER_GAME_HUD_PRESENTER::Configure() {
    
    GAME_HUD_PRESENTER::Configure();
}

void MULTIPLAYER_GAME_HUD_PRESENTER::GameStartedServer() {
    
    ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().Start();
}
