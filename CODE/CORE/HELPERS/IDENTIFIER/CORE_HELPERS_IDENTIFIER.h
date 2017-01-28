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
    #include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
    #include "CORE_ABSTRACT_PROGRAM_LUA.h"
    #include "CORE_ABSTRACT_RUNTIME_LUA.h"
    #include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
    #include "CORE_ABSTRACT_PROGRAM_BINDER.h"
    #include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"

    #include <string>
	
XS_CLASS_BEGIN_WITH_COPY( CORE_HELPERS_IDENTIFIER )

    XS_DEFINE_SERIALIZABLE

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_HELPERS_IDENTIFIER );

    CORE_HELPERS_IDENTIFIER();

    CORE_HELPERS_IDENTIFIER( const char * text );

    void Initialize( const char * text );

    friend class CORE_HELPERS_IDENTIFIER_SYSTEM;

    inline const char * GetTextValue() const {
        
        return CORE_HELPERS_IDENTIFIER_SYSTEM::GetInstance().GetIdentifierValue( Value );
    }
    
    inline int GetValue() const {
        
        return Value;
    }

    inline bool operator == ( const CORE_HELPERS_IDENTIFIER & other ) const {
        
        return Value == other.Value;
    }

    inline bool operator != ( const CORE_HELPERS_IDENTIFIER & other ) const {
        
        return Value != other.Value;
    }

private :

    CORE_HELPERS_IDENTIFIER( const char * text, bool it_must_initialize_table );

    CORE_HELPERS_IDENTIFIER( int value );

    int Value;
    
public:

    static const CORE_HELPERS_IDENTIFIER Empty;
XS_CLASS_END

inline bool operator < ( const CORE_HELPERS_IDENTIFIER & first, const CORE_HELPERS_IDENTIFIER & second ) {
    
    return first.GetValue() < second.GetValue();
}

#endif // __X_IDENTIFIER__
