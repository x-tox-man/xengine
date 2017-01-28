//
//  GRAPHIC_CAMERA_ORTHOGONAL.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_CAMERA_ORTHOGONAL.h"

GRAPHIC_CAMERA_ORTHOGONAL::GRAPHIC_CAMERA_ORTHOGONAL() :
    GRAPHIC_CAMERA() {
    
}

GRAPHIC_CAMERA_ORTHOGONAL::GRAPHIC_CAMERA_ORTHOGONAL( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelViewMatrix( position, lookat );
    
    Position = position;
}

GRAPHIC_CAMERA_ORTHOGONAL::~GRAPHIC_CAMERA_ORTHOGONAL() {

}

void GRAPHIC_CAMERA_ORTHOGONAL::CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) {
    
    const float half_width = width * 0.5f;
    const float half_height = height * 0.5f;

    const float far_minus_near = ( far_plane - near_plane );
    
    ProjectionMatrix[0] = 1.0f / half_width;
    ProjectionMatrix[1] =  0.0f;
    ProjectionMatrix[2] =  0.0f;
    ProjectionMatrix[3] =  0.0f;
    
    ProjectionMatrix[4] =  0.0f;
    ProjectionMatrix[5] =  1.0f / half_height;
    ProjectionMatrix[6] =  0.0f;
    ProjectionMatrix[7] =  0.0f;
    
    ProjectionMatrix[8] =  0.0f;
    ProjectionMatrix[9] =  0.0f;
    ProjectionMatrix[10] = 1 / far_minus_near;
    ProjectionMatrix[11] = - near_plane / far_minus_near;
    
    ProjectionMatrix[12] = 0.0f;
    ProjectionMatrix[13] = 0.0f;
    ProjectionMatrix[14] = 0.0f;
    ProjectionMatrix[15] = 1.0f;
}

void GRAPHIC_CAMERA_ORTHOGONAL::CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CORE_MATH_MATRIX translation,rotation, inverse;
    
    translation[3] = position[0];
    translation[7] = position[1];
    translation[11] = position[2];
    
    lookat.ToMatrix( &rotation[0] );

    inverse = rotation;
    inverse *= translation;
    
    inverse.GetInverse(ViewMatrix);
}
