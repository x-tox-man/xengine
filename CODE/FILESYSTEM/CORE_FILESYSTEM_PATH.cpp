//
//  CORE_FILESYSTEM_PATH.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM.h"
#include "SERVICE_LOGGER.h"

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH() {
    
}

CORE_FILESYSTEM_PATH::~CORE_FILESYSTEM_PATH() {

}

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH( const char * path ) {
    
    strcpy( Path, path );
}

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH( const CORE_FILESYSTEM_PATH & other ) {
    
    strcpy(Path, other.Path);
}

#if !PLATFORM_ANDROID && !PLATFORM_IOS
    CORE_FILESYSTEM_PATH CORE_FILESYSTEM_PATH::FindFilePath( const char * path, const char * extension, const char * directory, bool override_extension ) {
        
        char path_buffer[ FILE_PATH_MAX_LENGHT ];
        
        CORE_FILESYSTEM_PATH
            file_path;
        
        strcpy( path_buffer, CORE_FILESYSTEM::GetDefaultFilesystem().GetBaseDirectoryPath() );
        strcat( path_buffer, directory );
        strcat( path_buffer, CORE_FILESYSTEM::GetDirectorySeparator() );
        strcat( path_buffer, path );
        
        // Need to check if extension is already present in path
        // if it is then override it
        char * dot  = strrchr(path_buffer, '.' );
        
        if ( (dot == NULL|| !override_extension) && strlen( extension )  ) {
            
            strcat( path_buffer, "." );
            strcat( path_buffer, extension );
        }
        else if ( strlen( extension ) && override_extension ) {
            
            strcpy( ++dot, extension );
            dot+= strlen(extension);
            *dot = '\0';
        }
        
        file_path.SetPath( path_buffer );
        
        return file_path;
    }
#endif

const char * CORE_FILESYSTEM_PATH::GetFileName() const {

    const char * last_occurence = strrchr( Path, CORE_FILESYSTEM::GetDirectorySeparatorChar() );
    
    if ( last_occurence == NULL ) {
        last_occurence = &Path[0];
    }
    else {
        last_occurence = last_occurence + 1;
    }
    
    return last_occurence;
}

CORE_FILESYSTEM_PATH CORE_FILESYSTEM_PATH::NotExisting( "" );