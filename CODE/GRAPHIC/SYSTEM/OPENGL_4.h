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
        if ( error || error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION ) { SERVICE_LOGGER_Error( "GLError with %s  : - %d - %s\n", #__METHOD__ , error, gluErrorString(error) );  } \
        }
#endif

    GLint OPENGL_4_GetTextureFormat( GRAPHIC_TEXTURE_IMAGE_TYPE image_tye );

    GLenum OPENGL_4_GetCompareOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGL_4_GetBlendOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation );

    GLenum OPENGL_4_GetFillMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE mode );

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
