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
#include "R3D_LEVEL_TRACK_TURN.h"
#include "R3D_LEVEL_CHECKPOINT.h"
#include "GAMEPLAY_COMPONENT_BASE_ENTITY.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_RENDERTERRAIN.h"

R3D_LEVEL::R3D_LEVEL() :
    MaxPlayerCount( 16 ),
    Reverse( false ),
    PlayerTable(),
    Environment( NULL ),
    EndGameCallback( &Wrapper1<R3D_LEVEL, GAMEPLAY_COMPONENT_ENTITY *, &R3D_LEVEL::OnPlayerCompleted>, this ),
    Checkpoints(),
    Info( NULL ),
    Gravity( -2.81f ),
    Script( NULL ) ,
    Sky() {
    
}

void R3D_LEVEL::Initialize() {
    
    Checkpoints.SetPlayerFinishedCallback( EndGameCallback );
    
    CreateTracks();
    CreateGround();
    CreateMoon();
    CreateSky();
}

void R3D_LEVEL::Initialize( const CORE_FILESYSTEM_PATH & path ) {
    
    CORE_ABSTRACT_PROGRAM_LUA * program = new CORE_ABSTRACT_PROGRAM_LUA();
    
    CORE_ABSTRACT_RUNTIME_LUA * runtime = new CORE_ABSTRACT_RUNTIME_LUA;
    runtime->Initialize();
    
    CORE_ABSTRACT_PROGRAM_BINDER::GetInstance().BindRuntime<CORE_ABSTRACT_RUNTIME_LUA>( *runtime );
    
#if DEBUG
    Watcher =  new CORE_FILESYSTEM_FILE_WATCHER;
    
    CORE_HELPERS_CALLBACK *callback = new CORE_HELPERS_CALLBACK( &Wrapper< CORE_ABSTRACT_PROGRAM_LUA, &CORE_ABSTRACT_PROGRAM_LUA::Reload>, (void *) program );
    
    int l = (int) strlen( path.GetPath() );
    
    char * vsh_path = (char*) CORE_MEMORY_ALLOCATOR::Allocate ( l+1 );
    
    strncpy(vsh_path, path.GetPath(), l);
    vsh_path[l] = '\0';
    vsh_path[strlen(vsh_path) - 3 ] ='l';
    vsh_path[strlen(vsh_path) - 2 ] ='u';
    vsh_path[strlen(vsh_path) - 1 ] ='a';
    
    Watcher->Setup( path.GetPath(), *callback );
#endif
    
    program->Load( path.GetPath(), *runtime );
    
    Script = program;
    Script->Execute();
    
    Initialize();
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
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) Sky->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    pos->SetPosition( R3D_APP_PTR->GetCamera()->GetPosition() );
    ComputeCollisions( time_step );
}

void R3D_LEVEL::ComputeCollisions( const float time_step ) {
    
    //TODO in physics world
}

void R3D_LEVEL::CreateTracks() {
     
    CORE_MATH_VECTOR p1( 0.0f, 0.0f, 1.0f, 1.0f );
    
    auto base_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_TRACK >();
    base_entity->Initialize( p1 );
    
    auto base_entity_turn = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_TRACK_TURN >();
    auto base_entity_jump = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_TRACK_JUMP >();
    
    for ( int i = 0; i < 11; i++) {
        
        CORE_MATH_VECTOR p( 0.0f, 1.0f * i, 1.0f, 1.0f );
        
        if ( i > 0 && i % 10 == 0 ) {
            
            auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_LEVEL_CHECKPOINT >();
            
            entity->Initialize( p );
            
            auto child = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity<R3D_LEVEL_CHECKPOINT_COLLISION_OBJECT>();
            child->Initialize( p );
            
            Checkpoints.AddCheckpoint( child );
        }
    }
}

void R3D_LEVEL::CreateGround() {
    
    R3D_RENDERTERRAIN::CreateTerrain();
}

void R3D_LEVEL::CreateSky() {
    
    Sky = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_BASE_ENTITY >();
    
    GAMEPLAY_HELPER::CreateComponent_PositionRender( Sky );
    
    GAMEPLAY_HELPER::Set3DObject( Sky, CORE_HELPERS_UNIQUE_IDENTIFIER( "skydome" ) );
    GAMEPLAY_HELPER::SetEffect( Sky, CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SkyEffect" ) );
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "space_diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture( Sky, "space_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "high-resolution-space-1", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::AddToWorld( Sky );
}

void R3D_LEVEL::CreateMoon() {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< GAMEPLAY_COMPONENT_BASE_ENTITY >();
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderScript( entity );
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "moon" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetScript( entity, CORE_FILESYSTEM_PATH::FindFilePath( "moon", "lua", "SCRIPTS" ) );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "moon-diffuse" ), CORE_FILESYSTEM_PATH::FindFilePath( "moon", "png", "TEXTURES" ) );
    auto text2 = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "moon-normal" ), CORE_FILESYSTEM_PATH::FindFilePath( "moon-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetTexture( entity, "moon-diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "moon", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( entity, "moon-normal", CORE_FILESYSTEM_PATH::FindFilePath( "moon-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::AddToScripts( entity );
    GAMEPLAY_HELPER::AddToWorld( entity );
}
