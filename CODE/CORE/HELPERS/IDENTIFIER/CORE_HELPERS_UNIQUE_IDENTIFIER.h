//
//  CORE_HELPERS_UNIQUE_IDENTIFIER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_HELPERS_UNIQUE_IDENTIFIER__
#define __GAME_ENGINE_REBORN__CORE_HELPERS_UNIQUE_IDENTIFIER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MEMORY.h"

XS_CLASS_BEGIN_WITH_COPY( CORE_HELPERS_UNIQUE_IDENTIFIER )

XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_UNIQUE_IDENTIFIER();
    CORE_HELPERS_UNIQUE_IDENTIFIER( const char * text );
    virtual    ~CORE_HELPERS_UNIQUE_IDENTIFIER();

    friend bool operator < ( const CORE_HELPERS_UNIQUE_IDENTIFIER first, const CORE_HELPERS_UNIQUE_IDENTIFIER second );
    bool operator == ( const CORE_HELPERS_UNIQUE_IDENTIFIER other ) {
        
        return CheckSum == other.CheckSum;
    }

    char * GetIdentifier() { return Identifier; }

    CORE_HELPERS_UNIQUE_IDENTIFIER & operator = ( const CORE_HELPERS_UNIQUE_IDENTIFIER & other ){
        
        CheckSum = other.CheckSum;
        Identifier = (char*) CORE_MEMORY_ALLOCATOR::Allocate( 32 );
        strncpy( Identifier, other.Identifier, 31 );
        
        Identifier[31] = '\0';
        
        return *this;
    }

    bool operator == ( const CORE_HELPERS_UNIQUE_IDENTIFIER & other ) const {
        
        return CheckSum == other.CheckSum;
    }

    bool operator != ( const CORE_HELPERS_UNIQUE_IDENTIFIER & other ) const {
        
        return CheckSum != other.CheckSum;
    }


    void Generate( const char * value );

    static const CORE_HELPERS_UNIQUE_IDENTIFIER Empty;

private :

    char
        * Identifier;
    int
        CheckSum;

XS_CLASS_END

inline bool operator < ( const CORE_HELPERS_UNIQUE_IDENTIFIER first, const CORE_HELPERS_UNIQUE_IDENTIFIER second ) {
    
    return first.CheckSum < second.CheckSum;
}

#endif /* defined(__GAME_ENGINE_REBORN__CORE_HELPERS_UNIQUE_IDENTIFIER__) */
