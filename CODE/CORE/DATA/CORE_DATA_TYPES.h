//
//  CORE_DATA_TYPES.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 5/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_DATA_TYPES_h
#define GAME_ENGINE_REBORN_CORE_DATA_TYPES_h

typedef char * CHAR_ARRAY_POINTER;
typedef char ** CHAR_ARRAY_POINTER_POINTER;

typedef wchar_t * WCHAR_ARRAY_POINTER;
typedef wchar_t ** WCHAR_ARRAY_POINTER_POINTER;

#define CORE_DATA_COPY_STRING(__DESTINATION__, __SOURCE__) \
 { size_t ___s = strlen(__SOURCE__); strncpy(__DESTINATION__, __SOURCE__, ___s); }

#endif
