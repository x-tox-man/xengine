//
//  CORE_DATA_JSON.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_DATA_JSON.h"
#include "CORE_MEMORY.h"
#include <string>

template<>
void XSPrintf<bool>( char * string_stream, const char * name, bool & value) {
    if ( value ) {
        sprintf( string_stream, "\"%s\":true", name );
    }else {
        sprintf( string_stream, "\"%s\":false", name );
    }
}

template<>
void XSPrintf<double>( char * string_stream, const char * name, double & value) {
    
    sprintf( string_stream, "\"%s\":%f", name, value );
}

template<>
void XSPrintf<float>( char * string_stream, const char * name, float & value) {
    
    sprintf( string_stream, "\"%s\":%f", name, value );
}

template<>
void XSPrintf<int>( char * string_stream, const char * name, int & value) {
    
    sprintf( string_stream, "\"%s\":%d", name, value );
}

template<>
void XSPrintf<char>( char * string_stream, const char * name, char & value) {
    
    sprintf( string_stream, "\"%s\":\"%c\"", name, value );
}

template <>
void XSPrintf<char>( char * string_stream, const char * name, char * & value) {
    
    sprintf( string_stream, "\"%s\":\"%s\"", name, value );
}

template <>
void XSPrintf<char>( char * string_stream, const char * name, char ** value) {
    
    sprintf( string_stream, "\"%s\":\"%s\"", name, *value );
}

template<>
void XSPrintf<unsigned int>( char * string_stream, const char * name, unsigned int & value) {
    
    sprintf( string_stream, "\"%s\":%d", name, value );
}

template<>
void XSPrintf<SCALAR>( char * string_stream, const char * name, SCALAR & value) {
    
    CORE_RUNTIME_Abort();
    sprintf( string_stream, "\"%s\":%d", name, value );
}


template<>
void XSscanf<bool>( char * string_stream, const char * name, bool & value, int & string_size) {
    
    char format[64];
    char string_value[64];
    
    sprintf( format, "\"%s\":%s", name, "%s" );
    sscanf(string_stream, format, &string_value);
    
    if ( strcmp( string_value, "true") == 0 ) {
        value = true;
        string_size = strlen( format ) + 4;
    }else {
        value = false;
        string_size = strlen( format ) + 5;
    }
}

template<>
void XSscanf<double>( char * string_stream, const char * name, double & value, int & string_size) {
    
    char format[64];
    char format2[64];
    
    sprintf( format, "\"%s\":%s", name, "%f" );
    
    sscanf(string_stream, format, &value );
    sprintf( format2, format, value );
    string_size = strlen( format2 );
}

template<>
void XSscanf<float>( char * string_stream, const char * name, float & value, int & string_size ) {
    
    char format[64];
    char format2[64];
    
    sprintf( format, "\"%s\":%s", name, "%f" );
    
    sscanf(string_stream, format, &value );
    sprintf( format2, format, value );
    string_size = strlen( format2 );
}

template<>
void XSscanf<int>( char * string_stream, const char * name, int & value, int & string_size ) {
    
    char format[64];
    char format2[64];
    
    sprintf( format, "\"%s\":%s", name, "%d" );
    
    sscanf(string_stream, format, &value );
    sprintf( format2, format, value );
    string_size = strlen( format2 );
}

template<>
void XSscanf<char>( char * string_stream, const char * name, char & value, int & string_size ) {
    
    char format[64];
    char format2[64];
    
    sprintf( format, "\"%s\":\"%s\"", name, "%c" );
    
    string_size = sscanf(string_stream, format, &value );
    sprintf( format2, format, value );
    string_size = strlen( format2 );
}

template<>
void XSscanf<char>( char * string_stream, const char * name, char ** value, int & string_size ) {
    
    char format[64];
    char format2[64];
    char string_buffer[256];
    
    sprintf( format, "\"%s\":\"%s\"", name, "%s" );
    
    string_size = sscanf(string_stream, format, string_buffer );
    int first_slash = (strchr( string_buffer, '\"' ) - string_buffer) + 1;
    snprintf( format2, first_slash+strlen(format)-2, format, string_buffer );
    
    if ( value ) {
        free(*value);
        *value = NULL;
    }
    
    *value = (char *) malloc( first_slash );
    
    memcpy(*value, string_buffer, first_slash - 1);
    (*value)[first_slash - 1] ='\0';
    
    string_size = strlen( format2 );
}

template<>
void XSscanf<char>( char * string_stream, const char * name, char * & value, int & string_size ) {
    
    char format[64];
    char format2[64];
    char string_buffer[256];
    
    sprintf( format, "\"%s\":\"%s\"", name, "%s" );
    
    
    string_size = sscanf(string_stream, format, string_buffer );
    int first_slash = (strchr( string_buffer, '\"' ) - string_buffer) + 1;
    snprintf( format2, first_slash+strlen(format)-2, format, string_buffer );
    
    
    memcpy(value, string_buffer, first_slash - 1);
    value[first_slash - 1] ='\0';
    
    string_size = strlen( format2 );
    
    
}

