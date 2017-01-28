//
//  GRAPHIC_TEXTURE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE__
#define __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN( GRAPHIC_TEXTURE )

GRAPHIC_TEXTURE();

#if OPENGL2PLUS || OPENGLES2
    GLuint & GetTextureHandle() { return TextureHandle; }
    void SetTextureHandle( GLuint handle ) { TextureHandle = handle; }
#endif

virtual void Initialize( void * texture_data );
void Initialize();

void Apply( int texture_index, int shader_texture_attribute_index );
void Discard();

GRAPHIC_TEXTURE_INFO & GetTextureInfo() { return TextureInfo; }
void SetTextureInfo( const GRAPHIC_TEXTURE_INFO & texture_info ) { TextureInfo = texture_info; }

private :

GRAPHIC_TEXTURE_INFO
    TextureInfo;

#if OPENGL2PLUS || OPENGLES2
    GLuint
        TextureHandle;
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_TEXTURE__) */
