//
//  GRAPHIC_OBJECT_SHAPE_LINE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_LINE__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_LINE__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_SHADER_BIND.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "CORE_HELPERS_IDENTIFIER_SYSTEM.h"
#include "GRAPHIC_SHADER_PROGRAM_DATA_PROXY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_OBJECT_SHAPE_LINE, GRAPHIC_OBJECT_SHAPE)

    GRAPHIC_OBJECT_SHAPE_LINE();
    virtual ~GRAPHIC_OBJECT_SHAPE_LINE();

    virtual void InitializeShape() override;

    inline void SetFrom( const CORE_MATH_VECTOR & target) { Vertices[0] = target[0]; Vertices[1] = target[1]; Vertices[2] = target[2]; Vertices[3] = target[3];}
    inline void SetTo( const CORE_MATH_VECTOR & target) { Vertices[4] = target[0]; Vertices[5] = target[1]; Vertices[6] = target[2]; Vertices[7] = target[3]; }

    void UpdateShape();

private:    

    float
        Vertices[8];
    GRAPHIC_SHADER_ATTRIBUTE
        * ShaderPositions;

    static CORE_HELPERS_IDENTIFIER ShaderLineGeometry;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE_LINE__) */
