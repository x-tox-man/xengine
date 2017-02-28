//
//  GAMEPLAY_RULE_PAY_HOTEL_HOUSES.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 28/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PAY_HOTEL_HOUSES_hpp
#define GAMEPLAY_RULE_PAY_HOTEL_HOUSES_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_PAY_HOTEL_HOUSES, GAMEPLAY_RULE )

    GAMEPLAY_RULE_PAY_HOTEL_HOUSES( int amount_per_house, int amount_per_hotel );
    ~GAMEPLAY_RULE_PAY_HOTEL_HOUSES();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

private :

    int
        AmountPerHouse,
        AmountPerHotel;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_PAY_HOTEL_HOUSES_hpp */
