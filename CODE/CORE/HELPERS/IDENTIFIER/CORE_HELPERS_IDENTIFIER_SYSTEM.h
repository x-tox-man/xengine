#ifndef __X_IDENTIFIER_TABLE__
#define __X_IDENTIFIER_TABLE__

	#include "CORE_HELPERS_CLASS.h"
    #include "CORE_HELPERS_UNIQUE.h"
    #include "CORE_RUNTIME_ENVIRONMENT.h"
    #include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
    #include "CORE_ABSTRACT_PROGRAM_BINDER.h"

class CORE_HELPERS_IDENTIFIER;

XS_CLASS_BEGIN( CORE_HELPERS_IDENTIFIER_SYSTEM )

    XS_DEFINE_UNIQUE( CORE_HELPERS_IDENTIFIER_SYSTEM )

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_HELPERS_IDENTIFIER_SYSTEM );

public :

    virtual    ~CORE_HELPERS_IDENTIFIER_SYSTEM();
	friend class CORE_HELPERS_IDENTIFIER;

	void Remove();

	bool HasIdentifier( const char * text ); // Don't use too frequently
    CORE_HELPERS_IDENTIFIER CreateIdentifier( const char * text );

    CORE_HELPERS_IDENTIFIER FindIdentifier();

private :
	void create();

	unsigned int AddIdentifier( const char * );
	const char * GetIdentifierValue( int );

	std::vector< const char * > TextTable;

XS_CLASS_END

#endif
