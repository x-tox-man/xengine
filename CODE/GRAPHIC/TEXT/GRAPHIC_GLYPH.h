//
//  GRAPHIC_GLYPH.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_GLYPH__
#define __GAME_ENGINE_REBORN__GRAPHIC_GLYPH__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_GLYPH )

XS_DEFINE_SERIALIZABLE

GRAPHIC_GLYPH();
~GRAPHIC_GLYPH();

char
    Value;
CORE_MATH_VECTOR
    PaddingBounding,
    Advance;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_GLYPH__) */
