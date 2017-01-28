//
//  GLOBAL_RESOURCES.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GLOBAL_RESOURCES_hpp
#define GLOBAL_RESOURCES_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_OBJECT_SHAPE_FRAME.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_UI_RENDER_STYLE.h"
#include "GRAPHIC_OBJECT_ANIMATED.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GRAPHIC_OBJECT_SHAPE_CUBE.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h"
#include "GRAPHIC_OBJECT_SHAPE_LINE.h"
#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_PARTICLE_MANAGER.h"
#include "GRAPHIC_PARTICLE_EMITER.h"
#include "GRAPHIC_PARTICLE_MODIFIER_APPLY_VELOCITY.h"
#include "GRAPHIC_PARTICLE_MODIFIER_GRAVITY.h"
#include "GRAPHIC_PARTICLE_SYSTEM.h"
#include "GAMEPLAY_SCENE.h"

#define PARTICLE_SIZE 50000


XS_CLASS_BEGIN( GLOBAL_RESOURCES )

    XS_DEFINE_UNIQUE( GLOBAL_RESOURCES )

    void Initialize( GAMEPLAY_SCENE * scene );
    void Finalize();

    void CreateGround(GAMEPLAY_SCENE * scene);
    void CreateNakedGirl(GAMEPLAY_SCENE * scene);
    void CreateMoulin(GAMEPLAY_SCENE * scene);

    void InitializeFromApplicationRefactor( GAMEPLAY_SCENE * scene );

    GAMEPLAY_COMPONENT_ENTITY * CreateMesh( const CORE_FILESYSTEM_PATH & path, GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program, const CORE_MATH_VECTOR & position, GAMEPLAY_SCENE * scene );
    GRAPHIC_OBJECT_ANIMATED * CreateAnimatedObject( const CORE_FILESYSTEM_PATH & object_path, const CORE_FILESYSTEM_PATH & animation_path );

    GRAPHIC_TEXTURE * CreateTextureFromImagePath(const char * image_path);

    GRAPHIC_RENDER_TARGET & GetShadowMapRenderTarget() { return ShadowMapRenderTarget;}

    GRAPHIC_TEXTURE_ATLAS
        UITextureAtlas;
    GRAPHIC_OBJECT_SHAPE_PLAN
        * UIPlanObject,
        * UIPlanObjectColorOnly;
    GRAPHIC_OBJECT_SHAPE_FRAME
        * UIFramePlanObject;
    GRAPHIC_TEXTURE_BLOCK
        * UIFrameTextureBlock;
    GRAPHIC_UI_RENDER_STYLE
        * FrameRenderStyle,
        * CellRenderStyle,
        * PageFrameRenderStyle,
        * ButtonRenderStyle;

    GRAPHIC_OBJECT
        * NakedGirlObject,
        * AstroBoy,
        * Moulin,
        * ResourceObject;

    GRAPHIC_OBJECT_SHAPE_PLAN
        * PlanObject,
        * EffectPlan;
    GAMEPLAY_COMPONENT_ENTITY
        * component_entity,
        *component_entity2;
    GRAPHIC_OBJECT_SHAPE_CUBE
        * CubeObject;
    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP
        * HeightMapObject;
    GRAPHIC_OBJECT_SHAPE_SPHERE
        * SphereObject;
    GRAPHIC_OBJECT_SHAPE_LINE
        * Line;

    GRAPHIC_RENDER_TARGET
        ShadowMapRenderTarget,
        PrimaryRenderTarget,
        LightRenderTarget,
        SpecularRenderTarget,
        GaussianRenderTarget,
        BloomRenderTarget;
    GRAPHIC_SHADER_EFFECT
        ShadowMapEffect;
    GRAPHIC_SHADER_EFFECT::PTR
        BasicEffectShadowMap;
    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR
        BlurEffect,
        BasicGeometryEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR
        BloomEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR
        HorizontalBlurEffect,
        VerticalBlurEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::PTR
        CombineBloomEffect;
    GRAPHIC_SHADER_LIGHT
        * DirectionalLight,
        * PointLightOne,
        * PointLightTwo,
        * SpotLightOne,
        * SpotLightTwo;
    GRAPHIC_TEXTURE_BLOCK
        * TextureBlock,
        * AlternateTextureBlock;
    int
        ComponentIndex;
};

#endif /* GLOBAL_RESOURCES_hpp */
