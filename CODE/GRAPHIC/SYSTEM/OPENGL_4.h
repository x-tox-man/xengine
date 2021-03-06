//
//  OPENGL_4.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__OPENGL_4__
#define __GAME_ENGINE_REBORN__OPENGL_4__

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_BLEND_OPERATION.h"
#include "GRAPHIC_SYSTEM_POLYGON_FILL_MODE.h"
#include "GRAPHIC_TEXTURE_FILTERING.h"
#include "GRAPHIC_TEXTURE_WRAP.h"
#include "GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE.h"
#include "GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION.h"
#include "GRAPHIC_SYSTEM_BLEND_EQUATION.h"
#include "GRAPHIC_POLYGON_FACE.h"

#if PLATFORM_WINDOWS
	//#include <glcorearb.h>

    #include <GL/glew.h>	
	#include <gl/GLU.h>
	#include <gl/GL.h>
	#include <glext.h>
#else
	#include <OpenGL/gl3.h>
	//#include <GLUT/GLUT.h>
#endif

#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_OSX || PLATFORM_IOS
    #define GFX_CHECK( __METHOD__ ) \
        __METHOD__ \
        { \
            int error = glGetError(); \
            if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) { SERVICE_LOGGER_Error( "GLError with %s  : - %d - %s\n", #__METHOD__ , error, "" );  } \
        }
#else
    #define GFX_CHECK( __METHOD__ ) \
        __METHOD__ \
        { \
        int error = glGetError(); \
        if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) { SERVICE_LOGGER_Error( "GLError with %s  : - %d - %s\n", #__METHOD__ , error, "TODO gluErrorString(error)" );  } \
        }
#endif

    GLint OPENGL_4_GetTextureFormat( GRAPHIC_TEXTURE_IMAGE_TYPE image_tye );

    GLenum OPENGL_4_GetCompareOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGL_4_GetBlendOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGL_4_GetFillMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE mode );

    GLenum OPENGL_4_GetFiltermode( const GRAPHIC_TEXTURE_FILTERING mode );

    GLenum OPENGL_4_GetWrapMode( const GRAPHIC_TEXTURE_WRAP wrap );

    GLenum OPENGL_4_GetFrameBufferMode( const GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode );

    GLenum OPENGL_4_GetPolygonFace( const GRAPHIC_POLYGON_FACE face );

    GLenum OPENGL_4_GetStendilFailOperation( const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION action );

    GLenum OPENGL_4_GetBlendEquation( const GRAPHIC_SYSTEM_BLEND_EQUATION equation );

    #define GRAPHIC_SYSTEM_ApplyMatrix(index, size, transpose, array) \
        GFX_CHECK( glUniformMatrix4fv( \
            index, \
            size, \
            transpose, \
            (const GLfloat * )array); )

    #define GRAPHIC_SYSTEM_ApplyVector(index, size, array) \
        GFX_CHECK( glUniform4fv( \
            index, \
            size, \
            (const GLfloat * )array); )

    #define GRAPHIC_SYSTEM_ApplyFloat(index, value) \
            GFX_CHECK( glUniform1f( \
                index, \
                value ); )

#define GRAPHIC_SYSTEM_ApplyFloatArray(index, size, array) \
            GFX_CHECK( glUniform1fv( \
                index, \
                size, \
                array); )

#endif /* defined(__GAME_ENGINE_REBORN__OPENGL_2__) */
