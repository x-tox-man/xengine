//
//  GRAPHIC_SHADER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_SHADER_TYPE.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "CORE_FILESYSTEM.h"

XS_CLASS_BEGIN( GRAPHIC_SHADER )

    GRAPHIC_SHADER();

    void LoadShader( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type );
    void EnableShader();
    void DisableShader();
    void Finalize();

private :
    GRAPHIC_SHADER_TYPE
        ShaderType;

#if OPENGLES2
    #include "GRAPHIC_SHADER_OPENGLES2.hpp"
#elif OPENGL3
    #include "GRAPHIC_SHADER_OPENGL.hpp"
#else
#error "Must include file to match graphic runtime"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER__) */
