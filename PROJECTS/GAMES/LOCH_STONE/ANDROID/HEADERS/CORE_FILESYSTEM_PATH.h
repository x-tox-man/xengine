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

CORE_FILESYSTEM_PATH & operator = ( const CORE_FILESYSTEM_PATH & other ) {

    strcpy(Path, other.Path);
    
    return *this;
}

void SetPath( const char * file_path ) {
    
    strcpy( Path, file_path );
}

const char * GetPath() const { return Path; }

static CORE_FILESYSTEM_PATH FindFilePath( const char * path, const char * extension, const char * directory );

static CORE_FILESYSTEM_PATH NotExisting;

private :

char Path[ FILE_PATH_MAX_LENGHT ];

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FILESYSTEM_PATH__) */
