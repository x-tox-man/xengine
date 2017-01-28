//
//  ViewController.m
//  gamePOC
//
//  Created by Christophe Bernard on 7/10/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // Insert code here to initialize your application
    
    self.application = new MyTestApp();
    self.application->setApplicationName( "test" );
    
    GRAPHIC_WINDOW_IOS * window = new GRAPHIC_WINDOW_IOS;
    window->setHeight([[[[UIApplication sharedApplication] windows] objectAtIndex:0] frame].size.height);
    window->setWidth([[[[UIApplication sharedApplication] windows] objectAtIndex:0] frame].size.width);
    
    window->SetGlView(self.glView);
    window->Initialize();
    
    self.application->SetApplicationWindow( *window );
    self.application->Initialize();
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    
    [super viewWillAppear:animated];
}

@end
