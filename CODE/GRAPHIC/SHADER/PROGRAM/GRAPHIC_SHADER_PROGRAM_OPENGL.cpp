//
//  GRAPHIC_SHADER_PROGRAM_OPENGL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER.h"
#include "SERVICE_LOGGER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "CORE_MEMORY.h"

void GRAPHIC_SHADER_PROGRAM::Initialize() {
    
    ShaderProgram = 0;
    
    GFX_CHECK( ShaderProgram = glCreateProgram(); )
}

void GRAPHIC_SHADER_PROGRAM::LoadProgram( const CORE_FILESYSTEM_PATH & path, int shader_load_options ) {
    
    //todo insert shaders
    if ( shader_load_options & GRAPHIC_SHADER_LOAD_OPTION_Vertex) {
        
        GRAPHIC_SHADER * vertex = new GRAPHIC_SHADER();
        
        vertex->SetProgram( ShaderProgram );
        vertex->LoadShader( path, GRAPHIC_SHADER_Vertex );
        
        CORE_MEMORY_ObjectSafeDeallocation( vertex );
    }
    
    if ( shader_load_options & GRAPHIC_SHADER_LOAD_OPTION_Fragment) {
        
        GRAPHIC_SHADER * fragment = new GRAPHIC_SHADER;
        
        fragment->SetProgram( ShaderProgram );
        fragment->LoadShader( path, GRAPHIC_SHADER_Pixel );
        
        CORE_MEMORY_ObjectSafeDeallocation( fragment );
    }
    
    LinkTogether( GRAPHIC_SHADER_BIND_None );
}

void GRAPHIC_SHADER_PROGRAM::LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type ) {
    
    GRAPHIC_SHADER * shader = new GRAPHIC_SHADER;
    
    shader->SetProgram( ShaderProgram );
    shader->LoadShader( path, shader_type );
    
    delete shader;
}

void GRAPHIC_SHADER_PROGRAM::Finalize() {
    
    GFX_CHECK( glDeleteProgram(ShaderProgram); )
}

void GRAPHIC_SHADER_PROGRAM::LinkTogether( const GRAPHIC_SHADER_BIND shader_bind ) {
    
    // TODO: clean based on shader content
    
    BoundParameters = shader_bind;
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Position, "position" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Normal, "normal" ); )
    }
        
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord0) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Texcoord0, "tex0" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord1) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Texcoord1, "tex1" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_SkinWeight, "weights" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_JointIndices, "joint_indices" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Tangents, "tangent" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Bitangents, "bitangent" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Color ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL4_Color, "color" ); )
    }
    
    // TODO: color
    
    if ( /*!ValidateProgram() ||*/ !LinkProgram() ) {
        
        Finalize();
        
        CORE_RUNTIME_Abort();
        
        return;
    }
    
    
    /*GLint i, count, size;
    GLenum type;
    const GLsizei bufSize = 64;
    GLchar name[bufSize];
    GLsizei lenght;
    
    GFX_CHECK(glGetProgramiv(ShaderProgram, GL_ACTIVE_UNIFORMS, &count); )
    
    for ( int i = 0; i < count; i++ ) {
        
        GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        
        GFX_CHECK( glGetActiveUniform(ShaderProgram, (GLuint)i, bufSize, &lenght, &size, &type, name); )
        
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, name ); )
        attribute->AttributeName = CORE_HELPERS_IDENTIFIER( name );
        
        assert( attribute->AttributeIndex >= 0 );
        
        setShaderAttribute(*attribute);
        printf( "%d, %s\n", attribute->AttributeIndex, name);
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }*/
    
    // Get uniform locations.
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ProjectionMatrix.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ProjectionMatrix;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ModelMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ModelMatrix;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ViewMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ViewMatrix;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP1.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP1;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP2.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP2;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP3.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP3;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP4.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP4;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP5.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP5;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, CascadeEndClipSpace.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = CascadeEndClipSpace;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, MVPMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = MVPMatrix;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SkinningMatrixTable.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        attribute->AttributeName = SkinningMatrixTable;
    
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, AttrBindShapeMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        attribute->AttributeName = AttrBindShapeMatrix;
    
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture;
    
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture1.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture1;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture2.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture2;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture3.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture3;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture4.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture4;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTextureOut.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTextureOut;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTextureOut1.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTextureOut1;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTextureOut2.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTextureOut2;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTextureOut3.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTextureOut3;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTextureOut4.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTextureOut4;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, NormalTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = NormalTexture;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture1.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture1;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture2.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture2;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture3.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture3;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture4.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture4;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    //CameraWorldPosition
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, CameraWorldPosition.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = CameraWorldPosition;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    //AMBIENT
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, AmbientLightColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = AmbientLightColor;
        
        setShaderAttribute(*attribute);
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, AmbientLightAmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = AmbientLightAmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, AmbientLightDiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = AmbientLightDiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DirectionalLightColor;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightDirection.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightDirection;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightDiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightDiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightAmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightAmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // POINT LIGHT Deferred
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PointLightColor;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightPosition.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightPosition;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightDiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightDiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightAmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightAmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightExp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightExp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightConstant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightConstant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLightLinear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLightLinear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // POINT LIGHT 0
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PointLight0Color;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Position;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Exp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Constant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Linear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // POINT LIGHT 1
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PointLight1Color;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Position;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Exp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Constant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Linear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // SPOT NORMAL
    
    // SPOT 0
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SpotLightColor;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightPosition.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightPosition;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightDiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightDiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightAmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightAmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightExp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightExp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightConstant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightConstant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightLinear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightLinear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightDirection.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightDirection;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLightCutoff.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLightCutoff;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // SPOT 0
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SpotLight0Color;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Position;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Exp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Constant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Linear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Direction.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Direction;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Cutoff.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Cutoff;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    // SPOT 1
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SpotLight1Color;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Position;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Exp;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Constant;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Linear;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Direction.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Direction;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Cutoff.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Cutoff;
            
            setShaderAttribute(*attribute);
        }
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    else {
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
    }
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, GeometryColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = GeometryColor;
        attribute->AttributeValue.Value.FloatArray4[0] = 1.0f;
        attribute->AttributeValue.Value.FloatArray4[1] = 1.0f;
        attribute->AttributeValue.Value.FloatArray4[2] = 1.0f;
        attribute->AttributeValue.Value.FloatArray4[3] = 1.0f;
        
        setShaderAttribute(*attribute);
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, LightSpecularPower.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = LightSpecularPower;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, MaterialSpecularIntensity.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = MaterialSpecularIntensity;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, TimeModulator.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = TimeModulator;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, PreviousModelViewProjectionIdentifier.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PreviousModelViewProjectionIdentifier;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, SSAOSampleRadFOVRatio.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SSAOSampleRadFOVRatio;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, SSAOKernel.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SSAOKernel;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, SSAOTexture.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SSAOTexture;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, SSAOViewProjectionMatrix.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SSAOViewProjectionMatrix;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, SSAOViewMatrix.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SSAOViewMatrix;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex=glGetUniformLocation( ShaderProgram, FrameResolution.GetTextValue() ); )
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = FrameResolution;
        
        setShaderAttribute(*attribute);
    }
    CORE_MEMORY_ObjectSafeDeallocation( attribute );
}

