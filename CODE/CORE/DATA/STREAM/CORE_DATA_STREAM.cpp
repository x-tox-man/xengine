//
//  CORE_DATA_STREAM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_DATA_STREAM.h"
#include "CORE_MEMORY.h"
#include <string>

CORE_DATA_STREAM::CORE_DATA_STREAM() :
    MemoryBuffer( NULL ),
    AllocatedBytes(0),
    Offset( 0 ),
    Size( 0 ) {
    
}

CORE_DATA_STREAM::~CORE_DATA_STREAM() {
    
    if ( MemoryBuffer && AllocatedBytes ) {
    
        CORE_MEMORY_ALLOCATOR_Free( MemoryBuffer );
    }
    
    MemoryBuffer = NULL;
    AllocatedBytes = 0;
}

CORE_DATA_STREAM::CORE_DATA_STREAM( int size ) :
    MemoryBuffer(),
    AllocatedBytes( size ),
    Offset( 0 ) {
    
    MemoryBuffer = CORE_MEMORY_ALLOCATOR_Allocate( size );
}

CORE_DATA_STREAM::CORE_DATA_STREAM( const char * pointer, int size ) :
    MemoryBuffer(),
    AllocatedBytes( 0 ), // No bytes were allocated
    Offset( 0 ) {
        
    MemoryBuffer = (void * ) pointer;
    AllocatedBytes = size;
}

void CORE_DATA_STREAM::Open() {
    
}

void CORE_DATA_STREAM::Close() {
    
}

void CORE_DATA_STREAM::InitializeWithSize( int size ) {
    
    MemoryBuffer = CORE_MEMORY_ALLOCATOR_Allocate( size );
}

void CORE_DATA_STREAM::ResetOffset() {
    
    Size = Offset;
    Offset = 0;
}

void CORE_DATA_STREAM::Reset() {
    
    if ( MemoryBuffer ) {
        
        CORE_MEMORY_ALLOCATOR_Free( MemoryBuffer );
        MemoryBuffer = NULL;
    }
    
    Size = 0;
    Offset = 0;
    AllocatedBytes = 0;
}
