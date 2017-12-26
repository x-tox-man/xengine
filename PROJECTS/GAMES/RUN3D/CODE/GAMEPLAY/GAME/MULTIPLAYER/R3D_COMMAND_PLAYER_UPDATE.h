//
//  R3D_COMMAND_PLAYER_UPDATE.hpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_COMMAND_PLAYER_UPDATE_hpp
#define R3D_COMMAND_PLAYER_UPDATE_hpp

#include "GAMEPLAY_ACTION.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_COMMAND_PLAYER_UPDATE, GAMEPLAY_ACTION )

    R3D_COMMAND_PLAYER_UPDATE();
    virtual ~R3D_COMMAND_PLAYER_UPDATE() {
        
    }

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( R3D_COMMAND_PLAYER_UPDATE, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Custom_2 )

    virtual void Apply() override;

    SimpleTrickForSerialization()

    int
        Tick;
    float
        Thrust,
        Orientation;

XS_CLASS_END

#endif /* R3D_COMMAND_PLAYER_UPDATE_hpp */
