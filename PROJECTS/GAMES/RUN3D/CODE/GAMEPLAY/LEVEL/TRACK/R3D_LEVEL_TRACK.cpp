//
//  R3D_LEVEL_TRACK.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_TRACK.h"
#include "GAMEPLAY_HELPER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

R3D_LEVEL_TRACK::R3D_LEVEL_TRACK() {
    
}


GAMEPLAY_COMPONENT_ENTITY::PTR R3D_LEVEL_TRACK::CreateEntity( const CORE_MATH_VECTOR & position ) {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "flat" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( entity, position, 0.0f );
    //GAMEPLAY_HELPER::SetPhysicsBoxObject(this, position   , CORE_MATH_VECTOR( 0.5f, 0.5f, 0.5f, 0.0f), CORE_MATH_QUATERNION(), 0.0f);
    //GAMEPLAY_HELPER::SetPhysicsCustomMaterialCallback( this );
    
    entity->SetPosition( position );
    
    return entity;
}

void R3D_LEVEL_TRACK::AddToSystems() {
    
    abort(); //TODO
    //GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    //GAMEPLAY_HELPER::AddToWorld( this );
}
