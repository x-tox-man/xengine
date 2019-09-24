//
//  R3D_PLAYER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "GAMEPLAY_HELPER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "RUN3D_APPLICATION.h"

R3D_PLAYER::R3D_PLAYER() :
    Ship( NULL ),
    VirtualCredits( 0 ),
    RealMoney( 0 ),
    TotalExperience( 0 ),
    Level( 1 ),
    TotalRunTime( 0.0f ),
    Front(),
    Rear(),
    Top(),
    ModifiersMap() {

    ModifiersMap[ R3D_PLAYER_MODIFIER::MaxSpeedModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::HorsePowerModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::FuelCapacityModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::WeaponReloadTimeModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::GravityModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::MassModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::ExperienceGainModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::BrakeModifier ].SetValue( 0.0f );
}

void R3D_PLAYER::Initialize() {
    
    CORE_MATH_VECTOR
        start_position(0.0f, 2.0f, 0.0, 0.0f );
    CORE_MATH_MATRIX
        top_matrix;

    top_matrix.XRotate( -M_PI_2 );
    
    GAMEPLAY_HELPER::InitializeCamera( start_position, CORE_MATH_VECTOR::ZAxis, Front, CORE_MATH_VECTOR::YAxis );
    GAMEPLAY_HELPER::InitializeCamera( start_position, CORE_MATH_VECTOR::ZAxis, Rear, CORE_MATH_VECTOR::YAxis);
    GAMEPLAY_HELPER::InitializeCamera( start_position, top_matrix * CORE_MATH_VECTOR::ZAxis, Top, top_matrix * CORE_MATH_VECTOR::YAxis );
    
    InitializeEntity();
}

void R3D_PLAYER::Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    TotalRunTime = 0.0f;
}

std::vector< R3D_PLAYER_SHIP_MODEL::PTR > R3D_PLAYER::GetAllShipsOwned() {
    
    std::vector< R3D_PLAYER_SHIP_MODEL::PTR > all_ships;
    
    auto ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    
    return all_ships;
}

bool R3D_PLAYER::Buy( int amount ) {
    
    if ( VirtualCredits >= amount ) {
        
        VirtualCredits -= amount;
        
        return true;
    }
    
    return false;
}

const CORE_MATH_QUATERNION & R3D_PLAYER::GetOrientation() const {
    
    auto pos = Ship->GetComponentPosition();
    
    return pos->GetOrientation();
}

CORE_MATH_VECTOR R3D_PLAYER::GetPosition() const {
    
    if( Ship != NULL && Ship->GetHandle().IsValid() ) {
        
        auto pos = Ship->GetComponentPosition();
        
        return pos->GetPosition();
    }
    
    return CORE_MATH_VECTOR();
}

