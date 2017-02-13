//
//  GRAPHIC_SHADER_PROGRAM_OPENGL.cpp
//  GAME-ENGINE-REBORN
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

void GRAPHIC_SHADER_PROGRAM::LoadProgram( const CORE_FILESYSTEM_PATH & path ) {
    
    //todo insert shaders
    
    GRAPHIC_SHADER * vertex = new GRAPHIC_SHADER();
    
    vertex->SetProgram( ShaderProgram );
    vertex->LoadShader( path, GRAPHIC_SHADER_Vertex );
    
    delete vertex;
    
    GRAPHIC_SHADER * fragment = new GRAPHIC_SHADER;
    
    fragment->SetProgram( ShaderProgram );
    fragment->LoadShader( path, GRAPHIC_SHADER_Pixel );
    
    LinkTogether( GRAPHIC_SHADER_BIND_None );
    
    delete fragment;
    
    CORE_RUNTIME_Abort();
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
    
    //TODO : clean based on shader content
    
    BoundParameters = shader_bind;
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Position, "position" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Normal, "normal" ); )
    }
        
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord0) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0, "tex0" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord1) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Texcoord0, "tex1" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_SkinWeight, "weights" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_JointIndices, "joint_indices" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Tangents, "tangent" ); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGL3_Bitangents, "bitangent" ); )
    }
    
    //TODO : color
    
    if ( /*!ValidateProgram() ||*/ !LinkProgram() ) {
        
        Finalize();
        
        CORE_RUNTIME_Abort();
        
        return;
    }
    
    // Get uniform locations.
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ProjectionMatrix.GetTextValue() ); )
    attribute->AttributeName = ProjectionMatrix;
    
    setShaderAttribute(*attribute);
    delete attribute;
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ModelViewMatrix.GetTextValue() ); )
    attribute->AttributeName = ModelViewMatrix;
    
    setShaderAttribute(*attribute);
    
    delete attribute;
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ShadowMapMVP;
        
        setShaderAttribute(*attribute);
    }
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, MVPMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = MVPMatrix;
        
        setShaderAttribute(*attribute);
    }
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SkinningMatrixTable.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        attribute->AttributeName = SkinningMatrixTable;
    
        setShaderAttribute(*attribute);
    }
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, AttrBindShapeMatrix.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        attribute->AttributeName = AttrBindShapeMatrix;
    
        setShaderAttribute(*attribute);
    }
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture;
    
        setShaderAttribute(*attribute);
    }
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture1.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture1;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture2.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture2;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture3.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture3;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture4.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = ColorTexture4;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, NormalTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = NormalTexture;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DepthTexture.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DepthTexture;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightColor.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = DirectionalLightColor;
        
        setShaderAttribute(*attribute);
        
        delete attribute;
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightDirection.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightDirection;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightDiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightDiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, DirectionalLightAmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = DirectionalLightAmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
    }
    else {
        
        delete attribute;
    }
    
    // POINT LIGHT 0
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PointLight0Color;
        
        setShaderAttribute(*attribute);
        
        delete attribute;
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Position;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Exp;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Constant;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight0Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight0Linear;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
    }
    else {
        
        delete attribute;
    }
    
    // POINT LIGHT 1
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = PointLight1Color;
        
        setShaderAttribute(*attribute);
        
        delete attribute;
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Position;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Exp;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Constant;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, PointLight1Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = PointLight1Linear;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
    }
    else {
        
        delete attribute;
    }
    
    // SPOT 0
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SpotLight0Color;
        
        setShaderAttribute(*attribute);
        
        delete attribute;
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Position;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Exp;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Constant;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Linear;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Direction.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Direction;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight0Cutoff.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight0Cutoff;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
    }
    else {
        
        delete attribute;
    }
    
    // SPOT 1
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Color.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = SpotLight1Color;
        
        setShaderAttribute(*attribute);
        
        delete attribute;
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Position.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Position;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1DiffuseIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1DiffuseIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1AmbientIntensity.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1AmbientIntensity;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Exp.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Exp;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Constant.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Constant;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Linear.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Linear;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Direction.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Direction;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
        
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, SpotLight1Cutoff.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = SpotLight1Cutoff;
            
            setShaderAttribute(*attribute);
        }
        delete attribute;
    }
    else {
        
        delete attribute;
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
    
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, LightSpecularPower.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = LightSpecularPower;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
    
    attribute = new GRAPHIC_SHADER_ATTRIBUTE;
    GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, MaterialSpecularIntensity.GetTextValue() ); )
    
    if ( attribute->AttributeIndex != -1 ) {
        
        attribute->AttributeName = MaterialSpecularIntensity;
        
        setShaderAttribute(*attribute);
    }
    delete attribute;
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
            GLchar *log = (GLchar *)CORE_MEMORY_ALLOCATOR::Allocate( logLength );
            glGetProgramInfoLog( ShaderProgram, logLength, &logLength, log );
            //NSLog(@"Program link log:\n%s", log);
            
            SERVICE_LOGGER_Error("%s\n", log );
            CORE_MEMORY_ALLOCATOR_Free(log);
        }
    #endif
    
    GFX_CHECK( glGetProgramiv( ShaderProgram, GL_LINK_STATUS, &status ); )
    
    return status != 0;
}

void GRAPHIC_SHADER_PROGRAM::Enable() {
    
    GFX_CHECK( glUseProgram(ShaderProgram); )
}

void GRAPHIC_SHADER_PROGRAM::Disable() {
    
}

void GRAPHIC_SHADER_PROGRAM::BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, CORE_HELPERS_IDENTIFIER & identifier ) {
    
    GFX_CHECK(
		shader_attribute.AttributeIndex = glGetUniformLocation( ShaderProgram, identifier.GetTextValue() );
	)
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = GeometryColor;
        
        setShaderAttribute( shader_attribute );
    }
}
