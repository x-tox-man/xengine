//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM_hpp
#define GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM, GRAPHIC_SHADER_EFFECT )

    GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM( GRAPHIC_SHADER_EFFECT::PTR effect );
    virtual ~GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM();

    virtual void Apply( GRAPHIC_RENDERER & ) override;
    virtual void BindAttributes() override;

    static CORE_HELPERS_IDENTIFIER
        BloomThresholdIdentifier;

private:

    GRAPHIC_SHADER_EFFECT::PTR
        EffectInstance;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_EFFECT_FULLSCREEN_BLOOM_hpp */
