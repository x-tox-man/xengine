//
//  TERRAIN.cpp
//  Run3d
//
//  Created by Christophe Bernard on 12/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_RENDERTERRAIN.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"

GAMEPLAY_COMPONENT_ENTITY::PTR R3D_RENDERTERRAIN::Create() {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT_PHYSICS >();
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color" ), CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture : create %p\n", text );
    auto height_map_object = GAMEPLAY_HELPER::Set3DHeighFieldObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color", CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    
    GAMEPLAY_HELPER::SetShadowmapEffect( entity );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-grass" ), CORE_FILESYSTEM_PATH::FindFilePath("map-color-grass", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color-grass", CORE_FILESYSTEM_PATH::FindFilePath("map-color-grass", "png", "TEXTURES" ), GRAPHIC_SHADER_PROGRAM::ColorTexture1 );
    GAMEPLAY_HELPER::SetTextureRepeating( entity, GRAPHIC_SHADER_PROGRAM::ColorTexture1 );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-rock" ), CORE_FILESYSTEM_PATH::FindFilePath("map-color-rock", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color-rock", CORE_FILESYSTEM_PATH::FindFilePath("map-color-rock", "png", "TEXTURES" ), GRAPHIC_SHADER_PROGRAM::ColorTexture2 );
    GAMEPLAY_HELPER::SetTextureRepeating( entity, GRAPHIC_SHADER_PROGRAM::ColorTexture2 );
    
    text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color-sand" ), CORE_FILESYSTEM_PATH::FindFilePath("map_color_sand", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color-sand", CORE_FILESYSTEM_PATH::FindFilePath("map-color-sand", "png", "TEXTURES" ), GRAPHIC_SHADER_PROGRAM::ColorTexture3 );
    GAMEPLAY_HELPER::SetTextureRepeating( entity, GRAPHIC_SHADER_PROGRAM::ColorTexture3 );
    
    CORE_MATH_VECTOR p( -((height_map_object->GetXWidth() - 1) * height_map_object->GetLength())*0.5f, -10.0f, -((height_map_object->GetYWidth()- 1) * height_map_object->GetLength())*0.5f, 1.0f );
    
    GAMEPLAY_HELPER::SetPhysicsGroundHeightMapObject( entity, CORE_MATH_VECTOR(0.0f, -10.0f, 0.0f, 0.0f ), 0.0f );
    
    entity->SetPosition( p );
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( entity );
    
    return entity;
}
