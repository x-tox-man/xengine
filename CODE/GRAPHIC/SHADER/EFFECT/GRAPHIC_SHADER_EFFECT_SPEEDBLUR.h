//
//  GRAPHIC_SHADER_EFFECT_SPEEDBLUR.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_SPEEDBLUR__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_SPEEDBLUR__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_SPEEDBLUR, GRAPHIC_SHADER_EFFECT )

    GRAPHIC_SHADER_EFFECT_SPEEDBLUR( GRAPHIC_SHADER_EFFECT::PTR effect );
    virtual ~GRAPHIC_SHADER_EFFECT_SPEEDBLUR();

    virtual void Apply( GRAPHIC_RENDERER &, const char * ) override;
    virtual void BindAttributes() override;

    static CORE_HELPERS_IDENTIFIER
        InverseCurrentModelViewIdentifier,
        ViewRayIdentifier;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_SPEEDBLUR__) */
