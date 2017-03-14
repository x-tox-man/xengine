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

XS_CLASS_BEGIN_WITH_ANCESTOR_2( GAMEPLAY_RULE_CAISSE, GAMEPLAY_RULE, GAMEPLAY_ACTION )

    GAMEPLAY_RULE_CAISSE();
    virtual ~GAMEPLAY_RULE_CAISSE();

    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_RULE_CAISSE, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Custom_17 )

    virtual void Apply() override;

    SimpleTrickForSerialization()

XS_CLASS_END

#endif /* GAMEPLAY_RULE_CAISSE_hpp */
