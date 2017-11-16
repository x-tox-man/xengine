//
//  CORE_MATH_SHAPE_SPHERE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_SHAPE_SPHERE__
#define __GAME_ENGINE_REBORN__CORE_MATH_SHAPE_SPHERE__

#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"

bool CORE_MATH_SHAPE_SPHERE_GetIntersection( const CORE_MATH_RAY & other,
                                            const CORE_MATH_VECTOR & position,
                                            const CORE_MATH_VECTOR & half_extent,
                                            CORE_MATH_VECTOR & intersection );


#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_SHAPE_SPHERE__) */
