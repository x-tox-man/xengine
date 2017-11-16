//
//  GRAPHIC_FONT_MANAGER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 17/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_FONT_MANAGER_h
#define GRAPHIC_FONT_MANAGER_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "GRAPHIC_FONT.h"

XS_CLASS_BEGIN( GRAPHIC_FONT_MANAGER )

    XS_DEFINE_UNIQUE( GRAPHIC_FONT_MANAGER )

    ~GRAPHIC_FONT_MANAGER();

    void LoadFont( const CORE_HELPERS_UNIQUE_IDENTIFIER &, const CORE_FILESYSTEM_PATH &, const CORE_FILESYSTEM_PATH & );
    GRAPHIC_FONT * GetFont( const CORE_HELPERS_UNIQUE_IDENTIFIER & );

private :

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, GRAPHIC_FONT * >
        FontTable;

XS_CLASS_END

#endif /* GRAPHIC_FONT_MANAGER_hpp */
