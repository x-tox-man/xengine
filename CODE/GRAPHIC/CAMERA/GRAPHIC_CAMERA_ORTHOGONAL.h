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

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_CAMERA_ORTHOGONAL, GRAPHIC_CAMERA )

    GRAPHIC_CAMERA_ORTHOGONAL();
    GRAPHIC_CAMERA_ORTHOGONAL( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );
    virtual ~GRAPHIC_CAMERA_ORTHOGONAL();

    virtual void CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) override;
    virtual void CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) override;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_CAMERA_ORTHOGONAL__) */
