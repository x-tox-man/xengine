
//
//  CORE_DATA_JSON.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_DATA_JSON__
#define __GAME_ENGINE_REBORN__CORE_DATA_JSON__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_TYPES.h"
#include "SERVICE_LOGGER.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_HELPERS_SCALAR.h"

template <typename __TYPE__>
void XSPrintf( char * string_stream, const char * name, __TYPE__ & value) {
    abort();
}

template <typename __TYPE__>
void XSPrintf( char * string_stream, const char * name, __TYPE__ * & value) {
    abort();
}

template <typename __TYPE__>
void XSPrintf( char * string_stream, const char * name, __TYPE__ ** value) {
    abort();
}

template <typename __TYPE__>
void XSscanf( char * string_stream, const char * name, __TYPE__ & value, int & string_size ) {
    abort();
}

template <typename __TYPE__>
void XSscanf( char * string_stream, const char * name, __TYPE__ * & value, int & string_size ) {
    abort();
}

template <typename __TYPE__>
void XSscanf( char * string_stream, const char * name, __TYPE__ ** value, int & string_size ) {
    abort();
}

template<> void XSPrintf<bool>( char * string_stream, const char * name, bool & value );
template<> void XSPrintf<double>( char * string_stream, const char * name, double & value );
template<> void XSPrintf<float>( char * string_stream, const char * name, float & value );
template<> void XSPrintf<int>( char * string_stream, const char * name, int & value );
template<> void XSPrintf<char>( char * string_stream, const char * name, char & value );
template<> void XSPrintf<char>( char * string_stream, const char * name, char * & value );
template<> void XSPrintf<char>( char * string_stream, const char * name, char ** value );
template<> void XSPrintf<unsigned int>( char * string_stream, const char * name, unsigned int & value );
template<> void XSPrintf<SCALAR>( char * string_stream, const char * name, SCALAR & value );
template<> void XSscanf<bool>( char * string_stream, const char * name, bool & value, int & string_size );
template<> void XSscanf<double>( char * string_stream, const char * name, double & value, int & string_size );
template<> void XSscanf<float>( char * string_stream, const char * name, float & value, int & string_size );
template<> void XSscanf<int>( char * string_stream, const char * name, int & value, int & string_size );
template<> void XSscanf<char>( char * string_stream, const char * name, char & value, int & string_size );
template<> void XSscanf<char>( char * string_stream, const char * name, char ** value, int & string_size );
template<> void XSscanf<char>( char * string_stream, const char * name, char * & value, int & string_size );
template<> void XSscanf<unsigned int>( char * string_stream, const char * name, unsigned int & value, int & string_size );
template<> void XSscanf<SCALAR>( char * string_stream, const char * name, SCALAR & value, int & string_size );

XS_CLASS_BEGIN( CORE_DATA_JSON )

    CORE_DATA_JSON();
    CORE_DATA_JSON( int size );
    CORE_DATA_JSON( const char * pointer, int size );
    ~CORE_DATA_JSON();

    void Open();
    void Close();
    void Reset();

    void InitializeWithSize( int size );

    void ResetOffset();
    int GetSize() const { return Stream.GetSize(); }
    int GetAllocatedBytes() const { return Stream.GetAllocatedBytes(); }

    inline const void * GetMemoryBuffer() const { return Stream.GetMemoryBuffer(); }
    inline void * GetMemoryBuffer() { return Stream.GetMemoryBuffer(); }

    inline const int GetOffset() { return Stream.GetOffset(); }

    template < typename __TYPE__ >
    void InputBytes( const char * name, __TYPE__ & data, int size ) {
        char tmp[256];
        void * mem = (void*) malloc( sizeof( __TYPE__) * size );
        
        tmp[0] = '\0';
        
        memcpy(mem, &data, size );
        
        XSPrintf< __TYPE__ >( tmp, name, data );
        
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
        
        free( mem );
    }

    template < typename __TYPE__ >
    void InputBytes( const char * name, __TYPE__ ** pointer, int size ) {
        
        char tmp[256];
        
        tmp[0] = '\0';
        
        XSPrintf< __TYPE__ >( tmp, name, pointer );
        
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
    }

    template < typename __TYPE__ >
    void OutputBytes( const char * name, __TYPE__ ** pointer, int & size ) {
        
        int string_size = 0;
        XSscanf( (char * ) Stream.GetMemoryAtOffset(), name, pointer, string_size );
        
        Stream.SetOffset( Stream.GetOffset() + string_size);
    }

    //Stupid fix with size_t
    template < typename __TYPE__ >
    void InputBytes( const char * name, __TYPE__ * pointer, X_VERY_LONG size ) {
        
        char tmp[256];
        
        tmp[0] = '\0';
        
        XSPrintf< __TYPE__ >( tmp, name, *(pointer) );
        
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
    }

    template < typename __TYPE__ >
    void InputBytes( const char * name, __TYPE__ * & pointer, int size ) {
        
        char tmp[256];
        
        tmp[0] = '\0';
        
        XSPrintf< __TYPE__ >( tmp, name, pointer );
        
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
    }

    template < typename __TYPE__ >
    void OutputBytes( const char * name, __TYPE__ * & pointer, int & size ) {
        
        int string_size = 0;
        XSscanf( (char * ) Stream.GetMemoryAtOffset(), name, pointer, string_size );
        
        Stream.SetOffset( Stream.GetOffset() + string_size);
    }

    template < typename __TYPE__ >
    void OutputBytes( const char * name, __TYPE__ & pointer, int & size ) {
        
        int string_size = 0;
        XSscanf( (char * ) Stream.GetMemoryAtOffset(), name, pointer, string_size );
        
        Stream.SetOffset( Stream.GetOffset() + string_size);
    }

    void PushObject( const char * object_name );
    void PopObject();
    void PushArray( const char * object_name );
    void PopArray();
    void AppendMember();

    void ReadObject( const char * object_name );
    void ReadEndObject();
    void ReadArray( const char * object_name );
    void ReadEndArray();
    void ReadMember();

    private :

        CORE_DATA_STREAM
            Stream;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_DATA_JSON__) */
