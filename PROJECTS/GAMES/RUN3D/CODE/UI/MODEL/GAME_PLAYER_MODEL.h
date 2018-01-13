//
//  GAME_PLAYER_MODEL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 25/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef GAME_PLAYER_MODEL_hpp
#define GAME_PLAYER_MODEL_hpp

#include "NETWORK_PLAYER.h"
#include "R3D_PLAYER.h"

XS_CLASS_BEGIN_WITH_COPY( GAME_PLAYER_MODEL )

    GAME_PLAYER_MODEL();
    GAME_PLAYER_MODEL( NETWORK_PLAYER::PTR player, R3D_PLAYER::PTR game_player );
    ~GAME_PLAYER_MODEL() {
        
    }

    void operator = ( const GAME_PLAYER_MODEL & other ) {
        
        NetworkPlayer = other.NetworkPlayer;
    }

    NETWORK_PLAYER::PTR
        NetworkPlayer;
    R3D_PLAYER::PTR
        GamePlayer;
    CORE_HELPERS_UNIQUE_IDENTIFIER
        Identifier;

XS_CLASS_END

#endif /* GAME_PLAYER_MODEL_hpp */
