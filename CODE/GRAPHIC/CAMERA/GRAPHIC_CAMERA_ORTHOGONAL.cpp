//
//  GRAPHIC_CAMERA_ORTHOGONAL.cpp
//  GAME-ENGINE
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
    Lookat = lookat;
}

GRAPHIC_CAMERA_ORTHOGONAL::GRAPHIC_CAMERA_ORTHOGONAL( float left, float right, float bottom, float top, float near_, float far_ ) {
    
    InitOrthoProjTransform( left, right, bottom, top, near_, far_ );
}

GRAPHIC_CAMERA_ORTHOGONAL::~GRAPHIC_CAMERA_ORTHOGONAL() {

}

void GRAPHIC_CAMERA_ORTHOGONAL::CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) {
    
    const float half_width = width * 0.5f;
    const float half_height = height * 0.5f;

    /*const float far_minus_near = ( far_plane - near_plane );
    
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
    ProjectionMatrix[15] = 1.0f;*/
    
    InitOrthoProjTransform( -half_width, half_width, -half_height, half_height, near_plane, far_plane );
}

void GRAPHIC_CAMERA_ORTHOGONAL::CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CORE_MATH_MATRIX tmp,scale, translation,rotation;
    
    lookat.ToMatrix( &rotation[0] );
    translation.Translate( position );
    
    tmp = translation * rotation * scale;
    tmp.GetInverse( ViewMatrix );
}

void GRAPHIC_CAMERA_ORTHOGONAL::InitOrthoProjTransform( float left, float right, float bottom, float top, float near_, float far_ )
{
    float l = left;
    float r = right;
    float b = bottom;
    float t = top;
    float n = near_;
    float f = far_;
    
    float * m = ProjectionMatrix.GetRow(0);
    
    m[0] = 2.0f/(r - l);    m[1] = 0.0f;            m[2] = 0.0f;            m[3] = -(r + l)/(r - l);
    m[4] = 0.0f;            m[5] = 2.0f/(t - b);    m[6] = 0.0f;            m[7] = -(t + b)/(t - b);
    m[8] = 0.0f;            m[9] = 0.0f;            m[10] = 2.0f/(f - n);   m[11] = -(f + n) / (f - n );
    m[12] = 0.0f;           m[13] = 0.0f;           m[14] = 0.0f;           m[15] = 1.0;
    
    CalculateModelViewMatrix( GetPosition(), GetOrientation() );
}
