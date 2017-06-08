//
//  CORE_FILESYSTEM_FILE_WATCHER_OSX.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 13/03/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CORE_FILESYSTEM_FILE_WATCHER_OSX.h"

@implementation CORE_FILESYSTEM_FILE_WATCHER_OSX {
    __block dispatch_source_t source;
}

-(void) setup:(const char*) fileToWatch andCallback:(CORE_HELPERS_CALLBACK &) callback{
    
    int fdes = open( fileToWatch, O_RDONLY);
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    
    void (^eventHandler)(void), (^cancelHandler)(void);
    unsigned long mask = DISPATCH_VNODE_WRITE;
    
    eventHandler = ^{
        dispatch_async(dispatch_get_main_queue(), ^{
            unsigned long l = dispatch_source_get_data(source);
            if (l & DISPATCH_VNODE_DELETE) {
                printf("watched file deleted!  cancelling source\n");
                dispatch_source_cancel(source);
            }
            else {
                // handle the file has data case
                printf("watched file has data\n");
                
                callback();
            }
        });
    };
    
    source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE,fdes, mask, queue);
    dispatch_source_set_event_handler(source, eventHandler);
    dispatch_source_set_cancel_handler(source, cancelHandler);
    dispatch_resume(source);
    
    eventHandler = NULL;
    cancelHandler = NULL;
    //dispatch_main();
}

@end
