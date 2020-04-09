//
//  GRAPHIC_RENDER_TECHNIQUE_SSAO.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/07/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDER_TECHNIQUE_SSAO_hpp
#define GRAPHIC_RENDER_TECHNIQUE_SSAO_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_EFFECT_SSAO.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDER_TECHNIQUE_SSAO, GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDER_TECHNIQUE_SSAO();
    virtual ~GRAPHIC_RENDER_TECHNIQUE_SSAO();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    GRAPHIC_MATERIAL
        Material,
        MaterialBlur;
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR
        PlanObject;
    GRAPHIC_TEXTURE_BLOCK
        TextureBlock1,
        TextureBlock2,
        TextureBlock3,
        TextureBlock4;
    GRAPHIC_SHADER_EFFECT_SSAO::PTR
        SSAOEffect;
    GRAPHIC_SHADER_EFFECT::PTR
        SimpleBlurEffect;
    GRAPHIC_RENDER_TARGET::PTR
        SourceRenderTarget;

XS_CLASS_END

#endif /* GRAPHIC_RENDER_TECHNIQUE_SSAO_hpp */
