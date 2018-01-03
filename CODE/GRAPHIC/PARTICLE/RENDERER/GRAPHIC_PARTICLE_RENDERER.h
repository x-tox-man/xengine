//
//  GRAPHIC_PARTICLE_RENDERER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_PARTICLE_RENDERER_h
#define GRAPHIC_PARTICLE_RENDERER_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_PARTICLE.h"

template< typename __PARTICLE_TYPE__>
GRAPHIC_SHADER_BIND GetVertexComponent() {
    return GRAPHIC_SHADER_BIND_None;
}

template<>
GRAPHIC_SHADER_BIND GetVertexComponent<GRAPHIC_PARTICLE>();

template <typename __PARTICLE_TYPE__, size_t __ARRAY_SIZE__>
class GRAPHIC_PARTICLE_RENDERER {
    
public:
    
    void Initialize( GRAPHIC_SHADER_EFFECT * effect ) {
        VertexComponent = GetVertexComponent<__PARTICLE_TYPE__>();
        
        InternalInitialize( effect );
    }
    
    // contract :
    //void Render( std::array< __PARTICLE_TYPE__, __ARRAY_SIZE__ > & particle_table );

private:
    GRAPHIC_SHADER_BIND VertexComponent;
    
#if OPENGL2PLUS
    #include "GRAPHIC_PARTICLE_RENDERER_OPENGL.hpp"
#elif OPENGLES2
    #include "GRAPHIC_PARTICLE_RENDERER_OES2.hpp"
#elif X_VK
    #include "GRAPHIC_PARTICLE_RENDERER_VK.hpp"
#else
    #error "Implement Platforms"
#endif
    
};

#endif /* GRAPHIC_PARTICLE_RENDERER_hpp */
