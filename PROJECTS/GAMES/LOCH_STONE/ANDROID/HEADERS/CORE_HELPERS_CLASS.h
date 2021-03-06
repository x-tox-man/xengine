//
//  Header.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/11/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_XS_CLASS_h
#define GAME_ENGINE_REBORN_XS_CLASS_h

#include "CORE_RUNTIME_ENVIRONMENT.h"

class CORE_DATA_STREAM;
template< typename __CLASS_TYPE__ >
class XS_CLASS_SERIALIZER;

#define XS_CLASS_BEGIN( __CLASS_NAME__ ) \
class __CLASS_NAME__ \
{ \
private : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
public : \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__ >; \
    typedef __CLASS_NAME__ * PTR;

#define XS_CLASS_BEGIN_WITH_COPY( __CLASS_NAME__ ) \
class __CLASS_NAME__ \
{ \
    public : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    typedef __CLASS_NAME__ * PTR;

#define XS_CLASS_BEGIN_WITH_ANCESTOR( __CLASS_NAME__, __ANCESTOR__ ) \
class __CLASS_NAME__: public __ANCESTOR__ \
{ \
private : \
    __CLASS_NAME__( const __CLASS_NAME__ & other ); \
    __CLASS_NAME__( const __ANCESTOR__ & other ); \
    void operator =( const __CLASS_NAME__ & other ); \
    void operator =( const __ANCESTOR__ & other ); \
public : \
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__ >; \
    typedef __CLASS_NAME__ * PTR;

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
    friend class XS_CLASS_SERIALIZER< __CLASS_NAME__ >; \
    typedef __CLASS_NAME__ * PTR;

#define XS_CLASS_END \
};

#define Scalar_SGet( __TYPE__, __ACCESS_NAME__ ) \
    private : \
        __TYPE__ __ACCESS_NAME__; \
    public : \
        const __TYPE__ & get##__ACCESS_NAME__( void ) const { return __ACCESS_NAME__; } \
        void set##__ACCESS_NAME__( const __TYPE__ & parameter ) { __ACCESS_NAME__ = parameter; } \

#define Pointer_SGet( __TYPE__, __ACCESS_NAME__ ) \
private : \
    __TYPE__ * __ACCESS_NAME__; \
public : \
    const __TYPE__ & get##__ACCESS_NAME__( void ) const { return *__ACCESS_NAME__; } \
    void set##__ACCESS_NAME__( const __TYPE__ & parameter ) { __ACCESS_NAME__ = parameter; } \

#define XS_DEFINE_SERIALIZABLE \
    public : \
        void Serialize( CORE_DATA_STREAM & stream ); \
        void UnSerialize( CORE_DATA_STREAM & stream ); \
        template< typename __BOOLEAN_TYPE__ > \
        void SerializeMemoryLayout( CORE_DATA_STREAM & stream ); \

#define XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( __TYPE__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
        type.Serialize( stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
        (*type)->Serialize( stream ); \
    } \
    template <> template <> \
        void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val = 1; \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char >::Serialize< std::true_type >( val, stream ); \
            (*type).Serialize( stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char >::Serialize< std::true_type >( val, stream ); \
        }\
    } \
    template <> template <> \
        void XS_CLASS_SERIALIZER< __TYPE__ * >::Serialize< std::true_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val = 1; \
        if( type != NULL ) { \
            XS_CLASS_SERIALIZER< char >::Serialize< std::true_type >( val, stream ); \
            (*type).Serialize( stream ); \
        } \
        else { \
            val = 0; \
            XS_CLASS_SERIALIZER< char >::Serialize< std::true_type >( val, stream ); \
        }\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
        type.UnSerialize( stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
        *type = new __TYPE__; \
        (*type)->UnSerialize( stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val; \
        XS_CLASS_SERIALIZER< char >::Serialize< std::false_type >( val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( stream ); \
        } \
        else { \
            type = NULL; \
        }\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< __TYPE__ * >::Serialize< std::false_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
        char val; \
        XS_CLASS_SERIALIZER< char >::Serialize< std::false_type >( val, stream ); \
        if ( val == 1 ) { \
            type = new __TYPE__; \
            (*type).UnSerialize( stream ); \
        } \
        else { \
            type = NULL; \
        }\
    } \
    void __TYPE__::UnSerialize( CORE_DATA_STREAM & stream ) { \
        SerializeMemoryLayout< std::false_type >( stream ); \
    } \
    void __TYPE__::Serialize( CORE_DATA_STREAM & stream ) { \
        SerializeMemoryLayout< std::true_type >( stream ); \
    } \
    template<typename __BOOLEAN_TYPE__ > \
    void __TYPE__::SerializeMemoryLayout( CORE_DATA_STREAM & stream ) {

#define XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( __TYPE__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::true_type >( std::vector< __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = type.size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::true_type >( vector_size, stream ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( type[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::true_type >( std::vector< __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = type->size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::true_type >( vector_size, stream ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( (*type)[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::true_type >( std::vector< __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = (*type)->size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::true_type >( vector_size, stream ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( (*(*type))[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::false_type >( std::vector< __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = type.size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::false_type >( vector_size, stream ); \
        type.resize( vector_size ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( type[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::false_type >( std::vector< __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = type->size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::false_type >( vector_size, stream ); \
        type->resize( vector_size ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( (*type)[ __std_v_index ], stream ); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::vector< __TYPE__ > >::Serialize< std::false_type >( std::vector< __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        unsigned long vector_size = (*type)->size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::false_type >( vector_size, stream ); \
        (*type)->resize( vector_size ); \
        for ( int __std_v_index = 0; __std_v_index < vector_size; __std_v_index++ ) \
        XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( (*(*type))[ __std_v_index ], stream ); \
    }

#define XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT( __TYPE__, __KEY__ ) \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::true_type >( std::map< __KEY__, __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned long map_size = type.size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::true_type >( map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it=type.begin(); it!=type.end(); ++it ) { \
            XS_CLASS_SERIALIZER< __KEY__ >::Serialize< std::true_type >( *(const_cast< __KEY__ * >( &it->first )), stream ); \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( it->second, stream ); \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::true_type >( std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        unsigned long map_size = type->size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::true_type >( map_size, stream ); \
        for ( std::map< __KEY__, __TYPE__ >::iterator it = type->begin(); it != type->end(); ++it ) { \
            XS_CLASS_SERIALIZER< __KEY__ >::Serialize< std::true_type >( *(const_cast< __KEY__ * >( &it->first )), stream ); \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( it->second, stream ); \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::true_type >( std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        abort(); \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::false_type >( std::map< __KEY__, __TYPE__ > & type, CORE_DATA_STREAM & stream ) { \
        unsigned long map_size = type.size(); \
        XS_CLASS_SERIALIZER< unsigned long >::Serialize< std::false_type >( map_size, stream ); \
        for ( int __std_v_index = 0; __std_v_index < map_size; __std_v_index++ ) { \
            __KEY__ key; \
            __TYPE__ item; \
            XS_CLASS_SERIALIZER< __KEY__ >::Serialize< std::false_type >( key, stream ); \
            XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( item, stream ); \
            type[ key ] = item; \
        } \
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::false_type >( std::map< __KEY__, __TYPE__ > * & type, CORE_DATA_STREAM & stream ) { \
        abort();\
    } \
    template <> template <> \
    void XS_CLASS_SERIALIZER< std::map< __KEY__, __TYPE__ > >::Serialize< std::false_type >( std::map< __KEY__, __TYPE__ > ** type, CORE_DATA_STREAM & stream ) { \
        abort(); \
    }

#define XS_DEFINE_ClassMember( __TYPE__, __MEMBER__ ) \
    XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< __BOOLEAN_TYPE__ >( __MEMBER__, stream );
#define XS_DEFINE_ClassMemberArray( __TYPE__, __MEMBER__, __SIZE_T__ ) \
    XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< __BOOLEAN_TYPE__ >( __MEMBER__, stream, __SIZE_T__ );

#define XS_END_INTERNAL_MEMORY_LAYOUT }

#define XS_CLASS_SERIALIZER_TemplateScalar( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ & type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type;\
}

#define XS_CLASS_SERIALIZER_TemplateScalarPointer( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ * & type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream, int size ) { \
\
    stream.InputBytes( type, size ); \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream, int size ) { \
\
    stream.OutputBytes( type, size ); \
}

#define XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( __TYPE__ ) \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::true_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
\
    stream << type; \
} \
template<> template<>\
void XS_CLASS_SERIALIZER< __TYPE__ >::Serialize< std::false_type >( __TYPE__ ** type, CORE_DATA_STREAM & stream ) { \
\
    stream >> type; \
}

template< typename __CLASS_TYPE__ >
class XS_CLASS_SERIALIZER
{
public:
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( __CLASS_TYPE__ & type, CORE_DATA_STREAM & stream );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( __CLASS_TYPE__ ** type, CORE_DATA_STREAM & stream, int size );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( __CLASS_TYPE__ * & type, CORE_DATA_STREAM & stream, int size );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( __CLASS_TYPE__ ** type, CORE_DATA_STREAM & stream );
    
    template<typename __BOOLEAN_TYPE__ >
    static void Serialize( __CLASS_TYPE__ * & type, CORE_DATA_STREAM & stream );
    
    static int GetClassSize() {
        
        return sizeof( __CLASS_TYPE__ );
    }
};

#endif
