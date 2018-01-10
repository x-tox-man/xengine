#include "CORE_HELPERS_IDENTIFIER_SYSTEM.h"
#include "CORE_HELPERS_IDENTIFIER.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( CORE_HELPERS_IDENTIFIER_SYSTEM )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD(CORE_HELPERS_IDENTIFIER_SYSTEM& , CORE_HELPERS_IDENTIFIER_SYSTEM, GetInstance)
//CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1(CORE_HELPERS_IDENTIFIER, CORE_HELPERS_IDENTIFIER_SYSTEM, CreateIdentifier, const char *)
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( CORE_HELPERS_IDENTIFIER_SYSTEM )

CORE_HELPERS_IDENTIFIER_SYSTEM::CORE_HELPERS_IDENTIFIER_SYSTEM() :
    TextTable() {
    
}

CORE_HELPERS_IDENTIFIER_SYSTEM::~CORE_HELPERS_IDENTIFIER_SYSTEM() {

    unsigned int
        i;
    
    i = 0;
    
    while ( i < TextTable.size() )
    {
        CORE_MEMORY_ALLOCATOR_Free( (void * ) TextTable[ i ] );
        
        ++i;
    }
    
    TextTable.clear();
}

void CORE_HELPERS_IDENTIFIER_SYSTEM::create() {
    
	TextTable.reserve( 1024 );
}

void CORE_HELPERS_IDENTIFIER_SYSTEM::Remove() {
    
	TextTable.clear();
}

bool CORE_HELPERS_IDENTIFIER_SYSTEM::HasIdentifier( const char * text ) {
    
	return false;
}

CORE_HELPERS_IDENTIFIER CORE_HELPERS_IDENTIFIER_SYSTEM::CreateIdentifier( const char * text ) {
    
    return CORE_HELPERS_IDENTIFIER( text );
}

unsigned int CORE_HELPERS_IDENTIFIER_SYSTEM::AddIdentifier( const char * text ) {
    
    unsigned int
        i;

    i = 0;

    while ( i < TextTable.size() )
    {
        if ( strcmp( TextTable[ i ], text ) == 0 )
        {
            return i;
        }

        ++i;
    }
    
    char * text_copy = (char * ) CORE_MEMORY_ALLOCATOR_Allocate( strlen( text ) + 1 );
    strcpy( text_copy, text );

	TextTable.push_back( text_copy );

	return ( unsigned int )( TextTable.size() - 1 );
}

const char * CORE_HELPERS_IDENTIFIER_SYSTEM::GetIdentifierValue( int identifier ) // should be operator[]
{
	return TextTable.at( identifier );
}

CORE_HELPERS_IDENTIFIER CORE_HELPERS_IDENTIFIER_SYSTEM::FindIdentifier() {

    unsigned int i = 0;
    
    abort();
    
    return CORE_HELPERS_IDENTIFIER::Empty;
}
