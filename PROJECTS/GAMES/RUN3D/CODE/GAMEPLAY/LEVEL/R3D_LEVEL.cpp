//
//  R3D_LEVEL.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_HELPER.h"

R3D_LEVEL::R3D_LEVEL() :
    PlayerTable(),
    Environment() {
    
}

void R3D_LEVEL::Initialize() {
    
    PlayerTable.resize( 1 );
    
    PlayerTable[ 0 ] = new R3D_PLAYER();
    
    PlayerTable[ 0 ]->Initialize();
    
    CreateTracks();
    CreateGround();
}

void R3D_LEVEL::Finalize() {
    
}

void R3D_LEVEL::Update( const float time_step ) {
    
    ComputeCollisions( time_step );
}

void R3D_LEVEL::ComputeCollisions( const float time_step ) {
    
    //TODO in physics world
}

void R3D_LEVEL::CreateTracks() {
    
    for (int i = 0; i < 0; i++) {
        
        auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
        
        GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( entity );
        
        GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "straight_track" ) );
        GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
        GAMEPLAY_HELPER::SetTexture(entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
        
        CORE_MATH_VECTOR p( 0.0f, 1.0f * i, 0.0f, 1.0f );
        
        GAMEPLAY_HELPER::SetPhysicsObject( entity, p, 0.0f );
        //GAMEPLAY_HELPER::SetPhysicsSphereObject( entity, p, 0.0f );
        
        GAMEPLAY_HELPER::SetPosition( entity, p );
        //GAMEPLAY_HELPER::SetOrientation(entity, CORE_MATH_QUATERNION());
        
        GAMEPLAY_HELPER::AddStaticToPhysics( entity );
        GAMEPLAY_HELPER::AddToWorld( entity );
    }
}

void R3D_LEVEL::CreateGround() {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( entity );
    
    auto height_map_object = GAMEPLAY_HELPER::Set3DHeighFieldObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color", CORE_FILESYSTEM_PATH::FindFilePath("map-color", "png", "MAP" ) );
    
    CORE_MATH_VECTOR p( ((height_map_object->GetXWidth()-1) * height_map_object->GetLength())*0.5f, ((height_map_object->GetYWidth()-1) * height_map_object->GetLength())*0.5f, 0.0f, 1.0f );
    
    GAMEPLAY_HELPER::SetPhysicsGroundHeightMapObject( entity, p, 0.0f );
    
    //GAMEPLAY_HELPER::SetPosition( entity, p );
    //GAMEPLAY_HELPER::SetOrientation(entity, CORE_MATH_QUATERNION());
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity );
    GAMEPLAY_HELPER::AddToWorld( entity );
}
