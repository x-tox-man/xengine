//
//  SERVICE_LOGGER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_LOGGER__
#define __GAME_ENGINE_REBORN__SERVICE_LOGGER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

namespace SERVICE_LOGGER {
    
    #if PLATFORM_ANDROID
        #define SERVICE_LOGGER_Error(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
        #define SERVICE_LOGGER_Warning(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
        #define SERVICE_LOGGER_Verbose(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
        #define SERVICE_LOGGER_Info(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
    #else
        #define SERVICE_LOGGER_Error(...) (printf( __VA_ARGS__))
        #define SERVICE_LOGGER_Warning(...) (printf( __VA_ARGS__))
        #define SERVICE_LOGGER_Verbose(...) (printf( __VA_ARGS__))
        #define SERVICE_LOGGER_Info(...) (printf( __VA_ARGS__))
    #endif
}

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_LOGGER__) */
