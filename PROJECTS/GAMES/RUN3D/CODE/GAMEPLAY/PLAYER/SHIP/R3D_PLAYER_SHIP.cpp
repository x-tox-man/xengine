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

R3D_PLAYER_SHIP::R3D_PLAYER_SHIP() :
    GAMEPLAY_COMPONENT_ENTITY(),
    Parts(),
    Front(),
    Rear(),
    Top(),
    Steam() {
    
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
    GAMEPLAY_HELPER::SetScript(this, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
    
    q.RotateZ( M_PI_2 );
    q.Normalize();
    
    CORE_MATH_VECTOR
        start_position(0.0f, 0.0f, 3.0f, 0.0f );
    
    GAMEPLAY_HELPER::SetPhysicsSphereObject( this, start_position, q, 1.0f );
    //GAMEPLAY_HELPER::SetPhysicsBoxObject( this, start_position, CORE_MATH_VECTOR(0.1f,0.1f,0.1f, 0.0f), q, 1.0f );
    SetOrientation( q );
    
    GAMEPLAY_HELPER::AddToPhysics( this, PHYSICS_COLLISION_TYPE_SHIP, PHYSICS_COLLISION_TYPE_ALL );
    GAMEPLAY_HELPER::AddToScripts( this );
    GAMEPLAY_HELPER::AddToWorld( this );
    
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
    
    static const CORE_MATH_VECTOR f(0.0f, 0.1f, 0.01f, 0.0f );
    static const CORE_MATH_VECTOR r(0.0f, -0.5f, 0.04f, 0.0f );
    static const CORE_MATH_VECTOR t(0.0f, 0.0f, 5.0f, 0.0f );
    
    CORE_MATH_QUATERNION
        q, q2;
    
    q.RotateX( M_PI_2 );
    q.Normalize();
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    Front.UpdateCamera( pos->GetPosition() + f, q );
    Rear.UpdateCamera( pos->GetPosition() + r, q );
    Top.UpdateCamera( pos->GetPosition() + t, q2 );
    
    Steam.SetPosition( pos->GetPosition() );
    
    CORE_MATH_VECTOR elevation = GAMEPLAY_HELPER::GetElevation( this );
    
    if ( elevation.GetZ() < 1.0f && elevation.GetZ() > 0.0f ) {
        
        auto phys = (GAMEPLAY_COMPONENT_PHYSICS::PTR) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
        
        CORE_MATH_VECTOR & vel = phys->GetVelocity();
        
        float p = sinf( (1.0f - elevation.GetZ()) * M_PI_2) * 2.81f;
        
        vel.Z( vel.Z() + p * step );
        
        //phys->SetVelocity( vel );
    }
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        R3D_APP_PTR->SetCamera( &Front );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        R3D_APP_PTR->SetCamera( &Rear );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_T ) ) {
        
        R3D_APP_PTR->SetCamera( &Top );
    }
}
