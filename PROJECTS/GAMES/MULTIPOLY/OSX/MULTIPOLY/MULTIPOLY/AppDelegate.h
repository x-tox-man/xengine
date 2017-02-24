//
//  AppDelegate.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>

#include "MULTIPOLY_APPLICATION.h"
#include "GRAPHIC_WINDOW_OSX.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (assign) IBOutlet NSWindow * Window;
@property (assign) MULTIPOLY_APPLICATION * Application;
@property (assign) GRAPHIC_WINDOW_OSX * ApplicationMainScreen;

@end
