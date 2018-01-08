//
//  GAMEPLAY_CAMERA_FUSTRUM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/10/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_CAMERA_FUSTRUM.h"
#include "GRAPHIC_CAMERA.h"
#include "TOOLS_DEBUG_DRAW.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"

GRAPHIC_CAMERA_FUSTRUM::GRAPHIC_CAMERA_FUSTRUM() :
    FrustumPlanes()
{
        
}

GRAPHIC_CAMERA_FUSTRUM::~GRAPHIC_CAMERA_FUSTRUM() {
    
}

void GRAPHIC_CAMERA_FUSTRUM::UpdateFustrum( const GRAPHIC_CAMERA & camera ) {
    
    //Calculate fustrum orientation
    
    CORE_MATH_QUATERNION orientation = camera.GetOrientation();
    orientation.RotateX( ( float ) M_PI_2 );
    orientation.RotateX( ( float ) M_PI_2 );
    CORE_MATH_VECTOR fustrum_border_vector;
    CORE_MATH_MATRIX m, mm;
    orientation.ToMatrix( m.GetRow(0) );
    
    // front 0
    FrustumPlanes[0].Point = camera.GetPosition();
    
    FrustumPlanes[0].Normal = m * CORE_MATH_VECTOR(0.0f,
                                                   0.0f,
                                                   camera.GetNear(),
                                                   0.0f);
    FrustumPlanes[0].Normal.Normalize();
    FrustumPlanes[0].D = -FrustumPlanes[0].Point.X() * FrustumPlanes[0].Normal.X()
        -FrustumPlanes[0].Point.Y() * FrustumPlanes[0].Normal.Y()
        -FrustumPlanes[0].Point.Z() * FrustumPlanes[0].Normal.Z();
    
    // back 1
    FrustumPlanes[1].Point = camera.GetPosition() + m * CORE_MATH_VECTOR(0.0f, 0.0f, camera.GetFar(), 0.0f);
    
    FrustumPlanes[1].Normal = m * CORE_MATH_VECTOR(0.0f,
                                                   0.0f,
                                                   -camera.GetFar(),
                                                   0.0f);
    FrustumPlanes[1].Normal.Normalize();
    FrustumPlanes[1].D = -FrustumPlanes[1].Point.X() * FrustumPlanes[1].Normal.X()
    -FrustumPlanes[1].Point.Y() * FrustumPlanes[1].Normal.Y()
    -FrustumPlanes[1].Point.Z() * FrustumPlanes[1].Normal.Z();
    
    float l = ( float ) ( sin( M_PI / 6.0f ) * camera.GetFar() );
    
    // left 2
    {
        fustrum_border_vector.Set( -l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateZ( ( float )  -M_PI_2 );
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[2].Point = camera.GetPosition() + m * pt;
        ( r * orientation ).ToMatrix( mm.GetRow(0) );
        FrustumPlanes[2].Normal = mm * pt;
        FrustumPlanes[2].Normal.Normalize();
        FrustumPlanes[2].D = -FrustumPlanes[2].Point.X() * FrustumPlanes[2].Normal.X()
        -FrustumPlanes[2].Point.Y() * FrustumPlanes[2].Normal.Y()
        -FrustumPlanes[2].Point.Z() * FrustumPlanes[2].Normal.Z();
    }
    
    
    // rigth 3
    {
        fustrum_border_vector.Set( l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateZ( ( float ) M_PI_2 );
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[3].Point = camera.GetPosition() + m * pt;
        ( r * orientation ).ToMatrix( mm.GetRow(0) );
        FrustumPlanes[3].Normal = mm * pt;
        FrustumPlanes[3].Normal.Normalize();
        FrustumPlanes[3].D = -FrustumPlanes[3].Point.X() * FrustumPlanes[3].Normal.X()
        -FrustumPlanes[3].Point.Y() * FrustumPlanes[3].Normal.Y()
        -FrustumPlanes[3].Point.Z() * FrustumPlanes[3].Normal.Z();
    }
    
    // top 4
    {
        fustrum_border_vector.Set( 0.0f, l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) M_PI_2 );
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[4].Point = camera.GetPosition() + m * pt;
        (r * orientation ).ToMatrix( mm.GetRow(0) );
        FrustumPlanes[4].Normal = mm * pt;
        FrustumPlanes[4].Normal.Normalize();
        FrustumPlanes[4].D = -FrustumPlanes[4].Point.X() * FrustumPlanes[4].Normal.X()
        -FrustumPlanes[4].Point.Y() * FrustumPlanes[4].Normal.Y()
        -FrustumPlanes[4].Point.Z() * FrustumPlanes[4].Normal.Z();
    }
    
    // bottom 5
    {
        fustrum_border_vector.Set( 0.0f, - l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) -M_PI_2 );
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[5].Point = camera.GetPosition() + m * pt;
        (r * orientation ).ToMatrix( mm.GetRow(0) );
        FrustumPlanes[5].Normal = mm * pt;
        FrustumPlanes[5].Normal.Normalize();
        FrustumPlanes[5].D = -FrustumPlanes[5].Point.X() * FrustumPlanes[5].Normal.X()
            -FrustumPlanes[5].Point.Y() * FrustumPlanes[5].Normal.Y()
            -FrustumPlanes[5].Point.Z() * FrustumPlanes[5].Normal.Z();
    }
}

bool GRAPHIC_CAMERA_FUSTRUM::SphereInFrustum( const CORE_MATH_VECTOR & position, const float radius ) const
{
    //test all 6 frustum planes
    for (int i = 0; i < 6; i++)
    {
        //calculate distance from sphere center to plane.
        //if distance larger then sphere radius - sphere is outside frustum
        float t = FrustumPlanes[i].Normal.X() * position.X() + FrustumPlanes[i].Normal.Y() * position.Y() + FrustumPlanes[i].Normal.Z() * position.Z() + FrustumPlanes[i].D;
        if ( t <= (-radius) ) {
            return false; //with flag works faster
        }
    }
    
    return true;
}

void GRAPHIC_CAMERA_FUSTRUM::DebugDraw( const GRAPHIC_CAMERA & camera ) const {
    
#if DEBUG
    //Calculate fustrum orientation
    CORE_MATH_QUATERNION b;
    b.RotateX( ( float ) -M_PI_2 );
    
    const CORE_MATH_QUATERNION & orientation = camera.GetOrientation() * b;
    //CORE_MATH_QUATERNION orientation;
    CORE_MATH_VECTOR fustrum_border_vector, to1, to2, to3, to4;
    CORE_MATH_MATRIX m;
    orientation.ToMatrix( m.GetRow(0) );
    
    float l =( float ) ( sin( M_PI / 6.0f ) * camera.GetFar() );
    
    
    {
        fustrum_border_vector.Set( -l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateZ( ( float ) M_PI_2 );
        to1 = m * (camera.GetPosition() + CORE_MATH_VECTOR(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W()) );
        #ifndef X_VK
            TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to1);
        #endif
    }
    
    
    // rigth 3
    {
        fustrum_border_vector.Set( l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateZ( ( float ) -M_PI_2 );
        to2 = m * (camera.GetPosition() + CORE_MATH_VECTOR(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W()) );
#ifndef X_VK
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to2);
#endif
    }
    
    // top 4
    {
        fustrum_border_vector.Set( 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, l * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) -M_PI_2 );
        to3 = m * (camera.GetPosition() + CORE_MATH_VECTOR(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W()) );
#ifndef X_VK
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to3);
#endif
    }
    
#ifndef X_VK
    TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to1, to4);
    TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to1, to2);
    TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to2, to3);
    TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to3, to4);
#endif
#endif
}
