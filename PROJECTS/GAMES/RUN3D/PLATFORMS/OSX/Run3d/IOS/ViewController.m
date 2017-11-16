//
//  ViewController.m
//  IOS
//
//  Created by Christophe Bernard on 4/11/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#import "ViewController.h"
#import "PERIPHERIC_INTERACTION_SYSTEM.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)viewDidAppear:(BOOL)animated
{
    self.Application = new RUN3D_APPLICATION();
    self.Application->setApplicationName( "test" );
    
    GRAPHIC_WINDOW_IOS * window = new GRAPHIC_WINDOW_IOS;
    window->SetWidth( [[UIScreen mainScreen] bounds].size.width * [[UIScreen mainScreen] scale]);
    window->SetHeight([[UIScreen mainScreen] bounds].size.height * [[UIScreen mainScreen] scale]);
    
    window->SetGlView(self.glView);
    window->Initialize();
    
    self.Application->SetApplicationWindow( *window );
    self.Application->Initialize();
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
