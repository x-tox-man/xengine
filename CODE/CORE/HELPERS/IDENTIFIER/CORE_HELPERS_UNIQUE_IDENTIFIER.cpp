//
//  CORE_HELPERS_UNIQUE_IDENTIFIER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_MEMORY.h"
#include "SERVICE_LOGGER.h"
#include "CORE_DATA_JSON.h"

#define A_PRIME 54059 /* a prime */
#define B_PRIME 76963 /* another prime */
#define C_PRIME 86969 /* yet another prime */

// http://stackoverflow.com/questions/8317508/hash-function-for-a-string

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_HELPERS_UNIQUE_IDENTIFIER )
    XS_DEFINE_ClassMemberArray( "Identifier", char, Identifier, (size_t) 32 )
    XS_DEFINE_ClassMember( "CheckSum", unsigned int, CheckSum )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_HELPERS_UNIQUE_IDENTIFIER::CORE_HELPERS_UNIQUE_IDENTIFIER() :
    Identifier(),
    CheckSum( 0 ) {
    
    Identifier[0] = '\0';
}

CORE_HELPERS_UNIQUE_IDENTIFIER::CORE_HELPERS_UNIQUE_IDENTIFIER( const char * text ) {

    Generate( text );
}

CORE_HELPERS_UNIQUE_IDENTIFIER::CORE_HELPERS_UNIQUE_IDENTIFIER( const CORE_HELPERS_UNIQUE_IDENTIFIER & other ){
    
    CheckSum = other.CheckSum;
    
    strncpy( Identifier, other.Identifier, 31 );
    
    Identifier[31] = '\0';
}

CORE_HELPERS_UNIQUE_IDENTIFIER::~CORE_HELPERS_UNIQUE_IDENTIFIER() {

}

void CORE_HELPERS_UNIQUE_IDENTIFIER::Generate( const char * value ) {
    
    #if DEBUG
    if ( strlen( value ) > 31 ) {
        
        SERVICE_LOGGER_Info( "CORE_HELPERS_UNIQUE_IDENTIFIER::Generate too long %s\n", value );
    }
    #endif
    strncpy( Identifier, value, 31 );
    
    CheckSum = 31;
    
    while (*value) {
        
        CheckSum = (CheckSum * A_PRIME) ^ (value[0] * B_PRIME);
        
        value++;
    }
}

const CORE_HELPERS_UNIQUE_IDENTIFIER
    CORE_HELPERS_UNIQUE_IDENTIFIER::Empty( "::Empty" );
