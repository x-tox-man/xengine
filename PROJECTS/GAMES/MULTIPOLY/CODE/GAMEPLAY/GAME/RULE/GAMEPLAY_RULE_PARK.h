//
//  GAMEPLAY_RULE_PARK.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PARK_hpp
#define GAMEPLAY_RULE_PARK_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_PARK, GAMEPLAY_RULE )

    GAMEPLAY_RULE_PARK();
    ~GAMEPLAY_RULE_PARK();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override { return true; }

    void AddAmount( int amount );

private :

    void AddBill( int amount, GAMEPLAY_COMPONENT_RENDER * template_bill);

    int
        ParkAmount;
    std::vector<GAMEPLAY_COMPONENT_RENDER *>
        BillsRenderers;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_PARK_hpp */
