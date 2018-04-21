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

R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT() :
    GAMEPLAY_COMPONENT_ENTITY() {
    
}

void R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::Initialize( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "capsule" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    GAMEPLAY_HELPER::SetTexture( this, "waves", CORE_FILESYSTEM_PATH::FindFilePath( "waves", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( this, position, 0.0f );
    GAMEPLAY_HELPER::SetPhysicsCylinderObject(this, position, 0.75f, 0.15f, CORE_MATH_QUATERNION(), 0.0f );
    
    SetPosition( position );
    SetOrientation(CORE_MATH_QUATERNION(0.0f, 0.0f, 0.0f, 1.0f));
    
    GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_TARGET, PHYSICS_COLLISION_TYPE_SHIP );
    GAMEPLAY_HELPER::AddToWorldTransparent( this );
}

void R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT::CollidesWith( GAMEPLAY_COMPONENT_ENTITY * other ) {
    
    R3D_APP_PTR->GetGame()->GetLevel()->GetCheckpoints().OnCheckpointCollision( this, other );
}
