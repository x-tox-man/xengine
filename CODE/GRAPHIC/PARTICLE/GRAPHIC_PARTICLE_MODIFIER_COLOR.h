//
//  GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR_H
#define GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR_H

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MODIFIER.h"
#include "GRAPHIC_PARTICLE.h"

template <typename PARTICLE_TYPE, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR: GRAPHIC_PARTICLE_MODIFIER< PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE> {
    
public:
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR(CORE_MATH_VECTOR & base_color, CORE_MATH_VECTOR & target_color ) : GRAPHIC_PARTICLE_MODIFIER() {
        
    }
    
    virtual void Apply(float time_step, int start, int end) {
        
        PARTICLE_TYPE_ATTRIBUTE * ptra = ParticleAttributeTable[0];
        PARTICLE_TYPE * ptrp = ParticleTable[0];
        
        for (int i = 0; i < PARTICLE_ARRAY_SIZE; i++) {
            
            ++ptra;
            ++ptrp;
        }
    }
};


#endif /* GRAPHIC_PARTICLE_MODIFIER_APPLY_COLOR_H */
