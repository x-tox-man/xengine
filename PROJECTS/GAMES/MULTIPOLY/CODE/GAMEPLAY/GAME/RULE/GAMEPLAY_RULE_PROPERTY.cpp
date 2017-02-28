//
//  GAMEPLAY_RULE_FIELD.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PROPERTY.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "MULTIPOLY_APPLICATION.h"

GAMEPLAY_RULE_PROPERTY::GAMEPLAY_RULE_PROPERTY( int front_price ) :
    GAMEPLAY_RULE(),
    PropertyGroupement(),
    Owner( NULL ),
    BuyPrice( front_price ) {
    
}

GAMEPLAY_RULE_PROPERTY::~GAMEPLAY_RULE_PROPERTY() {
    
}

void GAMEPLAY_RULE_PROPERTY::OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    if ( Owner && Owner == player ) {
        //Actions are enabled
    }
    else {
        
        //Actions are disabled except from buying
    }
}

void GAMEPLAY_RULE_PROPERTY::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PROPERTY::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_PROPERTY::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    Apply( cell, player );
}

bool GAMEPLAY_RULE_PROPERTY::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {

    if ( Owner && Owner != player ) {
        
        int amount = CalculateAmount();
        
        int res = player->AttemptPay( amount );
        
        if ( res == amount ) {
            
            return false;
        }
        else {
            abort();
            //enchères
            return false;
        }
    }
    else {
        ProposeBuy( cell, player );
    }
    
    return false;
}

int GAMEPLAY_RULE_PROPERTY::CalculateAmount() {
    
    std::vector<GAMEPLAY_RULE_PROPERTY *>::iterator it = PropertyGroupement.begin();
    bool complete = true;
    int amount = 0;
    
    while (it != PropertyGroupement.end() ) {
        
        if ( (*it)->Owner == NULL || (*it)->Owner != (*PropertyGroupement.begin())->Owner ) {
            complete = false;
            break;
        }
        it++;
    }
    
    if ( complete ) {
        
    }
    
    return 0;
}

void GAMEPLAY_RULE_PROPERTY::ProposeBuy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player) {
    
    if ( player->GetMoney() >= BuyPrice ) {
        
        if ( player->IsHuman() ) {
            
            ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().ProposeBuyProperty( cell, player );
        }
        else {
            
            Buy( player );
        }
    }
    else {
        //enchères
        abort();
    }
}

void GAMEPLAY_RULE_PROPERTY::Buy( GAMEPLAY_PLAYER * player) {
    
    if ( player->GetMoney() >= BuyPrice ) {
        
        player->RemoveMoney( BuyPrice );
        
        TransferTo( player );
    }
}


void GAMEPLAY_RULE_PROPERTY::TransferTo( GAMEPLAY_PLAYER * player) {
    
}
