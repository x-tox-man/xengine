//
//  OPENGL_2.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__OPENGL_2__
#define __GAME_ENGINE_REBORN__OPENGL_2__

#include "GRAPHIC_SYSTEM.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_BLEND_OPERATION.h"
#include "GRAPHIC_SYSTEM_POLYGON_FILL_MODE.h"
#include "GRAPHIC_SYSTEM_COMPARE_OPERATION.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_IOS
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>

    #define GFX_CHECK( __METHOD__ ) \
        __METHOD__ \
        { \
            int error = glGetError(); \
            if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) { \
                SERVICE_LOGGER_Error( "GLError with %s  : - %d - \n", #__METHOD__ , error ); \
            } \
        }

#elif PLATFORM_ANDROID
    #include <dlfcn.h>
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <android/log.h>

    #define GFX_CHECK( __METHOD__ ) \
    __METHOD__ \
    { \
        int error = glGetError(); \
        if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) \
        { \
            SERVICE_LOGGER_Error( "GLError with %s  : - %d - \n", #__METHOD__ , error ); \
        } \
    }
#endif

    GLint OPENGLES_2_GetTextureFormat( GRAPHIC_TEXTURE_IMAGE_TYPE image_tye );

    GLenum OPENGLES_2_GetCompareOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGLES_2_GetBlendOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGLES_2_GetFillMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE mode );

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

#endif /* defined(__GAME_ENGINE_REBORN__OPENGL_2__) */
