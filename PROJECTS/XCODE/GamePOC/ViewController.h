//
//  ViewController.h
//  gamePOC
//
//  Created by Christophe Bernard on 7/10/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "Application.h"

#include "CORE_APPLICATION.h"
#include "GRAPHIC_WINDOW_IOS.h"

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet GLKView *glView;
@property (weak) UIWindow * window;
@property (assign) MyTestApp * application;

@end

