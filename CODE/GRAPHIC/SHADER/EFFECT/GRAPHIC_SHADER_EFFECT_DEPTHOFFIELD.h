//
//  GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/10/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD, GRAPHIC_SHADER_EFFECT )

    GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD();
    virtual ~GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD();

    virtual void Apply( GRAPHIC_RENDERER & ) override;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_EFFECT_DEPTHOFFIELD__) */
