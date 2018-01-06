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
        * GRAPHIC_SYSTEM::ShaderDirectoryPath="OPENGL2";
    CORE_HELPERS_COLOR
        GRAPHIC_SYSTEM::ClearColor=CORE_COLOR_Blue;
    /*VkInstance
        GraphicVKInstance;
    VkPhysicalDevice
        SelectedGraphicVKDevice;
    VkPhysicalDeviceProperties
        GraphicVKDeviceProperties;
    VkDevice
        * GraphicVKDevice;
    unsigned int
        GraphicVKDeviceCount;*/
    GRAPHIC_VK_ENGINE_INFO
        GraphicVKInfo = {};
    
    VkInstance & GetGraphicVKInstance() {

        return GraphicVKInfo.inst;
    }

    GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {

    }


    void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {

        GRAPHIC_VK_init_global_layer_properties( GraphicVKInfo );
        GRAPHIC_VK_init_instance_extension_names( GraphicVKInfo );
        GRAPHIC_VK_init_instance( GraphicVKInfo, app_name );
        GRAPHIC_VK_init_enumerate_device( GraphicVKInfo );
        GRAPHIC_VK_init_queue_family_index( GraphicVKInfo );
        GRAPHIC_VK_init_device( GraphicVKInfo );
    }

    void GRAPHIC_SYSTEM::Finalize() {

        /*if ( GraphicVKDevice ) {
            GFX_CHECK( vkDeviceWaitIdle( *GraphicVKDevice ); )
            vkDestroyDevice( *GraphicVKDevice, NULL );
        }

        vkDestroyInstance( GraphicVKInstance, NULL );*/
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

        abort();
    }

    void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {

        abort();
    }

    void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {

        abort();
    }

    void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, const void * texture_data, bool generate_mipmap ) {

        abort();
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
            res=vkEnumerateInstanceExtensionProperties(
                layer_name, &instance_extension_count, NULL );
            if ( res )
                return res;

            if ( instance_extension_count == 0 ) {
                return VK_SUCCESS;
            }

            layer_props.extensions.resize( instance_extension_count );
            instance_extensions=layer_props.extensions.data();
            res=vkEnumerateInstanceExtensionProperties(
                layer_name, &instance_extension_count, instance_extensions );
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
        VkApplicationInfo app_info={};
        app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pNext=NULL;
        app_info.pApplicationName=app_short_name;
        app_info.applicationVersion=1;
        app_info.pEngineName=app_short_name;
        app_info.engineVersion=1;
        app_info.apiVersion=VK_API_VERSION_1_0;

        VkInstanceCreateInfo inst_info={};
        inst_info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        inst_info.pNext=NULL;
        inst_info.flags=0;
        inst_info.pApplicationInfo=&app_info;
        inst_info.enabledLayerCount=info.instance_layer_names.size();
        inst_info.ppEnabledLayerNames=info.instance_layer_names.size()
            ? info.instance_layer_names.data()
            : NULL;
        inst_info.enabledExtensionCount=info.instance_extension_names.size();
        inst_info.ppEnabledExtensionNames=info.instance_extension_names.data();

        GFX_CHECK( vkCreateInstance( &inst_info, NULL, &info.inst ); )
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

        GFX_CHECK( vkEnumeratePhysicalDevices( info.inst, &gpu_count, NULL ); )

            assert( gpu_count );
        info.gpus.resize( gpu_count );

        GFX_CHECK( vkEnumeratePhysicalDevices( info.inst, &gpu_count, info.gpus.data() ); )
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

#endif