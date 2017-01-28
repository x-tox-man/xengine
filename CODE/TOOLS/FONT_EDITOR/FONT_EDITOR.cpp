//
//  FONT_EDITOR.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "FONT_EDITOR.h"
#include "CORE_MEMORY.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "CORE_DATA_STREAM.h"

FONT_EDITOR::FONT_EDITOR() {
    
}

FONT_EDITOR::~FONT_EDITOR() {
    
}

void FONT_EDITOR::CompileFont( int image_width,
                              int image_height,
                              const char * font_file,
                              const FONT_DESCRIPTOR & descriptor,
                              const CORE_FILESYSTEM_PATH & target_path,
                              const CORE_FILESYSTEM_PATH & font_target_path ) {
    
    FT_Library    library;
    FT_Face       face;
    
    FT_GlyphSlot  slot;
    FT_Matrix     matrix;                 /* transformation matrix */
    FT_Error      error;
    
    double        angle;
    int           target_height;
    int           n, num_chars;
    
    Width = image_width;
    Height = image_height;
    
    ImageBuffer = ( float * ) CORE_MEMORY_ALLOCATOR_Allocate( Width * Height * sizeof( float) );
    
    num_chars     = descriptor.CharacterSet.size();
    
    angle         = ( 0.0 / 360 ) * 3.14159 * 2;      /* use 25 degrees     */
    
    target_height = Height;
    
    error = FT_Init_FreeType( &library );              /* initialize library */
    /* error handling omitted */
    
    error = FT_New_Face( library, font_file, 0, &face );/* create face object */
    /* error handling omitted */
    
    /* use 50pt at 100dpi */
//    error = FT_Set_Char_Size( face, descriptor.Size * 64, 0, 100, 0 ); /* set character size */
    error = FT_Set_Pixel_Sizes(
                               face,   /* handle to face object */
                               0,      /* pixel_width           */
                               descriptor.Size );   /* pixel_height          */
    /* error handling omitted */
    
    slot = face->glyph;
    
    /* set up matrix */
    matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
    matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
    matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
    matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
    
    std::vector< GRAPHIC_GLYPH > glyph_table;
    
    glyph_table.resize( descriptor.CharacterSet.size() );
    
    int offset_x=0;
    int offset_y=0;
    
    for ( n = 0; n < num_chars; n++ ) {
        
        /* set transformation */
        
        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Char( face, descriptor.CharacterSet[ n ], FT_LOAD_RENDER );
        
        if ( error ) {
            
            continue;                 /* ignore errors */
        }
        
        /* now, draw to our target surface (convert position) */
        
        glyph_table[ n ].Value = descriptor.CharacterSet[ n ];
        
        FillBitmapAndGlyph( descriptor,
                           glyph_table[ n ],
                           &slot->bitmap,
                           slot->bitmap.width,
                           slot->bitmap.rows,
                           offset_x,
                           offset_y,
                           slot->bitmap_left,
                           slot->bitmap_top );
        
        offset_x += descriptor.Size * 2;
        
        
        if ( offset_x + descriptor.Size * 2 >= Width ) {
            
            offset_x = 0;
            offset_y += descriptor.Size* 2;
        }
    }
    
    SaveFont( descriptor,
             glyph_table,
             target_path,
             font_target_path );
    
    FT_Done_Face( face );
    FT_Done_FreeType( library );
    
    CORE_MEMORY_ALLOCATOR_Free( ImageBuffer );
}

void FONT_EDITOR::FillBitmapAndGlyph( const FONT_DESCRIPTOR & descriptor,
                                     GRAPHIC_GLYPH & glyph,
                                     FT_Bitmap * bitmap,
                                     int width,
                                     int height,
                                     int x_pos,
                                     int y_pos,
                                     int advance_x,
                                     int advance_y) {
    
    FT_Int  i, j, p, q;
    FT_Int  x_max = x_pos + width;
    FT_Int  y_max = y_pos + height;
    
    glyph.Advance[0] = (float) width;
    glyph.Advance[1] = (float) height;
    
    glyph.Advance[2] = (float) advance_x;
    glyph.Advance[3] = (float) advance_y;
    
    glyph.PaddingBounding[0] = (float) x_pos / Width;
    glyph.PaddingBounding[1] = (float) y_pos / Height;
    
    glyph.PaddingBounding[2] = (float) width / Width;
    glyph.PaddingBounding[3] = (float) height / Height;
    
    for ( i = x_pos, p = 0; i < x_max; i++, p++ )
    {
        for ( j = y_pos, q = 0; j < y_max; j++, q++ )
        {
            if ( i < 0 || j < 0 || i >= Width || j >= Height ) {
                
                continue;
            }
            
            char array[4];
                
            array[0] = 255 * descriptor.color[0] * bitmap->buffer[q * bitmap->width + p];
            array[1] = 255 * descriptor.color[1] * bitmap->buffer[q * bitmap->width + p];
            array[2] = 255 * descriptor.color[2] * bitmap->buffer[q * bitmap->width + p];
            array[3] = 255 * descriptor.color[3] * bitmap->buffer[q * bitmap->width + p];
            
            int inverted_index = (Height - j - 1 ) * Width + ( i);
            
            ImageBuffer[ inverted_index ] = *((float*) (void*) array);
        }
    }
}

void FONT_EDITOR::SaveFont( const FONT_DESCRIPTOR & descriptor,
                           std::vector< GRAPHIC_GLYPH > & glyph_table,
                           const CORE_FILESYSTEM_PATH & image_target_path,
                           const CORE_FILESYSTEM_PATH & font_target_path ) {
    
    GRAPHIC_FONT graphic_font;
    
    int font_name_size = strlen("Arial Black");
    
    graphic_font.Name = (char *) CORE_MEMORY_ALLOCATOR::Allocate( font_name_size );
    strcpy( graphic_font.Name, "Arial Black" );
    graphic_font.Size = descriptor.Size;
    
    for ( int i = 1; i < 128 ; i++ ) {
        
        graphic_font.GlyphTable[ i ];
    }
    
    GLYPH_TABLE::iterator it = graphic_font.GlyphTable.begin();
    
    while ( it != graphic_font.GlyphTable.end() ) {
        
        GRAPHIC_GLYPH * gl = NULL;
        
        for ( int i = 0; i < descriptor.CharacterSet.size() ; i++ ) {
            
            if ( glyph_table[i].Value == (char) it->first ) {
                
                gl = &glyph_table[i];
            }
            
        }
        
        if ( gl == NULL ) {
            
            gl = &glyph_table[ 0 ];
        }
        
        it->second = *gl;
        
        it++;
    }
    
    CORE_DATA_STREAM
        stream;
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< GRAPHIC_FONT >::Serialize<std::true_type>( graphic_font, stream );
    
    stream.Close();
    stream.ResetOffset();
    
    CORE_FILESYSTEM_FILE file( font_target_path );
    
    file.OpenInput();
    file.InputBytes( stream.GetMemoryBuffer(), stream.GetSize() );
    file.Close();
    
    RESOURCE_IMAGE_PNG_WRITER writer;
    RESOURCE_IMAGE * image;
    
    image = new RESOURCE_IMAGE;
    image->SetImageRawData( ( void* ) ImageBuffer );
    image->GetImageInfo().Height = Height;
    image->GetImageInfo().Width = Width;
    image->GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
    image->GetImageInfo().PixelSize = 0;
    image->GetImageInfo().ColorChannelWidth = 8;
    
    writer.Write(image_target_path.GetPath(), image);
}

