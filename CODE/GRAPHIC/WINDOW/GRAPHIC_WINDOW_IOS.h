//
//  GRAPHIC_WINDOW_OSX.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_WINDOW.h"
#import <UIKit/UIKit.h>

#if OPENGL2PLUS

    #import <GLKit/GLKit.h>

    @interface CustomGlView : GLKView
        -(void) refreshView;
    @end

#elif X_METAL

#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_WINDOW_IOS, GRAPHIC_WINDOW )

    GRAPHIC_WINDOW_IOS();
    virtual ~GRAPHIC_WINDOW_IOS();

    #if X_METAL
        inline void * GetMTKView() { return MetalView; }
        inline void SetMTKView( void * view) { MetalView = view; }
    #elif OPENGL2PLUS
        CustomGlView * GetGlView() { return glView; }

        GLKView * GetGlView() { return glView; }
        void SetGlView( GLKView * view) { glView = view; }
    #else
        #error "TODO : Implement"
    #endif

    virtual void Initialize() override;
    virtual void EnableBackgroundContext(bool enable) override;
    virtual void Resize( int width, int height );

private :

    #if X_METAL
        void
            * MetalView;
    #elif OPENGL2PLUS
        CustomGlView
            * glView;
    #else
        #error "TODO : Implement"
    #endif

XS_CLASS_END
