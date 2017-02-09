//
//  GRAPHIC_SHADER_ATTRIBUTE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_ATTRIBUTE__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_ATTRIBUTE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_HELPERS_SCALAR.h"

XS_CLASS_BEGIN( GRAPHIC_SHADER_ATTRIBUTE )

    GRAPHIC_SHADER_ATTRIBUTE();
    ~GRAPHIC_SHADER_ATTRIBUTE();

    CORE_HELPERS_IDENTIFIER
        AttributeName;
    CORE_SCALAR
        AttributeValue;
    int
        AttributeIndex;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_SHADER_ATTRIBUTE__) */
