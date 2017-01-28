//
//  GRAPHIC_RENDERER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_RENDERER__
#define __GAME_ENGINE_REBORN__GRAPHIC_RENDERER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "GRAPHIC_CAMERA.h"
#include "CORE_APPLICATION.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( GRAPHIC_RENDERER )
    XS_DEFINE_UNIQUE( GRAPHIC_RENDERER )

    void Initialize() {
        
    }

    void Finalize() {
        
    }
    
    void BeginFrame() {
        
    }

    void Render() {
        
        (*RenderCallback)();
    }

    void EndFrame() {
        
    }

    inline void SetCamera( GRAPHIC_CAMERA * camera ) { Camera = camera; };
    inline const GRAPHIC_CAMERA & GetCamera() const { return *Camera; };
    inline void SetRenderCallback( CORE_HELPER_CALLBACK * renderCallback ) { RenderCallback = renderCallback; }

private :
    
    GRAPHIC_CAMERA
        * Camera;
    CORE_HELPER_CALLBACK
        *RenderCallback;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDERER__) */
