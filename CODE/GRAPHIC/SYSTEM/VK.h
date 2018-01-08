#pragma once

#if PLATFORM_ANDROID
// Include files for Android
#include <unistd.h>
#include <android/log.h>
#include "vulkan_wrapper.h" // Include Vulkan_wrapper and dynamically load symbols.
#elif PLATFORM_WINDOWS
#include "vulkan/vk_sdk_platform.h"
#endif // _WIN32

#include "SERVICE_LOGGER.h"
#include <vulkan/vulkan.h>

VkInstance & GetGraphicVKInstance();

// From VULKAN UTIL.HPP

/* Number of descriptor sets needs to be the same at alloc,       */
/* pipeline layout creation, and descriptor set layout creation   */
#define NUM_DESCRIPTOR_SETS 1

/* Number of samples needs to be the same at image creation,      */
/* renderpass creation and pipeline creation.                     */
#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

/* Number of viewports and number of scissors have to be the same */
/* at pipeline creation and in any call to set them dynamically   */
/* They also have to be the same as each other                    */
#define NUM_VIEWPORTS 1
#define NUM_SCISSORS NUM_VIEWPORTS

/* Amount of time, in nanoseconds, to wait for a command buffer to complete */
#define FENCE_TIMEOUT 100000000

/*
* structure to track all objects related to a texture.
*/
struct texture_object {
    VkSampler sampler;

    VkImage image;
    VkImageLayout imageLayout;

    VkDeviceMemory mem;
    VkImageView view;
    int32_t tex_width, tex_height;
};

/*
* Keep each of our swap chain buffers' image, command buffer and view in one
* spot
*/
typedef struct _swap_chain_buffers {
    VkImage image;
    VkImageView view;
} swap_chain_buffer;

/*
* A layer can expose extensions, keep track of those
* extensions here.
*/
typedef struct {
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> extensions;
} layer_properties;

/*
* Structure for tracking information used / created / modified
* by utility functions.
*/
struct GRAPHIC_VK_ENGINE_INFO {
#ifdef _WIN32
#define APP_NAME_STR_LEN 80
    char name[ APP_NAME_STR_LEN ]; // Name to put on the window/icon
#elif defined(__ANDROID__)
    PFN_vkCreateAndroidSurfaceKHR fpCreateAndroidSurfaceKHR;
#else  // _WIN32
    xcb_connection_t *connection;
    xcb_screen_t *screen;
    xcb_window_t window;
    xcb_intern_atom_reply_t *atom_wm_delete_window;
#endif // _WIN32
    bool prepared;
    bool use_staging_buffer;
    bool save_images;

    std::vector<const char *>
        instance_layer_names;
    std::vector<const char *>
        instance_extension_names;
    std::vector<layer_properties>
        instance_layer_properties;
    std::vector<VkExtensionProperties>
        instance_extension_properties;
    VkInstance
        VkInstance;

    std::vector<const char *> device_extension_names;
    std::vector<VkExtensionProperties> device_extension_properties;
    std::vector<VkPhysicalDevice> gpus;
    VkDevice device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    uint32_t graphics_queue_family_index;
    uint32_t present_queue_family_index;
    VkPhysicalDeviceProperties gpu_props;
    std::vector<VkQueueFamilyProperties> queue_props;
    VkPhysicalDeviceMemoryProperties memory_properties;

    VkFramebuffer *framebuffers;
    int width, height;
    VkFormat format;

    uint32_t swapchainImageCount;
    VkSwapchainKHR swap_chain;
    std::vector<swap_chain_buffer> buffers;
    VkSemaphore imageAcquiredSemaphore;

    VkCommandPool cmd_pool;

    struct {
        VkFormat format;

        VkImage image;
        VkDeviceMemory mem;
        VkImageView view;
    } depth;

    struct {
        VkBuffer buf;
        VkDeviceMemory mem;
        VkDescriptorBufferInfo buffer_info;
    } uniform_data;

