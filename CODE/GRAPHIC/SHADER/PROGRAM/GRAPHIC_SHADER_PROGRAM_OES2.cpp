//
//  GRAPHIC_SHADER_PROGRAM_OPENGLES2.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER.h"
#include "CORE_FILESYSTEM.h"

void GRAPHIC_SHADER_PROGRAM::Initialize() {
    
    ShaderProgram = 0;
    
    GFX_CHECK( ShaderProgram = glCreateProgram(); )
}

void GRAPHIC_SHADER_PROGRAM::LoadProgram( const CORE_FILESYSTEM_PATH & path ) {
    //todo insert shaders
    
    CORE_RUNTIME_Abort();
    GRAPHIC_SHADER * vertex = new GRAPHIC_SHADER();
    
    vertex->SetProgram( ShaderProgram );
    vertex->LoadShader( path, GRAPHIC_SHADER_Vertex );
    
    GRAPHIC_SHADER * fragment = new GRAPHIC_SHADER;
    
    fragment->SetProgram( ShaderProgram );
    fragment->LoadShader( path, GRAPHIC_SHADER_Pixel );
    
    LinkTogether( GRAPHIC_SHADER_BIND_None );
}

void GRAPHIC_SHADER_PROGRAM::LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type ) {
    
    GRAPHIC_SHADER * vertex = new GRAPHIC_SHADER;
    
    vertex->SetProgram( ShaderProgram );
    vertex->LoadShader( path, shader_type );
}

void GRAPHIC_SHADER_PROGRAM::Finalize() {
    
    GFX_CHECK( glDeleteProgram(ShaderProgram); )
}

void GRAPHIC_SHADER_PROGRAM::LinkTogether( const GRAPHIC_SHADER_BIND shader_bind ) {
    
    //TODO : clean based on shader content
    
    GRAPHIC_SHADER_ATTRIBUTE * attribute = NULL;
    
    BoundParameters = shader_bind;
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Position, "position"); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Normal, "normal"); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord0) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord0, "tex0"); )
    }
    
    if ( shader_bind & GRAPHIC_SHADER_BIND_Texcoord1) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord1, "tex1" ); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_Texcoord1" );
    if ( shader_bind & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_SkinWeight, "weights"); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_JointIndices" );
    if ( shader_bind & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_JointIndices, "joint_indices"); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_JointIndices" );
    if ( shader_bind & GRAPHIC_SHADER_BIND_Tangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Tangents, "tangent" ); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_Tangents" );
    if ( shader_bind & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Bitangents, "bitangent" ); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_Bitangents" );
    if ( shader_bind & GRAPHIC_SHADER_BIND_Color ) {
        
        GFX_CHECK( glBindAttribLocation( ShaderProgram, GRAPHIC_SHADER_BIND_OPENGLES2_Color, "color" ); )
    }
    SERVICE_LOGGER_Error( "GRAPHIC_SHADER_BIND_Color" );
    if ( !LinkProgram() ) {
        
        Finalize();
        
        SERVICE_LOGGER_Error( "Could not link program ! exit" );
        
        return;
    }
    else {
        SERVICE_LOGGER_Error( "T1" );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE();
        SERVICE_LOGGER_Error( "T2" );
        
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ProjectionMatrix.GetTextValue() ); )
        attribute->AttributeName = ProjectionMatrix;
        
        setShaderAttribute(*attribute);
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ModelMatrix.GetTextValue() ); )
        attribute->AttributeName = ModelMatrix;
        
        setShaderAttribute(*attribute);
        
        CORE_MEMORY_ObjectSafeDeallocation( attribute );
        attribute = new GRAPHIC_SHADER_ATTRIBUTE;
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ShadowMapMVP.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = ShadowMapMVP;
            
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
        GFX_CHECK( attribute->AttributeIndex = glGetUniformLocation( ShaderProgram, ColorTexture5.GetTextValue() ); )
        
        if ( attribute->AttributeIndex != -1 ) {
            
            attribute->AttributeName = ColorTexture5;
            
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
    }
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
    
#if DEBUG
    GLint logLength;
    GFX_CHECK( glGetProgramiv( ShaderProgram, GL_INFO_LOG_LENGTH, &logLength ); )
    
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)CORE_MEMORY_ALLOCATOR::Allocate( logLength );
        glGetProgramInfoLog( ShaderProgram, logLength, &logLength, log );
        
        SERVICE_LOGGER_Error("Program link log:\n%s", log);
        
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
    
    GFX_CHECK( shader_attribute.AttributeIndex = glGetUniformLocation( ShaderProgram, identifier.GetTextValue() ); )
    
    if ( shader_attribute.AttributeIndex != -1 ) {
        
        shader_attribute.AttributeName = identifier;
        
        setShaderAttribute( shader_attribute );
    }
}
