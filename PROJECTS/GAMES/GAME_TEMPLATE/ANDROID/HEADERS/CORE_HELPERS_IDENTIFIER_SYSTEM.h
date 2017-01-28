#ifndef __X_IDENTIFIER_TABLE__
#define __X_IDENTIFIER_TABLE__

	#include "CORE_HELPERS_CLASS.h"
    #include "CORE_HELPERS_UNIQUE.h"
    #include "CORE_RUNTIME_ENVIRONMENT.h"

class CORE_HELPERS_IDENTIFIER;

XS_CLASS_BEGIN( CORE_HELPERS_IDENTIFIER_SYSTEM )
    XS_DEFINE_UNIQUE( CORE_HELPERS_IDENTIFIER_SYSTEM )
    
public :
	friend class CORE_HELPERS_IDENTIFIER;

	void remove();

	bool hasIdentifier( const std::string & text ); // Don't use too frequently

private :
	void create();

	unsigned int addIdentifier( const std::string & );
	const char * getIdentifierValue( int );

	std::vector< std::string > textTable;

XS_CLASS_END

#endif