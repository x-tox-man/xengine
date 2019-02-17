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
    CORE_MATH_MATRIX m, mm;
    orientation.ToMatrix( m.GetRow(0) );
    
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
        fustrum_border_vector.Set( -l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateY( ( float )  M_PI_2 );
        r.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[2].Normal = mm * fustrum_border_vector;
        orientation.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[2].Normal = mm * FrustumPlanes[2].Normal;
        FrustumPlanes[2].Normal.Normalize();
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[2].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[2].D = - FrustumPlanes[2].Point.ComputeDotProduct( FrustumPlanes[2].Normal );
    }
    
    
    // rigth 3
    {
        fustrum_border_vector.Set( l * 0.5f, 0.0f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateY( ( float ) -M_PI_2 );
        r.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[3].Normal = mm * fustrum_border_vector;
        orientation.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[3].Normal = mm * FrustumPlanes[3].Normal;
        FrustumPlanes[3].Normal.Normalize();
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[3].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[3].D = - FrustumPlanes[3].Point.ComputeDotProduct( FrustumPlanes[3].Normal );
    }
    
    // top 4
    {
        fustrum_border_vector.Set( 0.0f, l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) M_PI_2 );
        r.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[4].Normal = mm * fustrum_border_vector;
        orientation.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[4].Normal = mm * FrustumPlanes[4].Normal;
        FrustumPlanes[4].Normal.Normalize();
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[4].Point = camera.GetPosition() + m * pt;
        FrustumPlanes[4].D = - FrustumPlanes[4].Point.ComputeDotProduct( FrustumPlanes[4].Normal );
    }
    
    // bottom 5
    {
        fustrum_border_vector.Set( 0.0f, - l * 0.5f, (camera.GetFar() -camera.GetNear()) * 0.5f, 0.0f );
        CORE_MATH_QUATERNION r;
        r.RotateX( ( float ) -M_PI_2 );
        r.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[5].Normal = mm * fustrum_border_vector;
        orientation.ToMatrix( mm.GetRow(0) );
        FrustumPlanes[5].Normal = mm * FrustumPlanes[5].Normal;
        FrustumPlanes[5].Normal.Normalize();
        
        const CORE_MATH_VECTOR pt(fustrum_border_vector.X(), fustrum_border_vector.Y(), fustrum_border_vector.Z(), fustrum_border_vector.W());
        FrustumPlanes[5].Point = camera.GetPosition() + m * pt;
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
    
    CORE_MATH_VECTOR in_min, in_max;
    box.ComputeMinMax( in_min, in_max );

    CORE_MATH_VECTOR vmin, vmax;

    for(int i = 0; i < 6; ++i) {
        // X axis
        if(FrustumPlanes[i].Normal.X() > 0) {
            
            vmin.X( in_min.X() );
            vmax.X( in_max.X() );
        }
        else {
            
            vmin.X( in_max.X() );
            vmax.X( in_min.X() );
        }
        // Y axis
        if(FrustumPlanes[i].Normal.Y() > 0) {
            
            vmin.Y( in_min.Y() );
            vmax.Y( in_max.Y() );
        }
        else {
            
            vmin.Y( in_max.Y() );
            vmax.Y( in_min.Y() );
        }
        // Z axis
        if( FrustumPlanes[i].Normal.Z() > 0) {
            
            vmin.Z( in_min.Z() );
            vmax.Z( in_max.Z() );
        }
        else {
            
            vmin.Z( in_max.Z() );
            vmax.Z( in_min.Z() );
        }
        
        float distance = ( in_min - FrustumPlanes[i].Point ).ComputeDotProduct(FrustumPlanes[i].Normal );
        
        if ( distance < 0.0f )
            return false;
    }
    
    return true;
}
