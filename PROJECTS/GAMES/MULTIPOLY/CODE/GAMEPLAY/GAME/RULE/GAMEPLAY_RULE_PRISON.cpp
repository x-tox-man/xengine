//
//  GAMEPLAY_RULE_PRISON.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PRISON.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "APPLICATION_CONFIGURATION.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_PRISON )
    XS_DEFINE_ClassMember(bool , GotoPrisonCell)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_PRISON, GAMEPLAY_ACTION_TYPE_Custom_13 )

GAMEPLAY_RULE_PRISON::GAMEPLAY_RULE_PRISON() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    GotoPrisonCell( false ) {
    
}

GAMEPLAY_RULE_PRISON::GAMEPLAY_RULE_PRISON( bool is_goto_prison_cell ) :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    GotoPrisonCell( is_goto_prison_cell ) {
    
}

GAMEPLAY_RULE_PRISON::~GAMEPLAY_RULE_PRISON() {
    
}

void GAMEPLAY_RULE_PRISON::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PRISON::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    //CancelTurn if not double dice rolled
    
    if( !player->GetRollResult().IsDouble ) {
        
        player->GetRollResult().Total = 0;
        player->GetRollResult().FirstDice = 0;
        player->GetRollResult().SecondDice = 0;
    }
}

void GAMEPLAY_RULE_PRISON::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    if( GotoPrisonCell ) {
        
        player->JumpTo( APPLICATION_PRISON_CELL_INDEX );
    }
}

bool GAMEPLAY_RULE_PRISON::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    player->JumpTo( APPLICATION_PRISON_CELL_INDEX );
    
    return false;
}

void GAMEPLAY_RULE_PRISON::Apply() {
    
}
