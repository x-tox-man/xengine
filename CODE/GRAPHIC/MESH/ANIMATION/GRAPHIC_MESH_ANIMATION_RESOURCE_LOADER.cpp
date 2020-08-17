//
//  GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/07/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER.h"
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_MESH_ANIMATION.h"
#include "CORE_DATA_LOADER.h"

GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER() :
    RESOURCE_LOADER() {
    
};

GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::~GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER() {
    
}

GRAPHIC_MESH_ANIMATION * GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::Load( const CORE_FILESYSTEM_PATH & path, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_MESH_ANIMATION * animation = new GRAPHIC_MESH_ANIMATION;
    
    CORE_DATA_LOADER< GRAPHIC_MESH_ANIMATION >::Load( animation, path );
    
    return animation;
}

GRAPHIC_MESH_ANIMATION * GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::Load( CORE_DATA_STREAM & stream, int resource_load_flag, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_MESH_ANIMATION * animation = new GRAPHIC_MESH_ANIMATION;
    
    CORE_DATA_LOADER< GRAPHIC_MESH_ANIMATION >::Load( animation, stream );
    
    return animation;
}

void GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::ReloadResource( GRAPHIC_MESH_ANIMATION * resource_to_reload ) {
    
    abort();
}

#if ASSET_COMPILER

void GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::CompileResource( const CORE_FILESYSTEM_PATH & source_path, const CORE_FILESYSTEM_PATH & destination_path ) {
    
    abort();
}
#endif

GRAPHIC_MESH_ANIMATION * GRAPHIC_MESH_ANIMATION_RESOURCE_LOADER::LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad ) {
    
    abort();
    
    return NULL;
}
