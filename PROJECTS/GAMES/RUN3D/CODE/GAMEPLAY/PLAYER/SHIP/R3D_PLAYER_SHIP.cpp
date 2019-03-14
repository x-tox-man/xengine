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
    GAMEPLAY_HELPER::SetShadowmapEffect( this );
    GAMEPLAY_HELPER::SetTexture(this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
#if PLATFORM_IOS || PLATFORM_ANDROID
    GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship-touch", "lua", "SCRIPTS" ) );
#else
    GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
#endif
    
    CORE_MATH_VECTOR
        start_position(0.0f, 2.0f, 0.0, 0.0f );
    
    GAMEPLAY_HELPER::SetPhysicsSphereObject( this, start_position, q, 1.0f );
    GAMEPLAY_HELPER::SetPhysicsBoxObject( this, start_position, CORE_MATH_VECTOR(0.04f,0.03f, 0.15f, 0.0f), q, 1.0f );
    
    auto phys = ( GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    phys->EnableCCD();
    
    //GAMEPLAY_HELPER::ConfigureGroundSpring( this );
    
    GAMEPLAY_HELPER::AddToPhysics( this, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL, true );
    GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( this );

    CORE_MATH_MATRIX top_matrix;
    top_matrix.XRotate( -M_PI_2 );
    
    GAMEPLAY_HELPER::InitializeCamera( start_position, CORE_MATH_VECTOR::ZAxis, Front, CORE_MATH_VECTOR::YAxis );
    GAMEPLAY_HELPER::InitializeCamera( start_position, CORE_MATH_VECTOR::ZAxis, Rear, CORE_MATH_VECTOR::YAxis);
    GAMEPLAY_HELPER::InitializeCamera( start_position, top_matrix * CORE_MATH_VECTOR::ZAxis, Top, top_matrix * CORE_MATH_VECTOR::YAxis );
    
    CreateWeaponSystem( start_position, q );
    
    Steam.Initialize();
}

void R3D_PLAYER_SHIP::CreateWeaponSystem( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
        GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
            offset(0.05f, 0.0f, 0.0f, 0.0f );
        
        CORE_MATH_QUATERNION q;
        q.RotateY( M_PI_2 );
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        GRAPHIC_SHADER_LIGHT * light_spot_right = new GRAPHIC_SHADER_LIGHT;
        light_spot_right->InitializeSpot(CORE_MATH_VECTOR( 0.0f, 1.0f, 0.0f, 1.0f), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(0.0f, 0.0f, 1.0f, 0.0f), 10.0f, 1.0f, 1.0f, M_PI_4 , 10.1f, 10.1f);
        
        GAMEPLAY_HELPER::AddToLighting( entity, light_spot_right );
        GAMEPLAY_HELPER::AddToWorld( entity );
        SetChild(entity, 0);
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
        GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
            offset(-0.05f, 0.0f, 0.0f, 0.0f );
        
        GRAPHIC_SHADER_LIGHT * light_spot_left = new GRAPHIC_SHADER_LIGHT;
        light_spot_left->InitializeSpot(CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f, 1.0f), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(0.0f, 0.0f, 1.0f, 0.0f), 10.0f, 0.1f, 0.1f, M_PI_4 , 10.1f, 10.1f);
        
        CORE_MATH_QUATERNION q;
        q.RotateY( M_PI_2 );
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        
        GAMEPLAY_HELPER::AddToWorld( entity );
        GAMEPLAY_HELPER::AddToLighting( entity, light_spot_left );
        SetChild(entity, 1);
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
        GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(0.0f, -0.03f, 0.01f, 0.0f );
        
        CORE_MATH_QUATERNION q;
        q.RotateZ( M_PI_2 );
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        
        GAMEPLAY_HELPER::AddToWorld( entity );
        SetChild(entity, 2);
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_ENTITY >();
        GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(0.0f, -1.5f, 0.0f, 1.0f );
        
        GRAPHIC_SHADER_LIGHT * light = new GRAPHIC_SHADER_LIGHT;
        light->InitializePoint( CORE_MATH_VECTOR( 0.5f, 1.0f, 0.9f), CORE_MATH_VECTOR::Zero, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        
        CORE_MATH_QUATERNION q;
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );

        GAMEPLAY_HELPER::AddToLighting( entity, light );
        SetChild(entity, 3);
    }
}

