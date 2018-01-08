//
//  GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP.h
//  GAME-ENGINE
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

    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP( const void * heights, int x_width, int y_width, float lenght );
    virtual ~GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP();

    virtual void InitializeShape() override;

    inline int GetXWidth() const { return XWidth; }
    inline int GetYWidth() const { return YWidth; }
    inline float GetLength() const { return Length; }
    inline float GetHeightScale() const { return HeightScale; }
    inline void SetHeightScale( const float scale) { HeightScale = scale; }
    inline const float * GetHeights() { return (const float *) Heights; }

private :

    GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP();

    const void
        * Heights;
    int
        XWidth,
        YWidth;
    float
        Length,
        HeightScale;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_HEIGHT_MAP__) */
