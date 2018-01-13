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
#include "R3D_LEVEL_TRACK.h"
#include "R3D_LEVEL_CHECKPOINT.h"
#include "GAMEPLAY_COMPONENT_BASE_ENTITY.h"
#include "RUN3D_APPLICATION.h"

R3D_LEVEL::R3D_LEVEL() :
    MaxPlayerCount( 16 ),
    Reverse( false ),
    PlayerTable(),
    Environment( NULL ),
    EndGameCallback( &Wrapper1<R3D_LEVEL, GAMEPLAY_COMPONENT_ENTITY *, &R3D_LEVEL::OnPlayerCompleted>, this ),
    Checkpoints(),
    Info(),
    Gravity( -2.81f ) {
    
}

void R3D_LEVEL::Initialize() {
    
    Checkpoints.SetPlayerFinishedCallback( EndGameCallback );
    
    CreateTracks();
    CreateGround();
    CreateSky();
}


void R3D_LEVEL::OnPlayerCompleted( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    R3D_APP_PTR->GetGame()->OnPlayerCompleted( entity );
}

void R3D_LEVEL::Finalize() {
    
    PlayerTable.clear();
    CORE_MEMORY_ObjectSafeDeallocation( Environment );
}

void R3D_LEVEL::Start() {
    
    std::vector<GAMEPLAY_COMPONENT_ENTITY *> players_table;
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_PLAYER::PTR >::iterator it = PlayerTable.begin();
    
    while ( it != PlayerTable.end() ) {
        
        players_table.push_back( it->second->GetShip() );
        it++;
    }
    
    Checkpoints.Start( players_table );
}

void R3D_LEVEL::Restart() {
    
    Checkpoints.Reset();
    
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_PLAYER::PTR >::iterator it = PlayerTable.begin();
    
    while ( it != PlayerTable.end() ) {
        
        it->second->Reset( CORE_MATH_VECTOR( 0.0f, 0.0f, 1.6f, 1.0f), CORE_MATH_QUATERNION( 0.0f, 0.0f, 0.0f, 1.0f ));
        it++;
    }
}

void R3D_LEVEL::Update( const float time_step ) {
    
    ComputeCollisions( time_step );
}

void R3D_LEVEL::ComputeCollisions( const float time_step ) {
    
    //TODO in physics world
}

void R3D_LEVEL::CreateTracks() {
    
    CORE_MATH_VECTOR p1( 0.0f, 1.0f, 1.0f, 1.0f );
    
    auto base_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_TRACK >();
    base_entity->Initialize( p1 );
    
    for ( int i = 0; i < 21; i++) {
        
        CORE_MATH_VECTOR p( 0.0f, 1.0f * i, 1.0f, 1.0f );
        
        if ( i > 0 && i % 10 == 0 ) {
            
            auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_CHECKPOINT >();
            
            entity->Initialize( p );
            
            Checkpoints.AddCheckpoint( entity->GetChild( 0 ) );
        }
        
        base_entity->SetPosition( p );
        
        auto entity = (R3D_LEVEL_TRACK*)GAMEPLAY_COMPONENT_MANAGER::GetInstance().CloneEntity< R3D_LEVEL_TRACK >( base_entity );
        entity->AddToSystems();
        
        /*auto base_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_TRACK >();
        base_entity->Initialize( p );*/
    }
}

void R3D_LEVEL::CreateGround() {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_BASE_ENTITY >();
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( entity );
    
    auto height_map_object = GAMEPLAY_HELPER::Set3DHeighFieldObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color", CORE_FILESYSTEM_PATH::FindFilePath("map-color", "png", "MAP" ) );
    
    CORE_MATH_VECTOR p( -((height_map_object->GetXWidth()-1) * height_map_object->GetLength())*0.5f, -((height_map_object->GetYWidth()-1) * height_map_object->GetLength())*0.5f, -5.0f, 1.0f );
    
    //GAMEPLAY_HELPER::SetPhysicsGroundHeightMapObject( entity, CORE_MATH_VECTOR::Zero, 0.0f );
    GAMEPLAY_HELPER::SetPhysicsFlatGroundObject( entity, p, 0.0f, -2.0f );
    
    entity->SetPosition( p );
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( entity );
}

void R3D_LEVEL::CreateSky() {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_BASE_ENTITY >();
    
    GAMEPLAY_HELPER::CreateComponent_PositionRender( entity );
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "skydome" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "space_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture( entity, "space_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::AddToWorld( entity );
}
