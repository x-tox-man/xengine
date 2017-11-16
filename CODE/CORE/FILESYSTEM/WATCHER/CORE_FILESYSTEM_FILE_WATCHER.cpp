//
//  CORE_FILESYSTEM_FILE_WATCHER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 13/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_FILE_WATCHER.h"

#if PLATFORM_OSX
    #include "CORE_FILESYSTEM_FILE_WATCHER_OSX.h"
#endif

CORE_FILESYSTEM_FILE_WATCHER::CORE_FILESYSTEM_FILE_WATCHER() {
    
}

CORE_FILESYSTEM_FILE_WATCHER::~CORE_FILESYSTEM_FILE_WATCHER() {
    
}

void CORE_FILESYSTEM_FILE_WATCHER::Setup( const char * path, const CORE_HELPERS_CALLBACK & callback ) {
    
    Callback = callback;
    
    #if PLATFORM_OSX && DEBUG
        CORE_FILESYSTEM_FILE_WATCHER_OSX *Watcher;

        Watcher = [[CORE_FILESYSTEM_FILE_WATCHER_OSX alloc] init];
        [Watcher setup:path andCallback:Callback];
    #else
        //CORE_RUNTIME_Abort();
    #endif
}
