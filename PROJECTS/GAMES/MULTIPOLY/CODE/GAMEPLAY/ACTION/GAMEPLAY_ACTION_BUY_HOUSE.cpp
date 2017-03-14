//
//  GAMEPLAY_ACTION_BUY_HOUSE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 11/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_ACTION_BUY_HOUSE.h"
#include "GAMEPLAY_PLAYER.h"
#include "MULTIPOLY_APPLICATION.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_BUY_HOUSE )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_BUY_HOUSE, GAMEPLAY_ACTION_TYPE_Custom_3 )

GAMEPLAY_ACTION_BUY_HOUSE::GAMEPLAY_ACTION_BUY_HOUSE() :
    GAMEPLAY_ACTION() {
    
}

GAMEPLAY_ACTION_BUY_HOUSE::~GAMEPLAY_ACTION_BUY_HOUSE() {
    
}

void GAMEPLAY_ACTION_BUY_HOUSE::Apply() {
    
    auto state_machine = &((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().GetCurrentPlayer()->GetStateMachine();
    
    state_machine->DispatchEvent( GAMEPLAY_PLAYER::MULTIPLAYER_BUY_HOUSE() );
}
