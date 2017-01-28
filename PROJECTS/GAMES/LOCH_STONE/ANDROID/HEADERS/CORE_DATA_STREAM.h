
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
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_MEMORY.h"

XS_CLASS_BEGIN( CORE_DATA_STREAM )

CORE_DATA_STREAM();
CORE_DATA_STREAM( int size );

void Open();
void Close();

void ResetOffset();

template <typename __TYPE__ >
void operator << ( const __TYPE__ & data ) {
    
    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {
        
        AllocatedBytes += AllocatedBytes + sizeof( __TYPE__ );
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
        #if DEBUG
            if ( MemoryBuffer == NULL ) {
            
                abort();
            }
        #endif
    }
    
    memcpy( ( char* )MemoryBuffer + Offset, &data, sizeof(__TYPE__ ) );
    
    Offset += sizeof( __TYPE__ );
}

void operator << ( const int & data ) {
    
    if ( AllocatedBytes - Offset < sizeof( int ) ) {
        
        AllocatedBytes += AllocatedBytes + sizeof( int );
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            abort();
        }
#endif
    }

    memcpy( ( char* )MemoryBuffer + Offset, &data, sizeof( int ) );
    
    Offset += sizeof( int );
}

template <typename __TYPE__ >
void operator << ( const __TYPE__ * data ) {
    
    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {
        
        AllocatedBytes += AllocatedBytes + sizeof( __TYPE__ );
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            abort();
        }
#endif
    }
    
    abort();
}

void operator << ( const CHAR_ARRAY_POINTER_POINTER data ) {
    
    unsigned long length = strlen( *data );
    
    if ( AllocatedBytes - Offset < length ) {
        
        AllocatedBytes += AllocatedBytes + length;
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            abort();
        }
#endif
    }
    
    memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(unsigned long) );
    Offset  += sizeof(unsigned long);
    memcpy( ((( char* )MemoryBuffer) + Offset), *data, length );
    Offset += length;
}

template <typename __TYPE__ >
void operator >> ( __TYPE__ & data ) {
    
    memcpy( &data, ( char* )MemoryBuffer + Offset, sizeof(__TYPE__ ) );
    
    Offset += sizeof( __TYPE__ );
}

void operator >> ( CHAR_ARRAY_POINTER_POINTER data ) {
    
    unsigned long length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned long) );
    Offset  += sizeof(unsigned long);
    
    *data = (char *) CORE_MEMORY_ALLOCATOR::Allocate( length );
    
    memcpy( *data, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset += length;
}

void operator >> ( wchar_t ** data ) {
    
    unsigned long length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned long) );
    Offset  += sizeof(unsigned long);
    
    *data = (wchar_t *) CORE_MEMORY_ALLOCATOR::Allocate( length );
    
    memcpy( data, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset += length;
}

inline const void * GetMemoryBuffer() const { return MemoryBuffer; }
inline void * GetMemoryBuffer() { return MemoryBuffer; }

inline const int GetOffset() { return Offset; }

template < typename __TYPE__ >
void InputBytes(__TYPE__ ** pointer, int size ) {
    
    unsigned long length = size * sizeof( __TYPE__ );
    
    if ( AllocatedBytes - Offset < length ) {
        
        AllocatedBytes += AllocatedBytes + length;
        
        MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
        
#if DEBUG
        if ( MemoryBuffer == NULL ) {
            
            abort();
        }
#endif
    }
    
    memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(unsigned long) );
    Offset  += sizeof(unsigned long);
    memcpy( ((( char* )MemoryBuffer) + Offset), *pointer, length );
    Offset += length;
}

template < typename __TYPE__ >
void OutputBytes(__TYPE__ ** pointer, int size ) {
    
    int length;
    
    memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(unsigned long) );
    Offset  += sizeof(unsigned long);
    
    *pointer = ( __TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );
    
    memcpy( *pointer, ((( char* )MemoryBuffer) + Offset), length );
    
    Offset  += length;
}

private :

void * MemoryBuffer;
int AllocatedBytes,
    Offset;


XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_STREAM__) */
