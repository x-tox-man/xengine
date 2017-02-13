//
//  GRAPHIC_WINDOW_OSX.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_CLASS.h"

#import <AppKit/AppKit.h>
#import <GLKit/GLKit.h>
#import <Cocoa/Cocoa.h>
#include "GRAPHIC_WINDOW.h"

@interface CustomGlView : NSOpenGLView< NSWindowDelegate >

    @property NSOpenGLContext * context;
    @property NSTimer * DisplayTimer;

    -(void) surfaceNeedsUpdate;
    -(void) startUpdate;
    -(void) StopUpdate;
    - (void)windowWillClose:(NSNotification *)notification;

@end

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_OSX, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_OSX();
    virtual ~GRAPHIC_WINDOW_OSX();

    virtual void Initialize() override;
    void Display();

    CustomGlView * GetGlView() { return glView; }

private :

    CustomGlView
        * glView;

XS_CLASS_END
