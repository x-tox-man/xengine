//
//  GRAPHIC_OBJECT_SHAPE_GRID.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_GRID__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_GRID__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_MESH.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE_GRID, GRAPHIC_OBJECT_SHAPE)

    GRAPHIC_OBJECT_SHAPE_GRID( float position[ 4 ], CORE_MATH_QUATERNION & orientation );
    virtual ~GRAPHIC_OBJECT_SHAPE_GRID();

    virtual void InitializeShape() override;

private :

    GRAPHIC_OBJECT_SHAPE_GRID();

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_GRID__) */
