//
//  CORE_FILESYSTEM_FILE_WATCHER_OSX.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 13/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_FILESYSTEM_FILE_WATCHER_OSX_h
#define CORE_FILESYSTEM_FILE_WATCHER_OSX_h

#import <Foundation/Foundation.h>
#include "CORE_HELPERS_CALLBACK.h"

@interface CORE_FILESYSTEM_FILE_WATCHER_OSX : NSObject

-(void) setup:(const char*) fileToWatch andCallback:(CORE_HELPERS_CALLBACK &) callback;

@end


#endif /* CORE_FILESYSTEM_FILE_WATCHER_OSX_h */
