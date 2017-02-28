//
//  GAMEPLAY_RULE_CAISSE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_CAISSE.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "MULTIPOLY_APPLICATION.h"

GAMEPLAY_RULE_CAISSE::GAMEPLAY_RULE_CAISSE() :
    GAMEPLAY_RULE() {
    
}

GAMEPLAY_RULE_CAISSE::~GAMEPLAY_RULE_CAISSE() {
    
}


void GAMEPLAY_RULE_CAISSE::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_CAISSE::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_CAISSE::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().DisplayNextCommunityCaisseCard(cell, player);
}

bool GAMEPLAY_RULE_CAISSE::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    return true;
}
