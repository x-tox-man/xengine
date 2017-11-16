//
//  GRAPHIC_CAMERA_FUSTRUM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/10/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CAMERA_FUSTRUM_hpp
#define GAMEPLAY_CAMERA_FUSTRUM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"

class GRAPHIC_CAMERA;

XS_CLASS_BEGIN( GRAPHIC_CAMERA_FUSTRUM )

    GRAPHIC_CAMERA_FUSTRUM();
    ~GRAPHIC_CAMERA_FUSTRUM();

    void UpdateFustrum( const GRAPHIC_CAMERA & camera );

    bool SphereInFrustum( const CORE_MATH_VECTOR & position, const float radius ) const;

    void DebugDraw( const GRAPHIC_CAMERA & camera ) const;

private:

    struct __PLANE {
        
        CORE_MATH_VECTOR
            Point,
            Normal;
        float
            D;
    };

    __PLANE
        FrustumPlanes[ 6 ];

XS_CLASS_END

#endif /* GRAPHIC_CAMERA_FUSTRUM_hpp */
