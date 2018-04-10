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
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"

XS_CLASS_BEGIN( R3D_RENDER )

    R3D_RENDER();

    void Initialize();
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
        * RenderTargetCamera,
        * LightShadowCamera;
    GRAPHIC_SHADER_LIGHT
        Directional,
        Ambient;
    GRAPHIC_OBJECT_SHAPE_PLAN
        PlanObject;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget,
        FinalRenderTarget,
        LightRenderTarget,
        SpecularRenderTarget,
        GaussianRenderTarget1,
        GaussianRenderTarget2,
        BloomRenderTarget,
        ShadowMapRenderTarget;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock,
        TextureBlock2,
        TextureBlock3;
    GRAPHIC_SHADER_EFFECT::PTR
        UIShaderTextured;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR
        HorizontalBlurEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR
        VerticalBlurEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::PTR
        CombineBloomEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR
        BloomEffect;
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR
        SpeedBlurEffect;
#if DEBUG
    bool
        DebugRenderActive;
#endif

XS_CLASS_END


#endif /* R3D_RENDER_hpp */
