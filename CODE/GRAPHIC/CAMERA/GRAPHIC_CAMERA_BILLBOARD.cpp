//
//  GRAPHIC_CAMERA_BILLBOARD.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_CAMERA_BILLBOARD.h"

GRAPHIC_CAMERA_BILLBOARD::GRAPHIC_CAMERA_BILLBOARD() :
    GRAPHIC_CAMERA() {
    
}

GRAPHIC_CAMERA_BILLBOARD::GRAPHIC_CAMERA_BILLBOARD( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelViewMatrix( position, lookat );
    
    Position = position;
}

GRAPHIC_CAMERA_BILLBOARD::~GRAPHIC_CAMERA_BILLBOARD() {
    
}

void GRAPHIC_CAMERA_BILLBOARD::CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) {
    
}

void GRAPHIC_CAMERA_BILLBOARD::CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
}