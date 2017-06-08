//
//  CORE_FILESYSTEM_PATH_ANDROID.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM.h"
#include "SERVICE_LOGGER.h"

#if PLATFORM_ANDROID

    #include <android/asset_manager.h>
    #include <jni.h>

    CORE_FILESYSTEM_PATH CORE_FILESYSTEM_PATH::FindFilePath( const char * path, const char * extension, const char * directory, bool override_extension ) {
        
        CORE_FILESYSTEM_PATH
            file_path;
        char path_buffer[ FILE_PATH_MAX_LENGHT ];
        
        //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH constructing sequence %s %s %s", path, extension, directory );
        
        strcpy( path_buffer, path );
        //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH constructing sequence 2" );
        if ( strlen( extension ) ) {
            //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH constructing sequence 3" );
            strcat( path_buffer, "." );
            //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH constructing sequence 4" );
            strcat( path_buffer, extension );
        }
        
        //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH constructing sequence 5" );
        
        file_path.SetPath( path_buffer );
        
        //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH looking for %s - %d - %d", path_buffer, CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetDirectory(), CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetManager() );
        
        while ( 1 ) {
            
            const char * filename = AAssetDir_getNextFileName( CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetDirectory() );
            
            if ( filename == NULL ) {
                
                
                //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH could not find %s", path_buffer );
                
                AAssetDir_rewind( CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetDirectory() );
                
                file_path.SetPath( path_buffer );
                
                return file_path;
            }
            
            //SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH comparing %s and %s", path_buffer, filename);
            
            if ( strcmp( path_buffer, filename ) == 0 ) {
                
                file_path.SetPath( filename );
                
                SERVICE_LOGGER_Error( "CORE_FILESYSTEM_PATH found %s", path_buffer );
                
                AAssetDir_rewind( CORE_FILESYSTEM::GetDefaultFilesystem().GetAndroidAssetDirectory() );
                
                return file_path;
            }
        }
    }

#endif
