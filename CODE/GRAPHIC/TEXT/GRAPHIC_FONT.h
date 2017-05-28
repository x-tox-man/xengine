//
//  GRAPHIC_FONT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_FONT__
#define __GAME_ENGINE_REBORN__GRAPHIC_FONT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_GLYPH.h"
#include "CORE_FILESYSTEM.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"

typedef std::map< char, GRAPHIC_GLYPH > GLYPH_TABLE;

XS_CLASS_BEGIN( GRAPHIC_FONT )

    XS_DEFINE_SERIALIZABLE

    GRAPHIC_FONT();
    ~GRAPHIC_FONT();

    inline int GetSize() const { return Size; }
    inline void SetSize(int size) { Size = size; }
    inline GLYPH_TABLE & GetGlyphTable() { return GlyphTable; }
    inline void SetTexture( GRAPHIC_TEXTURE * texture ) { Texture = texture; }
    inline GRAPHIC_TEXTURE * GetTexture() { return Texture; }
    inline void SetName( const char * name ) { strcpy(Name, name ); }

    void Initialize();
    void Load( const CORE_FILESYSTEM_PATH & path, const CORE_FILESYSTEM_PATH & image_path );

private :

    int
        Size;
    GLYPH_TABLE
        GlyphTable;
    char
        Name[256];
    GRAPHIC_TEXTURE
        * Texture;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_FONT__) */
