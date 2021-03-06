//
//  CORE_FILESYSTEM_PATH.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM.h"
#include "SERVICE_LOGGER.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_FILESYSTEM_PATH )
    XS_DEFINE_ClassMemberArray( "Path", char, Path, (size_t) FILE_PATH_MAX_LENGHT )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH() :
    Path() {
    
    Path[0] = '\0';
}

CORE_FILESYSTEM_PATH::~CORE_FILESYSTEM_PATH() {

}

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH( const char * path ) :
    Path() {
    
    CORE_DATA_COPY_STRING( Path, path );
}

CORE_FILESYSTEM_PATH::CORE_FILESYSTEM_PATH( const CORE_FILESYSTEM_PATH & other ) {
    
    CORE_DATA_COPY_STRING( Path, other.Path );
}

#if !PLATFORM_ANDROID && !PLATFORM_IOS
    CORE_FILESYSTEM_PATH CORE_FILESYSTEM_PATH::FindFilePath( const char * path, const char * extension, const char * directory, bool override_extension ) {
        
        char path_buffer[ FILE_PATH_MAX_LENGHT ];
        
        CORE_FILESYSTEM_PATH
            file_path;
        
        path_buffer[0] = '\0';
        
        CORE_DATA_COPY_STRING( path_buffer, CORE_FILESYSTEM::GetDefaultFilesystem().GetBaseDirectoryPath() );
        
        if ( strlen(directory ) ) {
            
            CORE_DATA_STRING_CONCAT( path_buffer, directory );
            CORE_DATA_STRING_CONCAT( path_buffer, CORE_FILESYSTEM::GetDirectorySeparator() );
        }
        
        CORE_DATA_STRING_CONCAT( path_buffer, path );
        
        // Need to check if extension is already present in path
        // if it is then override it
        char * dot  = strrchr(path_buffer, '.' );
        
        if ( (dot == NULL|| !override_extension) && strlen( extension )  ) {
            
            CORE_DATA_STRING_CONCAT( path_buffer, "." );
            CORE_DATA_STRING_CONCAT( path_buffer, extension );
        }
        else if ( strlen( extension ) && override_extension ) {
            
            CORE_DATA_COPY_STRING( ++dot, extension );
            dot+= strlen(extension);
            *dot = '\0';
        }
        
        file_path.SetPath( path_buffer );
        
        return file_path;
    }

    std::vector< CORE_FILESYSTEM_PATH> CORE_FILESYSTEM_PATH::FindAllFilePaths( const char * pattern, const char * extension, const char * directory ) {
        std::vector< CORE_FILESYSTEM_PATH> files;
        
        
        
        return files;
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

CORE_FILESYSTEM_PATH
    CORE_FILESYSTEM_PATH::NotExisting( "\0" );

bool operator < (const CORE_FILESYSTEM_PATH & first, const CORE_FILESYSTEM_PATH & second ) {
    
    return strcmp(first.GetPath(), second.GetPath());
}
