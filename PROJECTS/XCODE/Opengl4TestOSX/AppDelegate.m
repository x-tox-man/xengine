//
//  AppDelegate.m
//  Opengl4TestOSX
//
//  Created by Christophe Bernard on 16/12/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    self.Application = new METAL_TEST();
    self.Application->setApplicationName( "3DRunner" );
    
    self.ApplicationMainScreen = new GRAPHIC_WINDOW_OSX;
    self.ApplicationMainScreen->SetHeight(768);
    self.ApplicationMainScreen->SetWidth(1024);
    self.ApplicationMainScreen->Initialize();
    
    self.Application->SetApplicationWindow( *self.ApplicationMainScreen );
    self.Application->Initialize();
    
    self.ApplicationMainScreen->Display();
    
    [[self window] setDelegate: self];
    
    self.window = [[NSApplication sharedApplication] mainWindow];
    [self.window setFrame:NSRectFromCGRect(CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f) ) display:YES];
    
    self.ApplicationMainScreen->SetupWindow( self.window );
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
