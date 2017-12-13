//
//  CORE_DATA_UTF8_TEXT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 12/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "CORE_DATA_UTF8_TEXT.h"

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT() :
    String( NULL ) {
    
}

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT( wchar_t * string ) :
    String( NULL ) {
        
    String = ( wchar_t * )  malloc( sizeof(wchar_t) * (wcslen( string ) + 1) );
    wcscpy( String, string );
}

CORE_DATA_UTF8_TEXT::CORE_DATA_UTF8_TEXT( const CORE_DATA_UTF8_TEXT & other ) :
    String( other.String ) {
    
}
