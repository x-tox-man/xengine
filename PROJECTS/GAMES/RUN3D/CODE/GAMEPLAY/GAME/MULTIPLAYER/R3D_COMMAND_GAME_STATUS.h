//
//  R3D_COMMAND_GAME_STATUS.hpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_COMMAND_GAME_STATUS_hpp
#define R3D_COMMAND_GAME_STATUS_hpp

#include "GAMEPLAY_ACTION.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_COMMAND_GAME_STATUS, GAMEPLAY_ACTION )

    R3D_COMMAND_GAME_STATUS();
    virtual ~R3D_COMMAND_GAME_STATUS() {
        
    }

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( R3D_COMMAND_GAME_STATUS, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Custom_1 )

    virtual void Apply() override;

    SimpleTrickForSerialization()

    int
        Tick;

XS_CLASS_END

#endif /* R3D_COMMAND_GAME_STATUS_hpp */
