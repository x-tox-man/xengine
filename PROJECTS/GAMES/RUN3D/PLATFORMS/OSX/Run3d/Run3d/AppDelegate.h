//
//  AppDelegate.h
//  Run3d
//
//  Created by Christophe Bernard on 17/04/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#import "GRAPHIC_WINDOW_OSX.h"
#import "RUN3D_APPLICATION.h"

@interface AppDelegate : UIResponder <NSApplicationDelegate, NSWindowDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) RUN3D_APPLICATION * Application;
@property (assign) GRAPHIC_WINDOW_OSX *ApplicationMainScreen;

@property (strong, nonatomic) UIWindow *window;


@end

