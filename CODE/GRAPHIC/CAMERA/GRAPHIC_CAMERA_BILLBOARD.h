//
//  GRAPHIC_CAMERA_BILLBOARD.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_CAMERA_BILLBOARD_hpp
#define GRAPHIC_CAMERA_BILLBOARD_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_CAMERA.h"


XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_CAMERA_BILLBOARD, GRAPHIC_CAMERA )

    GRAPHIC_CAMERA_BILLBOARD();
    GRAPHIC_CAMERA_BILLBOARD( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );
    virtual ~GRAPHIC_CAMERA_BILLBOARD();

    virtual void CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) override;
    virtual void CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) override;

XS_CLASS_END

#endif /* GRAPHIC_CAMERA_BILLBOARD_hpp */
