//
//  TOOLS_LOCALE_SYSTEM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef TOOLS_LOCALE_SYSTEM_hpp
#define TOOLS_LOCALE_SYSTEM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "TOOLS_LOCALE_STRING.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "RESOURCE.h"

XS_CLASS_BEGIN( TOOLS_LOCALE_SYSTEM )

    XS_DEFINE_UNIQUE( TOOLS_LOCALE_SYSTEM )

    void Initialize( const char * locale_code );

    inline const TOOLS_LOCALE_STRING & FindTranslation( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) const { return TranslationTable.at( identifier ); }
    void FindResourceForLocale( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier );

private:

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, TOOLS_LOCALE_STRING >
        TranslationTable;
    const char *
        LocaleCode;

XS_CLASS_END

#endif /* TOOLS_LOCALE_SYSTEM_hpp */