void R3D_PLAYER_SHIP::Update( float step ) {
    
    CORE_MATH_VECTOR
        elevation,
        normal,
        velocity,
        x( 0.0f, 0.0f, 1.0f, 0.0f ),
        dir;
    CORE_MATH_QUATERNION
        orientation,
        qr,
        qrtot;
    CORE_MATH_MATRIX
        mm;
    static float
        previous_rotation = 0.0f,
        previous_thrust = 0.0f;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    GAMEPLAY_HELPER::GetElevation( this, elevation, normal );
    
    velocity = phys->GetVelocity();
    orientation = pos->GetOrientation();
    
    if ( elevation.GetY() <= 1.0f && normal != CORE_MATH_VECTOR::Zero ) {
        
        velocity.X( 0.0f );
        velocity.Y( 2.f * (1.0f - elevation.GetY() ) );
        velocity.Z( 0.0f );
        
        phys->ApplyForce( velocity );
        SetPosition( pos->GetPosition() + CORE_MATH_VECTOR( 0.0f, fmax( 0.0f, 0.15f - elevation.GetY() ), 0.0f, 0.0f ) );
    }
    
    float
        actual_speed = velocity.ComputeLength();
    
    CORE_MATH_MATRIX
        inv;
    
    orientation.ToMatrix( mm.GetRow( 0 ) );
    mm.GetInverse( inv );

    dir = x * inv;
    
    phys->ApplyForce( dir * (GetThrust() * (10.0f - actual_speed ) ) );
    velocity = phys->GetVelocity();

    qr.RotateY( GetRotation() * step );
    
    CORE_MATH_QUATERNION reset_pos = pos->GetOrientation();
    
    //reset_pos.RotateZ( previous_rotation * 0.1f );
    //reset_pos.RotateX( - previous_thrust * 0.1f );
    
    qrtot = reset_pos * qr;
    qrtot.Normalize();
    
    qr.RotateY( -GetRotation() * step );
    qr.RotateY( -GetRotation() * step );
    
    qr.ToMatrix( mm.GetRow( 0 ) );
    
    velocity = velocity * mm;
    phys->SetVelocity( velocity );

    qrtot.Normalize();
    SetOrientation( qrtot );
    
    UpdateCamera( step, pos, phys );
    
    //qrtot.RotateX( GetThrust() * 0.1f );
    //qrtot.RotateZ( -GetRotation() * 0.1f );
    
    qrtot.Normalize();
    SetOrientation( qrtot );
    
#if DEBUG
    R3D_APP_PTR->SetFrom( pos->GetPosition() );
    R3D_APP_PTR->SetTo( pos->GetPosition() + velocity * 10.0f);
#endif
    
    Steam.SetPosition( pos->GetPosition() );
    Steam.SetVelocity( phys->GetVelocity() );
    
    previous_rotation = GetRotation();
    previous_thrust = GetThrust();
    
    Steam.Update( step );
}

void R3D_PLAYER_SHIP::UpdateCamera( float step, GAMEPLAY_COMPONENT_POSITION::PTR pos, GAMEPLAY_COMPONENT_PHYSICS::PTR phys ) {
    
    //FIX Z-UP bullshit
    static CORE_MATH_VECTOR
        f(0.0f, 0.1f, 0.01f, 0.0f ),
        r(0.0f, 0.15f, -1.95f, 0.0f ),
        t(0.0f, 2.5f, 0.0f, 0.0f );
    CORE_MATH_QUATERNION
        q = pos->GetOrientation(),
        q2 = pos->GetOrientation(),
        q3;
    CORE_MATH_MATRIX
        m;
    CORE_MATH_VECTOR
        vv;
    
    q.ToMatrix( m.GetRow(0) );
    vv = r * m;
    q2.ToMatrix( m.GetRow(0) );
    
    CORE_MATH_MATRIX top_matrix;
    top_matrix.XRotate( -M_PI_2 );
    
    Front.UpdateCamera( pos->GetPosition() - (f * q), vv );
    Rear.UpdateCamera( pos->GetPosition() + r, CORE_MATH_VECTOR::ZAxis );
    Top.UpdateCamera( pos->GetPosition() + t, top_matrix * CORE_MATH_VECTOR::ZAxis );
    
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
