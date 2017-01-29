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

typedef std::map< char, GRAPHIC_GLYPH > GLYPH_TABLE;

XS_CLASS_BEGIN( GRAPHIC_FONT )

XS_DEFINE_SERIALIZABLE

GRAPHIC_FONT();
~GRAPHIC_FONT();

void Initialize();
void Load( const CORE_FILESYSTEM_PATH & path, const CORE_FILESYSTEM_PATH & image_path );

char
    * Name;
int
    Size;
GLYPH_TABLE
    GlyphTable;
GRAPHIC_TEXTURE
    * Texture;


XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_FONT__) */
