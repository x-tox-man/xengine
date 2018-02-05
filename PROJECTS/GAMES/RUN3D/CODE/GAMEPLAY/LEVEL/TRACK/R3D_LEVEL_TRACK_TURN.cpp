//
//  R3D_LEVEL_TRACK_TURN.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 17/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_LEVEL_TRACK_TURN.h"
#include "GAMEPLAY_HELPER.h"

R3D_LEVEL_TRACK_TURN::R3D_LEVEL_TRACK_TURN() :
    GAMEPLAY_COMPONENT_ENTITY() {
    
}


void R3D_LEVEL_TRACK_TURN::Initialize( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "turn" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( this, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( this, position, 0.0f );
    
    SetPosition( position );
}

void R3D_LEVEL_TRACK_TURN::AddToSystems() {
    
    GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( this );
}

R3D_LEVEL_TRACK_JUMP::R3D_LEVEL_TRACK_JUMP() :
GAMEPLAY_COMPONENT_ENTITY() {
    
}


void R3D_LEVEL_TRACK_JUMP::Initialize( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "jump" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( this, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( this, position, 0.0f );
    
    SetPosition( position );
}

void R3D_LEVEL_TRACK_JUMP::AddToSystems() {
    
    GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( this );
}
