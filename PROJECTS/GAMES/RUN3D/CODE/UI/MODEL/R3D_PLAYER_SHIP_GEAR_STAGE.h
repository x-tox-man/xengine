//
//  R3D_PLAYER_SHIP_GEAR.hpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_SHIP_GEAR_hpp
#define R3D_PLAYER_SHIP_GEAR_hpp

#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN( R3D_PLAYER_SHIP_GEAR_STAGE )

    XS_DEFINE_SERIALIZABLE

    R3D_PLAYER_SHIP_GEAR_STAGE();
    ~R3D_PLAYER_SHIP_GEAR_STAGE();

    float
        Power,
        Torque;

XS_CLASS_END

#endif /* R3D_PLAYER_SHIP_GEAR_hpp */
