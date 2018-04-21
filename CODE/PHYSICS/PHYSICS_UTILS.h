//
//  PHYSICS_UTILS.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/09/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef PHYSICS_UTILS_hpp
#define PHYSICS_UTILS_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_RAY.h"
#include "CORE_MATH_RAY_SEGMENT.h"

XS_CLASS_BEGIN( PHYSICS_UTILS )

#ifdef __BULLET_PHYSICS__
    static bool FindCollisionInRayFromWorld( btDiscreteDynamicsWorld * world, CORE_MATH_VECTOR & result, CORE_MATH_VECTOR & normal, const CORE_MATH_RAY_SEGMENT & ray );

#endif

XS_CLASS_END

#endif /* PHYSICS_UTILS_hpp */
