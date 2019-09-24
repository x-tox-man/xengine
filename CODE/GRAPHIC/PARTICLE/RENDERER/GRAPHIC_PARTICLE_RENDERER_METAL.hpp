//
//  GRAPHIC_PARTICLE_RENDERER_METAL.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/08/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_RENDERER_METAL_hpp
#define GRAPHIC_PARTICLE_RENDERER_METAL_hpp

public :

void Render( std::array< __PARTICLE_TYPE__, __ARRAY_SIZE__ > & particle_table, GRAPHIC_SHADER_EFFECT * effect, GRAPHIC_RENDERER & renderer, int first_index, int last_index ) {
    
}

private :

void InternalInitialize( GRAPHIC_SHADER_EFFECT * effect ) {
    
    CORE_RUNTIME_Abort()
}

#endif /* GRAPHIC_PARTICLE_RENDERER_METAL_hpp */
