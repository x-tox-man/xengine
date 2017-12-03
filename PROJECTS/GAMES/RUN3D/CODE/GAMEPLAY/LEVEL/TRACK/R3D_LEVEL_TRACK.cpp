//
//  R3D_LEVEL_TRACK.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_TRACK.h"
#include "GAMEPLAY_HELPER.h"

R3D_LEVEL_TRACK::R3D_LEVEL_TRACK() :
    GAMEPLAY_COMPONENT_ENTITY() {
    
}


void R3D_LEVEL_TRACK::Initialize( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( this );
    
    GAMEPLAY_HELPER::Set3DObject( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "flat" ) );
    GAMEPLAY_HELPER::SetEffect( this, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetTexture( this, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( this, position, 0.0f );
    
    SetPosition( position );
}

void R3D_LEVEL_TRACK::AddToSystems() {
    
    GAMEPLAY_HELPER::AddStaticToPhysics( this, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( this );
}
