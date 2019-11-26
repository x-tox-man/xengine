//
//  ViewController.m
//  MetalTestOSX
//
//  Created by Christophe Bernard on 13/09/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#import "ViewController.h"
#import "CORE_APPLICATION.h"
#import "GRAPHIC_WINDOW_OSX.h"
#import "GRAPHIC_OBJECT.h"
#import "GRAPHIC_SHADER_EFFECT.h"
#import "GRAPHIC_SHADER_EFFECT_LOADER.h"
#import "GRAPHIC_RENDERER.h"
#import "GRAPHIC_CAMERA.h"
#import "GRAPHIC_TEXTURE.h"
#import "GRAPHIC_MESH_MANAGER.h"
#import "METAL_TEST.h"

@implementation ViewController
{
    METAL_TEST * MetalTest;
    GRAPHIC_WINDOW_OSX * Window;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    auto window = new GRAPHIC_WINDOW_OSX;
    self->Window = window;
#if X_METAL
    self->Window->SetMTKView( (void *) CFBridgingRetain(self.view) );
#else
    
#endif
    self->Window->Resize( self.view.bounds.size.width, self.view.bounds.size.height );
    self->Window->Initialize();
    
    self->MetalTest = new METAL_TEST();
    self->MetalTest->SetApplicationWindow( *window );
    self->MetalTest->Initialize();
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end
