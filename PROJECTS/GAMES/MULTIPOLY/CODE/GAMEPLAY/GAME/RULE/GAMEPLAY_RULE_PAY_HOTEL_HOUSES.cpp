//
//  GAMEPLAY_RULE_PAY_HOTEL_HOUSES.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PAY_HOTEL_HOUSES.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_PAY_HOTEL_HOUSES )
    XS_DEFINE_ClassMember(int , AmountPerHouse)
    XS_DEFINE_ClassMember(int , AmountPerHotel)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_PAY_HOTEL_HOUSES, GAMEPLAY_ACTION_TYPE_Custom_7 )

GAMEPLAY_RULE_PAY_HOTEL_HOUSES::GAMEPLAY_RULE_PAY_HOTEL_HOUSES() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    AmountPerHouse(),
    AmountPerHotel() {
    
}

GAMEPLAY_RULE_PAY_HOTEL_HOUSES::GAMEPLAY_RULE_PAY_HOTEL_HOUSES( int amount_per_house, int amount_per_hotel ) :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    AmountPerHouse( amount_per_house ),
    AmountPerHotel( amount_per_hotel ) {
    
}

GAMEPLAY_RULE_PAY_HOTEL_HOUSES::~GAMEPLAY_RULE_PAY_HOTEL_HOUSES() {
    
}

void GAMEPLAY_RULE_PAY_HOTEL_HOUSES::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PAY_HOTEL_HOUSES::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PAY_HOTEL_HOUSES::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

bool GAMEPLAY_RULE_PAY_HOTEL_HOUSES::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    //abort(); // TODO : change player state
    return true;
}

void GAMEPLAY_RULE_PAY_HOTEL_HOUSES::Apply() {
    
}
