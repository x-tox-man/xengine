//
//  GAMEPLAY_COMPONENT_ENTITY_PROXY.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 21/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_ENTITY_PROXY_hpp
#define GAMEPLAY_COMPONENT_ENTITY_PROXY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_COMPONENT_ENTITY_PROXY )

    GAMEPLAY_COMPONENT_ENTITY_PROXY();
    GAMEPLAY_COMPONENT_ENTITY_PROXY( GAMEPLAY_COMPONENT_ENTITY * entity );

    XS_DEFINE_SERIALIZABLE

    template< typename _COMPONENT_TYPE_ >
    inline _COMPONENT_TYPE_ * GetComponent( int component_index ) { return Entity->GetComponent(component_index); }
    inline GAMEPLAY_COMPONENT_ENTITY * GetEntity() { return Entity; }
    inline void SetEntity( GAMEPLAY_COMPONENT_ENTITY * entity ) { Entity = entity; }

private :

    GAMEPLAY_COMPONENT_ENTITY
        * Entity;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_ENTITY_PROXY_hpp */
