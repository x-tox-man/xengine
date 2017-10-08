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
#include "R3D_PLAYER_PARTS_COLLECTION.h"
#include "GRAPHIC_CAMERA.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(R3D_PLAYER_SHIP, GAMEPLAY_COMPONENT_ENTITY)

    R3D_PLAYER_SHIP();
    ~R3D_PLAYER_SHIP();

    void Initialize();
    void Update( float step );

    void CreateWeaponSystem(  const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );

private:

    R3D_PLAYER_PARTS_COLLECTION
        Parts;
    GRAPHIC_CAMERA
        Front,
        Rear,
        Top;

XS_CLASS_END

#endif /* R3D_PLAYER_SHIP_hpp */
