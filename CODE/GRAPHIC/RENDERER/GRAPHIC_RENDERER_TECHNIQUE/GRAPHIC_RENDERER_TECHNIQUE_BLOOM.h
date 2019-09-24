//
//  GRAPHIC_RENDERER_TECHNIQUE_BLOOM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_BLOOM_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_BLOOM_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.h"
#include "GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.h"

#define GRAPHIC_RENDERER_TECHNIQUE_BLOOM_MAX_BLUR   8

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDERER_TECHNIQUE_BLOOM, GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE_BLOOM();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE_BLOOM();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    inline int GetBlurPassCount() const { return BlurPassCount; }
    inline void SetBlurPassCount( int count ) {
#if DEBUG
        assert( count < GRAPHIC_RENDERER_TECHNIQUE_BLOOM_MAX_BLUR );
#endif
        BlurPassCount = count;
        
    }

    int
        BlurPassCount;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_GAUSSIAN_BLUR::PTR
        HorizontalBlurEffect,
        VerticalBlurEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM::PTR
        CombineBloomEffect;
    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM::PTR
        BloomEffect;
    GRAPHIC_MATERIAL
        Material;
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR
        PlanObject;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock,
        TextureBlock2;
    GRAPHIC_RENDER_TARGET::PTR
        PrimaryRenderTarget,
        BloomRenderTarget;
    GRAPHIC_RENDER_TARGET::PTR
        GaussianRenderTarget1Table[ GRAPHIC_RENDERER_TECHNIQUE_BLOOM_MAX_BLUR ],
        GaussianRenderTarget2Table[ GRAPHIC_RENDERER_TECHNIQUE_BLOOM_MAX_BLUR ];

XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_BLOOM_hpp */
