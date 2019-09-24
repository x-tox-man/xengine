//
//  R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 23/09/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT.h"
#include "GAMEPLAY_HELPER.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT() {
    
}

GAMEPLAY_COMPONENT_ENTITY::PTR R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::CreateEntity( const CORE_MATH_VECTOR & position ) {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_PHYSICS >();
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "capsule" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    GAMEPLAY_HELPER::SetTexture( entity, "waves", CORE_FILESYSTEM_PATH::FindFilePath( "waves", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( entity, position, 0.0f );
    GAMEPLAY_HELPER::SetPhysicsCylinderObject(entity, position, 0.75f, 0.15f, CORE_MATH_QUATERNION(), 0.0f );
    
    entity->SetPosition( position );
    entity->SetOrientation(CORE_MATH_QUATERNION(0.0f, 0.0f, 0.0f, 1.0f));
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_TARGET, PHYSICS_COLLISION_TYPE_SHIP );
    GAMEPLAY_HELPER::AddToWorldTransparent( entity );
    
    return entity;
}

void R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other ) {
    
    abort(); // TODO
    //R3D_APP_PTR->GetGame()->GetLevel()->GetCheckpoints().OnCheckpointCollision( this, other );
}
