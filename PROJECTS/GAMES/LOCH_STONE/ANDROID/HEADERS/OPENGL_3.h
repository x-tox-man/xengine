//
//  OPENGL_2.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__OPENGL_2__
#define __GAME_ENGINE_REBORN__OPENGL_2__

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

#include <OpenGL/gl3.h>
#include <GLUT/GLUT.h>
#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "SERVICE_LOGGER.h"

#define GFX_CHECK( __METHOD__ ) \
    __METHOD__ \
    { \
        int error = glGetError(); \
        if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) { SERVICE_LOGGER_Error( "GLError with %s  : - %d - %s\n", #__METHOD__ , error, gluErrorString(error) );  } \
    }

void OPENGL_3_Initialize();

GLint OPENGL_3_GetTextureFormat( GRAPHIC_TEXTURE_IMAGE_TYPE image_tye );

GLenum OPENGL_3_GetCompareOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

GLenum OPENGL_3_GetBlendOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

GLenum OPENGL_3_GetFillMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE mode );

#endif /* defined(__GAME_ENGINE_REBORN__OPENGL_2__) */