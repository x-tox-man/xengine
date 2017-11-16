//
//  GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY_H
#define GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY_H

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MODIFIER.h"
#include "GRAPHIC_PARTICLE.h"

template <typename PARTICLE_TYPE, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY: GRAPHIC_PARTICLE_MODIFIER< PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE> {
    
public:
    
    GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY() : GRAPHIC_PARTICLE_MODIFIER< PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE>() {
        
    }
    
    virtual ~GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY() {
        
    }
    
    virtual void Apply( float time_step, int start, int end, std::array< PARTICLE_TYPE, PARTICLE_ARRAY_SIZE > & particle_table, std::array< PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > & particle_attribute_table ) override {
        
        PARTICLE_TYPE_ATTRIBUTE * ptra = &particle_attribute_table[0];
        PARTICLE_TYPE * ptrp = &particle_table[0];
        
        for (int i = 0; i < PARTICLE_ARRAY_SIZE; i++) {
            
            ptrp->Position += ptra->Velocity * time_step;
            ++ptra;
            ++ptrp;
        }
    }
    
private :
    float
        Gravity;
};


#endif /* GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY */
