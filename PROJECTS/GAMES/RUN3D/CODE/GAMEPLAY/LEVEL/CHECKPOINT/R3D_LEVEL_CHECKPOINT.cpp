//
//  R3D_LEVEL_CHECKPOINT.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_CHECKPOINT.h"
#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

R3D_LEVEL_CHECKPOINT::R3D_LEVEL_CHECKPOINT() {
    
}

GAMEPLAY_COMPONENT_ENTITY::PTR CreateEntity( const CORE_MATH_VECTOR & position ) {
    
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_PHYSICS >();
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "checkpoint" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetShadowmapEffect( entity );
    
    GAMEPLAY_HELPER::SetPhysicsObject( entity, position, 0.0f );
    
    entity->SetPosition( position );
    entity->SetOrientation( CORE_MATH_QUATERNION(0.0f, 0.0f, 0.0f, 1.0f) );
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_SHIP );
    GAMEPLAY_HELPER::AddToWorld( entity );
    
    return entity;
}
