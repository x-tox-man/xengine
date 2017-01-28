//
//  GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MATH_MATRIX.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP, GRAPHIC_OBJECT_SHAPE)

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( float * heights, int x_width, int y_width, float lenght );

virtual void InitializeShape( GRAPHIC_SHADER_PROGRAM * shader);
virtual void Render( const GRAPHIC_RENDERER & renderer );

private :

GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP();

float
    * Heights;
int
    XWidth,
    YWidth;
float
    Lenght;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP__) */
