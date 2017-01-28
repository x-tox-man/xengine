//
//  APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_hpp
#define APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_CLIENT.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_GAME_PLAYER_LIST_ADAPTER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_MULTIPLAYER_GAME_CONFIGURATION, GRAPHIC_UI_FRAME )

APPLICATION_MULTIPLAYER_GAME_CONFIGURATION();

virtual void Initialize() override;
virtual void Update( const float) override;

NETWORK_GAME_PLAYER_LIST_ADAPTER * GetPlayersListAdapter() {
    
    return PlayersListAdapter;
}

std::vector< NETWORK_PLAYER * > & GetPlayersList() {
    
    return PlayersList;
}

private :

NETWORK_GAME_PLAYER_LIST_ADAPTER
    * PlayersListAdapter;
std::vector< NETWORK_PLAYER * >
    PlayersList;
APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER
    * Presenter;

XS_CLASS_END

#endif /* APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_hpp */
