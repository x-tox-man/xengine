//
//  METAL_TEST.hpp
//  MetalTestOSX
//
//  Created by Christophe Bernard on 16/10/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef METAL_TEST_hpp
#define METAL_TEST_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_APPLICATION.h"
#include "CORE_FILESYSTEM.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "ASSET_SCREEN.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_HELPERS_COLOR.h"
#include "GRAPHIC_UI_TEXT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "RESOURCE_CONTAINER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_LOADER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_BLOOM.h"
#include "GRAPHIC_OBJECT_ANIMATED.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(METAL_TEST, CORE_APPLICATION)

    METAL_TEST();
    virtual ~METAL_TEST();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;
    void RenderTechnique( GRAPHIC_RENDERER & renderer );
    void RenderFinalFrameBuffer( GRAPHIC_RENDERER & renderer );

    CORE_FILESYSTEM
        DefaultFileystem;

private:

    GRAPHIC_OBJECT_ANIMATED * CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path );

    GRAPHIC_CAMERA::PTR
        Camera;
    GRAPHIC_CAMERA_ORTHOGONAL::PTR
        RenderTargetCamera;
    GRAPHIC_SHADER_EFFECT::PTR
        Effect,
        UIEffect,
        AnimatedEffect;
    GRAPHIC_OBJECT::PTR
        StaticObject;
    GRAPHIC_OBJECT_ANIMATED::PTR
        NakedGirlObject;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget,
        FinalRenderTarget,
        BloomRenderTarget;
    GRAPHIC_RENDERER_TECHNIQUE
        DefaultTechnique,
        FinalTechnique;
    GRAPHIC_RENDERER_TECHNIQUE_BLOOM
        BloomTechnique;
    GRAPHIC_OBJECT_SHAPE_PLAN
        PlanObject;
    CORE_MATH_MATRIX
        m1,m2;
    GRAPHIC_SHADER_LIGHT
        * AmbientLight,
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;

XS_CLASS_END

#endif /* METAL_TEST_hpp */
