//
//  R3D_RENDER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_RENDER_hpp
#define R3D_RENDER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_CAMERA.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_BLOOM.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_RENDER_TECHNIQUE_SSAO.h"

XS_CLASS_BEGIN( R3D_RENDER )

    R3D_RENDER();

    void Initialize();
    void RenderOpaqueScene( GRAPHIC_RENDERER & renderer );
    void RenderSceneTransparentWithParticles( GRAPHIC_RENDERER & renderer );

    void Render( GRAPHIC_RENDERER & renderer );

    inline GRAPHIC_CAMERA * GetCamera() { return Camera; }
    inline void SetCamera( GRAPHIC_CAMERA::PTR camera ) { Camera = camera; }

    inline void SetDebugRenderActive( bool active ) {
    #if DEBUG
        DebugRenderActive = active;
    #endif
    }


private :

    CORE_MATH_QUATERNION
        Lookat;
    GRAPHIC_CAMERA
        * Camera;
    GRAPHIC_CAMERA_ORTHOGONAL
        * InterfaceCamera,
        * RenderTargetCamera;
    GRAPHIC_SHADER_LIGHT
        Directional,
        Ambient;
    GRAPHIC_OBJECT_SHAPE_PLAN
        PlanObject;
    GRAPHIC_OBJECT_SHAPE_SPHERE
        SphereObject;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget,
        FinalRenderTarget,
        LightRenderTarget,
        SpecularRenderTarget,
        BloomRenderTarget,
        ShadowMapRenderTarget1,
        ShadowMapRenderTarget2,
        ShadowMapRenderTarget3;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock1,
        TextureBlock2,
        TextureBlock3,
        TextureBlock4;
    GRAPHIC_SHADER_EFFECT::PTR
        UIShaderTextured;
    GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR
        SpeedBlurTechnique;
    GRAPHIC_RENDERER_TECHNIQUE_BLOOM
        BloomTechnique;
    GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP
        CascadeShadowMapTechnique;
    GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING
        DeferredShadingTechnique;
    GRAPHIC_RENDER_TECHNIQUE_SSAO
        SSAOTechnique;
#if DEBUG
    bool
        DebugRenderActive;
#endif

XS_CLASS_END


#endif /* R3D_RENDER_hpp */
