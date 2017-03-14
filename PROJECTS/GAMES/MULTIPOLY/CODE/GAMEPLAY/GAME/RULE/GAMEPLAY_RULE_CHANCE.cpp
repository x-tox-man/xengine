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

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_CHANCE )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_CHANCE, GAMEPLAY_ACTION_TYPE_Custom_12 )

GAMEPLAY_RULE_CHANCE::GAMEPLAY_RULE_CHANCE() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION() {
    
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

void GAMEPLAY_RULE_CHANCE::Apply() {
    
}
