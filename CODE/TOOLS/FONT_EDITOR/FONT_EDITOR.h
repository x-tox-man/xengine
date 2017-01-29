//
//  FONT_EDITOR.hp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef FONT_EDITOR_h
#define FONT_EDITOR_h

#include <ft2build.h>
#include FT_FREETYPE_H
#include <math.h>

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FILESYSTEM.h"
#include "FONT_DESCRIPTOR.h"
#include "GRAPHIC_GLYPH.h"
#include "GRAPHIC_FONT.h"

XS_CLASS_BEGIN( FONT_EDITOR )

FONT_EDITOR();
~FONT_EDITOR();

void CompileFont( int image_width,
                 int image_height,
                 const char * font_file,
                 const FONT_DESCRIPTOR & descriptor,
                 const CORE_FILESYSTEM_PATH & image_target_path,
                 const CORE_FILESYSTEM_PATH & font_target_path );

private :

void FillBitmapAndGlyph( const FONT_DESCRIPTOR & descriptor,
                        GRAPHIC_GLYPH & glyph,
                        FT_Bitmap * bitmap,
                        int width,
                        int height,
                        int x,
                        int y,
                        int advance_x,
                        int advance_y);

void SaveFont( const FONT_DESCRIPTOR & descriptor,
              std::vector< GRAPHIC_GLYPH > & glyph_table,
              const CORE_FILESYSTEM_PATH & image_target_path,
              const CORE_FILESYSTEM_PATH & font_target_path );


float * ImageBuffer;
int Width,
    Height;


XS_CLASS_END

#endif /* FONT_EDITOR_hpp */
