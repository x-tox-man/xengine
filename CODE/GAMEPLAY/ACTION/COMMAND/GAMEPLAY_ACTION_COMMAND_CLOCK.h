//
//  GAMEPLAY_ACTION_COMMAND_CLOCK.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 7/02/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_ACTION_COMMAND_CLOCK_hpp
#define GAMEPLAY_ACTION_COMMAND_CLOCK_hpp

#include "GAMEPLAY_ACTION.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_ACTION_COMMAND_CLOCK, GAMEPLAY_ACTION )

    GAMEPLAY_ACTION_COMMAND_CLOCK();
    GAMEPLAY_ACTION_COMMAND_CLOCK( NETWORK_PLAYER * player );
    ~GAMEPLAY_ACTION_COMMAND_CLOCK();

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_ACTION_COMMAND_CLOCK, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Clock )

    virtual void Apply() override;

    SimpleTrickForSerialization()

    NETWORK_PLAYER
        *Player;
    unsigned int
        SentTick,
        ReceivedTick,
        AveragePing;

XS_CLASS_END

#endif /* GAMEPLAY_ACTION_COMMAND_CLOCK_hpp */
