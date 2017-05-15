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
#include "RESOURCE.h"

XS_CLASS_BEGIN_WITH_COPY(RESOURCE_PROXY)

    RESOURCE_PROXY();
    virtual ~RESOURCE_PROXY();

    XS_DEFINE_SERIALIZABLE

    inline void SetIdentifier( const CORE_HELPERS_IDENTIFIER & identifier ) { Identifier = identifier; }
    inline void SetResource( BASE_RESOURCE * resource ) { Resource = resource; }
    inline bool ShouldLoad() { return ItShouldLoad; }
    inline void SetItShouldLoasd( bool should_load ) { ItShouldLoad = should_load; }
    inline RESOURCE_TYPE GetType() { return Type; }

    void operator = ( const RESOURCE_PROXY & other ) {
        
        Identifier = other.Identifier;
        Resource = other.Resource;
    }

private:

    CORE_HELPERS_IDENTIFIER
        Identifier;
    RESOURCE_TYPE
        Type;
    bool
        ItShouldLoad;
    BASE_RESOURCE
        * Resource;

XS_CLASS_END

#endif /* RESOURCE_PROXY_hpp */
