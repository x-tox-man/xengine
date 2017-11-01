//
//  GRAPHIC_CAMERA.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_CAMERA.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

GRAPHIC_CAMERA::GRAPHIC_CAMERA() :
    Near( 0.0f ),
    Far( 0.0f ),
    Width( 0.0f ),
    Height( 0.0f ),
    ProjectionMatrix( CORE_MATH_MATRIX::Identity ),
    ViewMatrix( CORE_MATH_MATRIX::Identity ),
    Position(),
    Lookat(),
    Fustrum() {
    
    Lookat.Normalize();
}

GRAPHIC_CAMERA::GRAPHIC_CAMERA( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelViewMatrix( position, lookat );
    
    Lookat = lookat;
    Position = position;
    
    Near = near_plane;
    Far = far_plane;
    Width = width;
    Height = height;
}

GRAPHIC_CAMERA::~GRAPHIC_CAMERA() {
    
}

void GRAPHIC_CAMERA::ActivateForRender() {
    
    Fustrum.UpdateFustrum( *this );
}

void GRAPHIC_CAMERA::Reset( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelViewMatrix( position, lookat );
    
    Lookat = lookat;
    Position = position;
    
    Near = near_plane;
    Far = far_plane;
    Width = width;
    Height = height;
}

void GRAPHIC_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    Lookat = lookat;
    Position = position;
    
    CalculateModelViewMatrix( position, lookat );
}

void GRAPHIC_CAMERA::CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) {
    
    const float half_width = width * 0.5f;
    const float half_height = height * 0.5f;
    
    float aspect = fabsf(half_width / half_height);
    float fovyRadians =  30.0f * (M_PI / 180);
    float cotan = 1.0f / tanf(fovyRadians * 0.5f);
    
    ProjectionMatrix[0] = cotan / aspect;
    ProjectionMatrix[1] =  0.0f;
    ProjectionMatrix[2] =  0.0f;
    ProjectionMatrix[3] =  0.0f;
    
    ProjectionMatrix[4] =  0.0f;
    ProjectionMatrix[5] =  cotan;
    ProjectionMatrix[6] =  0.0f;
    ProjectionMatrix[7] =  0.0f;
    
    ProjectionMatrix[8] =  0.0f;
    ProjectionMatrix[9] =  0.0f;
    ProjectionMatrix[10] = (far_plane + near_plane) / (near_plane - far_plane);
    ProjectionMatrix[11] = -1.0f;
    
    ProjectionMatrix[12] =  0.0f;
    ProjectionMatrix[13] =  0.0f;
    ProjectionMatrix[14] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);
    ProjectionMatrix[15] =  0.0f;
}

void GRAPHIC_CAMERA::CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat ) {
    
    CORE_MATH_MATRIX tmp, translation,rotation;
    
    translation[3] = position[0];
    translation[7] = position[1];
    translation[11] = position[2];
    
    lookat.ToMatrix( &rotation[0] );
    
    tmp =translation;
    tmp *=rotation;
    
    tmp.GetInverse(ViewMatrix);
}
