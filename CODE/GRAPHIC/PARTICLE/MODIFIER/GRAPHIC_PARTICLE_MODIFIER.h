//
//  GRAPHIC_PARTICLE_MODIFIER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_MODIFIER_hpp
#define GRAPHIC_PARTICLE_MODIFIER_hpp

#include "CORE_HELPERS_CLASS.h"

template <typename PARTICLE_TYPE, typename PARTICLE_TYPE_ATTRIBUTE, size_t PARTICLE_ARRAY_SIZE>
class GRAPHIC_PARTICLE_MODIFIER {
    
public:
    
    virtual void Apply( float time_step, int start, int end, std::array< PARTICLE_TYPE, PARTICLE_ARRAY_SIZE > & particle_table, std::array< PARTICLE_TYPE_ATTRIBUTE, PARTICLE_ARRAY_SIZE > & particle_attribute_table ) { }
    
protected :
    //hold a weak ptr to the particles & attributes tables
    
    GRAPHIC_PARTICLE_MODIFIER() {
        
    }
};

#endif /* GRAPHIC_PARTICLE_MODIFIER_hpp */
