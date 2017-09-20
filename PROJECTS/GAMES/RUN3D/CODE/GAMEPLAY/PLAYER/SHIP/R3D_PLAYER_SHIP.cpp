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
#include "GRAPHIC_RENDERER.h"
#include "RUN3D_APPLICATION.h"

R3D_PLAYER_SHIP::R3D_PLAYER_SHIP() :
    Entity( NULL ),
    Parts(),
    Front(),
    Rear(),
    Top() {
    
}

R3D_PLAYER_SHIP::~R3D_PLAYER_SHIP() {
    
}

void R3D_PLAYER_SHIP::Initialize() {
    
    Entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysicsScriptAnimation( Entity );
    
    GAMEPLAY_HELPER::Set3DObject( Entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1" ) );
    GAMEPLAY_HELPER::SetEffect( Entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture(Entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetScript(Entity, CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "lua", "SCRIPTS" ) );
    
    CORE_MATH_QUATERNION
        q;
    
    q.RotateZ( M_PI_2 );
    q.Normalize();
    
    CORE_MATH_VECTOR
        start_position(10.0f, 10.0f, 20.0f, 0.0f );
    
    GAMEPLAY_HELPER::SetPhysicsSphereObject( Entity, start_position, q, 10.0f );
    GAMEPLAY_HELPER::SetOrientation( Entity, q );

    GAMEPLAY_HELPER::AddToPhysics( Entity );
    GAMEPLAY_HELPER::AddToScripts( Entity );
    GAMEPLAY_HELPER::AddToWorld( Entity );
    
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Front );
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Rear);
    GAMEPLAY_HELPER::InitializeCamera( start_position, q, Top);
}

void R3D_PLAYER_SHIP::Update( float step ) {
    
    static const CORE_MATH_VECTOR f(0.0f, 0.1f, 0.01f, 0.0f );
    static const CORE_MATH_VECTOR r(0.0f, -0.3f, 0.04f, 0.0f );
    static const CORE_MATH_VECTOR t(0.0f, 0.0f, 5.0f, 0.0f );
    
    CORE_MATH_QUATERNION
        q, q2;
    
    q.RotateX( M_PI_2 );
    q.Normalize();
    
    q2.Normalize();
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) Entity->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    Front.UpdateCamera( pos->GetPosition() + f, q );
    Rear.UpdateCamera( pos->GetPosition() + r, q );
    Top.UpdateCamera( pos->GetPosition() + t, q2 );
    
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_A ) ) {
        
        R3D_APP_PTR->SetCamera( &Front );
    }
    else if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_Z ) ) {
        
        R3D_APP_PTR->SetCamera( &Rear );
    }
    if (  PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().IsKeyPressed( KEYBOARD_KEY_CHAR_T ) ) {
        
        R3D_APP_PTR->SetCamera( &Top );
    }
}

