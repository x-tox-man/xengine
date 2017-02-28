//
//  GAMEPLAY_RULE_CAISSE.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_CAISSE_hpp
#define GAMEPLAY_RULE_CAISSE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_CAISSE, GAMEPLAY_RULE )

    GAMEPLAY_RULE_CAISSE();
    ~GAMEPLAY_RULE_CAISSE();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_CAISSE_hpp */
