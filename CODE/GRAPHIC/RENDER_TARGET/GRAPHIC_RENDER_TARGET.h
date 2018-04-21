//
//  GRAPHIC_RENDER_TARGET.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_RENDER_TARGET__
#define __GAME_ENGINE_REBORN__GRAPHIC_RENDER_TARGET__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"

XS_CLASS_BEGIN( GRAPHIC_RENDER_TARGET )

    GRAPHIC_RENDER_TARGET();
    ~GRAPHIC_RENDER_TARGET();

    bool Initialize( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachment );
    bool InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    void Finalize();
    void Apply();
    void Discard();

    inline GRAPHIC_TEXTURE * GetTargetTexture() { return TargetTexture; }
    inline bool UsesDepth() { return ItUsesDepth; }

    inline void SetTargetTexture( GRAPHIC_TEXTURE * texture ) { TargetTexture= texture; }
    inline void SetItUsesDepth( bool uses ) { ItUsesDepth = uses; }

#if OPENGLES2
    #include "GRAPHIC_RENDER_TARGET_OES2.hpp"
#elif OPENGL2PLUS
    #include "GRAPHIC_RENDER_TARGET_OPENGL.hpp"
#elif X_VK
    #include "GRAPHIC_RENDER_TARGET_VK.hpp"
#else
    #error "Must implement graphic system"
#endif

private:

    GRAPHIC_TEXTURE
        * TargetTexture;
    bool
        ItUsesDepth;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDER_TARGET__) */
