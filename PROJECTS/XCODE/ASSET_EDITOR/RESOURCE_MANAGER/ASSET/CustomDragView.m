//
//  CustomDragView.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "CustomDragView.h"

@implementation CustomDragView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender {
    
    NSPasteboard *pboard = [sender draggingPasteboard];
    
    if ([[pboard types] containsObject:NSFilenamesPboardType]) {
        
        NSArray *paths = [pboard propertyListForType:NSFilenamesPboardType];
        for (NSString *path in paths) {
            NSError *error = nil;
            NSString *utiType = [[NSWorkspace sharedWorkspace]
                                 typeOfFile:path error:&error];
            if (![[NSWorkspace sharedWorkspace]
                  type:utiType conformsToType:(id)kUTTypeFolder]) {
                
                return NSDragOperationEvery;
            }
        }
    }
    
    return NSDragOperationEvery;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
    
    NSPasteboard *pboard = [sender draggingPasteboard];
    
    if ([[pboard types] containsObject:NSFilenamesPboardType]) {
        
        NSArray *paths = [pboard propertyListForType:NSFilenamesPboardType];
        
        for (NSString *path in paths) {

            [self.dragProtocol OnFileAdded: path];
        }
    }
    return YES;
}

@end
