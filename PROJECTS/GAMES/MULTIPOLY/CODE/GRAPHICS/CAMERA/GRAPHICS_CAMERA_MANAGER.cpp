//
//  GRAPHICS_CAMERA_MANAGER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 14/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GRAPHICS_CAMERA_MANAGER.h"
#include "CORE_MATH.h"

GRAPHICS_CAMERA_MANAGER::GRAPHICS_CAMERA_MANAGER() :
    StartPosition(),
    EndPosition(),
    StartOrientation(),
    EndOrientation(),
    Duration( 0.0f ),
    Accumulation( 0.0f ) {
    
}

GRAPHICS_CAMERA_MANAGER::~GRAPHICS_CAMERA_MANAGER() {
    
}

void GRAPHICS_CAMERA_MANAGER::Update( float step ) {
    
    if ( Accumulation < Duration ) {
        
        Accumulation += step;
        float percentage = sinf( M_PI_2 * (Accumulation / Duration ) );
        
        CORE_MATH_VECTOR v = CORE_MATH_GetLerpInterpolation(StartPosition, EndPosition, percentage);
        CORE_MATH_QUATERNION o = CORE_MATH_GetLerpInterpolation(StartOrientation, EndOrientation, percentage);
        
        Camera->UpdateCamera(v, o);
    }
}

void GRAPHICS_CAMERA_MANAGER::StartAnimation( float duration, const CORE_MATH_VECTOR & startp, const CORE_MATH_VECTOR & endp, const CORE_MATH_QUATERNION & starto, const CORE_MATH_QUATERNION &endo) {
    
    Accumulation = 0.0f;
    Duration = duration;
    StartPosition = startp;
    EndPosition = endp;
    StartOrientation = starto;
    EndOrientation = endo;
}
