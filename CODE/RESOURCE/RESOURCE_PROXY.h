//
//  RESOURCE_PROXY.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef RESOURCE_PROXY_hpp
#define RESOURCE_PROXY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_IDENTIFIER.h"

XS_CLASS_BEGIN(RESOURCE_PROXY)

private:

    CORE_FILESYSTEM_PATH
        Path;
    int
        Type;
    CORE_HELPERS_IDENTIFIER
        Identifier;
    void
        * ResourcePtr;

XS_CLASS_END

#endif /* RESOURCE_PROXY_hpp */
