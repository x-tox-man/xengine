//
//  R3D_PLAYER_SHIP_MODEL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER_SHIP_MODEL.h"

R3D_PLAYER_SHIP_MODEL::R3D_PLAYER_SHIP_MODEL() :
    BaseMass( 1.0f + ((rand() % 10) - 5) * 0.1f ),
    BaseEnergyCapacity( 1.0f + ((rand() % 10) - 5) * 0.1f ),
    BasePowerBoost( 1.0f + ((rand() % 10) - 5) * 0.1f  ),
    BaseSteering( 1.0f + ((rand() % 10) - 5) * 0.1f ),
    Gears(),
    ModelName( "spaceship1" ),
    TextureName( "BitsUV2048" ) {
    
}

R3D_PLAYER_SHIP_MODEL::~R3D_PLAYER_SHIP_MODEL() {
    
}
