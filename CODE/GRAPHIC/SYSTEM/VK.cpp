//
//  VK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/01/18.
//  Copyright (c) 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SYSTEM.h"

#if X_VK

    CORE_PARALLEL_LOCK_MUTEX
        GRAPHIC_SYSTEM::GraphicSystemLock;
    const char
        * GRAPHIC_SYSTEM::ShaderDirectoryPath="VK";
    CORE_HELPERS_COLOR
        GRAPHIC_SYSTEM::ClearColor=CORE_COLOR_Blue;
    GRAPHIC_VK_ENGINE_INFO
        GraphicVKInfo = {};
    
    VkInstance & GetGraphicVKInstance() {

        return GraphicVKInfo.VkInstance;
    }

    GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {

    }

    void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {

        GRAPHIC_VK_init_global_layer_properties( GraphicVKInfo );
        GRAPHIC_VK_init_instance_extension_names( GraphicVKInfo );
        GRAPHIC_VK_init_device_extension_names( GraphicVKInfo );
        GRAPHIC_VK_init_instance( GraphicVKInfo, app_name );
        GRAPHIC_VK_init_enumerate_device( GraphicVKInfo );
        //GRAPHIC_VK_init_queue_family_index( GraphicVKInfo );
        GRAPHIC_VK_init_device( GraphicVKInfo );
    }

    void GRAPHIC_SYSTEM::Finalize() {

        GRAPHIC_VK_destroy_depth_buffer( GraphicVKInfo );
        GRAPHIC_VK_destroy_swap_chain( GraphicVKInfo );
        GRAPHIC_VK_destroy_command_buffer( GraphicVKInfo );
        GRAPHIC_VK_destroy_command_pool( GraphicVKInfo );
        GRAPHIC_VK_destroy_device( GraphicVKInfo );
        GRAPHIC_VK_destroy_instance( GraphicVKInfo );
    }

    void GRAPHIC_SYSTEM::EnableScissor( bool enable ) {
        
        abort();
    }

    void GRAPHIC_SYSTEM::SetScissorRectangle( float x, float y, float width, float height ) {

        abort();
    }

    void GRAPHIC_SYSTEM::EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination ) {

        abort();
    }

    void GRAPHIC_SYSTEM::DisableBlend() {

        abort();
    }

    void GRAPHIC_SYSTEM::EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end ) {

        abort();
    }

    void GRAPHIC_SYSTEM::EnableBackfaceCulling() {

        abort();
    }

    void GRAPHIC_SYSTEM::DisableFaceCulling() {

        abort();
    }

    void GRAPHIC_SYSTEM::UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data ) {

        abort();
    }

    void GRAPHIC_SYSTEM::SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode ) {

        abort();
    }

    void GRAPHIC_SYSTEM::DisableDepthTest() {

        abort();
    }

    void GRAPHIC_SYSTEM::ReleaseTexture( GRAPHIC_TEXTURE * texture ) {

        vkDestroySampler( GraphicVKInfo.device, texture->GetVkSampler(), NULL );
        vkDestroyImageView( GraphicVKInfo.device, texture->GetVkImageview(), NULL );
        vkDestroyImage( GraphicVKInfo.device, texture->GetVkImage(), NULL );
        vkFreeMemory( GraphicVKInfo.device, texture->GetVkMemory(), NULL );
    }

    void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {

        abort();
    }

    void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {

        abort();
    }

    void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, void * texture_data, bool generate_mipmap ) {

        /* create image */
        //init_image( info, texObj, textureName, extraUsages, extraFeatures );
        VkFormatProperties
            format_properties;
        VkImageUsageFlags
            extra_usages = 0;
        VkResult
            res;

        vkGetPhysicalDeviceFormatProperties( GraphicVKInfo.gpus[ 0 ], VK_FORMAT_R8G8B8A8_UNORM, &format_properties );

        /* See if we can use a linear tiled image for a texture, if not, we will
        * need a staging image for the texture data */
        VkFormatFeatureFlags
            allFeatures = ( VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT | extra_usages );
        bool
            needStaging = ( ( format_properties.linearTilingFeatures & allFeatures ) != allFeatures ) ? true : false;

        if ( needStaging ) {

            assert( ( format_properties.optimalTilingFeatures & allFeatures ) == allFeatures );
        }

        VkImageCreateInfo
            image_create_info={};

        image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_create_info.pNext = NULL;
        image_create_info.imageType = VK_IMAGE_TYPE_2D;
        image_create_info.format = VK_FORMAT_R8G8B8A8_UNORM;
        image_create_info.extent.width = texture->GetTextureInfo().Width;
        image_create_info.extent.height = texture->GetTextureInfo().Height;
        image_create_info.extent.depth = 1;
        image_create_info.mipLevels = 1;
        image_create_info.arrayLayers = 1;
        image_create_info.samples = NUM_SAMPLES;
        image_create_info.tiling = VK_IMAGE_TILING_LINEAR;
        image_create_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
        image_create_info.usage = needStaging ? ( VK_IMAGE_USAGE_TRANSFER_SRC_BIT | extra_usages ) : ( VK_IMAGE_USAGE_SAMPLED_BIT | extra_usages );
        image_create_info.queueFamilyIndexCount = 0;
        image_create_info.pQueueFamilyIndices = NULL;
        image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        image_create_info.flags = 0;

        VkMemoryAllocateInfo
            mem_alloc = {};

        mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mem_alloc.pNext = NULL;
        mem_alloc.allocationSize = 0;
        mem_alloc.memoryTypeIndex = 0;

        VkImage
            mappable_image;
        VkDeviceMemory
            mappable_memory;
        VkMemoryRequirements
            mem_reqs;

        /* Create a mappable image.  It will be the texture if linear images are ok
        * to be textures or it will be the staging image if they are not. */
        GFX_CHECK( vkCreateImage( GraphicVKInfo.device, &image_create_info, NULL, &mappable_image ); )

        vkGetImageMemoryRequirements( GraphicVKInfo.device, mappable_image, &mem_reqs );

        mem_alloc.allocationSize=mem_reqs.size;

        /* Find the memory type that is host mappable */
        bool
            pass = GRAPHIC_VK_memory_type_from_properties( GraphicVKInfo, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &mem_alloc.memoryTypeIndex );

        assert( pass && "No mappable, coherent memory" );

        /* allocate memory */
        GFX_CHECK( vkAllocateMemory( GraphicVKInfo.device, &mem_alloc, NULL, &( mappable_memory ) ); )
        /* bind memory */
        GFX_CHECK( vkBindImageMemory( GraphicVKInfo.device, mappable_image, mappable_memory, 0 ); )
        GFX_CHECK( vkEndCommandBuffer( GraphicVKInfo.cmd ); )

        const VkCommandBuffer
            cmd_bufs[]={ GraphicVKInfo.cmd };
        VkFenceCreateInfo
            fence_info;
        VkFence
            cmd_fence;

        fence_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fence_info.pNext=NULL;
        fence_info.flags=0;
        vkCreateFence( GraphicVKInfo.device, &fence_info, NULL, &cmd_fence );

        VkSubmitInfo submit_info[ 1 ]={};
        submit_info[ 0 ].pNext = NULL;
        submit_info[ 0 ].sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info[ 0 ].waitSemaphoreCount = 0;
        submit_info[ 0 ].pWaitSemaphores = NULL;
        submit_info[ 0 ].pWaitDstStageMask = NULL;
        submit_info[ 0 ].commandBufferCount = 1;
        submit_info[ 0 ].pCommandBuffers = cmd_bufs;
        submit_info[ 0 ].signalSemaphoreCount = 0;
        submit_info[ 0 ].pSignalSemaphores = NULL;

        /* Queue the command buffer for execution */
        GFX_CHECK( vkQueueSubmit( GraphicVKInfo.graphics_queue, 1, submit_info, cmd_fence ); )

        VkImageSubresource
            subres={};

        subres.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subres.mipLevel = 0;
        subres.arrayLayer = 0;

        VkSubresourceLayout
            layout;

        /* Get the subresource layout so we know what the row pitch is */
        vkGetImageSubresourceLayout( GraphicVKInfo.device, mappable_image, &subres, &layout );

        /* Make sure command buffer is finished before mapping */
        do {

            res = vkWaitForFences( GraphicVKInfo.device, 1, &cmd_fence, VK_TRUE, FENCE_TIMEOUT );
        } while ( res == VK_TIMEOUT );

        assert( res == VK_SUCCESS );

        vkDestroyFence( GraphicVKInfo.device, cmd_fence, NULL );

        GFX_CHECK( vkMapMemory( GraphicVKInfo.device, mappable_memory, 0, mem_reqs.size, 0, &texture_data ); )

        vkUnmapMemory( GraphicVKInfo.device, mappable_memory );

        VkCommandBufferBeginInfo
            cmd_buf_info = {};
        cmd_buf_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cmd_buf_info.pNext = NULL;
        cmd_buf_info.flags = 0;
        cmd_buf_info.pInheritanceInfo = NULL;

        GFX_CHECK( vkResetCommandBuffer( GraphicVKInfo.cmd, 0 ); )
        GFX_CHECK( vkBeginCommandBuffer( GraphicVKInfo.cmd, &cmd_buf_info ); )

        if ( !needStaging ) {
            /* If we can use the linear tiled image as a texture, just do it */
            texture->SetVkImage( mappable_image );
            texture->SetVkDeviceMemory( mappable_memory );
            texture->SetVkImageLayout( VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
            GRAPHIC_VK_set_image_layout( GraphicVKInfo, texture->GetVkImage(), VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, texture->GetVkImageLayout(), VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT );
        }
        else {
            /* The mappable image cannot be our texture, so create an optimally
            * tiled image and blit to it */
            image_create_info.tiling=VK_IMAGE_TILING_OPTIMAL;
            image_create_info.usage=VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
            image_create_info.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;

            GFX_CHECK( vkCreateImage( GraphicVKInfo.device, &image_create_info, NULL, &texture->GetVkImage() ); )

            vkGetImageMemoryRequirements( GraphicVKInfo.device, texture->GetVkImage(), &mem_reqs );

            mem_alloc.allocationSize=mem_reqs.size;

            /* Find memory type - dont specify any mapping requirements */
            pass = GRAPHIC_VK_memory_type_from_properties( GraphicVKInfo, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &mem_alloc.memoryTypeIndex );
            assert( pass );

            /* allocate memory */
            GFX_CHECK( vkAllocateMemory( GraphicVKInfo.device, &mem_alloc, NULL, &texture->GetVkMemory() ); )

            /* bind memory */
            GFX_CHECK( vkBindImageMemory( GraphicVKInfo.device, texture->GetVkImage(), texture->GetVkMemory(), 0 ); )

            /* Since we're going to blit from the mappable image, set its layout to
            * SOURCE_OPTIMAL. Side effect is that this will create info.cmd */
            GRAPHIC_VK_set_image_layout( GraphicVKInfo, mappable_image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT );

            /* Since we're going to blit to the texture image, set its layout to
            * DESTINATION_OPTIMAL */
            GRAPHIC_VK_set_image_layout( GraphicVKInfo, texture->GetVkImage(), VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT );

            VkImageCopy
                copy_region;

            copy_region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            copy_region.srcSubresource.mipLevel = 0;
            copy_region.srcSubresource.baseArrayLayer = 0;
            copy_region.srcSubresource.layerCount = 1;
            copy_region.srcOffset.x = 0;
            copy_region.srcOffset.y = 0;
            copy_region.srcOffset.z = 0;
            copy_region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            copy_region.dstSubresource.mipLevel = 0;
            copy_region.dstSubresource.baseArrayLayer = 0;
            copy_region.dstSubresource.layerCount = 1;
            copy_region.dstOffset.x = 0;
            copy_region.dstOffset.y = 0;
            copy_region.dstOffset.z = 0;
            copy_region.extent.width = texture->GetTextureInfo().Width;
            copy_region.extent.height = texture->GetTextureInfo().Height;
            copy_region.extent.depth = 1;

            /* Put the copy command into the command buffer */
            vkCmdCopyImage( GraphicVKInfo.cmd, mappable_image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, texture->GetVkImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy_region );

            /* Set the layout for the texture image from DESTINATION_OPTIMAL to
            * SHADER_READ_ONLY */
            texture->SetVkImageLayout( VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );
            GRAPHIC_VK_set_image_layout( GraphicVKInfo, texture->GetVkImage(), VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, texture->GetVkImageLayout(), VK_PIPELINE_STAGE_TRANSFER_BIT,VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT );
        }

        VkImageViewCreateInfo
            view_info = {};

        view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.pNext = NULL;
        view_info.image = VK_NULL_HANDLE;
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = VK_FORMAT_R8G8B8A8_UNORM;
        view_info.components.r = VK_COMPONENT_SWIZZLE_R;
        view_info.components.g = VK_COMPONENT_SWIZZLE_G;
        view_info.components.b = VK_COMPONENT_SWIZZLE_B;
        view_info.components.a = VK_COMPONENT_SWIZZLE_A;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;

        /* create image view */
        view_info.image =texture->GetVkImage();

        GFX_CHECK( vkCreateImageView( GraphicVKInfo.device, &view_info, NULL, &texture->GetVkImageview() ); )

            /* create sampler */
            //init_sampler( info, texObj.sampler );

        VkSamplerCreateInfo
            samplerCreateInfo = {};

        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = VK_FILTER_NEAREST;
        samplerCreateInfo.minFilter = VK_FILTER_NEAREST;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
        samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samplerCreateInfo.mipLodBias = 0.0;
        samplerCreateInfo.anisotropyEnable = VK_FALSE,
        samplerCreateInfo.maxAnisotropy = 0;
        samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
        samplerCreateInfo.minLod = 0.0;
        samplerCreateInfo.maxLod = 0.0;
        samplerCreateInfo.compareEnable = VK_FALSE;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;

        /* create sampler */
        GFX_CHECK( vkCreateSampler( GraphicVKInfo.device, &samplerCreateInfo, NULL, &texture->GetVkSampler() ); )

        /* track a description of the texture */
        texture->SetVkImageLayout( VK_IMAGE_LAYOUT_GENERAL );
    }

    void GRAPHIC_SYSTEM::CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {

        abort();
    }

    void GRAPHIC_SYSTEM::DiscardTexture( GRAPHIC_TEXTURE * texture ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyShaderAttributeVector( const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( const float * matrix, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {

        abort();
    }

    void GRAPHIC_SYSTEM::CreateVertexBuffer( GRAPHIC_MESH &mesh ) {
        
        abort();
    }

    void GRAPHIC_SYSTEM::CreateIndexBuffer( GRAPHIC_MESH &mesh ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ApplyBuffers( GRAPHIC_MESH &mesh ) {

        abort();
    }

    void GRAPHIC_SYSTEM::ReleaseBuffers( GRAPHIC_MESH &mesh ) {

        abort();
    }

    /*
    * TODO: function description here
    */
    VkResult GRAPHIC_VK_init_global_extension_properties( layer_properties &layer_props ) {

        VkExtensionProperties *instance_extensions;
        uint32_t instance_extension_count;
        VkResult res;
        char *layer_name=NULL;

        layer_name=layer_props.properties.layerName;

        do {
            res=vkEnumerateInstanceExtensionProperties( layer_name, &instance_extension_count, NULL );

            if ( res )
                return res;

            if ( instance_extension_count == 0 ) {
                return VK_SUCCESS;
            }

            layer_props.extensions.resize( instance_extension_count );
            instance_extensions=layer_props.extensions.data();

            res = vkEnumerateInstanceExtensionProperties( layer_name, &instance_extension_count, instance_extensions );
        } while ( res == VK_INCOMPLETE );

        return res;
    }

    /*
    * TODO: function description here
    */
    VkResult GRAPHIC_VK_init_global_layer_properties( struct GRAPHIC_VK_ENGINE_INFO &info ) {
        uint32_t instance_layer_count;
        VkLayerProperties *vk_props=NULL;
        VkResult res;
#ifdef __ANDROID__
        // This place is the first place for samples to use Vulkan APIs.
        // Here, we are going to open Vulkan.so on the device and retrieve function pointers using
        // vulkan_wrapper helper.
        if ( !InitVulkan() ) {
            LOGE( "Failied initializing Vulkan APIs!" );
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        LOGI( "Loaded Vulkan APIs." );
#endif

        /*
        * It's possible, though very rare, that the number of
        * instance layers could change. For example, installing something
        * could include new layers that the loader would pick up
        * between the initial query for the count and the
        * request for VkLayerProperties. The loader indicates that
        * by returning a VK_INCOMPLETE status and will update the
        * the count parameter.
        * The count parameter will be updated with the number of
        * entries loaded into the data pointer - in case the number
        * of layers went down or is smaller than the size given.
        */
        do {
            res=vkEnumerateInstanceLayerProperties( &instance_layer_count, NULL );
            if ( res )
                return res;

            if ( instance_layer_count == 0 ) {
                return VK_SUCCESS;
            }

            vk_props=( VkLayerProperties * ) realloc(
                vk_props, instance_layer_count * sizeof( VkLayerProperties ) );

            res=
                vkEnumerateInstanceLayerProperties( &instance_layer_count, vk_props );
        } while ( res == VK_INCOMPLETE );

        /*
        * Now gather the extension list for each instance layer.
        */
        for ( uint32_t i=0; i < instance_layer_count; i++ ) {
            layer_properties layer_props;
            layer_props.properties=vk_props[ i ];
            res=GRAPHIC_VK_init_global_extension_properties( layer_props );

            if ( res )
                return res;

            info.instance_layer_properties.push_back( layer_props );
        }
        free( vk_props );

        return res;
    }

    VkResult GRAPHIC_VK_init_device_extension_properties( struct GRAPHIC_VK_ENGINE_INFO &info, layer_properties &layer_props ) {

        VkExtensionProperties
            *device_extensions;
        uint32_t
            device_extension_count;
        VkResult
            res;
        char
            * layer_name=NULL;

        layer_name=layer_props.properties.layerName;

        do {
            res=vkEnumerateDeviceExtensionProperties( info.gpus[ 0 ], layer_name, &device_extension_count, NULL );

            if ( res )
                return res;

            if ( device_extension_count == 0 ) {

                return VK_SUCCESS;
            }

            layer_props.extensions.resize( device_extension_count );
            device_extensions=layer_props.extensions.data();
            res=vkEnumerateDeviceExtensionProperties( info.gpus[ 0 ], layer_name, &device_extension_count, device_extensions );
        } while ( res == VK_INCOMPLETE );

        return res;
    }

    void GRAPHIC_VK_init_instance_extension_names( struct GRAPHIC_VK_ENGINE_INFO &info ) {
        info.instance_extension_names.push_back( VK_KHR_SURFACE_EXTENSION_NAME );
#ifdef __ANDROID__
        info.instance_extension_names.push_back( VK_KHR_ANDROID_SURFACE_EXTENSION_NAME );
#elif defined(_WIN32)
        //info.instance_extension_names.push_back( VK_KHR_WIN32_SURFACE_EXTENSION_NAME );
#else
        info.instance_extension_names.push_back( VK_KHR_XCB_SURFACE_EXTENSION_NAME );
#endif
    }

    void GRAPHIC_VK_init_instance( struct GRAPHIC_VK_ENGINE_INFO &info, char const *const app_short_name ) {

        VkApplicationInfo app_info = {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext = NULL;
        app_info.pApplicationName = app_short_name;
        app_info.applicationVersion = 1;
        app_info.pEngineName = app_short_name;
        app_info.engineVersion = 1;
        app_info.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo inst_info = {};
        inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext = NULL;
        inst_info.flags = 0;
        inst_info.pApplicationInfo = &app_info;
        inst_info.enabledLayerCount = info.instance_layer_names.size();
        inst_info.ppEnabledLayerNames = info.instance_layer_names.size() ? info.instance_layer_names.data() : NULL;
        inst_info.enabledExtensionCount = info.instance_extension_names.size();
        inst_info.ppEnabledExtensionNames = info.instance_extension_names.data();

        GFX_CHECK( vkCreateInstance( &inst_info, NULL, &info.VkInstance ); )
    }

    void GRAPHIC_VK_init_device_extension_names( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        info.device_extension_names.push_back( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
    }

    void GRAPHIC_VK_init_device( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        VkDeviceQueueCreateInfo
            queue_info={};
        VkDeviceCreateInfo
            device_info={};
        float
            queue_priorities[ 1 ]={ 0.0 };

        queue_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info.pNext=NULL;
        queue_info.queueCount=1;
        queue_info.pQueuePriorities=queue_priorities;
        queue_info.queueFamilyIndex=info.graphics_queue_family_index;

        device_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.pNext=NULL;
        device_info.queueCreateInfoCount=1;
        device_info.pQueueCreateInfos=&queue_info;
        device_info.enabledExtensionCount=info.device_extension_names.size();
        device_info.ppEnabledExtensionNames=device_info.enabledExtensionCount ? info.device_extension_names.data() : NULL;
        device_info.pEnabledFeatures=NULL;

        GFX_CHECK( vkCreateDevice( info.gpus[ 0 ], &device_info, NULL, &info.device ); )
    }

    void GRAPHIC_VK_init_enumerate_device( struct GRAPHIC_VK_ENGINE_INFO &info, uint32_t gpu_count ) {

        uint32_t
            req_count=gpu_count;

        GFX_CHECK( vkEnumeratePhysicalDevices( info.VkInstance, &gpu_count, NULL ); )

        assert( gpu_count );
        info.gpus.resize( gpu_count );

        GFX_CHECK( vkEnumeratePhysicalDevices( info.VkInstance, &gpu_count, info.gpus.data() ); )
        assert( gpu_count >= req_count );

        vkGetPhysicalDeviceQueueFamilyProperties( info.gpus[ 0 ], &info.queue_family_count, NULL );
        assert( info.queue_family_count >= 1 );

        info.queue_props.resize( info.queue_family_count );
        vkGetPhysicalDeviceQueueFamilyProperties( info.gpus[ 0 ], &info.queue_family_count, info.queue_props.data() );
        assert( info.queue_family_count >= 1 );

        /* This is as good a place as any to do this */
        vkGetPhysicalDeviceMemoryProperties( info.gpus[ 0 ], &info.memory_properties );
        vkGetPhysicalDeviceProperties( info.gpus[ 0 ], &info.gpu_props );
    }

    void GRAPHIC_VK_init_queue_family_index( struct GRAPHIC_VK_ENGINE_INFO & info ) {
        /* This routine simply finds a graphics queue for a later vkCreateDevice,
        * without consideration for which queue family can present an image.
        * Do not use this if your intent is to present later in your sample,
        * instead use the init_connection, init_window, init_swapchain_extension,
        * init_device call sequence to get a graphics and present compatible queue
        * family
        */

        vkGetPhysicalDeviceQueueFamilyProperties( info.gpus[ 0 ], &info.queue_family_count, NULL );
        assert( info.queue_family_count >= 1 );

        info.queue_props.resize( info.queue_family_count );
        vkGetPhysicalDeviceQueueFamilyProperties( info.gpus[ 0 ], &info.queue_family_count, info.queue_props.data() );
        assert( info.queue_family_count >= 1 );

        bool found=false;

        for ( unsigned int i=0; i < info.queue_family_count; i++ ) {

            if ( info.queue_props[ i ].queueFlags & VK_QUEUE_GRAPHICS_BIT ) {

                info.graphics_queue_family_index=i;
                found=true;
                break;
            }
        }
        assert( found );
    }

    void GRAPHIC_VK_destroy_depth_buffer( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        vkDestroyImageView( info.device, info.depth.view, NULL );
        vkDestroyImage( info.device, info.depth.image, NULL );
        vkFreeMemory( info.device, info.depth.mem, NULL );
    }

    void GRAPHIC_VK_destroy_swap_chain( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        for ( uint32_t i=0; i < info.swapchainImageCount; i++ ) {

            vkDestroyImageView( info.device, info.buffers[ i ].view, NULL );
        }

        vkDestroySwapchainKHR( info.device, info.swap_chain, NULL );
    }

    void GRAPHIC_VK_destroy_command_buffer( struct GRAPHIC_VK_ENGINE_INFO & info ) {

        VkCommandBuffer cmd_bufs[ 1 ] = { info.cmd };

        vkFreeCommandBuffers( info.device, info.cmd_pool, 1, cmd_bufs );
    }

    void GRAPHIC_VK_destroy_command_pool( struct GRAPHIC_VK_ENGINE_INFO & info ) {

        vkDestroyCommandPool( info.device, info.cmd_pool, NULL );
    }

    void GRAPHIC_VK_destroy_device( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        vkDeviceWaitIdle( info.device );
        vkDestroyDevice( info.device, NULL );
    }

    void GRAPHIC_VK_destroy_instance( struct GRAPHIC_VK_ENGINE_INFO &info ) {

        vkDestroyInstance( info.VkInstance, NULL );
    }

    bool GRAPHIC_VK_memory_type_from_properties( struct GRAPHIC_VK_ENGINE_INFO & info, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex ) {
        // Search memtypes to find first index with those properties
        for ( uint32_t i=0; i < info.memory_properties.memoryTypeCount; i++ ) {

            if ( ( typeBits & 1 ) == 1 ) {

                // Type is available, does it match user properties?
                if ( ( info.memory_properties.memoryTypes[ i ].propertyFlags & requirements_mask ) == requirements_mask ) {

                    *typeIndex=i;

                    return true;
                }
            }

            typeBits>>=1;
        }
        // No memory types matched, return failure
        return false;
    }

    void GRAPHIC_VK_set_image_layout( struct GRAPHIC_VK_ENGINE_INFO &info, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkPipelineStageFlags src_stages, VkPipelineStageFlags dest_stages ) {
        /* DEPENDS on info.cmd and info.queue initialized */

        assert( info.cmd != VK_NULL_HANDLE );
        assert( info.graphics_queue != VK_NULL_HANDLE );

        VkImageMemoryBarrier
            image_memory_barrier = {};

        image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        image_memory_barrier.pNext = NULL;
        image_memory_barrier.srcAccessMask = 0;
        image_memory_barrier.dstAccessMask = 0;
        image_memory_barrier.oldLayout = old_image_layout;
        image_memory_barrier.newLayout = new_image_layout;
        image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        image_memory_barrier.image = image;
        image_memory_barrier.subresourceRange.aspectMask = aspectMask;
        image_memory_barrier.subresourceRange.baseMipLevel = 0;
        image_memory_barrier.subresourceRange.levelCount = 1;
        image_memory_barrier.subresourceRange.baseArrayLayer = 0;
        image_memory_barrier.subresourceRange.layerCount = 1;

        switch ( old_image_layout ) {

            case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                image_memory_barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                break;

            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL :
                image_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                break;

            case VK_IMAGE_LAYOUT_PREINITIALIZED:
                image_memory_barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
                break;

            default:
                break;
        }

        switch ( new_image_layout ) {

            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                break;

            case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                break;

            case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
                break;

            case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                break;

            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                break;

            default:
                break;
        }

        vkCmdPipelineBarrier( info.cmd, src_stages, dest_stages, 0, 0, NULL, 0, NULL, 1, &image_memory_barrier );
    }

#endif