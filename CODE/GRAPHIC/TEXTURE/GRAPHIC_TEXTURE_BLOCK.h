//
//  GRAPHIC_TEXTURE_BLOCK.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_BLOCK__
#define __GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_BLOCK__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_TEXTURE.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_TEXTURE_BLOCK )

    GRAPHIC_TEXTURE_BLOCK();
    ~GRAPHIC_TEXTURE_BLOCK();

    XS_DEFINE_SERIALIZABLE

    void Initialize();

    void Apply( int texture_index, int shader_texture_attribute_index );
    void ApplyDepth( int texture_index, int shader_texture_attribute_index );

    void Discard();

    const CORE_MATH_VECTOR & GetOffset() const { return Offset; }
    const CORE_MATH_VECTOR & GetSize() const { return Size; }
    void SetOffset( const CORE_MATH_VECTOR & offset ) { Offset = offset; }
    void SetSize( const CORE_MATH_VECTOR & size ) { Size = size; }

    void SetTexture( GRAPHIC_TEXTURE * texture ) { Texture = texture; }
    GRAPHIC_TEXTURE * GetTexture() { return Texture; }
    const GRAPHIC_TEXTURE * GetTexture() const { return Texture; }

private:

    GRAPHIC_TEXTURE
        *Texture;
    CORE_MATH_VECTOR
        Offset,
        Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_TEXTURE_BLOCK__) */
