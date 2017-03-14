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
#include "GAMEPLAY_ACTION.h"

class GAMEPLAY_PLAYER;
class GAMEPLAY_GAME_BOARD_CELL;

XS_CLASS_BEGIN( GAMEPLAY_RULE )

    GAMEPLAY_RULE();
    virtual ~GAMEPLAY_RULE();

    virtual void OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {};
    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) = 0;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) { return true; }
    virtual void OnPicked(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {}
    virtual void OnDismiss(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {};

    template <typename  __ACTION__>
    static void CreateAndSendNetworkCommand(GAMEPLAY_RULE * rule);

XS_CLASS_END

#endif /* GAMEPLAY_RULE_hpp */
