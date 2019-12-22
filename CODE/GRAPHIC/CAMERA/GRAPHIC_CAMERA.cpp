//
//  GRAPHIC_CAMERA.cpp
//  GAME-ENGINE
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
    Fov( 30.0f ),
    AlternateProjectionMatrix( CORE_MATH_MATRIX::Identity ),
    ProjectionMatrix( CORE_MATH_MATRIX::Identity ),
    ViewMatrix( CORE_MATH_MATRIX::Identity ),
    Position(),
    Lookat(),
    Fustrum() {
    
    Lookat.Normalize();
}

GRAPHIC_CAMERA::GRAPHIC_CAMERA( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up_vector, float fov ) {
    
    Direction = -unnormalized_direction;
    Direction.Normalize();
    Position = position;
    Up = up_vector;
    
    Fov = fov;
    
    Near = near_plane;
    Far = far_plane;
    Width = width;
    Height = height;
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelMatrix( position, Direction, Up );
}

GRAPHIC_CAMERA::~GRAPHIC_CAMERA() {
    
}

void GRAPHIC_CAMERA::ActivateForRender() {
    
    Fustrum.UpdateFustrum( *this );
}

void GRAPHIC_CAMERA::Reset( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up_vector, float fov ) {
    
    Direction = -unnormalized_direction;
    Direction.Normalize();
    Position = position;
    Up = up_vector;
    
    CalculateProjectionMatrix( near_plane, far_plane, width, height );
    CalculateModelMatrix( position, Direction, Up );
    
    Near = near_plane;
    Far = far_plane;
    Width = width;
    Height = height;
    Fov = fov;
}

void GRAPHIC_CAMERA::UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up ) {
    
    Position = position;
    Direction = -unnormalized_direction;
    Direction.Normalize();
    Up = up;

    CalculateModelMatrix( Position, Direction, Up );
}

void GRAPHIC_CAMERA::CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height ) {
    
    const float half_width = width * 0.5f;
    const float half_height = height * 0.5f;
    
    float aspect = fabsf(half_width / half_height);
    float fovyRadians = ( float ) ( Fov * ( M_PI / 180.0f) );
    float cotan = 1.0f / tanf(fovyRadians * 0.5f);
    
    /*AlternateProjectionMatrix[0] = 1.0f / (aspect * tanf(fovyRadians * 0.5f));
    AlternateProjectionMatrix[1] =  0.0f;
    AlternateProjectionMatrix[2] =  0.0f;
    AlternateProjectionMatrix[3] =  0.0f;
    
    AlternateProjectionMatrix[4] =  0.0f;
    AlternateProjectionMatrix[5] =  cotan;
    AlternateProjectionMatrix[6] =  0.0f;
    AlternateProjectionMatrix[7] =  0.0f;
    
    AlternateProjectionMatrix[8] =  0.0f;
    AlternateProjectionMatrix[9] =  0.0f;
    AlternateProjectionMatrix[10] = (-near_plane -far_plane ) / (near_plane - far_plane);
    AlternateProjectionMatrix[11] = (2.0f * far_plane * near_plane) / (near_plane - far_plane);
    
    AlternateProjectionMatrix[12] =  0.0f;
    AlternateProjectionMatrix[13] =  0.0f;
    AlternateProjectionMatrix[14] =  1.0f;
    AlternateProjectionMatrix[15] =  0.0f;*/
    
    ProjectionMatrix[0] =  cotan / aspect;
    ProjectionMatrix[1] =  0.0f;
    ProjectionMatrix[2] =  0.0f;
    ProjectionMatrix[3] =  0.0f;

    ProjectionMatrix[4] =  0.0f;
    ProjectionMatrix[5] =  cotan;
    ProjectionMatrix[6] =  0.0f;
    ProjectionMatrix[7] =  0.0f;

    ProjectionMatrix[8] =  0.0f;
    ProjectionMatrix[9] =  0.0f;
    ProjectionMatrix[10] = far_plane / ( near_plane - far_plane);
    ProjectionMatrix[11] = -1.0f;


    ProjectionMatrix[12] =  0.0f;
    ProjectionMatrix[13] =  0.0f;
    ProjectionMatrix[14] =  near_plane * (far_plane / ( near_plane - far_plane));
    ProjectionMatrix[15] =  0.0f;
}

void GRAPHIC_CAMERA::CalculateModelMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & normalized_direction, const CORE_MATH_VECTOR & up_vector ) {
    
    CORE_MATH_MATRIX tmp, translation,rotation;
    
    translation.Translate( -position );
    
    CORE_MATH_VECTOR N, U, V;
    
    N = normalized_direction;
    U = up_vector;
    U = U.ComputeCrossProduct(N);
    U.Normalize();
    V = N.ComputeCrossProduct(U);
    
    rotation[0] = U.X(); rotation[1] = U.Y(); rotation[2] = U.Z(); rotation[3] = 0.0f;
    rotation[4] = V.X(); rotation[5] = V.Y(); rotation[6] = V.Z(); rotation[7] = 0.0f;
    rotation[8] = N.X(); rotation[9] = N.Y(); rotation[10] = N.Z(); rotation[11] = 0.0f;
    rotation[12] = 0.0f; rotation[13] = 0.0f; rotation[14] = 0.0f; rotation[15] = 1.0f;
    
    ViewMatrix = translation * rotation;
    ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;
}
