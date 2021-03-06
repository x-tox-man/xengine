//
//  GRAPHIC_SHADER_PROGRAM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_TYPE.h"
#include "GRAPHIC_SHADER.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "GRAPHIC_SHADER_LOAD_OPTION.h"
#include "GRAPHIC_RENDERER_STATE_DESCRIPTOR.h"

class GRAPHIC_RENDERER;

XS_CLASS_BEGIN( GRAPHIC_SHADER_PROGRAM )

    GRAPHIC_SHADER_PROGRAM();
    ~GRAPHIC_SHADER_PROGRAM();

    void Initialize();
    void LoadProgram( const CORE_FILESYSTEM_PATH & path, int shader_load_options = GRAPHIC_SHADER_LOAD_OPTION_Vertex & GRAPHIC_SHADER_LOAD_OPTION_Fragment );
    void LoadPartial( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_TYPE shader_type );
    void Finalize();

    void Enable( GRAPHIC_RENDERER & renderer );
    void Disable();

    GRAPHIC_SHADER_ATTRIBUTE & GetShaderAttribute( const CORE_HELPERS_IDENTIFIER & identifier ) { return ShaderAttributeTable[identifier]; }
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE> & GetShaderAttributeTable() { return ShaderAttributeTable; }

    void setShaderAttribute( const GRAPHIC_SHADER_ATTRIBUTE & attribute ) {

#if DEBUG
        assert( ShaderAttributeTable.find(attribute.AttributeName) == ShaderAttributeTable.end() );
#endif
        ShaderAttributeTable[attribute.AttributeName].AttributeIndex = attribute.AttributeIndex;
        ShaderAttributeTable[attribute.AttributeName].AttributeName = attribute.AttributeName;
        ShaderAttributeTable[attribute.AttributeName].AttributeValue = attribute.AttributeValue;
        ShaderAttributeTable[attribute.AttributeName].GPUBuffer = attribute.GPUBuffer;
    }

protected:

    std::map<GRAPHIC_SHADER_TYPE, GRAPHIC_SHADER *>
        ShaderTable;
    std::map<CORE_HELPERS_IDENTIFIER, GRAPHIC_SHADER_ATTRIBUTE>
        ShaderAttributeTable;

public:

static const CORE_HELPERS_IDENTIFIER
    ProjectionMatrix,
    ViewMatrix,
    ModelMatrix,
    MVPMatrix,
    ShadowMapMVP1,
    ShadowMapMVP2,
    ShadowMapMVP3,
    ShadowMapMVP4,
    ShadowMapMVP5,
    CascadeEndClipSpace,
    NormalMatrix,
    ColorTexture,
    ColorTexture1,
    ColorTexture2,
    ColorTexture3,
    ColorTexture4,
    ColorTexture5,
    ColorTextureOut,
    ColorTextureOut1,
    ColorTextureOut2,
    ColorTextureOut3,
    ColorTextureOut4,
    NormalTexture,
    DisplacementTexture,
    DepthTexture,
    DepthTexture1,
    DepthTexture2,
    DepthTexture3,
    DepthTexture4,
    ShadowDepthTexture1,
    ShadowDepthTexture2,
    ShadowDepthTexture3,
    ShadowDepthTexture4,
    SkinningMatrixTable,
    AttrBindShapeMatrix,
    GeometryColor,
    DirectionalLightColor,
    DirectionalLightDirection,
    DirectionalLightAmbientIntensity,
    DirectionalLightDiffuseIntensity,
    AmbientLightColor,
    AmbientLightAmbientIntensity,
    AmbientLightDiffuseIntensity,
    PointLightColor,
    PointLightPosition,
    PointLightAmbientIntensity,
    PointLightDiffuseIntensity,
    PointLightConstant,
    PointLightLinear,
    PointLightExp,
    PointLight0Color,
    PointLight0Position,
    PointLight0AmbientIntensity,
    PointLight0DiffuseIntensity,
    PointLight0Constant,
    PointLight0Linear,
    PointLight0Exp,
    PointLight1Color,
    PointLight1Position,
    PointLight1AmbientIntensity,
    PointLight1DiffuseIntensity,
    PointLight1Constant,
    PointLight1Linear,
    PointLight1Exp,
    SpotLightColor,
    SpotLightPosition,
    SpotLightDirection,
    SpotLightCutoff,
    SpotLightAmbientIntensity,
    SpotLightDiffuseIntensity,
    SpotLightConstant,
    SpotLightLinear,
    SpotLightExp,
    SpotLight0Color,
    SpotLight0Position,
    SpotLight0Direction,
    SpotLight0Cutoff,
    SpotLight0AmbientIntensity,
    SpotLight0DiffuseIntensity,
    SpotLight0Constant,
    SpotLight0Linear,
    SpotLight0Exp,
    SpotLight1Color,
    SpotLight1Position,
    SpotLight1Direction,
    SpotLight1Cutoff,
    SpotLight1AmbientIntensity,
    SpotLight1DiffuseIntensity,
    SpotLight1Constant,
    SpotLight1Linear,
    SpotLight1Exp,
    AmbientLight,
    CameraWorldPosition,
    LightSpecularPower,
    MaterialSpecularIntensity,
    TimeModulator,
    PreviousModelViewProjectionIdentifier,
    SSAOProjectionMatrix,
    SSAOViewProjectionMatrix,
    SSAOViewMatrix,
    SSAOSampleRadFOVRatio,
    SSAOKernel,
    SSAOTexture,
    FOVRatio,
    FrameResolution;

#if OPENGLES2
    #include "GRAPHIC_SHADER_PROGRAM_OES2.hpp"
#elif OPENGL4
	#include "GRAPHIC_SHADER_PROGRAM_OPENGL.hpp"
#elif X_VK
    #include "GRAPHIC_SHADER_PROGRAM_VK.hpp"
#elif X_METAL
    #include "GRAPHIC_SHADER_PROGRAM_METAL.hpp"
#else
    #error "Must include file to match graphic runtime"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM__) */
