//
//  ViewController.h
//  ASSET_EDITOR
//
//  Created by Christophe Bernard on 14/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ASSET_EDITOR.h"
#import "GRAPHIC_WINDOW_OSX.h"

@interface RootViewController : NSViewController

@property ASSET_EDITOR *Application;
@property GRAPHIC_WINDOW_OSX * applicationMainScreen;
@property (strong) IBOutlet NSView *view;

- (void)viewWillAppear;

@end

