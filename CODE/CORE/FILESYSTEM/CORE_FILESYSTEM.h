//
//  CORE_FILESYSTEM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_FILESYSTEM__
#define __GAME_ENGINE_REBORN__CORE_FILESYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM_FILE.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( CORE_FILESYSTEM )

    CORE_FILESYSTEM();
    ~CORE_FILESYSTEM();

    static void SetDefaultFilesystem( CORE_FILESYSTEM & file_system ) {
        
        DefaultFileSystem = &file_system;
    }

    static CORE_FILESYSTEM & GetDefaultFilesystem() {
        
        return *DefaultFileSystem;
    }

    #if PLATFORM_WINDOWS
    static const char * GetDirectorySeparator(){

        const char * separator = "\\";
        return separator;
    }

    static char GetDirectorySeparatorChar(){
        
        return '\\';
    }
    #else
    static const char *GetDirectorySeparator() {
        
        const char * separator="/";
        return separator;
    }

    static char GetDirectorySeparatorChar() {
        
        return '/';
    }
    #endif

    void Initialize( const char * base_directory_path );
    void Finalize();

    bool DoesFileExist( const CORE_FILESYSTEM_PATH & path );
    CORE_FILESYSTEM_FILE FindFile( const char * path, const char * extension, const char * directory );

    const char * GetBaseDirectoryPath() { return BaseDirectoryPath; }

    private :

    char BaseDirectoryPath[256];
    static CORE_FILESYSTEM * DefaultFileSystem;

#if PLATFORM_ANDROID
    #include "CORE_FILESYSTEM_ANDROID.hpp"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_FILESYSTEM__) */
