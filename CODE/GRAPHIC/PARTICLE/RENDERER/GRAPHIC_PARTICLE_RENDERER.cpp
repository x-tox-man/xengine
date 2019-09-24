//
//  GRAPHIC_PARTICLE_RENDERER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/09/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_PARTICLE_RENDERER.h"

template<>
GRAPHIC_SHADER_BIND GetVertexComponent<GRAPHIC_PARTICLE>() {
    return GRAPHIC_SHADER_BIND_PositionNormal;
}

#if OPENGL2PLUS
    #include "GRAPHIC_PARTICLE_RENDERER_OPENGL.cpp"
#elif OPENGLES2
    #include "GRAPHIC_PARTICLE_RENDERER_OES2.cpp"
#elif X_VK
    #include "GRAPHIC_PARTICLE_RENDERER_VK.cpp"
#elif X_METAL
    #import "GRAPHIC_PARTICLE_RENDERER_METAL.mm"
#else
    #error "Implement Platforms"
#endif
