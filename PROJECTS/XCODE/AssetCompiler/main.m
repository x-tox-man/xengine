//
//  main.m
//  AssetCompiler
//
//  Created by Christophe Bernard on 13/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "TOOL_ASSET_COMPILER.h"

const char * GetCurrentDir() {
    
    return "./";
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        if ( argc > 1 ) {
            
            const char * source_path = argv[1];
            const char * destination_dir = argv[2] == NULL ? GetCurrentDir() : argv[2];
            const char * options = argv[3] == NULL ? "" : argv[3];
            
            TOOL_ASSET_COMPILER(source_path, destination_dir, options);
        }
    }
    return 0;
}
