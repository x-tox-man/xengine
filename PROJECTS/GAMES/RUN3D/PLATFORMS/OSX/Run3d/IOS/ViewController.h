//
//  ViewController.h
//  IOS
//
//  Created by Christophe Bernard on 4/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "RUN3D_APPLICATION.h"

#include "CORE_APPLICATION.h"
#include "GRAPHIC_WINDOW_IOS.h"

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet GLKView *glView;
@property (weak) UIWindow * window;
@property (assign) RUN3D_APPLICATION * Application;

@end

