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

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_ADVANCE_TO )
    XS_DEFINE_ClassMember(int , CellIndex)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_ADVANCE_TO, GAMEPLAY_ACTION_TYPE_Custom_6 )

GAMEPLAY_RULE_ADVANCE_TO::GAMEPLAY_RULE_ADVANCE_TO() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION() {
    
}

GAMEPLAY_RULE_ADVANCE_TO::GAMEPLAY_RULE_ADVANCE_TO( int index ) :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
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

void GAMEPLAY_RULE_ADVANCE_TO::Apply() {
    
}
