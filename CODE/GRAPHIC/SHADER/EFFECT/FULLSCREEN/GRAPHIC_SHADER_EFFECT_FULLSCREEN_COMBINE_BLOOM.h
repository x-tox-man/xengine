//
//  GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 25/10/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM_hpp
#define GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_EFFECT.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM, GRAPHIC_SHADER_EFFECT )

GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM();

virtual void Apply();
virtual void BindAttributes();

static CORE_HELPERS_IDENTIFIER
    BloomIntensityIdentifier,
    BaseIntensityIdentifier,
    BloomSaturationIdentifier,
    BaseSaturationIdentifier;

XS_CLASS_END

#endif /* GRAPHIC_SHADER_EFFECT_FULLSCREEN_COMBINE_BLOOM_hpp */
