//
//  TOOL_ASSET_COMPILER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 13/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "TOOL_ASSET_COMPILER.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_FILESYSTEM_FILE.h"
#include "RESOURCE.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"

TOOL_ASSET_COMPILER::TOOL_ASSET_COMPILER(const char * source_path, const char * destination_dir, const char * options) {
    
    CORE_FILESYSTEM DefaultFileystem;
    
    #if PLATFORM_OSX
        DefaultFileystem.Initialize( destination_dir );
    #elif PLATFORM_IOS
        abort();
    #elif PLATFORM_ANDROID
        abort();
    #elif PLATFORM_WINDOWS
        DefaultFileystem.Initialize( destination_path );
    #endif
        
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    const char * file_name;
    const char * dotext = strrchr(source_path, '.' );
    const char * ext = dotext + 1;
    
    file_name = source_path;
    
    while( strrchr( file_name, '/' ) ) {
        
        file_name = strrchr(file_name, '/' ) + 1;
    }
    
    CORE_FILESYSTEM_PATH source_file_path( source_path );
    
    if ( strcmp(ext, "dae" ) == 0 ) {
        
        GRAPHIC_OBJECT_RESOURCE_LOADER
            loader;
        
        CORE_FILESYSTEM_PATH destination_file_path = CORE_FILESYSTEM_PATH::FindFilePath(file_name, "", ".smx" );
        
        loader.CompileResource( source_file_path, destination_file_path );
    }
    else if ( strcmp(ext, "font" ) == 0 ) {
        
    }
    else if ( strcmp( ext, "atlas" ) ) {
        
    }
    else if ( strcmp( ext, "png" ) ) {
        
    }
}

TOOL_ASSET_COMPILER::~TOOL_ASSET_COMPILER(){
    
}

