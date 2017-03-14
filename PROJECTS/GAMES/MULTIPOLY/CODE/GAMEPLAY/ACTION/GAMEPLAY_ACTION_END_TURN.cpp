//
//  GAMEPLAY_ACTION_END_TURN.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 11/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_ACTION_END_TURN.h"
#include "GAMEPLAY_PLAYER.h"
#include "MULTIPOLY_APPLICATION.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_END_TURN )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_END_TURN, GAMEPLAY_ACTION_TYPE_Custom_1 )

GAMEPLAY_ACTION_END_TURN::GAMEPLAY_ACTION_END_TURN() :
    GAMEPLAY_ACTION() {
    
}

GAMEPLAY_ACTION_END_TURN::~GAMEPLAY_ACTION_END_TURN() {
    
}

void GAMEPLAY_ACTION_END_TURN::Apply() {
    
    auto state_machine = &((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().GetCurrentPlayer()->GetStateMachine();
    
    state_machine->DispatchEvent( GAMEPLAY_PLAYER::MULTIPLAYER_END_TURN() );
}
