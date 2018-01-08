//
//  main.m
//  AssetCompiler
//
//  Created by Christophe Bernard on 13/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "TOOL_ASSET_COMPILER.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_FILESYSTEM.h"

const char * GetCurrentDir() {
    
    return "./";
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        if ( argc > 2 ) {
            
            const char * source_path = argv[1];
            const char * destination_dir = argv[2] == NULL ? GetCurrentDir() : argv[2];
            const char * options = argv[3] == NULL ? "" : argv[3];
            
            TOOL_ASSET_COMPILER(source_path, destination_dir, options);
        }
        else if ( argc > 1 ) {
            
            const char
                * source_path = argv[1];
            char
                * destination_dir = (char *) malloc( sizeof( char ) * strlen( argv[1] ) );
            const char
                * options = argv[3] == NULL ? "" : argv[3];
            CORE_FILESYSTEM fs;
                fs.Initialize( GetCurrentDir() );
            
            int
                last_occ = (strrchr(source_path, fs.GetDirectorySeparatorChar() ) - source_path )+1;
            
            strncpy( destination_dir, source_path, last_occ );
            
            TOOL_ASSET_COMPILER(source_path, destination_dir, options);
            
            free( destination_dir );
        }
    }
    return 0;
}
