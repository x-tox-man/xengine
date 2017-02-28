//
//  GAMEPLAY_RULE_PAY_AMOUNT.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PAY_AMOUNT_hpp
#define GAMEPLAY_RULE_PAY_AMOUNT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"
#include "GAMEPLAY_RULE_PARK.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_PAY_AMOUNT, GAMEPLAY_RULE )

    GAMEPLAY_RULE_PAY_AMOUNT( int amount );
    ~GAMEPLAY_RULE_PAY_AMOUNT();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

private :

    int
        AmountToPay;
    GAMEPLAY_RULE_PARK
        * Destination;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_PAY_AMOUNT_hpp */
