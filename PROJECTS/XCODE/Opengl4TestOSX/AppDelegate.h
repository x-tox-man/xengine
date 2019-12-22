//
//  AppDelegate.h
//  Opengl4TestOSX
//
//  Created by Christophe Bernard on 16/12/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>

#import "METAL_TEST.h"
#import "GRAPHIC_WINDOW_OSX.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (assign) METAL_TEST * Application;
@property (assign) GRAPHIC_WINDOW_OSX * ApplicationMainScreen;

@end

