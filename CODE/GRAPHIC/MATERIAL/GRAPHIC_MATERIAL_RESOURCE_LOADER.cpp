//
//  GRAPHIC_MATERIAL_RESOURCE_LOADER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_MATERIAL.h"
#include "CORE_DATA_LOADER.h"

GRAPHIC_MATERIAL_RESOURCE_LOADER::GRAPHIC_MATERIAL_RESOURCE_LOADER() {
    
}

GRAPHIC_MATERIAL_RESOURCE_LOADER::~GRAPHIC_MATERIAL_RESOURCE_LOADER() {
    
}

GRAPHIC_MATERIAL * GRAPHIC_MATERIAL_RESOURCE_LOADER::Load( const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_MATERIAL::PTR material = new GRAPHIC_MATERIAL();
    
    CORE_DATA_LOADER< GRAPHIC_MATERIAL >::Load(material, path );
    
    return material;
}

GRAPHIC_MATERIAL * GRAPHIC_MATERIAL_RESOURCE_LOADER::Load( CORE_DATA_STREAM & stream ,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    GRAPHIC_MATERIAL::PTR material;
    
    CORE_DATA_LOADER< GRAPHIC_MATERIAL >::Load( material, stream );
    
    return material;
}

void GRAPHIC_MATERIAL_RESOURCE_LOADER::ReloadResource( GRAPHIC_MATERIAL * resource_to_reload ) {
    
}

#if ASSET_COMPILER
void GRAPHIC_MATERIAL_RESOURCE_LOADER::CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file ) {
    
}
#endif

GRAPHIC_MATERIAL * GRAPHIC_MATERIAL_RESOURCE_LOADER::LoadObject( const CORE_FILESYSTEM_PATH & path, int meshIdentifier, int meshTypeToLoad ) {
    
    return NULL;
}
