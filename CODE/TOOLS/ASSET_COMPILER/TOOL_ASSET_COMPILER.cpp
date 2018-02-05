//
//  TOOL_ASSET_COMPILER.cpp
//  GAME-ENGINE
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
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"

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
        
        CORE_FILESYSTEM_PATH file_name_without_extension = source_file_path.RemoveExtension();
        
        CORE_FILESYSTEM_PATH destination_file_path = CORE_FILESYSTEM_PATH::FindFilePath(file_name_without_extension.GetFileName(), "smx", "" );
        
        loader.CompileResource( source_file_path, destination_file_path );
    }
    else if ( strcmp(ext, "font" ) == 0 ) {
        
        abort();
    }
    else if ( strcmp( ext, "atlas" ) == 0 ) {
        
        abort();
    }
    else if ( strcmp( ext, "png" ) == 0 ) {
        
        RESOURCE_IMAGE_PNG_LOADER
            loader;
        RESOURCE_IMAGE_PNG_WRITER
            writer;
        
        RESOURCE_IMAGE * image = loader.Load(source_file_path);
        
        char * buffer = (char*) malloc( strlen( destination_dir ) + strlen( source_file_path.GetFileName() + 5 ) );
        
        CORE_DATA_COPY_STRING(buffer, destination_dir );
        CORE_DATA_STRING_CONCAT( buffer, source_file_path.GetFileName() );
        CORE_DATA_STRING_CONCAT( buffer, ".png" );
        
        CORE_FILESYSTEM_PATH file_name_without_extension( buffer );
        
        image->Premultiply();
        writer.Write( file_name_without_extension, image );
    }
}

TOOL_ASSET_COMPILER::~TOOL_ASSET_COMPILER(){
    
}