template<>
void XSscanf<unsigned int>( char * string_stream, const char * name, unsigned int & value, int & string_size ) {
    
    char format[64];
    char format2[64];
    
    sprintf( format, "\"%s\":%s", name, "%d" );
    
    string_size = sscanf(string_stream, format, &value );
    sprintf( format2, format, value );
    string_size = strlen( format2 );
}

template<>
void XSscanf<SCALAR>( char * string_stream, const char * name, SCALAR & value, int & string_size ) {
    
    CORE_RUNTIME_Abort();
}

CORE_DATA_JSON::CORE_DATA_JSON() :
    Stream( 0 ) {
    
}

CORE_DATA_JSON::~CORE_DATA_JSON() {
    
}

CORE_DATA_JSON::CORE_DATA_JSON( int size ) :
    Stream( size ) {
    
}

CORE_DATA_JSON::CORE_DATA_JSON( const char * pointer, int size ) :
    Stream( pointer, size ) {

}

void CORE_DATA_JSON::Open() {
    
    Stream.Open();
}

void CORE_DATA_JSON::Close() {
    
    Stream.Close();
}

void CORE_DATA_JSON::InitializeWithSize( int size ) {
    
    Stream.InitializeWithSize( size );
    
}

void CORE_DATA_JSON::ResetOffset() {
    
    Stream.ResetOffset();
}

void CORE_DATA_JSON::Reset() {
    
    Stream.Reset();
}

void CORE_DATA_JSON::PushObject( const char * object_name) {
    
    AppendMember();
    
    if (Stream.GetOffset() > 0 && object_name != NULL && strlen(object_name) ) {
        char tmp[256];
        
        tmp[0] = '\0';
        
        sprintf( tmp, "\"%s\":", object_name );
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
    }
    
    Stream.InputBytesWithoutSize( "{", 1 );
}

void CORE_DATA_JSON::PopObject() {
    
    Stream.InputBytesWithoutSize( "}\0", 2 );
    Stream.SetOffset( Stream.GetOffset() - 1 );
}

void CORE_DATA_JSON::PushArray( const char * object_name ) {
    
    AppendMember();
    
    if (Stream.GetOffset() > 0 && object_name != NULL && strlen(object_name) ) {
        char tmp[256];
        
        tmp[0] = '\0';
        
        sprintf( tmp, "\"%s\":", object_name );
        Stream.InputBytesWithoutSize( tmp, (int) strlen( tmp ) );
    }
    
    Stream.InputBytesWithoutSize( "[", 1 );
}

void CORE_DATA_JSON::PopArray() {
    
    Stream.InputBytesWithoutSize( "]\0", 2 );
    Stream.SetOffset( Stream.GetOffset() - 1 );
}

void CORE_DATA_JSON::AppendMember() {
    
    if ( Stream.GetOffset() > 0 ) {
        
        char * ptr = (char *) Stream.GetMemoryBuffer();
        int offset = Stream.GetOffset() -1;
        char c = *(ptr + offset);
        if ( c != '{' && c != '[' && c != ',' && c != ':') {
            
            Stream.InputBytesWithoutSize( ",", 1 );
        }
    }
}

void CORE_DATA_JSON::ReadObject( const char * object_name ) {
    
    ReadMember();
    
    if (Stream.GetOffset() > 0 && object_name != NULL && strlen(object_name) ) {
        char tmp[256];
        
        tmp[0] = '\0';
        
        sprintf( tmp, "\"%s\":", object_name );
        Stream.SetOffset( Stream.GetOffset() + strlen( tmp ) );
    }
    
    char c = *((char *)Stream.GetMemoryAtOffset());
    
    if ( c == '{' ) {
        
        Stream.SetOffset( Stream.GetOffset() + 1 );
    }
}

void CORE_DATA_JSON::ReadEndObject() {
    
    char c = *((char *)Stream.GetMemoryAtOffset());
    
    if ( c == '}' ) {
        
        Stream.SetOffset( Stream.GetOffset() + 1 );
    }
}

void CORE_DATA_JSON::ReadArray( const char * object_name ) {
    
    ReadMember();
    
    if (Stream.GetOffset() > 0 && object_name != NULL && strlen(object_name) ) {
        char tmp[256];
        
        tmp[0] = '\0';
        
        sprintf( tmp, "\"%s\":", object_name );
        Stream.SetOffset( Stream.GetOffset() + strlen( tmp ) );
    }
    
    char c = *((char *)Stream.GetMemoryAtOffset());
    
    if ( c == '[' ) {
        
        Stream.SetOffset( Stream.GetOffset() + 1 );
    }
}

void CORE_DATA_JSON::ReadEndArray() {
    
    char c = *((char *)Stream.GetMemoryAtOffset());
    
    if ( c == ']' ) {
        
        Stream.SetOffset( Stream.GetOffset() + 1 );
    }
}

void CORE_DATA_JSON::ReadMember() {
    
    char c = *((char *)Stream.GetMemoryAtOffset());
    
    if ( c == ',' ) {
        
        Stream.SetOffset( Stream.GetOffset() + 1 );
    }
}
