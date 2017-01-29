//
//  ViewController.m
//  gamePOC
//
//  Created by Christophe Bernard on 7/10/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#import "ViewController.h"
#import "PERIPHERIC_INTERACTION_SYSTEM.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // Insert code here to initialize your application
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    
    [super viewWillAppear:animated];
}

-(void)viewDidAppear:(BOOL)animated
{
    self.application = new MyTestApp();
    self.application->setApplicationName( "test" );
    
    GRAPHIC_WINDOW_IOS * window = new GRAPHIC_WINDOW_IOS;
    window->SetWidth( [[UIScreen mainScreen] bounds].size.width * [[UIScreen mainScreen] scale]);
    window->SetHeight([[UIScreen mainScreen] bounds].size.height * [[UIScreen mainScreen] scale]);
    
    window->SetGlView(self.glView);
    window->Initialize();
    
    self.application->SetApplicationWindow( *window );
    self.application->Initialize();
}

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonClicked();
}

-(void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonReleased();
}

-(void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    
    int32_t deltaX, deltaY;
    
    static CGPoint loc_in_view = [[[event touchesForView:self.glView] anyObject] locationInView:self.glView];
    
    deltaX = loc_in_view.x - [[[event touchesForView:self.glView] anyObject] locationInView:self.glView].x;
    deltaY = loc_in_view.y - [[[event touchesForView:self.glView] anyObject] locationInView:self.glView].y;
    
    loc_in_view = [[[event touchesForView:self.glView] anyObject] locationInView:self.glView];
    
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.glView frame].size.width, deltaY / [self.glView frame].size.height);
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( loc_in_view.x / [self.glView frame].size.width, loc_in_view.y / [self.glView frame].size.height);
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [[[event touchesForView:self.glView] anyObject] locationInView:self.glView].x, [[[event touchesForView:self.glView] anyObject] locationInView:self.glView].y );
}

@end
