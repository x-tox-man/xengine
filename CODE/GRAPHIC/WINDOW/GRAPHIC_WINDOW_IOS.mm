//
//  GRAPHIC_WINDOW_OSX.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_WINDOW_IOS.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_RENDERER.h"

GRAPHIC_WINDOW_IOS::GRAPHIC_WINDOW_IOS() :
    GRAPHIC_WINDOW(),
    glView( NULL ),
    context( NULL )
{
    
}

GRAPHIC_WINDOW_IOS::~GRAPHIC_WINDOW_IOS() {
    
    glView.context = nil;
    [EAGLContext setCurrentContext:nil];
}

void GRAPHIC_WINDOW_IOS::Initialize()
{
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:context];
    
    glView.context = context;
    
    glView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
}

@implementation CustomGlView {
    NSTimer * displayTimer;
    CADisplayLink *displayLink;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self) {
        // Initialization code
    
    }
    
    return self;
}

-(instancetype)initWithCoder:(NSCoder *)aDecoder{
    
    self = [super initWithCoder:aDecoder];
    
    if (self) {
        // Initialization code
        
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(refreshView)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
        
    }
    
    return self;
}

-(void) refreshView {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self setNeedsDisplay];
    });
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    
    [EAGLContext setCurrentContext: self.context];
    
    CORE_APPLICATION * app = &CORE_APPLICATION::GetApplicationInstance();
    
    if ( app != NULL ) {
        
        CORE_APPLICATION::GetApplicationInstance().Update( 0.033f );
    }
    
    glClearColor(0.5f, 0, 0.0f, 0.5f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Do graphic system instead: a renderer is for a gfx implementation
    GRAPHIC_RENDERER::GetInstance().BeginFrame();
    GRAPHIC_RENDERER::GetInstance().Render();
    GRAPHIC_RENDERER::GetInstance().EndFrame();
    
    glFlush();
    
}

@end
