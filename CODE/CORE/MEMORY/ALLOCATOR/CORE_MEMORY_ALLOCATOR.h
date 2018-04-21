//
//  CORE_MEMORY.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/01/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MEMORY__
#define __GAME_ENGINE_REBORN__CORE_MEMORY__

#include "CORE_RUNTIME_ENVIRONMENT.h"

void * operator new( size_t size );
void operator delete( void * p );

class CORE_MEMORY_ALLOCATOR {

public:

    static void * Allocate( size_t size );
    static void Free( void * memory_pointer );

private:
    CORE_MEMORY_ALLOCATOR();

};

#define CORE_MEMORY_ALLOCATOR_Free( __POINTER__ ) \
    CORE_MEMORY_ALLOCATOR::Free( __POINTER__ );

#define CORE_MEMORY_ALLOCATOR_Allocate( __SIZE__ ) \
    CORE_MEMORY_ALLOCATOR::Allocate( __SIZE__ );

#define CORE_MEMORY_CopyBytes( __DESTINATION__, __SIZE__, __SOURCE__ ) \
    memcpy( __DESTINATION__, __SOURCE__, (int) __SIZE__ );

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MEMORY__) */
