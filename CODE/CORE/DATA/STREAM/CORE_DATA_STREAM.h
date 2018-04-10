
//
//  CORE_DATA_STREAM.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_DATA_STREAM__
#define __GAME_ENGINE_REBORN__CORE_DATA_STREAM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_TYPES.h"
#include "SERVICE_LOGGER.h"

XS_CLASS_BEGIN( CORE_DATA_STREAM )

CORE_DATA_STREAM();
CORE_DATA_STREAM( int size );
CORE_DATA_STREAM( const char * pointer, int size );
~CORE_DATA_STREAM();

void Open();
void Close();
void Reset();

void InitializeWithSize( int size );

void ResetOffset();
inline void SetOffset( int offset ) {
    Offset=offset;
}

inline size_t GetSize() const {
    return Size;
}
inline size_t GetAllocatedBytes() const {
    return AllocatedBytes;
}

template <typename __TYPE__ >
void operator << ( const __TYPE__ & data ) {

    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {

        AllocatedBytes+=AllocatedBytes + sizeof( __TYPE__ );

        void * new_buffer=realloc( MemoryBuffer, AllocatedBytes );

#if DEBUG
        if ( new_buffer == NULL ) {

            CORE_RUNTIME_Abort();
        }
#endif

        MemoryBuffer=new_buffer;
    }

    //TODO : byteswap :

    CORE_MEMORY_COPY_BYTES_SWAPPED< __TYPE__ >( MemoryBuffer, Offset, data );

    Offset+=sizeof( __TYPE__ );
}

template <typename __TYPE__ >
void operator << ( const __TYPE__ * data ) {

    if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {

        AllocatedBytes+=AllocatedBytes + sizeof( __TYPE__ );

        MemoryBuffer=realloc( MemoryBuffer, AllocatedBytes );

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

    memcpy( &data, ( char* ) MemoryBuffer + Offset, sizeof( __TYPE__ ) );

    Offset+=sizeof( __TYPE__ );
}

void operator >> ( wchar_t ** data ) {

    size_t
        length;

    memcpy( &length, ( ( char* ) MemoryBuffer + Offset ), sizeof( size_t ) );
    Offset+=sizeof( size_t );

    *data=( wchar_t * ) CORE_MEMORY_ALLOCATOR::Allocate( length );

    memcpy( data, ( ( ( char* ) MemoryBuffer ) + Offset ), length );

    Offset+=length;
}

inline const void * GetMemoryBuffer() const {
    return MemoryBuffer;
}
inline void * GetMemoryBuffer() {
    return MemoryBuffer;
}

inline size_t GetOffset() {
    return Offset;
}

void InputBytesWithoutSize( const char * pointer, int size ) {

    size_t
        length=size * sizeof( char );

    if ( AllocatedBytes - Offset < ( size_t ) size ) {

        AllocatedBytes+=AllocatedBytes + size;

        void * new_buffer=realloc( MemoryBuffer, AllocatedBytes );

#if DEBUG
        if ( new_buffer == NULL ) {

            CORE_RUNTIME_Abort();
        }
#endif

        MemoryBuffer=new_buffer;
    }

    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), pointer, length );
    Offset+=length;
}

template < typename __TYPE__ >
void InputBytes( __TYPE__ ** pointer, int size ) {

    size_t
        length=size * sizeof( __TYPE__ );

    if ( AllocatedBytes - Offset < length + sizeof( size_t ) ) {

        AllocatedBytes+=AllocatedBytes + length + sizeof( size_t );

        MemoryBuffer=realloc( MemoryBuffer, AllocatedBytes );

#if DEBUG
        if ( MemoryBuffer == NULL ) {

            CORE_RUNTIME_Abort();
        }
#endif
    }

    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), &length, sizeof( size_t ) );
    Offset+=sizeof( size_t );
    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), *pointer, length );
    Offset+=length;
}

template < typename __TYPE__ >
void OutputBytes( __TYPE__ ** pointer, int & size ) {

    size_t
        length;

    memcpy( &length, ( ( char* ) MemoryBuffer + Offset ), sizeof( size_t ) );
    Offset+=sizeof( size_t );

    *pointer=( __TYPE__ * ) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );

    memcpy( *pointer, ( ( ( char* ) MemoryBuffer ) + Offset ), length );

    Offset+=length;
    size=length;
}

//Stupid fix with size_t
template < typename __TYPE__ >
void InputBytes( __TYPE__ * pointer, size_t size ) {

    unsigned long length=size * sizeof( __TYPE__ );

    if ( AllocatedBytes - Offset < length + sizeof( size_t ) ) {

        AllocatedBytes+=AllocatedBytes + length + sizeof( size_t );

        MemoryBuffer=realloc( MemoryBuffer, AllocatedBytes );

#if DEBUG
        if ( MemoryBuffer == NULL ) {

            CORE_RUNTIME_Abort();
        }
#endif
    }

    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), &length, sizeof( size_t ) );
    Offset+=sizeof( size_t );
    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), ( void* ) pointer, length );
    Offset+=length;
}

template < typename __TYPE__ >
void InputBytes( __TYPE__ * & pointer, int size ) {

    size_t
        length=size * sizeof( __TYPE__ );

    if ( AllocatedBytes - Offset < length + sizeof( size_t ) ) {

        AllocatedBytes+=AllocatedBytes + length + sizeof( size_t );

        MemoryBuffer=realloc( MemoryBuffer, AllocatedBytes );

#if DEBUG
        if ( MemoryBuffer == NULL ) {

            CORE_RUNTIME_Abort();
        }
#endif
    }

    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), &length, sizeof( size_t ) );
    Offset+=sizeof( size_t );
    memcpy( ( ( ( char* ) MemoryBuffer ) + Offset ), ( void* ) pointer, length );
    Offset+=length;
}

template < typename __TYPE__ >
void OutputBytes( __TYPE__ * & pointer, int & size ) {

    size_t
        length;

    memcpy( &length, ( ( char* ) MemoryBuffer + Offset ), sizeof( size_t ) );
    Offset+=sizeof( size_t );

    pointer=( __TYPE__ * ) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );

    memcpy( ( void* ) pointer, ( ( ( char* ) MemoryBuffer ) + Offset ), ( size_t ) length );

    Offset+=length;
    size=length;
}

//Stupid fix with size_t
template < typename __TYPE__ >
void OutputBytes( __TYPE__ * pointer, size_t & size ) {

    size_t
        length;

    memcpy( &length, ( ( char* ) MemoryBuffer + Offset ), sizeof( size_t ) );
    Offset+=sizeof( size_t );

    memcpy( ( void* ) pointer, ( ( ( char* ) MemoryBuffer ) + Offset ), ( size_t ) length );

    Offset+=length;

    size=length;
}

template < typename __TYPE__ >
void OutputBytesWithoutSize( __TYPE__ * pointer, size_t & size ) {

    memcpy( ( void* ) pointer, ( ( ( char* ) MemoryBuffer ) + Offset ), ( size_t ) sizeof( __TYPE__ ) );

    Offset+=sizeof( __TYPE__ );

    size=sizeof( __TYPE__ );
}

void * GetMemoryAtOffset() {

    return ( ( ( char* ) MemoryBuffer ) + Offset );
}

private:

    void
        * MemoryBuffer;
    size_t
        AllocatedBytes,
        Offset,
        Size;

    XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_STREAM__) */

