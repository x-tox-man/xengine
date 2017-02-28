//
//  GAMEPLAY_RULE_STATION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_STATION.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_STATION::GAMEPLAY_RULE_STATION( int amount ) :
    GAMEPLAY_RULE_PROPERTY( amount ) {
    
}

GAMEPLAY_RULE_STATION::~GAMEPLAY_RULE_STATION() {
    
}

void GAMEPLAY_RULE_STATION::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_STATION::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_STATION::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}
