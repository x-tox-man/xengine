//
//  GRAPHIC_WINDOW_OSX.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_WINDOW_IOS.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_PARALLEL_LOCK.h"

#if X_METAL
    #import <Metal/Metal.h>
    #import <MetalKit/MetalKit.h>
    #import "METAL_VIEW_DELEGATE.h"
#endif

GRAPHIC_WINDOW_IOS::GRAPHIC_WINDOW_IOS() :
    GRAPHIC_WINDOW()
#if OPENGL2PLUS
    ,glView( NULL ),
    context( NULL )
#endif
{
    
}

GRAPHIC_WINDOW_IOS::~GRAPHIC_WINDOW_IOS() {
    
#if OPENGL2PLUS
    glView.context = nil;
    [EAGLContext setCurrentContext:nil];
#endif
}

void GRAPHIC_WINDOW_IOS::Initialize()
{
    #if OPENGL2PLUS
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        [EAGLContext setCurrentContext:context];
        
        glView.context = context;
        
        glView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    #elif X_METAL
        MTKView * v = (__bridge MTKView *) MetalView;
    
        GRAPHIC_SYSTEM::InitializeMetal( MetalView );
    #endif
}

void GRAPHIC_WINDOW_IOS::Resize( int width, int height ) {
    
    SetWidth( width );
    SetHeight( height );
    
    GRAPHIC_RENDERER::GetInstance().Resize(width, height);
}

void GRAPHIC_WINDOW_IOS::EnableBackgroundContext(bool enable) {
    
    #if OPENGL2PLUS
        [EAGLContext setCurrentContext:context];
    #endif
}

#if OPENGL2PLUS
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
    CORE_PARALLEL_LOCK Lock( GRAPHIC_SYSTEM::GraphicSystemLock );
    
    [EAGLContext setCurrentContext: self.context];
    
    CORE_APPLICATION * app = &CORE_APPLICATION::GetApplicationInstance();
    
    if ( app != NULL ) {
        
        CORE_APPLICATION::GetApplicationInstance().Update( 0.033f );
    }
    
    glClearColor(GRAPHIC_SYSTEM::ClearColor.GetX(), GRAPHIC_SYSTEM::ClearColor.GetY(), GRAPHIC_SYSTEM::ClearColor.GetZ(), 1.0f );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Do graphic system instead: a renderer is for a gfx implementation
    GRAPHIC_RENDERER::GetInstance().BeginFrame();
    GRAPHIC_RENDERER::GetInstance().Render();
    GRAPHIC_RENDERER::GetInstance().EndFrame();
    
    glFlush();
    
}

@end

#endif
