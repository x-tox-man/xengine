//
//  CORE_MEMORY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/01/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_MEMORY_ALLOCATOR.h"

#include <stdlib.h>

void * operator new( size_t size )
{
    void *p = CORE_MEMORY_ALLOCATOR::Allocate( size );

    return p;
}

void * CORE_MEMORY_ALLOCATOR::Allocate( size_t size ) {

    return (void *) malloc( size );
}

void CORE_MEMORY_ALLOCATOR::Free( void * memory_pointer ) {

    free( memory_pointer );
}