//
//  GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_TEXTURE_TYPE.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT_DEFERRED_SHADING.h"
#include "GRAPHIC_SHADER_EFFECT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING, GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    GRAPHIC_MATERIAL
        Material;
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR
        PlanObject;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock,
        TextureBlock1,
        TextureBlock2;
    GRAPHIC_SHADER_EFFECT::PTR
        AmbientDirectionalDefferedEffect,
        SpotDeferredEffect,
        PointDefferedEffect;
    GRAPHIC_RENDER_TARGET
        RenderTarget;
    GRAPHIC_RENDER_TARGET::PTR
        FinalRenderTarget;

XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp */
