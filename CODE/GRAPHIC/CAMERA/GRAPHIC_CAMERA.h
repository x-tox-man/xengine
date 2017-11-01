//
//  GRAPHIC_CAMERA.h
//  GAME-ENGINE-REBORN
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
    GRAPHIC_CAMERA( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );
    virtual ~GRAPHIC_CAMERA();

    inline const CORE_MATH_MATRIX & GetProjectionMatrix() const { return ProjectionMatrix; }
    inline const CORE_MATH_MATRIX & GetViewMatrix() const { return ViewMatrix; }
    inline const CORE_MATH_VECTOR & GetPosition() const { return Position; }
    inline const CORE_MATH_QUATERNION & GetOrientation() const { return Lookat; }
    inline float GetNear() const { return Near; }
    inline float GetFar() const { return Far; }
    inline float GetWidth() const { return Width; }
    inline float GetHeight() const { return Height; }

    inline const GRAPHIC_CAMERA_FUSTRUM & GetFustrum() const {return Fustrum; }

    void Reset( float near_plane, float far_plane, float width, float height, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );
    void UpdateCamera( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );
    void ActivateForRender();

private :

    virtual void CalculateProjectionMatrix( float near_plane, float far_plane, float width, float height );
    virtual void CalculateModelViewMatrix( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat );

protected :

    float
        Near,
        Far,
        Width,
        Height;
    CORE_MATH_VECTOR
        Position;
    CORE_MATH_MATRIX
        ProjectionMatrix,
        ViewMatrix;
    CORE_MATH_QUATERNION
        Lookat;
    GRAPHIC_CAMERA_FUSTRUM
        Fustrum;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_CAMERA__) */
