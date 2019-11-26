//
//  GRAPHIC_WINDOW_OSX.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_WINDOW_OSX.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_SYSTEM.h"
#include "CORE_PARALLEL_LOCK.h"

#if X_METAL
    #import <Metal/Metal.h>
    #import <MetalKit/MetalKit.h>
    #import "METAL_VIEW_DELEGATE.h"
#endif

GRAPHIC_WINDOW_OSX::GRAPHIC_WINDOW_OSX() :
    GRAPHIC_WINDOW()
{
    
}

GRAPHIC_WINDOW_OSX::~GRAPHIC_WINDOW_OSX() {
    
}

CORE_HELPERS_CALLBACK_1< const char * >
    GRAPHIC_WINDOW_OSX::OndraggedCallback;

void GRAPHIC_WINDOW_OSX::Initialize()
{
    #if X_METAL
        MTKView * v = (__bridge MTKView *) MetalView;
        v.allowedTouchTypes = NSTouchTypeMaskDirect;
    
        GRAPHIC_SYSTEM::InitializeMetal( MetalView );
    #elif OPENGL4
        glView = [[CustomGlView alloc] initWithFrame:NSMakeRect( GetPositionX(), GetPositionY(), GetWidth(), GetHeight())];
    
        [glView registerForDraggedTypes:[NSArray arrayWithObjects: NSFilenamesPboardType, nil]];
    #else
        #error "TODO : Implement"
    #endif
}

void GRAPHIC_WINDOW_OSX::Display() {

    #if X_METAL
        //#error "TODO : Implement"
    #elif OPENGL4
        [glView startUpdate];
    #else
        #error "TODO : Implement"
    #endif
}

void GRAPHIC_WINDOW_OSX::EnableBackgroundContext(bool enable) {
    
    #if X_METAL
        //#error "TODO : Implement"
    #elif OPENGL4
        [glView enableBackgroundContext:(BOOL)enable];
    #else
    #error "TODO : Implement"
    #endif
}

void GRAPHIC_WINDOW_OSX::Resize( int width, int height ) {
    
    SetWidth( width );
    SetHeight( height );
    
    #if X_METAL
        //#error "TODO : Implement"
    #elif OPENGL4
    
        CGRect newFrame = glView.frame;
        newFrame.size.width = width;
        newFrame.size.height = height;
    
        [glView setFrame:newFrame];
        [glView.superview setFrame:newFrame];
    #else
        #error "TODO : Implement"
    #endif
    
    GRAPHIC_RENDERER::GetInstance().Resize(width, height);
}

void GRAPHIC_WINDOW_OSX::SetupWindow( NSWindow * window ) {
    
    //[window.contentView setAcceptsTouchEvents:YES];
    window.contentView.allowedTouchTypes = NSTouchTypeMaskDirect;
    
    #if X_METAL
        
    #elif OPENGL4
        glView.allowedTouchTypes = NSTouchTypeMaskDirect;
        [window.contentView addSubview:glView];
    #else
        #error "TODO : Implement"
    #endif
    
}

#if OPENGL4
@implementation CustomGlView

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender {
    
    NSPasteboard *pboard = [sender draggingPasteboard];
    
    if ([[pboard types] containsObject:NSFilenamesPboardType]) {
        
        NSArray *paths = [pboard propertyListForType:NSFilenamesPboardType];
        for (NSString *path in paths) {
            NSError *error = nil;
            NSString *utiType = [[NSWorkspace sharedWorkspace]
                                 typeOfFile:path error:&error];
            if (![[NSWorkspace sharedWorkspace]
                  type:utiType conformsToType:(id)kUTTypeFolder]) {
                
                return NSDragOperationEvery;
            }
        }
    }
    
    return NSDragOperationEvery;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
    
    NSPasteboard *pboard = [sender draggingPasteboard];
    
    if ([[pboard types] containsObject:NSFilenamesPboardType]) {
        
        NSArray *paths = [pboard propertyListForType:NSFilenamesPboardType];
        
        for (NSString *path in paths) {
            
            if ( GRAPHIC_WINDOW_OSX::OndraggedCallback.IsConnected() ) {
                
                GRAPHIC_WINDOW_OSX::OndraggedCallback( [path cStringUsingEncoding:NSASCIIStringEncoding] );
            }
        }
    }
    return YES;
}

