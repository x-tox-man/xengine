//
//  CORE_DATA_TYPES.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_DATA_TYPES_h
#define GAME_ENGINE_REBORN_CORE_DATA_TYPES_h

#include "CORE_RUNTIME_ENVIRONMENT.h"

typedef char * CHAR_ARRAY_POINTER;
typedef char ** CHAR_ARRAY_POINTER_POINTER;

typedef wchar_t * WCHAR_ARRAY_POINTER;
typedef wchar_t ** WCHAR_ARRAY_POINTER_POINTER;

#if PLATFORM_WINDOWS
#define CORE_DATA_COPY_STRING(__DESTINATION__, __SOURCE__) \
    { size_t ___s = (strlen(__SOURCE__) ); if ( ___s++ ) strcpy_s(__DESTINATION__, ___s, __SOURCE__); }
#define CORE_DATA_COPY_STRING_WITH_SIZE(__DESTINATION__, __SOURCE__, __SIZE__) \
    { strcpy_s(__DESTINATION__, __SIZE__, __SOURCE__); }
#define CORE_DATA_STRING_CONCAT( __DESTINATION__, __SOURCE__) \
    { size_t ___s = (strlen(__SOURCE__) ) + (strlen(__DESTINATION__) ); if ( ___s++ ) strcat_s(__DESTINATION__, ___s, __SOURCE__); }
#define CORE_DATA_COPY_WIDE_STRING(__DESTINATION__, __SOURCE__) \
    { size_t ___s = (wcslen(__SOURCE__) ); if ( ___s++ ) wcscpy_s(__DESTINATION__, ___s, __SOURCE__); }

#else
#define CORE_DATA_COPY_STRING(__DESTINATION__, __SOURCE__) \
    { size_t ___s = (strlen(__SOURCE__) ); if ( ___s++ ) strcpy(__DESTINATION__, __SOURCE__ ); }
#define CORE_DATA_COPY_STRING_WITH_SIZE(__DESTINATION__, __SOURCE__, __SIZE__) \
    { if ( __SIZE__ ) strcpy(__DESTINATION__, __SOURCE__ ); }
#define CORE_DATA_STRING_CONCAT( __DESTINATION__, __SOURCE__) \
    { strcat(__DESTINATION__, __SOURCE__); }
#define CORE_DATA_COPY_WIDE_STRING(__DESTINATION__, __SOURCE__) \
    { size_t ___s = (wcslen(__SOURCE__) ); if ( ___s++ ) wcscpy(__DESTINATION__, __SOURCE__); }
#endif

#endif
