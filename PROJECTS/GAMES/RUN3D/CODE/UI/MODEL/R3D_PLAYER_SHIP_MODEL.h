//
//  R3D_PLAYER_SHIP_MODEL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_SHIP_MODEL_hpp
#define R3D_PLAYER_SHIP_MODEL_hpp

#include "R3D_PLAYER_SHIP_MODEL.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "R3D_PLAYER_SHIP_GEAR_STAGE.h"

XS_CLASS_BEGIN( R3D_PLAYER_SHIP_MODEL )

    XS_DEFINE_SERIALIZABLE

    R3D_PLAYER_SHIP_MODEL();
    ~R3D_PLAYER_SHIP_MODEL();

    float
        BaseMass,
        BaseEnergyCapacity,
        BasePowerBoost,
        BaseSteering;
    std::vector< R3D_PLAYER_SHIP_GEAR_STAGE::PTR >
        Gears;
    CORE_HELPERS_IDENTIFIER
        ModelName,
        TextureName;

XS_CLASS_END

#endif /* R3D_PLAYER_SHIP_MODEL_hpp */
