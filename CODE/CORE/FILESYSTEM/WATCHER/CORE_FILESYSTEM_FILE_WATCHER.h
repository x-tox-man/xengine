//
//  CORE_FILESYSTEM_FILE_WATCHER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 13/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_FILESYSTEM_FILE_WATCHER_h
#define CORE_FILESYSTEM_FILE_WATCHER_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CALLBACK.h"


XS_CLASS_BEGIN( CORE_FILESYSTEM_FILE_WATCHER )

    CORE_FILESYSTEM_FILE_WATCHER();
    ~CORE_FILESYSTEM_FILE_WATCHER();

    void Setup( const char * path, const CORE_HELPERS_CALLBACK & callback );

    CORE_HELPERS_CALLBACK Callback;

XS_CLASS_END

#endif /* CORE_FILESYSTEM_FILE_WATCHER_h */
