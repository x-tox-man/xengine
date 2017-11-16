//
//  CORE_FILESYSTEM_PATH_IOS.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM.h"

#if PLATFORM_IOS

    #import <Foundation/Foundation.h>

    CORE_FILESYSTEM_PATH CORE_FILESYSTEM_PATH::FindFilePath( const char * path, const char * extension, const char * directory, bool override_extension ) {
        
        CORE_FILESYSTEM_PATH
            file_path;
        
        const char * found_path = [[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:[NSString stringWithUTF8String:extension]] cStringUsingEncoding:NSASCIIStringEncoding];
        
        if ( found_path ) {
            
            file_path.SetPath( found_path );
        }
        else {
            file_path.SetPath( path );
        }
        
        return file_path;
    }
#endif
