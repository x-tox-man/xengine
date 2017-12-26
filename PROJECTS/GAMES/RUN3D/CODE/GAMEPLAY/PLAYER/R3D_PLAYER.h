//
//  R3D_PLAYER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_hpp
#define R3D_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_PLAYER_SHIP.h"
#include "R3D_PLAYER_SHIP_MODEL.h"

XS_CLASS_BEGIN( R3D_PLAYER )

    R3D_PLAYER();

    void Initialize();
    void Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );

    inline R3D_PLAYER_SHIP::PTR GetShip() { return Ship; }
    std::vector<R3D_PLAYER_SHIP_MODEL::PTR> GetAllShipsOwned();

private :

    R3D_PLAYER_SHIP::PTR
        Ship;

XS_CLASS_END

#endif /* R3D_PLAYER_hpp */
