//
//  NETWORK_GAME_INFO.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "NETWORK_GAME_INFO.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( NETWORK_GAME_INFO )
    XS_DEFINE_ClassMemberArray( "GameId", char, (char **) &GameId, (int)strlen( GameId ) )
    XS_DEFINE_ClassMemberArray( "GameStartedTime", char, (char **) &GameStartedTime, (int)strlen( GameStartedTime ) )
XS_END_INTERNAL_MEMORY_LAYOUT

NETWORK_GAME_INFO::NETWORK_GAME_INFO() :
    GameId(NULL),
    GameStartedTime(NULL) {
    
}

NETWORK_GAME_INFO::NETWORK_GAME_INFO(const char * game_id, const char * started_time ) {
    
    CORE_DATA_COPY_STRING( GameId, game_id );
    CORE_DATA_COPY_STRING( GameStartedTime, started_time );
}

NETWORK_GAME_INFO::~NETWORK_GAME_INFO() {
    
}
