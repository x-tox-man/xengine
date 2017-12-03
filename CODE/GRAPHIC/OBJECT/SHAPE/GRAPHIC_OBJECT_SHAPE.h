//
//  GRAPHIC_OBJECT_SHAPE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE, GRAPHIC_OBJECT)

    GRAPHIC_OBJECT_SHAPE();
    virtual ~GRAPHIC_OBJECT_SHAPE();

    virtual void InitializeShape();

    void BindShaderColorAttribute();

protected :

    //TODO : Change to Material

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__) */
