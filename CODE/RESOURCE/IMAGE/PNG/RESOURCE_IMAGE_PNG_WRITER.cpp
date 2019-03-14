//
//  RESOURCE_IMAGE_PNG_WRITER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 14/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_TEXTURE_INFO.h"

#include <png.h>
#include <zlib.h>

void * xs_user_write_error_ptr;

//static int test = 0; // For debug purposes

void xs_png_write_error_callback( png_struct * png_struct, const char *png_error ) {
    
}

void xs_user_write_warning_fn( png_struct * png_struct, const char *png_warning ) {
    
}

void xs_write_row_callback( png_struct * png_ptr, png_uint_32 row, int pass ) {
    
    //test++;
    //printf( "%d\n", row );
    /* put your code here */
}

RESOURCE_IMAGE_PNG_WRITER::RESOURCE_IMAGE_PNG_WRITER() {
    
}

RESOURCE_IMAGE_PNG_WRITER::~RESOURCE_IMAGE_PNG_WRITER() {

}

bool RESOURCE_IMAGE_PNG_WRITER::Write( const CORE_FILESYSTEM_PATH & path, RESOURCE_IMAGE * image ) {
    
    FILE
        * fp = fopen(path.GetPath(), "wb");
    
    unsigned char
        header[8];
    int
        pixel_size = 4;
    
    if ( !fp ) {
        
        return false;
    }
    
    png_structp png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, ( png_voidp ) xs_user_write_error_ptr, xs_png_write_error_callback, xs_user_write_warning_fn );
    
    if (!png_ptr) {
        
        return false;
    }
    
    png_infop info_ptr = png_create_info_struct( png_ptr );
    
    if (!info_ptr) {
        
        png_destroy_write_struct( &png_ptr, ( png_infopp ) NULL );
        
        return false;
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return false;
    }
    
    png_set_write_status_fn( png_ptr, xs_write_row_callback );
    
    png_init_io(png_ptr, fp);
    
    png_set_filter( png_ptr, 0, PNG_FILTER_NONE );
    
    /* set the zlib compression level */
    //png_set_compression_level( png_ptr, Z_BEST_COMPRESSION );
    /* set other zlib parameters */
    //png_set_compression_mem_level( png_ptr, 8 );
    //png_set_compression_strategy( png_ptr, Z_DEFAULT_STRATEGY );
    //png_set_compression_window_bits( png_ptr, 15 );
    //png_set_compression_method( png_ptr, 8 );
    //png_set_compression_buffer_size( png_ptr, 8192 );
    
    switch (image->GetImageInfo().ImageType) {
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 :
            
            png_set_IHDR(png_ptr, info_ptr,
                         image->GetImageInfo().Width,
                         image->GetImageInfo().Height,
                         16,
                         PNG_COLOR_TYPE_GRAY_ALPHA,
                         PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_DEFAULT,
                         PNG_FILTER_TYPE_DEFAULT);
            pixel_size = 2;
            break;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_RGB :
            
            png_set_IHDR(png_ptr, info_ptr,
                         image->GetImageInfo().Width,
                         image->GetImageInfo().Height,
                         8,
                         PNG_COLOR_TYPE_RGB,
                         PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_DEFAULT,
                         PNG_FILTER_TYPE_DEFAULT);
            pixel_size = 3;
            break;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY :
            
            png_set_IHDR(png_ptr, info_ptr,
                         image->GetImageInfo().Width,
                         image->GetImageInfo().Height,
                         8,
                         PNG_COLOR_TYPE_GRAY,
                         PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_DEFAULT,
                         PNG_FILTER_TYPE_DEFAULT);
            
            pixel_size = 1;
            
            break;
            
        case GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA :
            
            png_set_IHDR(png_ptr, info_ptr,
                         image->GetImageInfo().Width,
                         image->GetImageInfo().Height,
                         8,
                         PNG_COLOR_TYPE_RGB_ALPHA,
                         PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_BASE,
                         PNG_FILTER_TYPE_BASE);
            
            pixel_size = 4;
            break;
            
        default:
            CORE_RUNTIME_Abort();
            
    }
    
    png_write_info( png_ptr, info_ptr );
    
    if (setjmp(png_jmpbuf(png_ptr))) {
        
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return false;
    }
    
    int line_size = image->GetImageInfo().Width * pixel_size / 4;
    
    png_bytep * ptr = ( png_bytep * ) CORE_MEMORY_ALLOCATOR::Allocate ( sizeof( png_bytep ) * image->GetImageInfo().Height );
    
    for ( int i = 0; i < image->GetImageInfo().Height; i++ ) {
        
        ptr[i] = (png_bytep) ((int*)image->GetImageRawData() + (image->GetImageInfo().Height - i - 1) * line_size);
    }
    

    png_set_rows( png_ptr, info_ptr, ptr );
    
    png_write_png( png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    
    png_write_end( png_ptr, NULL );
    
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    
    fclose(fp);

	CORE_MEMORY_ALLOCATOR_Free( ptr );
    
    return true;
}
