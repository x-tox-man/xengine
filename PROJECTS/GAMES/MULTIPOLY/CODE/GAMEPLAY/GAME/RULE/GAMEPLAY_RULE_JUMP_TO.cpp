//
//  GAMEPLAY_RULE_JUMP_TO.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_JUMP_TO.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_JUMP_TO::GAMEPLAY_RULE_JUMP_TO( int cell_index_to_remove ) :
    CellOffset( cell_index_to_remove ) {

}

GAMEPLAY_RULE_JUMP_TO::~GAMEPLAY_RULE_JUMP_TO() {
    
}

void GAMEPLAY_RULE_JUMP_TO::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_JUMP_TO::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_JUMP_TO::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

bool GAMEPLAY_RULE_JUMP_TO::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    int index = player->GetCurrentCellIndex() -  CellOffset;
    
    if( index < 0 ) {
        
        index += 40;
    }
    
    player->JumpTo( index );
    
    return false;
}
