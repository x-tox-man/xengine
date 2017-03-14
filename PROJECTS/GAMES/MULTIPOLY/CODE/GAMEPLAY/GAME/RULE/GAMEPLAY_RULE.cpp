//
//  GAMEPLAY_RULE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "MULTIPOLY_APPLICATION.h"

GAMEPLAY_RULE::GAMEPLAY_RULE() {
    
}

GAMEPLAY_RULE::~GAMEPLAY_RULE() {
    
}

template <typename  __ACTION__>
void GAMEPLAY_RULE::CreateAndSendNetworkCommand(GAMEPLAY_RULE * rule) {
    
    auto command = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand< __ACTION__ >( rule );
    ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetNetworkManager().SendCommand( command );
}
