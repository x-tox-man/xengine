//
//  AppDelegate.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 15/10/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>

#include "Application.h"

#include "CORE_APPLICATION.h"
#include "GRAPHIC_WINDOW_OSX.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) MyTestApp * application;
@property (assign) GRAPHIC_WINDOW_OSX * applicationMainScreen;

@end
