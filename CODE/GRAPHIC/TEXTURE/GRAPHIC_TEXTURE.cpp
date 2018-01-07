//
//  GRAPHIC_TEXTURE.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_SYSTEM.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "CORE_DATA_JSON.h"


XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_TEXTURE )

XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_TEXTURE::GRAPHIC_TEXTURE() :
    GR_T_ANCESTOR_TYPE(),
    TextureInfo()
#if OPENGL2PLUS || OPENGLES2
    ,TextureHandle( 0 )
    ,DepthTextureHandle( 0 )
#elif X_VK
    ,Sampler(),
    Image(),
    ImageLayout(),
    Memory(),
    Imageview()
#endif
{

}

GRAPHIC_TEXTURE::~GRAPHIC_TEXTURE() {

    GRAPHIC_SYSTEM::ReleaseTexture( this );
}

void GRAPHIC_TEXTURE::Initialize( void * texture_data, bool generate_mip_map ) {
    
    GRAPHIC_SYSTEM::CreateTexture( this, texture_data, generate_mip_map );
}

void GRAPHIC_TEXTURE::Initialize( bool it_creates_depth, GRAPHIC_TEXTURE_IMAGE_TYPE depth_type ) {
    
    GRAPHIC_SYSTEM::CreateTexture( this );
    
    if ( it_creates_depth ) {
        
        GRAPHIC_SYSTEM::CreateDepthTexture( this , depth_type);
    }
}

void GRAPHIC_TEXTURE::InitializeDepth( GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    GRAPHIC_SYSTEM::CreateDepthTexture( this, type );
}

void GRAPHIC_TEXTURE::Finalize() {
    
    GRAPHIC_SYSTEM::ReleaseTexture( this );
}

void GRAPHIC_TEXTURE::Apply( int texture_index, int shader_texture_attribute_index ) {
    
    GRAPHIC_SYSTEM::ApplyTexture( this, texture_index, shader_texture_attribute_index );
}

void GRAPHIC_TEXTURE::ApplyDepth( int texture_index, int shader_texture_attribute_index ) {
    
    GRAPHIC_SYSTEM::ApplyDepthTexture( this, texture_index, shader_texture_attribute_index );
}

void GRAPHIC_TEXTURE::Discard() {
    
    GRAPHIC_SYSTEM::DiscardTexture( this );
}

void GRAPHIC_TEXTURE::SaveDepthTo( const CORE_FILESYSTEM_PATH & path ) {
    
    RESOURCE_IMAGE_PNG_WRITER
        writer;
    RESOURCE_IMAGE
        img;
    
    int size = GetTextureInfo().Width * GetTextureInfo().Height;

    #if OPENGL2PLUS
        float * pixels = new GLfloat [size];
    
        GFX_CHECK( glReadPixels(0, 0, GetTextureInfo().Width, GetTextureInfo().Height, GL_DEPTH_COMPONENT, GL_FLOAT, pixels); )
    
        img.SetImageRawData(pixels);
        img.GetImageInfo().Height = GetTextureInfo().Height;
        img.GetImageInfo().Width = GetTextureInfo().Width;
        img.GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16;
        img.GetImageInfo().PixelSize = 4;
    
        writer.Write(path, &img);
    
        delete[] pixels;
    #else
        abort();//implement
    #endif
    
    img.SetImageRawData( NULL );
}

void GRAPHIC_TEXTURE::SaveTo( const CORE_FILESYSTEM_PATH & path ) {
    
    RESOURCE_IMAGE_PNG_WRITER
        writer;
    RESOURCE_IMAGE
        img;
    
    int size = GetTextureInfo().Width * GetTextureInfo().Height * 4;

    #if OPENGL2PLUS
        float * pixels = new GLfloat [size];
    
        GFX_CHECK( glReadPixels(0, 0, GetTextureInfo().Width, GetTextureInfo().Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels); )
    
        img.SetImageRawData(pixels);
    
        img.GetImageInfo().Height = GetTextureInfo().Height;
        img.GetImageInfo().Width = GetTextureInfo().Width;
        img.GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE::GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
        img.GetImageInfo().PixelSize = 0;
        img.GetImageInfo().ColorChannelWidth = 0;
    
        writer.Write( path, &img );
    
        delete[] pixels;
    #else
        abort();//implement
    #endif
    
    img.SetImageRawData( NULL );
}
