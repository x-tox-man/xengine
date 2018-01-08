//
//  CORE_FILESYSTEM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM.h"
#include "CORE_MEMORY.h"

#if PLATFORM_ANDROID
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <jni.h>
#endif

CORE_FILESYSTEM::CORE_FILESYSTEM() :
    BaseDirectoryPath()
#if PLATFORM_ANDROID
    ,AssetDirectory( NULL ),
    AssetManager( NULL  ),
    JNIEnvironment( NULL )
#endif
{
        
}

CORE_FILESYSTEM::~CORE_FILESYSTEM() {

}

void CORE_FILESYSTEM::Initialize( const char * base_directory_path ) {

    CORE_DATA_COPY_STRING( BaseDirectoryPath, base_directory_path );
}

void CORE_FILESYSTEM::Finalize() {
    
    #if PLATFORM_ANDROID
        AAssetDir_close( AssetDirectory );
    #endif
}

bool CORE_FILESYSTEM::DoesFileExist( const CORE_FILESYSTEM_PATH & path ) {

    bool exists = false;
    
    #if PLATFORM_ANDROID
    
        const char * filename = (const char *) NULL;
    
        while ( ( filename = AAssetDir_getNextFileName( AssetDirectory ) ) != NULL) {
            
            if ( strcmp( path.GetPath(), filename ) == 0 ) {
                
                return true;
            }
        }
    #else
        CORE_FILESYSTEM_FILE
            file( path );
        
        exists = file.OpenOutput();
            
        file.Close();
    #endif
    
    return exists;
}

CORE_FILESYSTEM_FILE CORE_FILESYSTEM::FindFile( const char * path, const char * extension, const char * directory ) {
    
    CORE_FILESYSTEM_PATH
        file_path = CORE_FILESYSTEM_PATH::FindFilePath( path , extension, directory );
    
    if ( DoesFileExist( file_path ) ) {
        
        return CORE_FILESYSTEM_FILE( file_path );
    }
    
    return CORE_FILESYSTEM_FILE::NotFound;
}

CORE_FILESYSTEM * CORE_FILESYSTEM::DefaultFileSystem = NULL;
