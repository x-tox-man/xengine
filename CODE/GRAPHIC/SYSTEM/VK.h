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

void VK_Initialize();

#define GFX_CHECK( __METHOD__ ) \
        { \
            VkResult result = __METHOD__ \
            if ( result) { \
                if ( result == VK_ERROR_INCOMPATIBLE_DRIVER ) { \
                    SERVICE_LOGGER_Error( "cannot find a compatible Vulkan ICD\n" ); \
                } \
                else if ( result ) { \
                    SERVICE_LOGGER_Error( "unknown error\n" ); \
                } \
            } \
        }

#define GRAPHIC_SYSTEM_ApplyMatrix(index, size, transpose, array) \
    abort();

#define GRAPHIC_SYSTEM_ApplyVector(index, size, array) \
    abort();

#define GRAPHIC_SYSTEM_ApplyFloat(index, value) \
    abort();

VkInstance VKInstance;
