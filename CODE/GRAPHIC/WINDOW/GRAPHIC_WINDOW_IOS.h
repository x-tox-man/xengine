//
//  GRAPHIC_WINDOW_OSX.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_WINDOW.h"
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface CustomGlView : GLKView

-(void) refreshView;
@end

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_IOS, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_IOS();
    virtual ~GRAPHIC_WINDOW_IOS();

    virtual void Initialize() override;
    GLKView * GetGlView() { return glView; }
    void SetGlView( GLKView * view) { glView = view; }

private :

    GLKView
        * glView;
    EAGLContext
        * context;

XS_CLASS_END
