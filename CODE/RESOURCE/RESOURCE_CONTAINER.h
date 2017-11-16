//
//  RESOURCE_SYSTEM.hpp
//  GAME-ENGINE
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
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "RESOURCE_PROXY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(RESOURCE_CONTAINER, RESOURCE_PROXY)

    RESOURCE_CONTAINER();
    virtual ~RESOURCE_CONTAINER();

    XS_DEFINE_SERIALIZABLE

    void AddResource(RESOURCE_PROXY * resource, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier);
    void RemoveResource(const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier);

    void Save( const CORE_FILESYSTEM_PATH & path );
    void Load( const CORE_FILESYSTEM_PATH & path );

    void Reload();
    void Unload();

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY * > & GetResourceMap() { return ResourceMap; }

private:

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, RESOURCE_PROXY * >
        ResourceMap;

XS_CLASS_END

#endif /* RESOURCE_SYSTEM_hpp */
