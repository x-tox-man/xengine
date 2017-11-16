//
//  GRAPHIC_MESH_OPENGL.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 15/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_OPENGL__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_OPENGL__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

#if OPENGL2PLUS
    XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_MESH_OPENGL, GRAPHIC_MESH)

    virtual ~GRAPHIC_MESH_OPENGL();

    virtual void Enable();
    virtual void Disable();

    private :
        GLuint
            VertexBuffer,
            IndexBuffer;

    XS_CLASS_END
#endif

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_OPENGL__) */
