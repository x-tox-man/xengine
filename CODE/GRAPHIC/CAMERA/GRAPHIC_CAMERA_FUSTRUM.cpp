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
    
    CORE_MATH_QUATERNION orientation = camera.GetOrientation().Inverse();
    CORE_MATH_VECTOR fustrum_border_vector;
    CORE_MATH_MATRIX m;
    
    m = CORE_MATH_MATRIX::FromDirectionAndUpVector( -camera.GetDirection(), -camera.GetUp() );
    // front 0
    FrustumPlanes[0].Point = camera.GetPosition();
    
    FrustumPlanes[0].Normal = m * CORE_MATH_VECTOR(0.0f,
                                                   0.0f,
                                                   camera.GetNear(),
                                                   0.0f);
    FrustumPlanes[0].Normal.Normalize();
    FrustumPlanes[0].D = - FrustumPlanes[0].Point.ComputeDotProduct( FrustumPlanes[0].Normal );
    
    // back 1
    FrustumPlanes[1].Point = camera.GetPosition() + m * CORE_MATH_VECTOR(0.0f, 0.0f, camera.GetFar(), 0.0f);
    
    FrustumPlanes[1].Normal = m * CORE_MATH_VECTOR(0.0f,
                                                   0.0f,
                                                   -camera.GetFar(),
                                                   0.0f);
    FrustumPlanes[1].Normal.Normalize();
    FrustumPlanes[1].D = - FrustumPlanes[1].Point.ComputeDotProduct( FrustumPlanes[1].Normal );
    
    float l = ( float ) ( sin( M_PI / 6.0f ) * camera.GetFar() );
    
    // left 2
    {
        CORE_MATH_MATRIX mm;
        fustrum_border_vector.Set( -l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        mm.YRotate( ( float )  M_PI_2 );
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[2].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[2].Normal = m * mm * pt;
        FrustumPlanes[2].Normal.Normalize();
        FrustumPlanes[2].D = - FrustumPlanes[2].Point.ComputeDotProduct( FrustumPlanes[2].Normal );
    }
    
    
    // rigth 3
    {
        CORE_MATH_MATRIX mm;
        fustrum_border_vector.Set( l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        mm.YRotate( ( float )  -M_PI_2 );
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[3].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[3].Normal = m * mm * pt;
        FrustumPlanes[3].Normal.Normalize();
        FrustumPlanes[3].D = - FrustumPlanes[3].Point.ComputeDotProduct( FrustumPlanes[3].Normal );
    }
    
    // top 4
    {
        CORE_MATH_MATRIX mm;
        fustrum_border_vector.Set( 0.0f, l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        mm.XRotate( ( float )  M_PI_2 );
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[4].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[4].Normal = m * mm * pt;
        FrustumPlanes[4].Normal.Normalize();
        FrustumPlanes[4].D = - FrustumPlanes[4].Point.ComputeDotProduct( FrustumPlanes[4].Normal );
    }
    
    // bottom 5
    {
        CORE_MATH_MATRIX mm;
        fustrum_border_vector.Set( 0.0f, -l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        mm.XRotate( ( float ) -M_PI_2 );
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[5].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[5].Normal = m * mm * pt;
        FrustumPlanes[5].Normal.Normalize();
        FrustumPlanes[5].D = - FrustumPlanes[5].Point.ComputeDotProduct( FrustumPlanes[5].Normal );
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
    CORE_MATH_VECTOR fustrum_border_vector, to1, to2, to3, to4;
    CORE_MATH_MATRIX m;
    b.RotateX( ( float ) -M_PI_2 );
    
    CORE_MATH_VECTOR
        up(0.0f, 1.0f, 0.0f, 0.0f),dir;
    
    camera.GetOrientation().ToMatrix( m.GetRow(0) );
    dir = m * up;
    
    const CORE_MATH_QUATERNION & orientation = camera.GetOrientation() * b;
    //CORE_MATH_QUATERNION orientation;
    
    orientation.ToMatrix( m.GetRow(0) );
    
    float l =( float ) ( sin( M_PI / 6.0f ) * camera.GetFar() );
    
    
    //top left
    {
        fustrum_border_vector.Set( -l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, l * 0.5f, 0.0f );
        //CORE_MATH_QUATERNION r;
        //r.RotateZ( ( float ) M_PI_2 );
        to1 = camera.GetPosition() + m * fustrum_border_vector;
        #if X_VK == 0
            TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to1);
        #endif
    }
    
    
    //top right
    {
        fustrum_border_vector.Set( l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, l * 0.5f, 0.0f );
        //CORE_MATH_QUATERNION r;
        //r.RotateZ( ( float ) -M_PI_2 );
        to2 = camera.GetPosition() + m * fustrum_border_vector;
#if X_VK == 0
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to2);
#endif
    }
    
    // bottom right
    {
        fustrum_border_vector.Set( l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, -l * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) -M_PI_2 );
        to3 = camera.GetPosition() + m * fustrum_border_vector;
#if X_VK == 0
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to3);
#endif
    }
    
    // bottom right
    {
        fustrum_border_vector.Set( -l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, -l * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) -M_PI_2 );
        to4 = camera.GetPosition() + m * fustrum_border_vector;
#if X_VK == 0
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), camera.GetPosition(), to3);
#endif
    }
    
    #if X_VK == 0
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to1, to4);
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to1, to2);
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to2, to3);
        TOOLS_DEBUG_DRAW::Instance->DrawLine(GRAPHIC_RENDERER::GetInstance(), to3, to4);
    #endif
#endif
}

bool GRAPHIC_CAMERA_FUSTRUM::BoxInFrustum( const CORE_MATH_SHAPE & box ) const {
    
    //http://old.cescg.org/CESCG-2002/DSykoraJJelinek/
    float m, n; int i, result = true;
    
    for (i = 0; i < 6; i++) {
        
        m = (box.GetPosition().X() * FrustumPlanes[i].Normal.X() ) + (box.GetPosition().Y() * FrustumPlanes[i].Normal.Y()) + (box.GetPosition().Z() * FrustumPlanes[i].Normal.Z() ) + FrustumPlanes[i].D;
        n = ( box.GetHalfDiagonal().X() * fabs( FrustumPlanes[i].Normal.X() ) ) + ( box.GetHalfDiagonal().Y() * fabs( FrustumPlanes[i].Normal.Y() ) ) + ( box.GetHalfDiagonal().Z() * fabs(FrustumPlanes[i].Normal.Z() ) );
        
        if (m + n < 0)
            return false;
        if (m - n < 0)
            result = true;
        
    }
    
    return result;
}
