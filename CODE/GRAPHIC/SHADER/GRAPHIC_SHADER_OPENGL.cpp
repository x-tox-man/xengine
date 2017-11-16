//
//  GRAPHIC_SHADER_OPENGL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "GRAPHIC_SHADER.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "SERVICE_LOGGER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "CORE_MEMORY.h"

void GRAPHIC_SHADER::LoadShader( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type )
{
    GLenum type;
    
    switch ( shader_type )
    {
        case GRAPHIC_SHADER_Vertex :
            type = GL_VERTEX_SHADER;
            break;
            
        case GRAPHIC_SHADER_Pixel :
            type = GL_FRAGMENT_SHADER;
            break;
            
#ifdef OPENGL2PLUS
        case GRAPHIC_SHADER_Geometry:
            type = GL_GEOMETRY_SHADER;
            break;
#endif
            
        default:
            CORE_RUNTIME_Abort();
            break;
    }
    
    // Create and compile vertex shader.
    if (!CompileShader( Shader, type, path ) ) {
        
        SERVICE_LOGGER_Error( "Failed to compile vertex shader");
        return;
    }
    
    // Attach vertex shader to program.
    GFX_CHECK( glAttachShader( Program, Shader); )
    
    return;
}

bool GRAPHIC_SHADER::CompileShader( GLuint & shader, GLenum type,  const CORE_FILESYSTEM_PATH & path )
{
    GLint status;
    
    GLchar *source;
    
    CORE_FILESYSTEM_FILE file( path );
    
    if ( ! file.OpenOutput() ) {
        
        SERVICE_LOGGER_Error( "GRAPHIC_SHADER::CompileShader could not open file output" );
        
        return false;
    }
    
    unsigned int length = file.GetSize();
    
    SERVICE_LOGGER_Info("%d\n", (int) length );
    
    source = new GLchar [length +1];
    
    int bytes_read = file.OutputBytes( source, length );
    
    if ( source ) {
        
        SERVICE_LOGGER_Error( "all characters read successfully." );
    }
    else {
        
        SERVICE_LOGGER_Error( "error: only %d could be read", bytes_read );
    }
    
    file.Close();
    
    if (!source)
    {
        SERVICE_LOGGER_Error( "GRAPHIC_SHADER::CompileShader source error" );
        
        return false;
    }
    
    source[length] = '\0';
    
    //SERVICE_LOGGER_Info("source %s\n", source );
    
    shader = glCreateShader( type );
    
    GFX_CHECK( glShaderSource( shader, 1, &source, NULL ); )
    GFX_CHECK( glCompileShader( shader ); )
    
    #if defined(DEBUG)
        GLint logLength;
        GFX_CHECK( glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength); )
    
        if (logLength > 0)
        {
            GLchar *log = (GLchar *)CORE_MEMORY_ALLOCATOR::Allocate(logLength);
            
            GFX_CHECK( glGetShaderInfoLog(shader, logLength, &logLength, log); )
            
            if ( logLength )
            {
                SERVICE_LOGGER_Info( "%s\n", log);
            }

            CORE_MEMORY_ALLOCATOR_Free(log);
        }
    #endif
    
    GFX_CHECK( glGetShaderiv(shader, GL_COMPILE_STATUS, &status); )
    
    CORE_MEMORY_ALLOCATOR_Free(source);
    
    if (status == 0)
    {
        GFX_CHECK( glDeleteShader(shader); )
        
        CORE_RUNTIME_Abort();
        
        return false;
    }
    
    return true;
}

void GRAPHIC_SHADER::EnableShader()
{
    
}

void GRAPHIC_SHADER::DisableShader()
{
    
}

void GRAPHIC_SHADER::Finalize()
{
    if ( Shader )
    {
        GFX_CHECK( glDetachShader( Program, Shader); )
        GFX_CHECK( glDeleteShader( Shader); )
    }
}
