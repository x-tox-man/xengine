//
//  RESOURCE_IMAGE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_IMAGE.h"
#include "CORE_MEMORY.h"

RESOURCE_IMAGE::RESOURCE_IMAGE() :
    RESOURCE< RESOURCE_IMAGE, RESOURCE_IMAGE_PNG_LOADER>(),
    TextureInfo(),
    Path( NULL ),
    RawData( NULL ) {
    
}

RESOURCE_IMAGE::~RESOURCE_IMAGE() {
    
    if ( RawData ) {
        
        CORE_MEMORY_ALLOCATOR_Free( RawData );
    }
    
    RawData = NULL;
}

GRAPHIC_TEXTURE * RESOURCE_IMAGE::CreateTextureObject( bool generate_mip_map ) {
    
    GRAPHIC_TEXTURE * texture =  new GRAPHIC_TEXTURE();
    
    texture->GetTextureInfo().ColorChannelWidth = TextureInfo.ColorChannelWidth;
    texture->GetTextureInfo().ImageType = TextureInfo.ImageType;
    texture->GetTextureInfo().Width = TextureInfo.Width;
    texture->GetTextureInfo().Height = TextureInfo.Height;
    
    texture->Initialize( RawData, generate_mip_map );
    
    return texture;
}

void RESOURCE_IMAGE::Blit( RESOURCE_IMAGE * image, int x_offset, int y_offset, int rows, int columns, int mask ) {
    
    //int pixel_size = GRAPHIC_TEXTURE_INFO_GetPixelBitSizeByColorType(GetImageInfo().ImageType, GetImageInfo().ColorChannelWidth ) / 8;
    
    float * ptr_dest = (float *) RawData;
    const float * ptr_src = (const float *) image->GetImageRawData();
    
    if ( image->GetImageInfo().PixelSize != GetImageInfo().PixelSize ) {
        
        CORE_RUNTIME_Abort();
    }
    
    ptr_dest += y_offset * GetImageInfo().Width + x_offset;
    
    for (int i = 0; i < columns; i++ ) {
        
        memcpy( (void*) ptr_dest, (void*)ptr_src, rows * sizeof(float) );
        
        ptr_dest += GetImageInfo().Width;
        
        ptr_src += rows;
    }
}
