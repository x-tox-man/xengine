//
//  GAME_PLAYER_MODEL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 25/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "GAME_PLAYER_MODEL.h"

GAME_PLAYER_MODEL::GAME_PLAYER_MODEL() :
    NetworkPlayer( NULL ),
    GamePlayer( NULL ) {
    
}

GAME_PLAYER_MODEL::GAME_PLAYER_MODEL( NETWORK_PLAYER::PTR player, R3D_PLAYER::PTR game_player ) :
    NetworkPlayer( player ),
    GamePlayer( game_player ) {
    
}

GAME_PLAYER_MODEL::GAME_PLAYER_MODEL( const GAME_PLAYER_MODEL & other ) :
    NetworkPlayer( other.NetworkPlayer ),
    GamePlayer( other.GamePlayer ){
    
}
