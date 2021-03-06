//
//  GRAPHIC_OBJECT_SHAPE_CUBE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_CUBE__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_CUBE__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE_CUBE, GRAPHIC_OBJECT_SHAPE)

    GRAPHIC_OBJECT_SHAPE_CUBE();
    virtual ~GRAPHIC_OBJECT_SHAPE_CUBE();

    virtual void InitializeShape() override;

    void UpdateGeometry( const CORE_MATH_VECTOR & center, const CORE_MATH_VECTOR & extent );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_CUBE__) */
