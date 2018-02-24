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
#include "GRAPHIC_FONT_MANAGER.h"
#include "GRAPHIC_UI_HELPER.h"

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
    RESOURCE_PROXY::PTR text_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR skydome_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR sky_effect_proxy = new RESOURCE_PROXY;
    RESOURCE_PROXY::PTR shadow_map_proxy = new RESOURCE_PROXY;
    
    spaceship1_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("spaceship", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    track_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("flat", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    weapon1_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("weapon1", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    checkpoint_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("checkpoint", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    capsule_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("capsule", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    skydome_proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath("skydome", "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    
    auto effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShaderPoNoUVTaBi", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto basic_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicGeometryShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicGeometryShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto basic_terrain_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicTerrainShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto checkpoint_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ), CORE_FILESYSTEM_PATH::FindFilePath( "CheckpointEffect", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto particle_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ), CORE_FILESYSTEM_PATH::FindFilePath( "BasicParticleShader", "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    auto text_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShaderTextured"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    auto sky_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SkyEffect" ), CORE_FILESYSTEM_PATH::FindFilePath( "BackgroundSky" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    auto shadow_map_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowMapEffect"), CORE_FILESYSTEM_PATH::FindFilePath( "ShadowMapEffect" , "vsh", GRAPHIC_SYSTEM::GetShaderDirectoryPath() ) );
    
    
    effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTextureTangentBitangent );
    basic_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormal );
    basic_terrain_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    checkpoint_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    particle_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    text_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    sky_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    shadow_map_effect->Initialize( GRAPHIC_SHADER_BIND_PositionNormalTexture );
    
    shader_proxy->SetResource( effect );
    basic_geometry_shader_proxy->SetResource( basic_effect );
    terrain_geometry_shader_proxy->SetResource( basic_terrain_effect );
    checkpoint_effect_proxy->SetResource( checkpoint_effect );
    particle_proxy->SetResource( particle_effect );
    text_proxy->SetResource( text_effect );
    sky_effect_proxy->SetResource( sky_effect );
    shadow_map_proxy->SetResource( shadow_map_effect );
    
    Resources->AddResource( spaceship1_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "spaceship" ) );
    Resources->AddResource( track_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "flat" ) );
    Resources->AddResource( weapon1_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "weapon1" ) );
    Resources->AddResource( shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    Resources->AddResource( basic_geometry_shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicGeometryShader" ) );
    Resources->AddResource( terrain_geometry_shader_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    Resources->AddResource( checkpoint_effect_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    Resources->AddResource( checkpoint_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "checkpoint" ) );
    Resources->AddResource( capsule_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "capsule" ) );
    Resources->AddResource( skydome_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "skydome" ) );
    Resources->AddResource( particle_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "BasicParticleShader" ) );
    Resources->AddResource( text_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "UIShaderTextured" ) );
    Resources->AddResource( sky_effect_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::SkyEffect" ) );
    Resources->AddResource( shadow_map_proxy, CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::ShadowMapEffect" ) );
    
    CreateModel( "moon", CORE_HELPERS_UNIQUE_IDENTIFIER( "moon" ) );
    CreateModel( "turn", CORE_HELPERS_UNIQUE_IDENTIFIER( "turn" ) );
    CreateModel( "jump", CORE_HELPERS_UNIQUE_IDENTIFIER( "jump" ) );
    CreateModel( "flat_ground", CORE_HELPERS_UNIQUE_IDENTIFIER( "flat_ground" ) );
    CreateModel( "thruster", CORE_HELPERS_UNIQUE_IDENTIFIER( "thruster" ) );
    
    GRAPHIC_FONT_MANAGER::GetInstance().LoadFont(
                                                 CORE_HELPERS_UNIQUE_IDENTIFIER( "stellar-light_32" ),
                                                 CORE_FILESYSTEM_PATH::FindFilePath( "stellar-light_32" , "fxb", "FONTS/" ),
                                                 CORE_FILESYSTEM_PATH::FindFilePath( "stellar-light_32" , "png", "FONTS/" ) );
    
    GRAPHIC_FONT * font = GRAPHIC_FONT_MANAGER::GetInstance().GetFont( CORE_HELPERS_UNIQUE_IDENTIFIER( "stellar-light_32" ) );
    
    RESOURCE_IMAGE::FlushCache();
    
    GRAPHIC_UI_HELPER::DefaultFont = font;
}

RESOURCE_PROXY::PTR R3D_RESOURCES::CreateEffect( const char * name, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, const GRAPHIC_SHADER_BIND & bind ) {
    
    RESOURCE_PROXY::PTR proxy = new RESOURCE_PROXY;
    
    auto effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath( identifier, CORE_FILESYSTEM_PATH::FindFilePath( name, "vsh", GRAPHIC_SYSTEM::ShaderDirectoryPath ) );
    
    effect->Initialize( bind );
    
    AddResource( proxy, identifier );
    
    return proxy;
}

RESOURCE_PROXY::PTR R3D_RESOURCES::CreateModel( const char * name, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    RESOURCE_PROXY::PTR proxy = new RESOURCE_PROXY;
    
    proxy->SetResource( GRAPHIC_MESH_MANAGER::GetInstance().LoadObject( CORE_FILESYSTEM_PATH::FindFilePath( name, "smx", "MODELS" ), 0, GRAPHIC_MESH_TYPE_ModelResource ) );
    
    AddResource( proxy, identifier );
    
    return proxy;
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

void R3D_RESOURCES::AddResource( RESOURCE_PROXY::PTR & resource, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    Resources->AddResource( resource, identifier );
}