- (id) initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format
{
    self = [super initWithFrame:frameRect pixelFormat:format];
    
    if (self) {
        // Initialization code
        
        NSOpenGLPixelFormatAttribute attributes[] = {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, (NSOpenGLPixelFormatAttribute )32,
            NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute )24,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAMinimumPolicy,
            NSOpenGLPFAMaximumPolicy,
            // NSOpenGLPFAClosestPolicy,
            0
        };
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(surfaceNeedsUpdate)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];
        
        GLint swapInt = 1;
        
        [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
        NSOpenGLPixelFormat * pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        
        self.openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        
        //self.backgroundContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        
        [self setContext:self.openGLContext];
        
        [self setPixelFormat:pixelFormat];
        [self setOpenGLContext:self.openGLContext];
        [self prepareOpenGL];
        
        [self.openGLContext makeCurrentContext];
        
        [self.openGLContext flushBuffer];
        
        // https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_threading/opengl_threading.html#//apple_ref/doc/uid/TP40001987-CH409-SW12
        /*CGLError err =  CGLEnable( CGLGetCurrentContext(), kCGLCEMPEngine);
        
        if (err != kCGLNoError )
        {
            // Multithreaded execution may not be available
            // Insert your code to take appropriate action
        }*/
        
        [[self window] setDelegate:self];
        
        const float s = (1.0f / 30.0f );
        
        self.DisplayTimer = [NSTimer timerWithTimeInterval:s target:self selector:@selector(surfaceNeedsUpdate) userInfo:nil repeats:YES];
        
        [[NSRunLoop mainRunLoop] addTimer:self.DisplayTimer forMode:NSDefaultRunLoopMode];
    }
    
    return self;
}

-(void)windowWillClose:(NSNotification *)notification {
    
}

- (void)lockFocus
{
    [super lockFocus];
    
    if ([self.openGLContext view] != self)
    {
        [self.openGLContext setView:self];
    }
    
    [self.openGLContext makeCurrentContext];
}

- (void) surfaceNeedsUpdate {
    
    const float s = (1.0f / 30.0f );
    CORE_APPLICATION * app = &CORE_APPLICATION::GetApplicationInstance();
    
    if ( app != NULL ) {
        
        CORE_APPLICATION::GetApplicationInstance().Update( s );
    }
    
    [self update];
    
    [self setNeedsDisplay:YES];
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    
    CORE_PARALLEL_LOCK Lock( GRAPHIC_SYSTEM::GraphicSystemLock );
    
    [self.openGLContext makeCurrentContext];
    
    GFX_CHECK( glClearColor(GRAPHIC_SYSTEM::ClearColor.GetX(), GRAPHIC_SYSTEM::ClearColor.GetY(), GRAPHIC_SYSTEM::ClearColor.GetZ(), 1.0f ); )
    GFX_CHECK( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); )

    //Do graphic system instead: a renderer is for a gfx implementation
    GRAPHIC_RENDERER::GetInstance().BeginFrame();
    GFX_CHECK( glViewport( 0, 0, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight()); )
    
    GRAPHIC_RENDERER::GetInstance().Render();
    GRAPHIC_RENDERER::GetInstance().EndFrame();
    
    GFX_CHECK( glFlush(); )
    
    [[self openGLContext] flushBuffer];
    //Not sure what it does??
    //[NSOpenGLContext clearCurrentContext];
}

-(void) startUpdate {
    
    [self.DisplayTimer fire];
}

-(void) StopUpdate {
    
    [self.DisplayTimer invalidate];
}

-(void) enableBackgroundContext:(BOOL) enable {
    
    if ( enable ) {

        [self.openGLContext makeCurrentContext];
        
        GFX_CHECK( glViewport( 0, 0, CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetWidth(), CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().GetHeight()); )
        
    }
}
@end

#endif
