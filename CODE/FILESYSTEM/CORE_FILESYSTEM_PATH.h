//
//  CORE_FILESYSTEM_PATH.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_FILESYSTEM_PATH__
#define __GAME_ENGINE_REBORN__CORE_FILESYSTEM_PATH__

#include "CORE_HELPERS_CLASS.h"

#define FILE_PATH_MAX_LENGHT 256

XS_CLASS_BEGIN_WITH_COPY( CORE_FILESYSTEM_PATH )

    CORE_FILESYSTEM_PATH();
    CORE_FILESYSTEM_PATH( const char * path );
    ~CORE_FILESYSTEM_PATH();

    CORE_FILESYSTEM_PATH & operator = ( const CORE_FILESYSTEM_PATH & other ) {
        
        size_t l = strlen( other.Path ) + 1;

        strcpy_s( Path, l, other.Path );
        
        return *this;
    }

    void SetPath( const char * file_path ) {
        
        size_t l=strlen( file_path ) + 1;
            strcpy_s( Path, l, file_path );
    }

    CORE_FILESYSTEM_PATH RemoveExtension() const {
        
        CORE_FILESYSTEM_PATH new_path( Path );
        
        char * dot = strrchr( new_path.Path, '.' );
        
        if ( dot ) {
            *dot = '\0';
        }
        
        return new_path;
    }

    const char * GetPath() const { return Path; }
    const char * GetFileName() const;

    static CORE_FILESYSTEM_PATH FindFilePath( const char * path, const char * extension, const char * directory, bool override_extension = false );

    static CORE_FILESYSTEM_PATH NotExisting;

private :

    char
        Path[ FILE_PATH_MAX_LENGHT ];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FILESYSTEM_PATH__) */
