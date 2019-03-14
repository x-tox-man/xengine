//
//  GRAPHIC_CAMERA.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_CAMERA__
#define __GAME_ENGINE_REBORN__GRAPHIC_CAMERA__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_QUATERNION.h"
#include "GRAPHIC_CAMERA_FUSTRUM.h"

XS_CLASS_BEGIN( GRAPHIC_CAMERA )
    
    GRAPHIC_CAMERA();
    GRAPHIC_CAMERA( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up_vector, float fov = 30.0f );
    virtual ~GRAPHIC_CAMERA();

    inline const CORE_MATH_MATRIX & GetProjectionMatrix() const { return ProjectionMatrix; }
    inline CORE_MATH_MATRIX GetAlternateProjectionMatrix() const { return AlternateProjectionMatrix; }
    inline const CORE_MATH_MATRIX & GetViewMatrix() const { return ViewMatrix; }
    inline const CORE_MATH_MATRIX & GetProjectionViewMatrix() const { return ProjectionViewMatrix; }
    inline const CORE_MATH_VECTOR & GetPosition() const { return Position; }
    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Lookat; }
    inline float GetNear() const { return Near; }
    inline float GetFar() const { return Far; }
    inline float GetWidth() const { return Width; }
    inline float GetHeight() const { return Height; }
    inline float GetFov() const { return Fov; }

    inline const CORE_MATH_VECTOR & GetUp() const { return Up; }
    inline const CORE_MATH_VECTOR & GetDirection() const { return Direction; }

    inline const GRAPHIC_CAMERA_FUSTRUM & GetFustrum() const {return Fustrum; }

    void Reset( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up_vector, float fov = 30.0f );
    void UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & unnormalized_direction, const CORE_MATH_VECTOR & up = CORE_MATH_VECTOR::YAxis );
    void ActivateForRender();

private :

protected :

    virtual void CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height );
    virtual void CalculateModelMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_VECTOR & normalized_direction, const CORE_MATH_VECTOR & up_vector );

    float
        Near,
        Far,
        Width,
        Height,
        Fov;
    CORE_MATH_VECTOR
        Position,
        Direction,
        Up;
    CORE_MATH_MATRIX
        AlternateProjectionMatrix,
        ProjectionMatrix,
        ViewMatrix,
        ProjectionViewMatrix;
    CORE_MATH_QUATERNION
        Lookat;
    GRAPHIC_CAMERA_FUSTRUM
        Fustrum;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_CAMERA__) */
