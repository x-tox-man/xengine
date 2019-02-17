//
//  GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 18/07/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT_h
#define GAME_ENGINE_REBORN_GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT_h

#ifdef OPENGL3
   #error "UNSUPPORTED OLD API"
#endif

#ifdef OPENGL
    #error "UNSUPPORTED OLD API"
#endif

#ifdef OPENGL2
    #error "UNSUPPORTED OLD API"
#endif



#ifdef X_VK
    #define X_VK 1
#else
    #define X_VK 0
#endif

#ifdef X_METAL
    #define X_METAL 1
#else
    #define X_METAL 0
#endif

#ifdef OPENGL4
    #define OPENGL4 1
    #define GRAPHIC_SYSTEM_NAME OPENGL_4
#else
    #define OPENGL4 0
#endif

#ifdef DX11
    #define DX11 1
    #define GRAPHIC_SYSTEM_NAME DIRECTX11
#else
    #define DX11 0
#endif

#ifdef DX12
	#define DX12 1
	#define GRAPHIC_SYSTEM_NAME DIRECTX12
#else
	#define DX12 0
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

#if OPENGL4 || OPENGL3 || OPENGL3 || OPENGLES2
    #define OPENGL2PLUS 1
#else
    #define OPENGL2PLUS 0
#endif

#endif

#if OPENGL4
    #include "OPENGL_4.h"
#elif OPENGLES2
    #include "OPENGLES_2.h"
#elif X_VK
    #include "VK.h"
#elif X_METAL
    #include "X_METAL.h"
#endif
