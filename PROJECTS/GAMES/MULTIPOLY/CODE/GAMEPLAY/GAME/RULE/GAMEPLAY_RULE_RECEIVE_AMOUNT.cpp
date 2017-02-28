//
//  GAMEPLAY_RULE_RECEIVE_AMOUNT.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_RECEIVE_AMOUNT.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_RECEIVE_AMOUNT::GAMEPLAY_RULE_RECEIVE_AMOUNT( int amount ) :
    GAMEPLAY_RULE(),
    AmountToReceive( amount ) {
    
}

GAMEPLAY_RULE_RECEIVE_AMOUNT::~GAMEPLAY_RULE_RECEIVE_AMOUNT() {
    
}

void GAMEPLAY_RULE_RECEIVE_AMOUNT::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_RECEIVE_AMOUNT::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_RECEIVE_AMOUNT::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    Apply( cell, player );
}

bool GAMEPLAY_RULE_RECEIVE_AMOUNT::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    player->AddMoney( AmountToReceive );
    
    return true;
}
