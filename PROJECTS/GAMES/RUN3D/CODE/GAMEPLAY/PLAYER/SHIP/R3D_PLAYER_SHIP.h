//
//  R3D_PLAYER_SHIP.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_SHIP_hpp
#define R3D_PLAYER_SHIP_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GRAPHIC_CAMERA.h"
#include "GRAPHICS_STEAM_ENGINE.h"
#include "R3D_PLAYER_MODIFIER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"

#define R3D_GAMEPLAY_COMPONENT_TYPE_PlayerShip (GAMEPLAY_COMPONENT_TYPE_Count + 1)

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_PLAYER_SHIP, GAMEPLAY_COMPONENT )

    R3D_PLAYER_SHIP();
    ~R3D_PLAYER_SHIP();

    inline void SetThrust( float thrust ) { Thrust = thrust; }
    inline void SetRotation( float orientation ) { Rotation = orientation; }
    inline float GetThrust() const { return Thrust; }
    inline float GetRotation() const { return Rotation; }

    void ApplyInputParamters( float thrust, float orientation ) {
        
        SetThrust( thrust );
        SetRotation( orientation );
    }

private:

    float
        Thrust,
        Rotation;

XS_CLASS_END

#endif /* R3D_PLAYER_SHIP_hpp */
