//
//  R3D_PLAYER_SHIP.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER_SHIP.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GRAPHIC_RENDERER.h"
#include "RUN3D_APPLICATION.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( R3D_PLAYER_SHIP )
    
XS_END_INTERNAL_MEMORY_LAYOUT

R3D_PLAYER_SHIP::R3D_PLAYER_SHIP() :
    GAMEPLAY_COMPONENT_ENTITY(),
    Parts(),
    Front(),
    Rear(),
    Top(),
    Steam(),
    Thrust( 0.0f ),
    Rotation( 0.0f ) {
    
}

R3D_PLAYER_SHIP::~R3D_PLAYER_SHIP() {
    
}

void R3D_PLAYER_SHIP::Initialize() {
    
    CORE_MATH_QUATERNION
        q;
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysicsScriptAnimation( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture(this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
#if PLATFORM_IOS || PLATFORM_ANDROID
    GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship-touch", "lua", "SCRIPTS" ) );
#else
    GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
#endif
    
    q.Normalize();
    
    CORE_MATH_VECTOR
        start_position(0.0f, 0.0f, 1.6f, 0.0f );
    
    //GAMEPLAY_HELPER::SetPhysicsSphereObject( this, start_position, q, 1.0f );
    GAMEPLAY_HELPER::SetPhysicsBoxObject( this, start_position, CORE_MATH_VECTOR(0.1f,0.1f,0.1f, 0.0f), q, 1.0f );
    
    GAMEPLAY_HELPER::AddToPhysics( this, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL, true );
    GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( this );

    SetOrientation( q );
    
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Front );
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Rear);
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Top);
    
    CreateWeaponSystem(start_position, q);
    
    Steam.Initialize();
}

void R3D_PLAYER_SHIP::CreateWeaponSystem( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
    GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    //GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
    
    CORE_MATH_VECTOR
        offset(0.1f, 2.0f, -0.1f, 0.0f );
    
    entity->SetOrientation( CORE_MATH_QUATERNION() );
    entity->SetPosition( offset );
    
    //GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( entity );
    SetChild(entity, 0);
}

void R3D_PLAYER_SHIP::Update( float step ) {
    
    CORE_MATH_VECTOR f(0.0f, 0.1f, 0.01f, 0.0f );
    CORE_MATH_VECTOR r(0.0f, -1.0f, 0.0f, 0.0f );
    CORE_MATH_VECTOR t(0.0f, 0.0f, 1.5f, 0.0f );
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    CORE_MATH_QUATERNION
        q = pos->GetOrientation(),
        q2 = pos->GetOrientation(),
        q3;
    
    q2.Normalize();
    q.Normalize();
    
    CORE_MATH_MATRIX m;
    q.RotateY( M_PI_2 );
    q.RotateY( M_PI_2 );
    q.ToMatrix( m.GetRow(0) );
    CORE_MATH_VECTOR vv = r * m;
    
    q2.RotateX( M_PI_2 );
    
    Front.UpdateCamera( pos->GetPosition() - (f * q), q2 );
    Rear.UpdateCamera( pos->GetPosition() + vv, q2 );
    Top.UpdateCamera( pos->GetPosition() + t, q3 );
    
    Steam.SetPosition( pos->GetPosition() );
    Steam.SetVelocity( phys->GetVelocity() );
    
    CORE_MATH_VECTOR elevation = GAMEPLAY_HELPER::GetElevation( this );
    
    /*if ( elevation.GetZ() < 1.0f ) {
        
        CORE_MATH_VECTOR & vel = phys->GetVelocity();
        
        float p = (1.0f - fabs(elevation.GetZ() ) ) * 2.81f;
        
        vel.Z( vel.Z() + p * step );
        
        phys->SetVelocity( vel );
    }*/
    
    #if PLATFORM_IOS || PLATFORM_ANDROID
        R3D_APP_PTR->SetCamera( &Rear );
    #endif
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        R3D_APP_PTR->SetCamera( &Front );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        R3D_APP_PTR->SetCamera( &Rear );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_T ) ) {
        
        R3D_APP_PTR->SetCamera( &Top );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_R ) ) {
        
        Reset(CORE_MATH_VECTOR( 0.0f, 0.0f, 1.5f, 0.0f), CORE_MATH_QUATERNION());
    }
    
    auto comp = (GAMEPLAY_COMPONENT_PHYSICS *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    auto comp_pos = (GAMEPLAY_COMPONENT_POSITION *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    CORE_MATH_VECTOR v = comp->GetVelocity();
    CORE_MATH_QUATERNION orientation = comp_pos->GetOrientation();
    
    R3D_APP_PTR->SetFrom( comp_pos->GetPosition() );
    R3D_APP_PTR->SetTo( comp_pos->GetPosition() + v * 10.0f);
    
    CORE_MATH_VECTOR x( 0.0f, 1.0f );
    CORE_MATH_VECTOR dir = orientation * (x * (GetThrust() * 5.0f) );
    
    comp->ApplyForce( dir );

    v = comp->GetVelocity();
    CORE_MATH_QUATERNION qr, qr2;
    qr.RotateZ( M_PI_4 * GetRotation() * step );
    qr2.RotateZ( M_PI_4 * GetRotation() * step );
    CORE_MATH_MATRIX
        mm;

    qr.ToMatrix( mm.GetRow( 0 ) );

    CORE_MATH_VECTOR v2 = v * mm;
    comp->SetVelocity( v2 );

    CORE_MATH_QUATERNION qrtot = comp_pos->GetOrientation() * qr2;
    qrtot.Normalize();

    SetOrientation( qrtot );
}

void R3D_PLAYER_SHIP::Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    SetPosition( position );
    SetOrientation( orientation );
    auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    phys->Reset();
}
