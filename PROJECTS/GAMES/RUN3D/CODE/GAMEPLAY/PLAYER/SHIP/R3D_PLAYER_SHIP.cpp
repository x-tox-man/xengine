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
    Rotation( 0.0f ),
    ModifiersMap() {
        
    ModifiersMap[ R3D_PLAYER_MODIFIER::MaxSpeedModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::HorsePowerModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::FuelCapacityModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::WeaponReloadTimeModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::GravityModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::MassModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::SteeringModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::ExperienceGainModifier ].SetValue( 1.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::BrakeModifier ].SetValue( 1.0f );
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
    
    GAMEPLAY_HELPER::SetPhysicsSphereObject( this, start_position, q, 100.0f );
    //GAMEPLAY_HELPER::SetPhysicsBoxObject( this, start_position, CORE_MATH_VECTOR(0.1f,0.1f,0.1f, 0.0f), q, 1.0f );
    
    auto phys = ( GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    phys->EnableCCD();
    
    GAMEPLAY_HELPER::AddToPhysics( this, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL, true );
    GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( this );

    SetOrientation( q );
    
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Front );
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Rear);
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Top);
    
    //CreateWeaponSystem(start_position, q);
    
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
    
    CORE_MATH_VECTOR
        elevation,
        normal,
        velocity,
        x( 0.0f, 1.0f ),
        dir;
    CORE_MATH_QUATERNION
        orientation,
        qr,
        qrtot;
    CORE_MATH_MATRIX
        mm;
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    UpdateCamera( step, pos, phys );
    
    GAMEPLAY_HELPER::GetElevation( this, elevation, normal );
    
    velocity = phys->GetVelocity();
    orientation = pos->GetOrientation();
    
    if ( elevation.GetZ() <= 0.1f && normal != CORE_MATH_VECTOR::Zero ) {
        
        velocity.Y( 0.0f );
        velocity.X( 0.0f );
        velocity.Z( 400.81f * cosf( 0.5f - elevation.GetZ() * 2.0f ) );
        
        phys->ApplyForce( velocity );
    }
    
    float
        actual_speed = velocity.ComputeLength();
    
    orientation.ToMatrix( mm.GetRow( 0 ) );

    dir = x * mm;
    
    phys->ApplyForce( dir * (GetThrust() * (500.0f - actual_speed ) ) );
    velocity = phys->GetVelocity();

    qr.RotateZ( GetRotation() * step );

    qrtot = pos->GetOrientation() * qr;
    qrtot.Normalize();
    
    qr.RotateZ( -GetRotation() * step );
    qr.RotateZ( -GetRotation() * step );
    qr.ToMatrix( mm.GetRow( 0 ) );
    
    velocity = velocity * mm;
    phys->SetVelocity( velocity );
    
    SetOrientation( qrtot );
    
#if DEBUG
    R3D_APP_PTR->SetFrom( pos->GetPosition() );
    R3D_APP_PTR->SetTo( pos->GetPosition() + velocity * 10.0f);
#endif
    
    Steam.SetPosition( pos->GetPosition() );
    Steam.SetVelocity( phys->GetVelocity() );
}

void R3D_PLAYER_SHIP::UpdateCamera( float step, GAMEPLAY_COMPONENT_POSITION::PTR pos, GAMEPLAY_COMPONENT_PHYSICS::PTR phys ) {
    
    static CORE_MATH_VECTOR
        f(0.0f, 0.1f, 0.01f, 0.0f ),
        r(0.0f, -0.5f, -0.1f, 0.0f ),
        t(0.0f, 0.0f, 1.5f, 0.0f );
    CORE_MATH_QUATERNION
        q = pos->GetOrientation(),
        q2 = pos->GetOrientation(),
        q3;
    CORE_MATH_MATRIX
        m;
    CORE_MATH_VECTOR
        vv;
    
    q.RotateY( M_PI_2 );
    q.RotateY( M_PI_2 );
    q.ToMatrix( m.GetRow(0) );
    q2.RotateX( M_PI_2 );
    
    vv = r * m;
    
    Front.UpdateCamera( pos->GetPosition() - (f * q), q2 );
    Rear.UpdateCamera( pos->GetPosition() + vv, q2 );
    Top.UpdateCamera( pos->GetPosition() + t, q3 );
    
#if PLATFORM_IOS || PLATFORM_ANDROID
    R3D_APP_PTR->SetCamera( &Rear );
#else
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
        
        Reset(CORE_MATH_VECTOR( 0.0f, 0.0f, 2.5f, 0.0f), CORE_MATH_QUATERNION());
    }
#endif
}

void R3D_PLAYER_SHIP::Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    SetPosition( position );
    SetOrientation( orientation );
    auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    phys->Reset();
}
