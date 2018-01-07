//
//  CORE_DATA_UTF8_TEXT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 12/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "CORE_DATA_UTF8_TEXT.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_DATA_UTF8_TEXT )
    //XS_DEFINE_ClassMember( "String", CORE_DATA_UTF8_TEXT , UTF8String )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT() :
    String( NULL ) {
    
}

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT( const wchar_t * string ) :
    String( NULL ) {
        
    String = ( wchar_t * )  malloc( sizeof(wchar_t) * (wcslen( string ) + 1) );
    CORE_DATA_COPY_WIDE_STRING( String, string );
}

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT( const CORE_DATA_UTF8_TEXT & other ) :
    String( other.String ) {
    
}

CORE_DATA_UTF8_TEXT::~CORE_DATA_UTF8_TEXT() {
    
    CORE_MEMORY_ObjectSafeDeallocation( String );
}
