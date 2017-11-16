//
//  CORE_HELPERS_CLASS.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"
#include "CORE_DATA_TYPES.h"

#include <string>

XS_CLASS_SERIALIZER_TemplateScalar( int )
XS_CLASS_SERIALIZER_TemplateScalar( bool )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned int )
XS_CLASS_SERIALIZER_TemplateScalar( long int )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned long )
XS_CLASS_SERIALIZER_TemplateScalar( char )
XS_CLASS_SERIALIZER_TemplateScalar( unsigned char )
XS_CLASS_SERIALIZER_TemplateScalar( float )
XS_CLASS_SERIALIZER_TemplateScalar( double )
XS_CLASS_SERIALIZER_TemplateScalar( wchar_t )
XS_CLASS_SERIALIZER_TemplateScalarPointer( char )
XS_CLASS_SERIALIZER_TemplateScalarPointer( float )
XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( char )
XS_CLASS_SERIALIZER_TemplateScalarPointerPointer( wchar_t )


template<> template<>
void XS_CLASS_SERIALIZER< std::string, CORE_DATA_STREAM >::Serialize< std::true_type >( const char * member_name,std::string & type, CORE_DATA_STREAM & stream ) {
    
    stream.InputBytes(type.c_str(), type.length());
}

template<> template<>
void XS_CLASS_SERIALIZER< std::string, CORE_DATA_JSON >::Serialize< std::true_type >( const char * member_name,std::string & type, CORE_DATA_JSON & stream ) {
    
    stream.InputBytes( member_name, (const char *) type.c_str(), type.length());
}

template<> template<>
void XS_CLASS_SERIALIZER< std::string, CORE_DATA_JSON >::Serialize< std::false_type >( const char * member_name,std::string & type, CORE_DATA_JSON & stream ) {
    
    abort();
}

template<> template<>
void XS_CLASS_SERIALIZER< std::string, CORE_DATA_STREAM >::Serialize< std::false_type >( const char * member_name,std::string & type, CORE_DATA_STREAM & stream ) {
    int size;
    char * string;
    
    stream.OutputBytes( &string, size);
    string[size] = 0;
    type = std::string( string );
    type.resize( size );
}
