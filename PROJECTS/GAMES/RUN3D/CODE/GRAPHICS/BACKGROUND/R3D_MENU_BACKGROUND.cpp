//
//  R3D_MENU_BACKGROUND.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 24/03/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_MENU_BACKGROUND.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "GRAPHIC_SHADER_PROGRAM.h"

GAMEPLAY_COMPONENT_ENTITY::PTR R3D_MENU_BACKGROUND::Create( const CORE_MATH_VECTOR & size ) {
    
    auto entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntityWithComponents< GAMEPLAY_COMPONENT_POSITION, GAMEPLAY_COMPONENT_RENDER >();
    
    GAMEPLAY_HELPER::Set3DPlane( entity, size );
    
    auto text = GRAPHIC_TEXTURE::LoadResourceForPath( CORE_HELPERS_UNIQUE_IDENTIFIER( "map-color" ), CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    SERVICE_LOGGER_Error( "GAMEPLAY_HELPER::SetTexture : create %p\n", text );
    auto height_map_object = GAMEPLAY_HELPER::Set3DHeighFieldObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "heightmap" ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "TerrainShader" ) );
    GAMEPLAY_HELPER::SetTexture(entity, "map-color", CORE_FILESYSTEM_PATH::FindFilePath("map_color_0", "png", "MAP" ) );
    
    return entity;
}
