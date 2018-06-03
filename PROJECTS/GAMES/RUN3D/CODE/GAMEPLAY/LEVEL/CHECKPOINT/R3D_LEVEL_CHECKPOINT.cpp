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

R3D_LEVEL_CHECKPOINT::R3D_LEVEL_CHECKPOINT() :
    GAMEPLAY_COMPONENT_ENTITY() {
    
}

void R3D_LEVEL_CHECKPOINT::Initialize( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "checkpoint" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( this, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetShadowmapEffect( this );
    
    GAMEPLAY_HELPER::SetPhysicsObject( this, position, 0.0f );
    
    SetPosition( position );
    SetOrientation( CORE_MATH_QUATERNION(0.0f, 0.0f, 0.0f, 1.0f) );
    
    GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_SHIP );
    GAMEPLAY_HELPER::AddToWorld( this );
}
