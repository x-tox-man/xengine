//
//  RESOURCE_IMAGE_PNG_LOADER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE.h"
#include "GRAPHIC_TEXTURE_INFO.h"
#include "CORE_MEMORY.h"
#include "RESOURCE_IMAGE.h"

#include <png.h>

void * xs_user_error_ptr;

void xs_png_error_callback( png_struct * png_struct, const char *png_error ) {
    
}

void xs_user_warning_fn( png_struct * png_struct, const char *png_warning ) {
    
}

int read_chunk_callback(png_struct * ptr, png_unknown_chunkp chunk) {
    /* The unknown chunk structure contains your
     chunk data, along with similar data for any other
     unknown chunks: */
    //png_byte name[5];
    //png_byte *data;
    //png_size_t size;
    /* Note that libpng has already taken care of
     the CRC handling */
    /* put your code here. Search for your chunk in the
     unknown chunk structure, process it, and return one
     of the following: */
    //return (-n); /* chunk had an error */
    return (0); /* did not recognize */
    //return (n); /* success */
}

RESOURCE_IMAGE_PNG_LOADER::RESOURCE_IMAGE_PNG_LOADER() :
    RESOURCE_LOADER() {
    
};

RESOURCE_IMAGE_PNG_LOADER::~RESOURCE_IMAGE_PNG_LOADER() {

}

RESOURCE_IMAGE * RESOURCE_IMAGE_PNG_LOADER::Load( const CORE_FILESYSTEM_PATH & path, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    bool is_png;
    
    CORE_FILESYSTEM_FILE file (path);
    
    if ( !file.OpenOutput() ) {
        
        return NULL;
    }
    
    unsigned char * header = (unsigned char *) CORE_MEMORY_ALLOCATOR::Allocate(8);
    
    file.OutputBytes(header, 8);
    file.Rewind();
    
    is_png = !png_sig_cmp( header, 0, 8 );
    
    if (!is_png) {
        
        return NULL;
    }
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, xs_user_error_ptr, xs_png_error_callback, xs_user_warning_fn);
    
    if (!png_ptr) {

        return NULL;
    }
    
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    if (!info_ptr) {
        
        png_destroy_read_struct( &png_ptr, (png_infopp)NULL, (png_infopp) NULL);
        
        file.Close();
        
        CORE_MEMORY_ALLOCATOR_Free( header );
        
        return NULL;
    }
    
    png_infop end_info = png_create_info_struct(png_ptr);
    
    if(!end_info) {
        
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        
        file.Close();
        
        CORE_MEMORY_ALLOCATOR_Free( header );
        
        return NULL;
    }
    
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr,
                                &end_info);
        file.Close();
        
        CORE_MEMORY_ALLOCATOR_Free( header );
        
        return NULL;
    }
    
    png_init_io(png_ptr, file.GetFilePointer() );

    png_data_freer( png_ptr, info_ptr, PNG_DESTROY_WILL_FREE_DATA, PNG_FREE_ALL );
    
    png_read_png(png_ptr, info_ptr, 0, NULL);
    
    int height = png_get_image_height(png_ptr, info_ptr);
    int width = png_get_image_width(png_ptr, info_ptr);
    
    int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    
    int color_type = png_get_color_type(png_ptr, info_ptr);
    
    png_bytep * row_pointers = png_get_rows(png_ptr, info_ptr);
    
    void * imageData = NULL;
    
    RESOURCE_IMAGE * image_resource = new RESOURCE_IMAGE();
    
    image_resource->GetImageInfo().ColorChannelWidth = bit_depth;
    
    image_resource->GetImageInfo().Width = width;
    image_resource->GetImageInfo().Height = height;
    
    switch (color_type) {
        case PNG_COLOR_TYPE_RGB_ALPHA :{
            
            image_resource->GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
            
            int pixel_size = GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType( image_resource->GetImageInfo().ImageType, bit_depth) / 8;
            
            int offset = width * pixel_size;
            
            imageData = CORE_MEMORY_ALLOCATOR::Allocate( height * width * pixel_size );
            
            
            for ( int i = 0; i < height; i++ ) {
                
                memcpy( (void *) ((char*)imageData + (height - i - 1) * offset), row_pointers[i], offset);
            }
            
            break;
        }
            
        case PNG_COLOR_TYPE_RGB : {
            
            image_resource->GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_RGB;
            
            int pixel_size = GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType( image_resource->GetImageInfo().ImageType, bit_depth) / 8;
            
            int offset = width * pixel_size;
            
            imageData = CORE_MEMORY_ALLOCATOR::Allocate( height * width * pixel_size );
            
            for ( int i = 0; i < height; i++ ) {
                
                memcpy( (void *) ((char*)imageData + (height - i - 1) * offset), row_pointers[i], offset);
            }
            
            break;
        }
            
        case PNG_COLOR_TYPE_GRAY : {
            
            image_resource->GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_GRAY;
            
            int pixel_size = GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType( image_resource->GetImageInfo().ImageType, bit_depth) / 8;
            
            int offset = width * pixel_size;
            
            imageData = CORE_MEMORY_ALLOCATOR::Allocate( height * width * pixel_size );
            
            for ( int i = 0; i < height; i++ ) {
                
                memcpy( (void *) ((char*)imageData + (height - i - 1) * offset), row_pointers[i], offset);
            }
            
            break;
        }
            
        case PNG_COLOR_TYPE_GRAY_ALPHA : {
            
            CORE_RUNTIME_Abort();
            
            break;
        }
            
        default: {
            
            CORE_RUNTIME_Abort();
            break;
        }
    }
    
    CORE_MEMORY_ALLOCATOR_Free( header );
    
    image_resource->SetImageRawData( imageData );
    image_resource->SetIdentifier( identifier );
    
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    png_destroy_info_struct(png_ptr, &info_ptr);
    
    file.Close();
    
    return image_resource;
}

RESOURCE_IMAGE * RESOURCE_IMAGE_PNG_LOADER::Load( CORE_DATA_STREAM & stream, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) {
    
    abort();
    return new RESOURCE_IMAGE();
}

void RESOURCE_IMAGE_PNG_LOADER::ReloadResource( RESOURCE_IMAGE * resource_to_reload ) {
    
    abort();
}
