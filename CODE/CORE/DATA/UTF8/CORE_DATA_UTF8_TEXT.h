//
//  CORE_DATA_UTF8_TEXT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 12/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef CORE_DATA_UTF8_TEXT_hpp
#define CORE_DATA_UTF8_TEXT_hpp

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN_WITH_COPY( CORE_DATA_UTF8_TEXT )

    CORE_DATA_UTF8_TEXT();
    CORE_DATA_UTF8_TEXT( wchar_t * string);

    void operator = ( const CORE_DATA_UTF8_TEXT & other ) {
        
        if ( String ) {
            free( String );
            String = NULL;
        }
        
        String = ( wchar_t * )  malloc( sizeof(wchar_t) * ( wcslen( other.String ) + 1 ) );
        wcscpy( String, other.String );
    }

    wchar_t operator[] (const int index ) const {
#if DEBUG
        assert( String != NULL );
        assert( wcslen( String ) > index );
#endif
        
        return String[ index ];
    }

    inline int GetLenght() const {
#if DEBUG
        assert( String != NULL );
#endif
        
        return (int) wcslen( String );
    }

private:

    wchar_t
        * String;

XS_CLASS_END

#endif /* CORE_DATA_UTF8_TEXT_hpp */
