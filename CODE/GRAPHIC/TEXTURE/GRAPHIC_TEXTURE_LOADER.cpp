//
//  GRAPHIC_TEXTURE_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_TEXTURE.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"

GRAPHIC_TEXTURE_LOADER::GRAPHIC_TEXTURE_LOADER() :
    GRAPHIC_TEXTURE_ANCESTOR_LOADER_TYPE() {
    
}

GRAPHIC_TEXTURE_LOADER::~GRAPHIC_TEXTURE_LOADER() {
    
}

GRAPHIC_TEXTURE * GRAPHIC_TEXTURE_LOADER::Load( const CORE_FILESYSTEM_PATH & path,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    RESOURCE_IMAGE_PNG_LOADER
        loader;
    RESOURCE_IMAGE * image = loader.Load( path, identifier );
    
    if ( image == NULL ) {
        
        return NULL;
    }
    
    GRAPHIC_TEXTURE * texture = image->CreateTextureObject( false );
    
    CORE_MEMORY_ObjectSafeDeallocation( image );
    
    return texture;
}

GRAPHIC_TEXTURE * GRAPHIC_TEXTURE_LOADER::Load( CORE_DATA_STREAM & stream ,const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier) {
    
    abort();
}

void GRAPHIC_TEXTURE_LOADER::ReloadResource( GRAPHIC_TEXTURE * resource_to_reload ) {
    
}

#if ASSET_COMPILER
void GRAPHIC_TEXTURE_LOADER::GRAPHIC_TEXTURE_LOADER::CompileResource( const CORE_FILESYSTEM_PATH & source_file, const CORE_FILESYSTEM_PATH & destination_file ) {
    
}

#endif
