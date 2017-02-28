//
//  GAMEPLAY_RULE_CHANCE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_CHANCE_hpp
#define GAMEPLAY_RULE_CHANCE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_CHANCE, GAMEPLAY_RULE )

    GAMEPLAY_RULE_CHANCE();
    ~GAMEPLAY_RULE_CHANCE();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_CHANCE_hpp */
