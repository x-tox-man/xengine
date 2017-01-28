//
//  GRAPHIC_SHADER_OPENGL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_OPENGL__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_OPENGL__

#include <stdlib.h>
#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

#if OPENGL2PLUS
    XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_OPENGL, GRAPHIC_SHADER )

        GRAPHIC_SHADER_OPENGL();

        Scalar_SGet( GLuint, Program );

        virtual void LoadShader( const char * shader_name, GRAPHIC_SHADER_TYPE shader_type );
        virtual void EnableShader();
        virtual void DisableShader();
        virtual void Finalize();

    private :

        bool CompileShader( GLuint & shader, GLenum type,  const char * file );

    GLuint
        Shader;

    XS_CLASS_END
#endif

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_OPENGL__) */
