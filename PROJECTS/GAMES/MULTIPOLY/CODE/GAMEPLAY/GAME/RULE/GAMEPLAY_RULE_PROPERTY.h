//
//  GAMEPLAY_RULE_FIELD.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PROPERTY_hpp
#define GAMEPLAY_RULE_PROPERTY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_PROPERTY, GAMEPLAY_RULE )

    GAMEPLAY_RULE_PROPERTY( int front_price );
    ~GAMEPLAY_RULE_PROPERTY();

    virtual void OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

    void Buy( GAMEPLAY_PLAYER * player);

private:

    virtual int CalculateAmount();
    void ProposeBuy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void TransferTo( GAMEPLAY_PLAYER * player);

    std::vector<GAMEPLAY_RULE_PROPERTY *>
        PropertyGroupement;
    GAMEPLAY_PLAYER
        * Owner;
    int
        BuyPrice;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_PROPERTY_hpp */
