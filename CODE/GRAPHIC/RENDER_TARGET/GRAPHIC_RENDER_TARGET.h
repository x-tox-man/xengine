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
#include "GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE.h"
#include "GRAPHIC_RENDERER.h"

#define MAX_FRAME_BUFFERS   8

XS_CLASS_BEGIN( GRAPHIC_RENDER_TARGET )

    GRAPHIC_RENDER_TARGET();
    ~GRAPHIC_RENDER_TARGET();

    bool Initialize( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool uses_stencil, bool generates_separate_depth_texture, int attachments, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode );
    bool InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    void Finalize();
    void Apply( GRAPHIC_RENDERER & renderer );
    void Discard();

    void Clear();
    void ClearDepth();
    void ClearStencil();

    // -- METAL API
    void EnableTextureBlending();
    // --

    void BindForWriting();
    void BindForReading();
    void SetReadBuffer( int type );
    void SetWriteBuffer( int type );

    void AddAttachment( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type );

    inline GRAPHIC_TEXTURE * GetTargetTexture( int attachment) { return TargetTextures[ attachment ]; }
    GRAPHIC_TEXTURE * GetDepthTexture() { return DepthTexture; }
    inline bool UsesDepth() { return ItUsesDepth; }

    inline void SetTargetTexture( GRAPHIC_TEXTURE * texture, int attachment ) { TargetTextures[ attachment ] = texture; }
    inline void SetItUsesDepth( bool uses ) { ItUsesDepth = uses; }

    void CopyDepthFrom( GRAPHIC_RENDER_TARGET & other );

#if OPENGLES2
    #include "GRAPHIC_RENDER_TARGET_OES2.hpp"
#elif OPENGL2PLUS
    #include "GRAPHIC_RENDER_TARGET_OPENGL.hpp"
#elif X_VK
    #include "GRAPHIC_RENDER_TARGET_VK.hpp"
#elif X_METAL
    #include "GRAPHIC_RENDER_TARGET_METAL.hpp"
#else
    #error "Must implement graphic system"
#endif

private:

    bool
        ItUsesDepth,
        ItUsesStencil;
    int
        Attachments;
    GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE
        Mode;
    GRAPHIC_TEXTURE
        * TargetTextures[ MAX_FRAME_BUFFERS ],
        * DepthTexture,
        * StencilTexture;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDER_TARGET__) */
