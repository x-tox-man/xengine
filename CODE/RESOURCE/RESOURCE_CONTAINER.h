//
//  RESOURCE_SYSTEM.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef RESOURCE_SYSTEM_hpp
#define RESOURCE_SYSTEM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_FILESYSTEM_PATH.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "RESOURCE_PROXY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(RESOURCE_CONTAINER, RESOURCE_PROXY)

    template <typename __RESOURCE__>
    void AddResource(__RESOURCE__ & resource, const CORE_HELPERS_IDENTIFIER & identifier) {
        
    }

    void RemoveResource(const CORE_HELPERS_IDENTIFIER & identifier);

    void Reload();
    void Unload();

private:

    std::map< CORE_HELPERS_IDENTIFIER, RESOURCE_PROXY >
        ResourceMap;

XS_CLASS_END

#endif /* RESOURCE_SYSTEM_hpp */
