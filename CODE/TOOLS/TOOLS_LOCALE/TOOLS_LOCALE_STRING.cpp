//
//  TOOLS_LOCALE_STRING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "TOOLS_LOCALE_STRING.h"

TOOLS_LOCALE_STRING::TOOLS_LOCALE_STRING( const CORE_DATA_UTF8_TEXT & value ) :
    UTF8String( value ) {
    
}

TOOLS_LOCALE_STRING::TOOLS_LOCALE_STRING( const TOOLS_LOCALE_STRING & other ) :
    UTF8String( other.UTF8String ) {
    
}
