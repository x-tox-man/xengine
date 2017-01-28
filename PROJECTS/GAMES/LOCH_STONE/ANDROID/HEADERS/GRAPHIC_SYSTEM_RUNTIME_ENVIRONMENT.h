//
//  GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 18/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT_h
#define GAME_ENGINE_REBORN_GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT_h

#ifdef OPENGL3
    #define OPENGL3 1
    #define OPENGL2PLUS 1
    #define GRAPHIC_SYSTEM_NAME OPENGL_3

    #include "OPENGL_3.h"
#else
    #define OPENGL3 0
    #define OPENGL2PLUS 0
#endif

#ifdef OPENGL4
    #define OPENGL4 1
    #define OPENGL2PLUS 1
    #define GRAPHIC_SYSTEM_NAME OPENGL_4
#else
    #define OPENGL4 0
#endif

#ifdef DX11
    #define DX11 1
    #define GRAPHIC_SYSTEM_NAME DIRECTX_11
#else
    #define DX11 0
#endif

#ifdef AMD_MANTLE
    #define AMD_MANTLE 1
    #define GRAPHIC_SYSTEM_NAME AMD_MANTLE
#else
    #define AMD_MANTLE 0
#endif

#ifdef OPENGLES2
    #define OPENGLES2 1
    #define GRAPHIC_SYSTEM_NAME OPENGLES_2
#else
    #define OPENGLES2 0
#endif

#endif

#if OPENGL3
    #include "OPENGL_3.h"
#endif

#if OPENGLES2
    #include "OPENGLES_2.h"
#endif
