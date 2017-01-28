//
//  GRAPHIC_RENDER_TARGET.h
//  GAME-ENGINE-REBORN
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

XS_CLASS_BEGIN( GRAPHIC_RENDER_TARGET )

GRAPHIC_RENDER_TARGET();

bool Initialize( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type, bool uses_depth, bool generates_separate_depth_texture, int attachment );
bool InitializeDepthTexture( int width, int height, GRAPHIC_TEXTURE_IMAGE_TYPE type = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
void Finalize();
void Apply();
void Discard();

GRAPHIC_TEXTURE
    * TargetTexture;
bool
    ItUsesDepth;

#if OPENGL2PLUS
    #include "GRAPHIC_RENDER_TARGET_OPENGL.hpp"
#elif OPENGLES2
    #include "GRAPHIC_RENDER_TARGET_OES2.hpp"
#else
    #error "Must implement graphic system"
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_RENDER_TARGET__) */
