
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
    inline void SetOffset( int offset ) { Offset = offset; }

    inline X_VERY_LONG GetSize() const { return Size; }
    inline X_VERY_LONG & GetSize() { return Size; }
    inline X_VERY_LONG GetAllocatedBytes() const { return AllocatedBytes; }

    template <typename __TYPE__ >
    void operator << ( const __TYPE__ & data ) {
        
        if ( AllocatedBytes - Offset < sizeof( __TYPE__ ) ) {
            
            AllocatedBytes += AllocatedBytes + sizeof( __TYPE__ );
            
            void * new_buffer = realloc( MemoryBuffer, AllocatedBytes );
            
            #if DEBUG
                if ( new_buffer == NULL ) {
                
                    CORE_RUNTIME_Abort();
                }
            #endif
            
            MemoryBuffer = new_buffer;
        }
        
        // TODO: byteswap :
        
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
        
        X_VERY_LONG
            length;
        
        memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        
        *data = (wchar_t *) CORE_MEMORY_ALLOCATOR::Allocate( length );
        
        memcpy( data, ((( char* )MemoryBuffer) + Offset), length );
        
        Offset += length;
    }

    inline const void * GetMemoryBuffer() const { return MemoryBuffer; }
    inline void * GetMemoryBuffer() { return MemoryBuffer; }

    inline X_VERY_LONG GetOffset() { return Offset; }

    void InputBytesWithoutSize( const char * pointer, int size ) {
        
        X_VERY_LONG
            length = size * sizeof( char );
        
        if ( AllocatedBytes - Offset < (X_VERY_LONG) size ) {
            
            AllocatedBytes += AllocatedBytes + size;
            
            void * new_buffer = realloc( MemoryBuffer, AllocatedBytes );
            
#if DEBUG
            if ( new_buffer == NULL ) {
                
                CORE_RUNTIME_Abort();
            }
#endif
            
            MemoryBuffer = new_buffer;
        }
        
        memcpy( ((( char* )MemoryBuffer) + Offset), pointer, length );
        Offset += length;;
    }

    template < typename __TYPE__ >
    void InputBytes(__TYPE__ ** pointer, int size ) {
        
        X_VERY_LONG
            length = size * sizeof( __TYPE__ );
        
        if ( AllocatedBytes - Offset < length + sizeof(X_VERY_LONG) ) {
            
            AllocatedBytes += AllocatedBytes + length + sizeof(X_VERY_LONG);
            
            MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
            
    #if DEBUG
            if ( MemoryBuffer == NULL ) {
                
                CORE_RUNTIME_Abort();
            }
    #endif
        }
        
        memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        memcpy( ((( char* )MemoryBuffer) + Offset), *pointer, length );
        Offset += length;
    }

    template < typename __TYPE__ >
    void OutputBytes(__TYPE__ ** pointer, int & size ) {
        
        X_VERY_LONG
            length;
        
        memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        
        *pointer = ( __TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );
        
        memcpy( *pointer, ((( char* )MemoryBuffer) + Offset), length );
        
        Offset  += length;
        size = (int) length;
    }

    //Stupid fix with X_VERY_LONG
    template < typename __TYPE__ >
    void InputBytes(__TYPE__ * pointer, X_VERY_LONG size ) {
        
        X_VERY_LONG length = size * sizeof( __TYPE__ );
        
        if ( AllocatedBytes - Offset < length + sizeof(X_VERY_LONG) ) {
            
            AllocatedBytes += AllocatedBytes + length + sizeof(X_VERY_LONG);
            
            MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
            
    #if DEBUG
            if ( MemoryBuffer == NULL ) {
                
                CORE_RUNTIME_Abort();
            }
    #endif
        }
        
        memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        memcpy( ((( char* )MemoryBuffer) + Offset), (void*)pointer, length );
        Offset += length;
    }

    template < typename __TYPE__ >
    void InputBytes(__TYPE__ * & pointer, int size ) {
        
        X_VERY_LONG
            length = size * sizeof( __TYPE__ );
        
        if ( AllocatedBytes - Offset < length + sizeof(X_VERY_LONG) ) {
            
            AllocatedBytes += AllocatedBytes + length + sizeof(X_VERY_LONG);
            
            MemoryBuffer = realloc( MemoryBuffer, AllocatedBytes );
            
    #if DEBUG
            if ( MemoryBuffer == NULL ) {
                
                CORE_RUNTIME_Abort();
            }
    #endif
        }
        
        memcpy( ((( char* )MemoryBuffer) + Offset), &length, sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        memcpy( ((( char* )MemoryBuffer) + Offset), (void*)pointer, length );
        Offset += length;
    }

    template < typename __TYPE__ >
    void OutputBytes(__TYPE__ * & pointer, int & size ) {
        
        X_VERY_LONG
            length;
        
        memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        
        pointer = ( __TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( length * sizeof( __TYPE__ ) );
        
        memcpy( (void*)pointer, ((( char* )MemoryBuffer) + Offset), (X_VERY_LONG) length );
        
        Offset  += length;
        size = (int) length;
    }

    //Stupid fix with X_VERY_LONG
    template < typename __TYPE__ >
    void OutputBytes(__TYPE__ * pointer, X_VERY_LONG & size ) {
        
        X_VERY_LONG
            length;
        
        memcpy( &length, (( char* )MemoryBuffer + Offset), sizeof(X_VERY_LONG) );
        Offset  += sizeof(X_VERY_LONG);
        
        memcpy( (void*)pointer, ((( char* )MemoryBuffer) + Offset), (X_VERY_LONG) length );
        
        Offset  += length;
        
        size = length;

    }

    template < typename __TYPE__ >
    void OutputBytesWithoutSize(__TYPE__ * pointer, X_VERY_LONG & size ) {
        
        memcpy( (void*)pointer, ((( char* )MemoryBuffer) + Offset), (X_VERY_LONG) sizeof( __TYPE__ ) );
        
        Offset  += sizeof( __TYPE__ );
        
        size = sizeof( __TYPE__ );
    }

    void * GetMemoryAtOffset() {
        
        return ((( char* )MemoryBuffer) + Offset);
    }

private :

    void
        * MemoryBuffer;
    X_VERY_LONG
        AllocatedBytes,
        Offset,
        Size;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_STREAM__) */