bool GRAPHIC_SHADER_PROGRAM::ValidateProgram() {
    
    GLint logLength, status;
    
    GFX_CHECK( glValidateProgram( ShaderProgram ); )
    GFX_CHECK( glGetProgramiv( ShaderProgram, GL_INFO_LOG_LENGTH, &logLength ); )
    
    if (logLength > 0) {
        
        GLchar *log = (GLchar *)CORE_MEMORY_ALLOCATOR::Allocate( logLength );
        GFX_CHECK( glGetProgramInfoLog( ShaderProgram, logLength, &logLength, log ); )
        //NSLog(@"Shader validate log:\n%s", log);
        SERVICE_LOGGER_Info("%s\n", log);
        CORE_MEMORY_ALLOCATOR_Free( log );
    }
    
    GFX_CHECK( glGetProgramiv( ShaderProgram, GL_VALIDATE_STATUS, &status ); )
    
    return status != 0;
}

bool GRAPHIC_SHADER_PROGRAM::LinkProgram() {
    
    GLint status;
    GFX_CHECK( glLinkProgram( ShaderProgram ); )
    
    #if defined(DEBUG)
        GLint logLength;
        GFX_CHECK( glGetProgramiv( ShaderProgram, GL_INFO_LOG_LENGTH, &logLength ); )
        
        if (logLength > 0)
        {
            GLchar log[1024];
            glGetProgramInfoLog( ShaderProgram, logLength, &logLength, log );
            //NSLog(@"Program link log:\n%s", log);
            
            SERVICE_LOGGER_Error("%s\n", log );
        }
    #endif
    
    GFX_CHECK( glGetProgramiv( ShaderProgram, GL_LINK_STATUS, &status ); )
    
    return status != 0;
}

void GRAPHIC_SHADER_PROGRAM::Enable( GRAPHIC_RENDERER & renderer ) {
    
    GFX_CHECK( glUseProgram(ShaderProgram); )
}

void GRAPHIC_SHADER_PROGRAM::Disable() {
    
}

void GRAPHIC_SHADER_PROGRAM::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, const CORE_HELPERS_IDENTIFIER & identifier ) {
    
    GFX_CHECK(
		shader_attribute.AttributeIndex = glGetUniformLocation( ShaderProgram, identifier.GetTextValue() );
	)
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = identifier;
        
        setShaderAttribute( shader_attribute );
    }
}
