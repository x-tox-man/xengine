//
//  GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_RENDER_TARGET.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR, GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    GRAPHIC_SHADER_EFFECT_SPEEDBLUR::PTR
        SpeedBlurEffect;
    GRAPHIC_MATERIAL
        Material;
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR
        PlanObject;
    GRAPHIC_TEXTURE_BLOCK::PTR
        TextureBlock,
        TextureBlock2;
    GRAPHIC_RENDER_TARGET::PTR
        PrimaryRenderTarget,
        FinalRenderTarget;

XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR_hpp */
