//
//  CORE_MEMORY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_MEMORY_h
#define GAME_ENGINE_REBORN_CORE_MEMORY_h

#include "CORE_MEMORY_ALLOCATOR.h"

template < typename __TYPE__ >
void CORE_MEMORY_COPY_BYTES_SWAPPED( void * MemoryBuffer, int Offset, const __TYPE__ & data ) {
    
    
    memcpy( ( char* )MemoryBuffer + Offset, &data, sizeof(__TYPE__ ) );
}

#define CORE_MEMORY_ObjectSafeDeallocation( __OBJECT__ ) \
    if ( __OBJECT__ ) { \
        delete __OBJECT__;\
        __OBJECT__ = NULL; \
    }

#endif
