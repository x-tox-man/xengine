//
//  RESOURCE_PROXY.hpp
//  GAME-ENGINE
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

XS_CLASS_BEGIN_WITH_COPY( RESOURCE_PROXY )

    RESOURCE_PROXY();
    RESOURCE_PROXY( BASE_RESOURCE * Resource );

    virtual ~RESOURCE_PROXY();

    XS_DEFINE_SERIALIZABLE

    inline void SetIdentifier( const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier ) { Identifier = identifier; }
    inline void SetResource( BASE_RESOURCE * resource ) { Resource = resource; }
    inline bool ShouldLoad() { return ItShouldLoad; }
    inline void SetItShouldLoad( bool should_load ) { ItShouldLoad = should_load; }
    inline RESOURCE_TYPE GetType() { return Type; }
    inline void SetType( const RESOURCE_TYPE type ) { Type = type; }
    inline const CORE_HELPERS_UNIQUE_IDENTIFIER & GetIdentifier() { return Identifier; }

    void operator = ( const RESOURCE_PROXY & other ) {
        
        Identifier = other.Identifier;
        Resource = other.Resource;
    }

    template <typename __RESOURCE_TYPE_>
    __RESOURCE_TYPE_ * GetResource() {
        if ( Resource == NULL )
            Resource = __RESOURCE_TYPE_::GetResourceForIdentifier( Identifier );
        
        return static_cast<__RESOURCE_TYPE_ *>(Resource);
    }

private:

    CORE_HELPERS_UNIQUE_IDENTIFIER
        Identifier;
    BASE_RESOURCE
        * Resource;
    RESOURCE_TYPE
        Type;
    bool
        ItShouldLoad;

XS_CLASS_END

#endif /* RESOURCE_PROXY_hpp */
