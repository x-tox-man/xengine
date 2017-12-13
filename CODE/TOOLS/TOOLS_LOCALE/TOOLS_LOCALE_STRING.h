//
//  TOOLS_LOCALE_STRING.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef TOOLS_LOCALE_STRING_hpp
#define TOOLS_LOCALE_STRING_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_UTF8_TEXT.h"

XS_CLASS_BEGIN_WITH_COPY( TOOLS_LOCALE_STRING )

    TOOLS_LOCALE_STRING( const CORE_DATA_UTF8_TEXT & value );

    inline const CORE_DATA_UTF8_TEXT & GetUTF8String() { return UTF8String; }

private:

    CORE_DATA_UTF8_TEXT
        UTF8String;

XS_CLASS_END

#endif /* TOOLS_LOCALE_STRING_hpp */
