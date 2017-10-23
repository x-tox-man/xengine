//
//  RESOURCES.cpp
//  Run3d
//
//  Created by Christophe Bernard on 16/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_RESOURCES.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"

R3D_RESOURCES::R3D_RESOURCES() :
    Resources( NULL ) {
    
}

void R3D_RESOURCES::Initialize() {
    
    Resources = new RESOURCE_CONTAINER;
    
    RESOURCE_PROXY::PTR spaceship1_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR track_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR weapon1_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR shader_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR basic_geometry_shader_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR terrain_geometry_shader_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR checkpoint_effect_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR checkpoint_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR capsule_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR particle_proxy = new RESOURCE_PROXY;
    
    spaceship1_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("spaceship1", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    track_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("straight_track", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    weapon1_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("weapon1", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    checkpoint_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("checkpoint", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    capsule_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("capsule", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    
    auto effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto basic_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicGeometryShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto basic_terrain_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "TerrainShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto checkpoint_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ), CORE_FILESYSTEM_PATH::FindFilePath( "CheckpointEffect", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto particle_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicParticleShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    
    effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    basic_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    basic_terrain_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    checkpoint_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    particle_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    shader_proxy->SetResource( effect );
    basic_geometry_shader_proxy->SetResource( basic_effect );
    terrain_geometry_shader_proxy->SetResource( basic_terrain_effect );
    checkpoint_effect_proxy->SetResource( checkpoint_effect );
    particle_proxy->SetResource( particle_effect );
    
    Resources->AddResource( spaceship1_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship1" ) );
    Resources->AddResource( track_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "straight_track" ) );
    Resources->AddResource( weapon1_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
    Resources->AddResource( shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    Resources->AddResource( basic_geometry_shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicGeometryShader" ) );
    Resources->AddResource( terrain_geometry_shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    Resources->AddResource( checkpoint_effect_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    Resources->AddResource( checkpoint_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "checkpoint" ) );
    Resources->AddResource( capsule_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "capsule" ) );
    Resources->AddResource( particle_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ) );
}

void R3D_RESOURCES::Finalize() {
    
}

void R3D_RESOURCES::LoadCommon() {
    
}

void R3D_RESOURCES::LoadPackage( const CORE_FILESYSTEM_PATH & path ) {
    
}

void R3D_RESOURCES::UnloadPackage() {
    
}

RESOURCE_PROXY::PTR R3D_RESOURCES::FindResourceProxy( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    return Resources->GetResourceMap().at( identifier );
}
