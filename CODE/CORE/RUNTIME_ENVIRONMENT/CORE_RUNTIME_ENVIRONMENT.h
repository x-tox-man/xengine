//
//  CORE_RUNTIME_ENVIRONMENT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 27/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifdef __PLATFORM_OSX__
    #define PLATFORM_OSX 1
    #include "CORE_RUNTIME_ENVIRONMENT_OSX.h"
    #define PLATFORM_CPU_ARCH_X86_64 1
#else
    #define PLATFORM_OSX 0
#endif

#ifdef __PLATFORM_ANDROID__
    #define PLATFORM_ANDROID 1
    #define PLATFORM_CPU_ARCH_ARM 1
#else
    #define PLATFORM_ANDROID 0
#endif

#ifdef __PLATFORM_IOS__
    #define PLATFORM_IOS 1
    #include "CORE_RUNTIME_ENVIRONMENT_IOS.h"
    #define PLATFORM_CPU_ARCH_ARM 1
#else
    #define PLATFORM_IOS 0
#endif

#ifdef __PLATFORM_WINDOWS__
    #define PLATFORM_WINDOWS 1
    #include "CORE_RUNTIME_ENVIRONMENT_WINDOWS.h"
#else
    #define PLATFORM_WINDOWS 0
	#define WINDOWS_THREAD 0
#endif

#if PLATFORM_ANDROID
    #include "CORE_RUNTIME_ENVIRONMENT_ANDROID.h"
#endif

#if PLATFORM_OSX
    #include "CORE_RUNTIME_ENVIRONMENT_OSX.h"
#endif

#if PLATFORM_IOS
    #include "CORE_RUNTIME_ENVIRONMENT_IOS.h"
#endif

#define __STRING_MAX_LENGHT__ 256

#if DEBUG
    #define safe_strlen( __string__ ) \
        strlen( __string__ ); \
        int len = strlen( __string__ ); \
        if ( len > __STRING_MAX_LENGHT__ ) \
            CORE_RUNTIME_Abort();
#else
#define safe_strlen( __string__ ) \
    strlen( __string__ );
#endif

#ifndef CORE_RUNTIME_Abort
    #define CORE_RUNTIME_Abort() \
        abort();
#endif

#ifndef CORE_RUNTIME_Assert
    #define CORE_RUNTIME_Assert( __TEST__ ) \
        assert( __TEST__ );
#endif
