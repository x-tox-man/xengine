//
//  GRAPHICS_CAMERA_MANAGER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 14/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GRAPHICS_CAMERA_MANAGER_hpp
#define GRAPHICS_CAMERA_MANAGER_hpp

#include "GRAPHIC_CAMERA.h"
#include "CORE_MATH_QUATERNION.h"
XS_CLASS_BEGIN(GRAPHICS_CAMERA_MANAGER)

    GRAPHICS_CAMERA_MANAGER();
    ~GRAPHICS_CAMERA_MANAGER();

    void Update( float step );
    inline void SetCamera(GRAPHIC_CAMERA* camera) { Camera = camera; }
    inline GRAPHIC_CAMERA * GetCamera() { return Camera; }
    void StartAnimation( float duration, const CORE_MATH_VECTOR & start, const CORE_MATH_VECTOR & end, const CORE_MATH_QUATERNION &, const CORE_MATH_QUATERNION &);

private:
    CORE_MATH_VECTOR
        StartPosition,
        EndPosition;
    CORE_MATH_QUATERNION
        StartOrientation,
        EndOrientation;
    float
        Duration,
        Accumulation;
    GRAPHIC_CAMERA
        * Camera;
XS_CLASS_END

#endif /* GRAPHICS_CAMERA_MANAGER_hpp */
