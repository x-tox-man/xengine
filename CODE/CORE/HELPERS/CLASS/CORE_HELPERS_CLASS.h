//
//  Header.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 23/11/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_XS_CLASS_h
#define GAME_ENGINE_REBORN_XS_CLASS_h

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_TYPES.h"

class CORE_DATA_STREAM;
class CORE_DATA_JSON;

template< typename __CLASS_TYPE__, typename __STREAM__TYPE_ >
class XS_CLASS_SERIALIZER;

template<typename T>
struct XS_TYPE_
{
    typedef T Type;
};

template<typename T>
struct XS_TYPE_< T* >
{
    typedef typename XS_TYPE_< T >::Type Type;
};

template<typename T>
struct XS_TYPE_< T& >
{
    typedef typename XS_TYPE_< T >::Type Type;
};

#define XS_CLASS_BEGIN( __CLASS_NAME__ ) \
class __CLASS_NAME__ \
{ \
private : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
public : \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_STREAM >; \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_JSON >; \
    typedef __CLASS_NAME__ * PTR; \

#define XS_CLASS_BEGIN_WITH_COPY( __CLASS_NAME__ ) \
class __CLASS_NAME__ \
{ \
    public : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    typedef __CLASS_NAME__ * PTR; \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_STREAM >; \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_JSON >; \

#define XS_CLASS_BEGIN_WITH_ANCESTOR( __CLASS_NAME__, __ANCESTOR__ ) \
class __CLASS_NAME__: public __ANCESTOR__ \
{ \
private : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    __CLASS_NAME__( const __ANCESTOR__ & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
    void operator =( const __ANCESTOR__ & other ); \
public : \
friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_STREAM >; \
friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_JSON >; \
    typedef __CLASS_NAME__ * PTR; \

#define XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( __CLASS_NAME__, __ANCESTOR__ ) \
class __CLASS_NAME__: public __ANCESTOR__ \
{ \
    private : \
    __CLASS_NAME__( const __ANCESTOR__ & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
    void operator =( const __ANCESTOR__ & other ); \
    public : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_STREAM >; \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_JSON >; \
    typedef __CLASS_NAME__ * PTR; \

#define XS_CLASS_BEGIN_WITH_ANCESTOR_2( __CLASS_NAME__, __ANCESTOR__, __ANCESTOR__2 ) \
class __CLASS_NAME__: public __ANCESTOR__, public __ANCESTOR__2 \
{ \
    private : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    __CLASS_NAME__( const __ANCESTOR__ & other ); \
    __CLASS_NAME__( const __ANCESTOR__2 & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
    void operator =( const __ANCESTOR__ & other ); \
    void operator =( const __ANCESTOR__2 & other ); \
    public : \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_STREAM >; \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__, CORE_DATA_JSON >; \
    typedef __CLASS_NAME__ * PTR; \

#define XS_CLASS_END \
};

#define Scalar_SGet( __TYPE__, __ACCESS_NAME__ ) \
    private : \
        __TYPE__ __ACCESS_NAME__; \
    public : \
        const __TYPE__ & Get##__ACCESS_NAME__( void ) const { return __ACCESS_NAME__; } \
        __TYPE__ & Get##__ACCESS_NAME__( void ) { return __ACCESS_NAME__; } \
        void Set##__ACCESS_NAME__( const __TYPE__ & parameter ) { __ACCESS_NAME__ = parameter; } \

#define DEFINE_SGet( __TYPE__, __ACCESS_NAME__ ) \
    private : \
    __TYPE__ __ACCESS_NAME__; \
    public : \
    const __TYPE__ & Get##__ACCESS_NAME__( void ) const { return __ACCESS_NAME__; } \
    __TYPE__ & Get##__ACCESS_NAME__( void ) { return __ACCESS_NAME__; } \
    void Set##__ACCESS_NAME__( const __TYPE__ & parameter ) { __ACCESS_NAME__ = parameter; } \

#define Pointer_SGet( __TYPE__, __ACCESS_NAME__ ) \
private : \
    __TYPE__ * __ACCESS_NAME__; \
public : \
    const __TYPE__ & get##__ACCESS_NAME__( void ) const { return *__ACCESS_NAME__; } \
    void set##__ACCESS_NAME__( const __TYPE__ & parameter ) { __ACCESS_NAME__ = parameter; } \

#define XS_DEFINE_SERIALIZABLE \
    public : \
        void Serialize( const char * member_name, CORE_DATA_STREAM & stream ); \
        void UnSerialize( const char * member_name, CORE_DATA_STREAM & stream ); \
        void Serialize( const char * member_name, CORE_DATA_JSON & stream ); \
        void UnSerialize( const char * member_name, CORE_DATA_JSON & stream ); \
        template< typename __BOOLEAN_TYPE__, typename __STREAM__TYPE_ > \
        void SerializeMemoryLayout( __STREAM__TYPE_ & stream ); \

#define XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( __TYPE__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
        type.Serialize( member_name, stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
        (*type)->Serialize( member_name, stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val = 1; \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::true_type >( "val", val, stream ); \
            (*type).Serialize( member_name, stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::true_type >( "val", val, stream ); \
        }\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ *, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val = 1; \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::true_type >( "val", val, stream ); \
            (*type).Serialize( member_name, stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::true_type >( "val", val, stream ); \
        }\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
        type.UnSerialize( member_name, stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
        *type = new __TYPE__; \
        (*type)->UnSerialize( member_name, stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val; \
        XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::false_type >( "val", val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( member_name, stream ); \
        } \
        else { \
            type = NULL; \
        }\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ *, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val; \
        XS_CLASS_SERIALIZER< char, CORE_DATA_STREAM >::Serialize< std::false_type >( "val", val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( member_name, stream ); \
        } \
        else { \
            type = NULL; \
        }\
    } \
    template<> template<>\
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream, int size ) { \
    \
        unsigned int array_size = size; \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "array_size", array_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < array_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( "", type[ __std_v_index ], stream ); \
    } \
    template<> template<>\
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream, int size ) { \
    \
        unsigned int array_size; \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::false_type >( "array_size", array_size, stream ); \
        type = (__TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( array_size * sizeof( __TYPE__ ) ); \
        for ( size_t __std_v_index = 0; __std_v_index < array_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__TYPE__, type[ __std_v_index ], stream ); \
    } \
    void __TYPE__::UnSerialize( const char * member_name, CORE_DATA_STREAM & stream ) { \
        SerializeMemoryLayout< std::false_type >( stream ); \
    } \
    void __TYPE__::Serialize( const char * member_name, CORE_DATA_STREAM & stream ) { \
        SerializeMemoryLayout< std::true_type >( stream ); \
    } \
    \
    \
    \
    \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ & type, CORE_DATA_JSON & stream ) { \
        stream.AppendMember(); \
        stream.PushObject( member_name ); \
        type.Serialize( member_name, stream ); \
        stream.PopObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream ) { \
        stream.AppendMember(); \
        stream.PushObject( member_name ); \
        (*type)->Serialize( member_name, stream ); \
        stream.PopObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
        char val = 1; \
        stream.PushObject( member_name ); \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::true_type >( "pointer", val, stream ); \
            (*type).Serialize( member_name, stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::true_type >( "pointer", val, stream ); \
        }\
        stream.PopObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ *, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
        stream.PushObject( member_name ); \
        char val = 1; \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::true_type >( "pointer", val, stream ); \
            (*type).Serialize( member_name, stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::true_type >( "pointer", val, stream ); \
        }\
        stream.PopObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ & type, CORE_DATA_JSON & stream ) { \
        stream.ReadMember(); \
        stream.ReadObject( member_name ); \
        type.UnSerialize( member_name, stream ); \
        stream.ReadEndObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream ) { \
        *type = new __TYPE__; \
        stream.ReadMember(); \
        stream.ReadObject( member_name ); \
        (*type)->UnSerialize( member_name, stream ); \
        stream.ReadEndObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
        char val; \
        stream.ReadMember(); \
        stream.ReadObject( member_name ); \
        XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::false_type >( "pointer", val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( member_name, stream ); \
        } \
        else { \
            type = NULL; \
        }\
        stream.ReadEndObject(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ *, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
        char val; \
        stream.ReadMember(); \
        stream.ReadObject( member_name ); \
        XS_CLASS_SERIALIZER< char, CORE_DATA_JSON >::Serialize< std::false_type >( "pointer", val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( member_name, stream ); \
        } \
        else { \
            type = NULL; \
        }\
        stream.ReadEndObject(); \
    } \
    template<> template<>\
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream, int size ) { \
        unsigned int array_size = size; \
        stream.PushArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "array_size", array_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < array_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( "", type[ __std_v_index ], stream ); \
        stream.PopArray(); \
    } \
    template<> template<>\
    void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream, int size ) { \
    \
        unsigned int array_size; \
        stream.ReadArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "array_size", array_size, stream ); \
        if ( array_size > 0 ) { \
            type = (__TYPE__ *) CORE_MEMORY_ALLOCATOR::Allocate( array_size * sizeof( __TYPE__ ) ); \
            for ( size_t __std_v_index = 0; __std_v_index < array_size; __std_v_index++ ) { \
                XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( #__TYPE__, type[ __std_v_index ], stream ); \
            } \
        } \
        stream.ReadEndArray(); \
    } \
    void __TYPE__::UnSerialize( const char * member_name, CORE_DATA_JSON & stream ) { \
        SerializeMemoryLayout< std::false_type >( stream ); \
    } \
    void __TYPE__::Serialize( const char * member_name, CORE_DATA_JSON & stream ) { \
        SerializeMemoryLayout< std::true_type >( stream ); \
    } \
    \
    \
    \
    template<typename __BOOLEAN_TYPE__, typename __STREAM__TYPE_ > \
    void __TYPE__::SerializeMemoryLayout( __STREAM__TYPE_ & stream ) {

#define XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( __TYPE__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) type.size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__TYPE__, type[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) type->size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__TYPE__, (*type)[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) (*type)->size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__TYPE__, (*(*type))[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) type.size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        type.resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__TYPE__, type[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) type->size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        type->resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__TYPE__, (*type)[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        unsigned int vector_size = (int) (*type)->size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        (*type)->resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__TYPE__, (*(*type))[ __std_v_index ], stream ); \
    } \
    \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > & type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = (int) type.size(); \
        stream.PushArray( member_name ); \
        stream.PushObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        stream.PopObject(); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( NULL, type[ __std_v_index ], stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > * & type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = (int) type->size(); \
        stream.PushArray( member_name ); \
        stream.PushObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        stream.PopObject(); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( NULL, (*type)[ __std_v_index ], stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::vector< __TYPE__ > ** type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = (int) (*type)->size(); \
        stream.PushArray( member_name ); \
        stream.PushObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "vector_size", vector_size, stream ); \
        stream.PopObject(); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( NULL, (*(*type))[ __std_v_index ], stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > & type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = 0; \
        stream.ReadArray( member_name ); \
        stream.ReadObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        stream.ReadEndObject(); \
        type.resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( NULL, type[ __std_v_index ], stream ); \
        } \
        stream.ReadEndArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > * & type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = 0; \
        stream.ReadArray( member_name ); \
        stream.ReadObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        stream.ReadEndObject(); \
        type->resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( NULL, (*type)[ __std_v_index ], stream ); \
        } \
        stream.ReadEndArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::vector< __TYPE__ > ** type, CORE_DATA_JSON & stream ) { \
        unsigned int vector_size = 0; \
        stream.ReadArray( member_name ); \
        stream.ReadObject( "" ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "vector_size", vector_size, stream ); \
        stream.ReadEndObject(); \
        (*type)->resize( vector_size ); \
        for ( size_t __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) {\
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( NULL, (*(*type))[ __std_v_index ], stream ); \
        } \
        stream.ReadEndArray(); \
    }

#define XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( __TYPE__, __KEY__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned int map_size = (int) type.size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=type.begin(); it!=type.end(); it++ ) { \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__TYPE__, it->second, stream ); \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned int map_size = (int) type->size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::true_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it = type->begin(); it != type->end(); it++ ) { \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( #__TYPE__, it->second, stream ); \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        CORE_RUNTIME_Abort(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned int map_size = (int) type.size(); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_STREAM >::Serialize< std::false_type >( "map_size", map_size, stream ); \
        for ( size_t __std_v_index = 0; __std_v_index < map_size; __std_v_index++ ) { \
            __KEY__ key; \
            __TYPE__ item; \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__KEY__, key, stream ); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( #__TYPE__, item, stream ); \
            type[ key ] = item; \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        CORE_RUNTIME_Abort();\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        CORE_RUNTIME_Abort(); \
    }\
    \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > & type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = (int) type.size(); \
        stream.PushArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=type.begin(); it!=type.end(); it++ ) { \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::true_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = (int) type->size(); \
        stream.PushArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=(*type).begin(); it!=type->end(); it++ ) { \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::true_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = (int) (*type)->size(); \
        stream.PushArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::true_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=(*(*type)).begin(); it!=(*type)->end(); it++ ) { \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::true_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.AppendMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.PopArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > & type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = 0; \
        stream.ReadArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=type.begin(); it!=type.end(); it++ ) { \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::false_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.ReadEndArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = 0; \
        stream.ReadArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=(*type).begin(); it!=type->end(); it++ ) { \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::false_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.ReadEndArray(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ >, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_JSON & stream ) { \
        unsigned int map_size = 0; \
        stream.ReadArray( member_name ); \
        XS_CLASS_SERIALIZER< unsigned int, CORE_DATA_JSON >::Serialize< std::false_type >( "map_size", map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=(*(*type)).begin(); it!=(*type)->end(); it++ ) { \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __KEY__, CORE_DATA_JSON >::Serialize< std::false_type >( #__KEY__, *(const_cast< __KEY__ * >( &it->first )), stream ); \
            stream.ReadMember(); \
            XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( #__TYPE__, it->second, stream ); \
        } \
        stream.ReadEndArray(); \
    }

#define XS_DEFINE_ClassMember( __MEMBER_NAME__, __TYPE__, __MEMBER__ ) \
    XS_CLASS_SERIALIZER< __TYPE__, __STREAM__TYPE_ >::template Serialize< __BOOLEAN_TYPE__ >( __MEMBER_NAME__, __MEMBER__, stream );
#define XS_DEFINE_ClassMemberArray( __MEMBER_NAME__, __TYPE__, __MEMBER__, __SIZE_T__ ) \
    XS_CLASS_SERIALIZER< __TYPE__, __STREAM__TYPE_ >::template Serialize< __BOOLEAN_TYPE__ >( __MEMBER_NAME__, __MEMBER__, stream, __SIZE_T__ );

#define XS_END_INTERNAL_MEMORY_LAYOUT }

#define XS_CLASS_SERIALIZER_TemplateScalar( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type;\
}\
\
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ & type, CORE_DATA_JSON & stream ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, sizeof( __TYPE__ ) ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ & type, CORE_DATA_JSON & stream ) { \
\
    int size = 0; \
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size ); \
}

#define XS_CLASS_SERIALIZER_TemplateScalarPointer( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream, int size ) { \
\
stream.InputBytes( (__TYPE__ * &) type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_STREAM & stream, int size ) { \
\
stream.OutputBytes( (__TYPE__ * &) type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ * type, CORE_DATA_STREAM & stream, size_t size ) { \
\
stream.InputBytes( (__TYPE__ *) type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ * type, CORE_DATA_STREAM & stream, size_t size ) { \
\
    stream.OutputBytes( (__TYPE__ *) type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream, int size ) { \
\
    stream.InputBytes( type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream, int size ) { \
\
    stream.OutputBytes( type, size ); \
}\
\
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, sizeof( __TYPE__ ) ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream ) { \
\
    int size = 0; \
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream, int size ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * & type, CORE_DATA_JSON & stream, int size ) { \
\
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ * type, CORE_DATA_JSON & stream, size_t size ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ * type, CORE_DATA_JSON & stream, size_t size ) { \
\
    int size_read = 0; \
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size_read ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream, int size ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream, int size ) { \
\
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size ); \
}

#define XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type; \
}\
\
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream ) { \
\
    stream.AppendMember(); \
    stream.InputBytes( member_name, type, sizeof( __TYPE__ ) ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name, __TYPE__ ** type, CORE_DATA_JSON & stream ) { \
\
    int size = 0; \
    stream.ReadMember(); \
    stream.OutputBytes( member_name, type, size ); \
}\
\

template< typename __CLASS_TYPE__, typename __STREAM__TYPE_ >
class XS_CLASS_SERIALIZER
{
public:
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ & type, __STREAM__TYPE_ & stream );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ ** type, __STREAM__TYPE_ & stream, int size );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ * & type, __STREAM__TYPE_ & stream, int size );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ * type, __STREAM__TYPE_ & stream, size_t size );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ ** type, __STREAM__TYPE_ & stream );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( const char * member_name, __CLASS_TYPE__ * & type, __STREAM__TYPE_ & stream );
    
    static int GetClassSize() {
        
        return sizeof( __CLASS_TYPE__ );
    }
};

template< typename __CLASS_TO_TEST__ >
class XS_CLASS_TEMPLATE_SINGLETON {
    
    typedef char HasNoInstance;
    typedef long HasInstance;
    
	#if PLATFORM_WINDOWS || PLATFORM_ANDROID
		template < typename C > static HasInstance TestInstance( decltype( &C::GetInstance ) );
	#else
		template <typename C> static HasInstance TestInstance(typeof(&C::GetInstance));
	#endif

	template <typename C> static HasNoInstance TestInstance(...);

    public :
    
    // If the "sizeof" of the result of calling test<T>(nullptr) would be equal to sizeof(yes),
    // the first overload worked and T has a nested type named foobar.
    static const bool IsSingleton = sizeof( TestInstance< __CLASS_TO_TEST__ >( nullptr ) ) == sizeof( HasInstance );
    enum IsSingleton {
		Value = sizeof(TestInstance< __CLASS_TO_TEST__ >( nullptr ) ) == sizeof( HasInstance )
    };
};

#endif
