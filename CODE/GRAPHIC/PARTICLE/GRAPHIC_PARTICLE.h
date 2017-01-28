//
//  GRAPHIC_PARTICLE.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_h
#define GRAPHIC_PARTICLE_h

#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"

struct GRAPHIC_PARTICLE {
    
    CORE_MATH_VECTOR Position;
    CORE_MATH_QUATERNION Orientation;
};

struct GRAPHIC_PARTICLE_STATIC_ATTRIBUTES {
    
    CORE_MATH_VECTOR Velocity;
    float Modulator;
};

struct GRAPHIC_PARTICLE_DYNAMIC_ATTRIBUTES : GRAPHIC_PARTICLE_STATIC_ATTRIBUTES {
    
    float Lifetime;
};

#endif /* GRAPHIC_PARTICLE_hpp */