    struct {
        VkDescriptorImageInfo image_info;
    } texture_data;

    struct {
        VkBuffer buf;
        VkDeviceMemory mem;
        VkDescriptorBufferInfo buffer_info;
    } vertex_buffer;
    VkVertexInputBindingDescription vi_binding;
    VkVertexInputAttributeDescription vi_attribs[ 2 ];

    VkCommandBuffer cmd; // Buffer for initialization commands
    VkPipelineLayout pipeline_layout;
    std::vector<VkDescriptorSetLayout> desc_layout;
    VkPipelineCache pipelineCache;
    VkRenderPass render_pass;
    VkPipeline pipeline;

    VkPipelineShaderStageCreateInfo shaderStages[ 2 ];

    VkDescriptorPool desc_pool;
    std::vector<VkDescriptorSet> desc_set;

    PFN_vkCreateDebugReportCallbackEXT dbgCreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT dbgDestroyDebugReportCallback;
    PFN_vkDebugReportMessageEXT dbgBreakCallback;
    std::vector<VkDebugReportCallbackEXT> debug_report_callbacks;

    uint32_t current_buffer;
    uint32_t queue_family_count;

    VkViewport viewport;
    VkRect2D scissor;
};

#define GFX_CHECK( __METHOD__ ) \
        { \
            VkResult result = __METHOD__ \
            if ( result != VK_SUCCESS) { \
                switch( result ) { \
                    case VK_ERROR_INCOMPATIBLE_DRIVER: \
                        SERVICE_LOGGER_Error( "VK_ERROR_INCOMPATIBLE_DRIVER cannot find a compatible Vulkan ICD %s\n", #__METHOD__ ); \
                        break; \
                    case VK_NOT_READY: \
                        SERVICE_LOGGER_Error( "VK_NOT_READY %s\n", #__METHOD__ ); \
                        break; \
                    case VK_TIMEOUT: \
                        SERVICE_LOGGER_Error( "VK_TIMEOUT %s\n", #__METHOD__ ); \
                        break; \
                    case VK_EVENT_SET: \
                        SERVICE_LOGGER_Error( "VK_EVENT_SET %s\n", #__METHOD__ ); \
                        break; \
                    case VK_EVENT_RESET: \
                        SERVICE_LOGGER_Error( "VK_EVENT_RESET %s\n", #__METHOD__ ); \
                        break; \
                    case VK_INCOMPLETE: \
                        SERVICE_LOGGER_Error( "VK_INCOMPLETE %s\n", #__METHOD__ ); \
                        break; \
                    case VK_SUBOPTIMAL_KHR: \
                        SERVICE_LOGGER_Error( "VK_SUBOPTIMAL_KHR %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_OUT_OF_HOST_MEMORY: \
                        SERVICE_LOGGER_Error( "VK_ERROR_OUT_OF_HOST_MEMORY %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_OUT_OF_DEVICE_MEMORY: \
                        SERVICE_LOGGER_Error( "VK_ERROR_OUT_OF_DEVICE_MEMORY %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_INITIALIZATION_FAILED: \
                        SERVICE_LOGGER_Error( "VK_ERROR_INITIALIZATION_FAILED %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_MEMORY_MAP_FAILED: \
                        SERVICE_LOGGER_Error( "VK_ERROR_MEMORY_MAP_FAILED %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_DEVICE_LOST: \
                        SERVICE_LOGGER_Error( "VK_ERROR_DEVICE_LOST %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_TOO_MANY_OBJECTS: \
                        SERVICE_LOGGER_Error( "VK_ERROR_TOO_MANY_OBJECTS %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_FORMAT_NOT_SUPPORTED: \
                        SERVICE_LOGGER_Error( "VK_ERROR_FORMAT_NOT_SUPPORTED %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_SURFACE_LOST_KHR: \
                        SERVICE_LOGGER_Error( "VK_ERROR_SURFACE_LOST_KHR %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_OUT_OF_DATE_KHR: \
                        SERVICE_LOGGER_Error( "VK_ERROR_OUT_OF_DATE_KHR %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: \
                        SERVICE_LOGGER_Error( "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: \
                        SERVICE_LOGGER_Error( "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR %s\n", #__METHOD__ ); \
                        break; \
                    case VK_ERROR_VALIDATION_FAILED_EXT: \
                        SERVICE_LOGGER_Error( "VK_ERROR_VALIDATION_FAILED_EXT %s\n", #__METHOD__ ); \
                        break; \
                    default: \
                        SERVICE_LOGGER_Error( "VK_ERROR unknown error %s\n", #__METHOD__ ); \
                        break; \
                } \
            } \
        }

#define GRAPHIC_SYSTEM_ApplyMatrix(index, size, transpose, array) \
    abort();

#define GRAPHIC_SYSTEM_ApplyVector(index, size, array) \
    abort();

#define GRAPHIC_SYSTEM_ApplyFloat(index, value) \
    abort();

VkResult GRAPHIC_VK_init_global_extension_properties( layer_properties &layer_props );
VkResult GRAPHIC_VK_init_global_layer_properties( GRAPHIC_VK_ENGINE_INFO & info );
VkResult GRAPHIC_VK_init_device_extension_properties( struct GRAPHIC_VK_ENGINE_INFO &info, layer_properties &layer_props );
void GRAPHIC_VK_init_instance_extension_names( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_init_instance( struct GRAPHIC_VK_ENGINE_INFO &info, char const *const app_short_name );
void GRAPHIC_VK_init_device_extension_names( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_init_device( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_init_enumerate_device( struct GRAPHIC_VK_ENGINE_INFO &info, uint32_t gpu_count=1 );
void GRAPHIC_VK_init_connection( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_init_queue_family_index( struct GRAPHIC_VK_ENGINE_INFO &info );


void GRAPHIC_VK_destroy_pipeline( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_destroy_pipeline_cache( struct GRAPHIC_VK_ENGINE_INFO &info );
void GRAPHIC_VK_destroy_descriptor_pool( struct GRAPHIC_VK_ENGINE_INFO &info );

/*
//TODO : graphic vertex buffer
void destroy_vertex_buffer( struct sample_info &info );
//TODO : graphic texture
void destroy_textures( struct sample_info &info );
//TODO : graphic render target
void destroy_framebuffers( struct sample_info &info );
//TODO : graphic shader
void destroy_shaders( struct sample_info &info );
//TODO : ???
void destroy_renderpass( struct sample_info &info );


//TODO : ??
void destroy_descriptor_and_pipeline_layouts( struct GRAPHIC_VK_ENGINE_INFO & info );
void destroy_uniform_buffer( struct GRAPHIC_VK_ENGINE_INFO & info );
*/
void GRAPHIC_VK_destroy_depth_buffer( struct GRAPHIC_VK_ENGINE_INFO & info );
void GRAPHIC_VK_destroy_swap_chain( struct GRAPHIC_VK_ENGINE_INFO & info );
void GRAPHIC_VK_destroy_command_buffer( struct GRAPHIC_VK_ENGINE_INFO & info );
void GRAPHIC_VK_destroy_command_pool( struct GRAPHIC_VK_ENGINE_INFO & info );
void GRAPHIC_VK_destroy_device( struct GRAPHIC_VK_ENGINE_INFO & info );
void GRAPHIC_VK_destroy_instance( struct GRAPHIC_VK_ENGINE_INFO & info );

bool GRAPHIC_VK_memory_type_from_properties( struct GRAPHIC_VK_ENGINE_INFO &info, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex );
void GRAPHIC_VK_set_image_layout( struct GRAPHIC_VK_ENGINE_INFO &info, VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout, VkImageLayout new_image_layout, VkPipelineStageFlags src_stages, VkPipelineStageFlags dest_stages );
