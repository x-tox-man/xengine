//
//  GAMEPLAY_RULE_PAY_AMOUNT.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PAY_AMOUNT.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_PAY_AMOUNT )
    XS_DEFINE_ClassMember(int , AmountToPay)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_PAY_AMOUNT, GAMEPLAY_ACTION_TYPE_Custom_9 )

GAMEPLAY_RULE_PAY_AMOUNT::GAMEPLAY_RULE_PAY_AMOUNT() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    AmountToPay( 0 ),
    Destination( NULL ) {
    
}

GAMEPLAY_RULE_PAY_AMOUNT::GAMEPLAY_RULE_PAY_AMOUNT( int amount ) :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    AmountToPay( amount ),
    Destination( NULL ) {
    
}

GAMEPLAY_RULE_PAY_AMOUNT::~GAMEPLAY_RULE_PAY_AMOUNT() {
    
}

void GAMEPLAY_RULE_PAY_AMOUNT::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PAY_AMOUNT::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_PAY_AMOUNT::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    Apply( cell, player );
}

bool GAMEPLAY_RULE_PAY_AMOUNT::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
#if DEBUG
    if ( AmountToPay== -1 ) {
        abort();
    }
#endif
    
    int amount = player->AttemptPay( AmountToPay );
    
    if ( amount == AmountToPay ) {
        
        if ( Destination ) {
            
            Destination->AddAmount( amount );
            abort(); // TODO : change player state
        }
        
        return true;
    }
    else {
        abort();
        //médiation de dettes
        return false;
    }
}

void GAMEPLAY_RULE_PAY_AMOUNT::Apply() {
    
}
