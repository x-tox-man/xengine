//
//  CORE_MATH_RAY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_RAY__
#define __GAME_ENGINE_REBORN__CORE_MATH_RAY__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"

XS_CLASS_BEGIN( CORE_MATH_RAY )

    CORE_MATH_RAY();
    ~CORE_MATH_RAY();

    inline void SetOrigin( const CORE_MATH_VECTOR & origin ) { Origin = origin; }
    inline void SetDirection( const CORE_MATH_VECTOR & direction ) { Direction = direction; }

    inline const CORE_MATH_VECTOR & GetOrigin() const { return Origin; }
    inline const CORE_MATH_VECTOR & GetDirection() const { return Direction; }

    inline CORE_MATH_VECTOR & GetOrigin() { return Origin; }
    inline CORE_MATH_VECTOR & GetDirection() { return Direction; }

private :

    CORE_MATH_VECTOR
        Origin,
        Direction;
    float
        Lenght;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_RAY__) */
