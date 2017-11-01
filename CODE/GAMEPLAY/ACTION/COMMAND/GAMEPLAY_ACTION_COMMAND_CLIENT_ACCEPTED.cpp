//
//  APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED )
    XS_DEFINE_ClassMember(NETWORK_PLAYER, &Player )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED, GAMEPLAY_ACTION_TYPE_ClientAccepted)

GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED() :
    GAMEPLAY_ACTION(),
    Player() {
    
}

GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED( const GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED & other) :
GAMEPLAY_ACTION(),
Player() {
    
    abort();
}

GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED( NETWORK_PLAYER * player ) :
    GAMEPLAY_ACTION(),
    Player( player ) {
    
}

GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::~GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED() {
    
}

void GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::Apply() {
    
    PlayerAcceptedCallback( Player );
}

CORE_HELPERS_CALLBACK_1< NETWORK_PLAYER * >
    GAMEPLAY_ACTION_COMMAND_CLIENT_ACCEPTED::PlayerAcceptedCallback;
