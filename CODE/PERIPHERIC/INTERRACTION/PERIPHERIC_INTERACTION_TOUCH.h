//
//  PERIPHERIC_INTERACTION_TOUCH.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_TOUCH__
#define __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_TOUCH__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERACTION_TOUCH )

    PERIPHERIC_INTERACTION_TOUCH();
    ~PERIPHERIC_INTERACTION_TOUCH();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( PERIPHERIC_INTERACTION_TOUCH );

    void Update( float time_step, float accel_x, float accel_y, float accel_z );

    inline float GetX() { return X; }
    inline float GetY() { return Y; }
    inline float GetZ() { return Z; }

private:

    float
        X,
        Y,
        Z;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_TOUCH__) */
