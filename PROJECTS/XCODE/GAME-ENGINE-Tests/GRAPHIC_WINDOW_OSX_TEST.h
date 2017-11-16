//
//  GRAPHIC_WINDOW_OSX_TEST.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_WINDOW_OSX_TEST_h
#define GRAPHIC_WINDOW_OSX_TEST_h

#include "CORE_HELPERS_CLASS.h"

#import <AppKit/AppKit.h>
#import <GLKit/GLKit.h>
#import <Cocoa/Cocoa.h>
#import "GRAPHIC_WINDOW.h"
#import "CORE_HELPERS_CALLBACK.h"

@interface CustomGlViewTest : NSOpenGLView< NSWindowDelegate >

@property NSOpenGLContext * context;
@property NSOpenGLContext * backgroundContext;
@property NSTimer * DisplayTimer;

-(void) surfaceNeedsUpdate;
-(void) startUpdate;
-(void) StopUpdate;
-(void) enableBackgroundContext:(BOOL) enable;
-(void) windowWillClose:(NSNotification *)notification;

@end

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_OSX_TEST, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_OSX_TEST();
    virtual ~GRAPHIC_WINDOW_OSX_TEST();

    virtual void Initialize() override;
    void Display();

    CustomGlViewTest * GetGlView() { return glView; }

    virtual void EnableBackgroundContext(bool enable) override;
    virtual void Resize( int width, int height ) override;

    static void SetOndraggedCallback( const CORE_HELPERS_CALLBACK_1<const char *> & callback) { OndraggedCallback = callback; }

    static CORE_HELPERS_CALLBACK_1< const char * >
        OndraggedCallback;

private :

    CustomGlViewTest
        * glView;

    XS_CLASS_END


#endif /* GRAPHIC_WINDOW_OSX_TEST_h */
