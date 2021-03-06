//
//  GRAPHIC_CAMERA_ORTHOGONAL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_CAMERA_ORTHOGONAL__
#define __GAME_ENGINE_REBORN__GRAPHIC_CAMERA_ORTHOGONAL__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_CAMERA.h"

// We will not handle the orthogonal camera for now, perspective only

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_CAMERA_ORTHOGONAL, GRAPHIC_CAMERA )

    GRAPHIC_CAMERA_ORTHOGONAL();

    GRAPHIC_CAMERA_ORTHOGONAL( float near, float far, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );

    virtual void CalculateProjectionMatrix( float near, float far, float width, float height );
    virtual void CalculateViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_CAMERA_ORTHOGONAL__) */
