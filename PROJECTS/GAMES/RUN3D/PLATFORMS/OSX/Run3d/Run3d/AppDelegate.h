//
//  AppDelegate.h
//  Run3d
//
//  Created by Christophe Bernard on 17/04/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import <Carbon/Carbon.h>

#import "RUN3D_APPLICATION.h"
#import "GRAPHIC_WINDOW_OSX.h"
#import "PERIPHERIC_INTERACTION_SYSTEM.h"


@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (assign) RUN3D_APPLICATION * Application;
@property (assign) GRAPHIC_WINDOW_OSX * ApplicationMainScreen;
@property (assign) CGPoint initialPoint;
@property (assign) id EventMonitor;
@end
