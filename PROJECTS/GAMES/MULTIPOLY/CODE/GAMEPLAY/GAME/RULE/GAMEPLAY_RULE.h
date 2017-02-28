//
//  GAMEPLAY_RULE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_hpp
#define GAMEPLAY_RULE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_DICE_ROLL_RESULT.h"

class GAMEPLAY_PLAYER;
class GAMEPLAY_GAME_BOARD_CELL;

XS_CLASS_BEGIN( GAMEPLAY_RULE )

    GAMEPLAY_RULE();
    ~GAMEPLAY_RULE();

    virtual void OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {};
    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) { return true; }

XS_CLASS_END

#endif /* GAMEPLAY_RULE_hpp */
