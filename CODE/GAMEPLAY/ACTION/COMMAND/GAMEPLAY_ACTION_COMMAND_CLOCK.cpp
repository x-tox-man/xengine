//
//  GAMEPLAY_ACTION_COMMAND_CLOCK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 7/02/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_ACTION_COMMAND_CLOCK.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_COMMAND_CLOCK )
    XS_DEFINE_ClassMember( "Player", NETWORK_PLAYER, &Player )
    XS_DEFINE_ClassMember( "SentTick", unsigned int, SentTick )
    XS_DEFINE_ClassMember( "ReceivedTick", unsigned int, ReceivedTick )
    XS_DEFINE_ClassMember( "AveragePing", unsigned int, AveragePing )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_COMMAND_CLOCK, GAMEPLAY_ACTION_TYPE_Clock)

GAMEPLAY_ACTION_COMMAND_CLOCK::GAMEPLAY_ACTION_COMMAND_CLOCK() :
    GAMEPLAY_ACTION(),
    Player(),
    SentTick( 0 ),
    ReceivedTick( 0 ),
    AveragePing( 0 ) {
    
}

GAMEPLAY_ACTION_COMMAND_CLOCK::GAMEPLAY_ACTION_COMMAND_CLOCK( const GAMEPLAY_ACTION_COMMAND_CLOCK & other) :
    GAMEPLAY_ACTION(),
    Player(),
    SentTick( other.SentTick ),
    ReceivedTick( other.ReceivedTick ),
    AveragePing( other.AveragePing ) {
    
    CORE_RUNTIME_Abort();
}

GAMEPLAY_ACTION_COMMAND_CLOCK::GAMEPLAY_ACTION_COMMAND_CLOCK( NETWORK_PLAYER * player ) :
    GAMEPLAY_ACTION(),
    Player( player ),
    SentTick( 0 ),
    ReceivedTick( 0 ),
    AveragePing( 0 ) {
    
}

GAMEPLAY_ACTION_COMMAND_CLOCK::~GAMEPLAY_ACTION_COMMAND_CLOCK() {
    
}

void GAMEPLAY_ACTION_COMMAND_CLOCK::Apply() {
    
}
