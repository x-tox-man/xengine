//
//  CORE_MATH_SHAPE_RECTANGLE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MATH_SHAPE_RECTANGLE__
#define __GAME_ENGINE_REBORN__CORE_MATH_SHAPE_RECTANGLE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"

XS_CLASS_BEGIN( CORE_MATH_SHAPE_RECTANGLE )

CORE_MATH_SHAPE_RECTANGLE();
~CORE_MATH_SHAPE_RECTANGLE();

CORE_MATH_SHAPE_RECTANGLE( const CORE_MATH_VECTOR & center, const CORE_MATH_VECTOR & size );

static bool Contains( const CORE_MATH_VECTOR & rectangle_position,
                     const CORE_MATH_VECTOR & rectangle_size,
                     const CORE_MATH_VECTOR & other );

CORE_MATH_VECTOR
    Center,
    Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MATH_SHAPE_RECTANGLE__) */
