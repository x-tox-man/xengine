
//
//  CORE_DATA_STREAM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_DATA_STREAM__
#define __GAME_ENGINE_REBORN__CORE_DATA_STREAM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_MEMORY.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "SERVICE_LOGGER.h"

XS_CLASS_BEGIN( CORE_DATA_STREAM )

CORE_DATA_STREAM();
CORE_DATA_STREAM( int size );
CORE_DATA_STREAM( const char * pointer, int size );
~CORE_DATA_STREAM();

void Open();
void Close();

void Reset();

void ResetOffset();
int GetSize() const { return Size; }
int GetAllocatedBytes() const { return AllocatedBytes; }

template <typename __TYPE__ >
void operator << ( const __TYPE__ & data ) {
    
    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {
        
        AllocatedBytes += AllocatedBytes + sizeof( __TYPE__ );
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
        #if DEBUG
            if ( MemoryBuffer == NULL ) {
            
                CORE_RUNTIME_Abort();
            }
        #endif
    }
    
    //TODO : byteswap :
    
    CORE_MEMORY_COPY_BYTES_SWAPPED< __TYPE__ >( MemoryBuffer, Offset, data );
    
    Offset += sizeof( __TYPE__ );
}

template <typename __TYPE__ >
void operator << ( const __TYPE__ * data ) {
    
    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {
        
        AllocatedBytes += AllocatedBytes + sizeof( __TYPE__ );
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
        #if DEBUG
            if ( MemoryBuffer == NULL ) {
                
                CORE_RUNTIME_Abort();
            }
        #endif
    }
    
    CORE_RUNTIME_Abort();
}

template <typename __TYPE__ >
void operator >> ( __TYPE__ & data ) {
    
    memcpy( &data, ( char* )MemoryBuffer + Offset, sizeof(__TYPE__ ) );
    
    Offset += sizeof( __TYPE__ );
}

void operator >> ( wchar_t ** data ) {
    
    unsigned int length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned int) );
    Offset  += sizeof(unsigned int);
    
    *data = (wchar_t *) CORE_MEMORY_ALLOCATOR::Allocate( length );
    
    memcpy( data, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset += length;
}

inline const void * GetMemoryBuffer() const { return MemoryBuffer; }
inline void * GetMemoryBuffer() { return MemoryBuffer; }

inline const int GetOffset() { return Offset; }

template < typename __TYPE__ >
void InputBytes(__TYPE__ ** pointer, int size ) {
    
    unsigned int length = size * sizeof( __TYPE__ );
    
    if ( AllocatedBytes - Offset < length + sizeof(unsigned int) ) {
        
        AllocatedBytes += AllocatedBytes + length + sizeof(unsigned int);
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            CORE_RUNTIME_Abort();
        }
#endif
    }
    
    memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(unsigned int) );
    Offset  += sizeof(unsigned int);
    memcpy( ((( char* )MemoryBuffer) + Offset), *pointer, length );
    Offset += length;
}

template < typename __TYPE__ >
void OutputBytes(__TYPE__ ** pointer, int size ) {
    
    int length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned int) );
    Offset  += sizeof(unsigned int);
    
    *pointer = ( __TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );
    
    memcpy( *pointer, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset  += length;
}

template < typename __TYPE__ >
void InputBytes(__TYPE__ * & pointer, int size ) {
    
    unsigned int length = size * sizeof( __TYPE__ );
    
    if ( AllocatedBytes - Offset < length + sizeof(unsigned int) ) {
        
        AllocatedBytes += AllocatedBytes + length + sizeof(unsigned int);
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            CORE_RUNTIME_Abort();
        }
#endif
    }
    
    memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(unsigned int) );
    Offset  += sizeof(unsigned int);
    memcpy( ((( char* )MemoryBuffer) + Offset), (void*)pointer, length );
    Offset += length;
}

template < typename __TYPE__ >
void OutputBytes(__TYPE__ * & pointer, int size ) {
    
    int length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned int) );
    Offset  += sizeof(unsigned int);
    
    pointer = ( __TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );
    
    memcpy( (void*)pointer, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset  += length;
}

private :

void * MemoryBuffer;
int AllocatedBytes,
    Offset,
    Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_STREAM__) */
