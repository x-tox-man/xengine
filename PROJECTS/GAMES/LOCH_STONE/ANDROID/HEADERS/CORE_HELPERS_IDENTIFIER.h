//
//  CORE_HELPERS_IDENTIFIER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __X_IDENTIFIER__
#define __X_IDENTIFIER__

    #include "CORE_HELPERS_CLASS.h"
	#include "CORE_HELPERS_IDENTIFIER_SYSTEM.h"

    #include <string>
	
XS_CLASS_BEGIN_WITH_COPY( CORE_HELPERS_IDENTIFIER )

    CORE_HELPERS_IDENTIFIER();

    CORE_HELPERS_IDENTIFIER( std::string & text );

    CORE_HELPERS_IDENTIFIER( const char * text );
    
    XS_DEFINE_SERIALIZABLE

    inline const char * getTextValue() const {
        
        return CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().getIdentifierValue( Value );
    }
    
    inline int getValue() const {
        
        return Value;
    }

    inline bool operator == ( const CORE_HELPERS_IDENTIFIER & other ) const {
        
        return Value == other.Value;
    }

private :

    CORE_HELPERS_IDENTIFIER( const char * text, bool it_must_initialize_table );

    int Value;
    
public:

    static const CORE_HELPERS_IDENTIFIER empty;
XS_CLASS_END

inline bool operator < ( const CORE_HELPERS_IDENTIFIER & first, const CORE_HELPERS_IDENTIFIER & second ) {
    
    return first.getValue() < second.getValue();
}

#endif // __X_IDENTIFIER__