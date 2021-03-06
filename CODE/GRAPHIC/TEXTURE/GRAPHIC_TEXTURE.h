//
//  GRAPHIC_TEXTURE.h
//  GAME-ENGINE
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
#include "CORE_FILESYSTEM_PATH.h"
#include "RESOURCE.h"
#include "CORE_DATA_BUFFER.h"

class GRAPHIC_TEXTURE;
class GRAPHIC_TEXTURE_LOADER;

typedef RESOURCE<GRAPHIC_TEXTURE, GRAPHIC_TEXTURE_LOADER> GR_T_ANCESTOR_TYPE;

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_TEXTURE, GR_T_ANCESTOR_TYPE )

    GRAPHIC_TEXTURE();
    virtual ~GRAPHIC_TEXTURE();

    XS_DEFINE_SERIALIZABLE

    #if OPENGL2PLUS || OPENGLES2
        GLuint & GetTextureHandle() { return TextureHandle; }
        GLuint & GetDepthTextureHandle() { return DepthTextureHandle; }
        void SetTextureHandle( GLuint handle ) { TextureHandle = handle; }
        void SetDepthTextureHandle( GLuint handle ) { DepthTextureHandle = handle; }
    #elif X_METAL
        inline void* GetTextureHandle() { return TextureHandle; }
        inline void* GetDepthTextureHandle() { return DepthTextureHandle; }
        inline void SetTextureHandle(void* texture ) { TextureHandle = texture; }
        inline void SetDepthTextureHandle(void* texture ) { DepthTextureHandle = texture; }
    #elif X_VK
        inline VkSampler & GetVkSampler() { return Sampler; }
        inline VkImage & GetVkImage() { return Image; }
        inline VkImageLayout & GetVkImageLayout() { return ImageLayout; }
        inline VkDeviceMemory & GetVkMemory() { return Memory; }
        inline VkImageView & GetVkImageview() { return Imageview; }

        inline void SetVkSampler( VkSampler & sampler ) { Sampler = sampler; }
        inline void SetVkImage( VkImage & image ) { Image = image; }
        inline void SetVkImageLayout( VkImageLayout layout ) { ImageLayout = layout; }
        inline void SetVkDeviceMemory( VkDeviceMemory & memory ) { Memory = memory; }
        inline void SetVkImageView( VkImageView & view ) { Imageview = view; }
    #endif

    virtual void Initialize( CORE_DATA_BUFFER & texture_data, bool generate_mip_map );
    void Initialize( bool it_creates_depth = false, GRAPHIC_TEXTURE_IMAGE_TYPE depth_type = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );
    void InitializeDepth( GRAPHIC_TEXTURE_IMAGE_TYPE type = GRAPHIC_TEXTURE_IMAGE_TYPE_DEPTH16 );

    void Finalize();

    void Apply( int texture_index, int shader_texture_attribute_index );
    void ApplyDepth( int texture_index, int shader_texture_attribute_index );
    void Discard();

    void SaveTo( const CORE_FILESYSTEM_PATH & path );
    void SaveDepthTo( const CORE_FILESYSTEM_PATH & path );

    inline GRAPHIC_TEXTURE_INFO & GetTextureInfo() { return TextureInfo; }
    inline void SetTextureInfo( const GRAPHIC_TEXTURE_INFO & texture_info ) { TextureInfo = texture_info; }
    inline const GRAPHIC_TEXTURE_INFO & GetTextureInfo() const  { return TextureInfo; }

private :

    GRAPHIC_TEXTURE_INFO
        TextureInfo;

    #if OPENGL2PLUS
        GLuint
            TextureHandle,
            DepthTextureHandle;
    #elif X_METAL
        void
            * TextureHandle,
            * DepthTextureHandle;
    #elif X_VK
        VkSampler
            Sampler;
        VkImage
            Image;
        VkImageLayout
            ImageLayout;
        VkDeviceMemory
            Memory;
        VkImageView
            Imageview;
    #endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_TEXTURE__) */
