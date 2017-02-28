//
//  GAMEPLAY_RULE_CHANCE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_CHANCE.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "MULTIPOLY_APPLICATION.h"

GAMEPLAY_RULE_CHANCE::GAMEPLAY_RULE_CHANCE() :
    GAMEPLAY_RULE() {
    
}

GAMEPLAY_RULE_CHANCE::~GAMEPLAY_RULE_CHANCE() {
    
}

void GAMEPLAY_RULE_CHANCE::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_CHANCE::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_CHANCE::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().DisplayNextChanceCard( cell, player );
}

bool GAMEPLAY_RULE_CHANCE::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    return true;
}
