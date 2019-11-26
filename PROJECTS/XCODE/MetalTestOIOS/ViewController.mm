//
//  ViewController.m
//  MetalTestOIOS
//
//  Created by Christophe Bernard on 12/11/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import "ViewController.h"
#import "GRAPHIC_WINDOW_IOS.h"
#import "METAL_TEST.h"
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@implementation ViewController
{
    METAL_TEST * MetalTest;
    GRAPHIC_WINDOW_IOS * Window;
    MTKView * _view;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    auto window = new GRAPHIC_WINDOW_IOS;
    self->Window = window;
    self->Window->SetMTKView( (void *) CFBridgingRetain(self.view) );
    self->Window->Resize( self.view.bounds.size.width, self.view.bounds.size.height );
    self->Window->Initialize();
    
    self->MetalTest = new METAL_TEST();
    self->MetalTest->SetApplicationWindow( *window );
    self->MetalTest->Initialize();
}

@end
