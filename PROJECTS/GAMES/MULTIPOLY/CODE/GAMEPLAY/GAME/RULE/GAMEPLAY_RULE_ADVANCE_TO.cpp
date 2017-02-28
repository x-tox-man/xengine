//
//  GAMEPLAY_RULE_ADVANCE_TO.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_ADVANCE_TO.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_ADVANCE_TO::GAMEPLAY_RULE_ADVANCE_TO( int index ) :
    CellIndex( index ) {
    
}

GAMEPLAY_RULE_ADVANCE_TO::~GAMEPLAY_RULE_ADVANCE_TO() {
    
}

void GAMEPLAY_RULE_ADVANCE_TO::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_ADVANCE_TO::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_ADVANCE_TO::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

bool GAMEPLAY_RULE_ADVANCE_TO::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    
    player->ForceAdvanceTo( CellIndex );
    
    return false;
}
