//
//  GRAPHIC_PARTICLE_MODIFIER_GRAVITY.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_MODIFIER_GRAVITY_hpp
#define GRAPHIC_PARTICLE_MODIFIER_GRAVITY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_PARTICLE_MODIFIER.h"
#include "GRAPHIC_PARTICLE.h"

template <typename PARTICLE_TYPE, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_MODIFIER_GRAVITY: GRAPHIC_PARTICLE_MODIFIER< PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE> {
    
public:
    
    GRAPHIC_PARTICLE_MODIFIER_GRAVITY( float gravity ) :
        GRAPHIC_PARTICLE_MODIFIER< PARTICLE_TYPE, PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE>() {
        Gravity = gravity;
    }
    
    virtual ~GRAPHIC_PARTICLE_MODIFIER_GRAVITY() {
        
    }
    
    virtual void Apply( float time_step, int start, int end, std::array< PARTICLE_TYPE, PARTICLE_ARRAY_SIZE > & particle_table, std::array< PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > & particle_attribute_table ) override {
        
        float current_g = Gravity * time_step;
        
        PARTICLE_TYPE_ATTRIBUTE * ptr = &particle_attribute_table[0];
        
        for (int i = 0; i < PARTICLE_ARRAY_SIZE; i++) {
            
            ptr->Velocity.Z( ptr->Velocity.Z() - current_g);
            ++ptr;
        }
    }
    
private :
    
    float Gravity;

};


#endif /* GRAPHIC_PARTICLE_MODIFIER_GRAVITY_hpp */
