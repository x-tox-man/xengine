//
//  CORE_HELPERS_IDENTIFIER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( CORE_HELPERS_IDENTIFIER )
    XS_DEFINE_ClassMember( "Value", int , Value )
XS_END_INTERNAL_MEMORY_LAYOUT

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( CORE_HELPERS_IDENTIFIER )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1( CORE_HELPERS_IDENTIFIER, Initialize, const char * )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( CORE_HELPERS_IDENTIFIER )

CORE_HELPERS_IDENTIFIER::CORE_HELPERS_IDENTIFIER( const char * text ) {

	Value = CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().AddIdentifier( text );
}

CORE_HELPERS_IDENTIFIER::~CORE_HELPERS_IDENTIFIER() {

}

CORE_HELPERS_IDENTIFIER::CORE_HELPERS_IDENTIFIER( const CORE_HELPERS_IDENTIFIER & other ) {
    
	Value = other.Value;
}

void CORE_HELPERS_IDENTIFIER::Initialize( const char * text ) {
    
    Value = CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().AddIdentifier( text );
}

CORE_HELPERS_IDENTIFIER::CORE_HELPERS_IDENTIFIER() : CORE_HELPERS_IDENTIFIER( Empty ) {
    
}

CORE_HELPERS_IDENTIFIER::CORE_HELPERS_IDENTIFIER( const char * text, bool it_must_initialize_table ) {
    
	CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().create();
	Value = CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().AddIdentifier( text );
}

CORE_HELPERS_IDENTIFIER::CORE_HELPERS_IDENTIFIER( int value ) {

    Value = value;
}

const CORE_HELPERS_IDENTIFIER
	CORE_HELPERS_IDENTIFIER::Empty( "", true );