void R3D_PLAYER::UpdateCamera( float step, GAMEPLAY_COMPONENT_POSITION::PTR pos, GAMEPLAY_COMPONENT_PHYSICS::PTR phys ) {
    
    //FIX Z-UP bullshit
    static CORE_MATH_VECTOR
        f(0.0f, 0.1f, 0.01f, 0.0f ),
        r(0.0f, 0.15f, -1.95f, 0.0f ),
        t(0.0f, 2.5f, 0.0f, 0.0f );
    CORE_MATH_QUATERNION
        q = pos->GetOrientation(),
        q2 = pos->GetOrientation(),
        q3,
        inv_q;
    CORE_MATH_MATRIX
        m,
        behind_matrix,
        top_matrix;
    CORE_MATH_VECTOR
        vv;
    
    q.ToMatrix( m.GetRow(0) );
    vv = r * m;
    q2.ToMatrix( m.GetRow(0) );
    
    top_matrix.XRotate( -M_PI_2 );
    
    m.GetInverse( behind_matrix );
    
    Front.UpdateCamera( pos->GetPosition() - (f * q), vv );
    Rear.UpdateCamera( pos->GetPosition() + r * behind_matrix, CORE_MATH_VECTOR::ZAxis * behind_matrix, CORE_MATH_VECTOR::YAxis * behind_matrix );
    Top.UpdateCamera( pos->GetPosition() + t * behind_matrix, CORE_MATH_VECTOR::ZAxis * top_matrix, CORE_MATH_VECTOR::YAxis * top_matrix );
    
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

void R3D_PLAYER::InitializeEntity() {
    
    CORE_MATH_QUATERNION
        q;
    
    Ship = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_PHYSICS, GAMEPLAY_COMPONENT_SCRIPT, R3D_PLAYER_SHIP >();
    
    GAMEPLAY_HELPER::Set3DObject( Ship, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship" ) );
    GAMEPLAY_HELPER::SetEffect( Ship, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetSecondaryEffect( Ship, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader_spaceship_special" ) );
    GAMEPLAY_HELPER::SetShadowmapEffect( Ship );
    GAMEPLAY_HELPER::SetTexture( Ship, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( Ship, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
#if PLATFORM_IOS || PLATFORM_ANDROID
    GAMEPLAY_HELPER::SetScript( Ship, CORE_FILESYSTEM_PATH::FindFilePath("spaceship-touch", "lua", "SCRIPTS" ) );
#else
    GAMEPLAY_HELPER::SetScript( Ship, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
#endif
    
    CORE_MATH_VECTOR
        start_position(0.0f, 2.0f, 0.0, 0.0f );
    
    //GAMEPLAY_HELPER::SetPhysicsSphereObject( this, start_position, q, 1.0f );
    GAMEPLAY_HELPER::SetPhysicsBoxObject( Ship, start_position, CORE_MATH_VECTOR(0.04f,0.03f, 0.15f, 0.0f), q, 1.0f );
    
    auto phys = ( GAMEPLAY_COMPONENT_PHYSICS::PTR) Ship->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    phys->EnableCCD();
    
    //GAMEPLAY_HELPER::ConfigureGroundSpring( this );
    
    GAMEPLAY_HELPER::AddToPhysics( Ship, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL, true );
    //GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( Ship );
    GAMEPLAY_HELPER::AddToSpecialEffect( Ship );
    //GAMEPLAY_HELPER::Scale3dComponent( (GAMEPLAY_COMPONENT_RENDER::PTR) Ship->GetComponent( GAMEPLAY_COMPONENT_TYPE_Light ), 2.0f );
    
    CORE_MATH_MATRIX top_matrix;
    top_matrix.XRotate( -M_PI_2 );
    
    //CreateWeaponSystem( start_position, q );
    
    //Steam.Initialize();
}

void R3D_PLAYER::CreateWeaponSystem( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(0.05f, 0.0f, 0.0f, 0.0f );
        
        CORE_MATH_QUATERNION q;
        q.RotateY( -M_PI_2 );
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        GRAPHIC_SHADER_LIGHT * light_spot_right = new GRAPHIC_SHADER_LIGHT;
        light_spot_right->InitializeSpot(CORE_MATH_VECTOR( 0.0f, 1.0f, 0.0f, 1.0f), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(0.0f, 0.0f, 1.0f, 0.0f), 10.0f, 1.0f, 1.0f, M_PI_4 , 10.1f, 10.1f);
        
        GAMEPLAY_HELPER::AddToLighting( entity, light_spot_right );
        GAMEPLAY_HELPER::AddToWorld( entity );
        Ship->SetChild( entity, entity->GetHandle() );
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(-0.05f, 0.0f, 0.0f, 0.0f );
        
        GRAPHIC_SHADER_LIGHT * light_spot_left = new GRAPHIC_SHADER_LIGHT;
        light_spot_left->InitializeSpot(CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f, 1.0f), CORE_MATH_VECTOR::Zero, CORE_MATH_VECTOR(0.0f, 0.0f, 1.0f, 0.0f), 10.0f, 0.1f, 0.1f, M_PI_4 , 10.1f, 10.1f);
        
        CORE_MATH_QUATERNION q;
        q.RotateY( -M_PI_2 );
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        
        GAMEPLAY_HELPER::AddToWorld( entity );
        GAMEPLAY_HELPER::AddToLighting( entity, light_spot_left );
        Ship->SetChild( entity, entity->GetHandle() );
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(0.0f, -0.03f, 0.01f, 0.0f );
        
        CORE_MATH_QUATERNION q;
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        
        GAMEPLAY_HELPER::AddToWorld( entity );
        Ship->SetChild( entity, entity->GetHandle() );
    }
    
    {
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetShadowmapEffect( entity );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR
        offset(0.0f, -1.5f, 0.0f, 1.0f );
        
        GRAPHIC_SHADER_LIGHT * light = new GRAPHIC_SHADER_LIGHT;
        light->InitializePoint( CORE_MATH_VECTOR( 0.5f, 1.0f, 0.9f), CORE_MATH_VECTOR::Zero, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        
        CORE_MATH_QUATERNION q;
        
        entity->SetOrientation( q );
        entity->SetPosition( offset );
        
        GAMEPLAY_HELPER::AddToLighting( entity, light );
        Ship->SetChild( entity, entity->GetHandle() );
    }
}

void R3D_PLAYER::Fire() {
    
    // Create Weapon's Bullet
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader_color" ) );
    GAMEPLAY_HELPER::Scale3dObject(entity, 2.2f );
    GAMEPLAY_HELPER::SetShadowmapEffect( entity );
    
    auto phys = Ship->GetComponentPhysics();
    phys->ConfigureShapeBox( CORE_MATH_VECTOR(), CORE_MATH_VECTOR(0.1f, 0.1f, 0.1f, 0.0f), CORE_MATH_QUATERNION() );
    
    auto pos = Ship->GetComponentPosition();
    pos->SetPosition( pos->GetPosition() );
    
    GAMEPLAY_HELPER::AddToWorldTransparent( entity );
    //GAMEPLAY_HELPER::AddToPhysics(entity, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL, true );
    
    // Apply bullet parameters
    // Add bullet to world
    
    // how to collide? => Physics world
    // configure physics world for weapons collision
}
