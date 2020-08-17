//
//  GAMEPLAY_COMPONENT_ACTION.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_ACTION_hpp
#define GAMEPLAY_COMPONENT_ACTION_hpp

#include "GAMEPLAY_COMPONENT.h"
#include "CORE_HELPERS_CALLBACK.h"

class GAMEPLAY_COMPONENT_ENTITY;

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_ACTION )

    GAMEPLAY_COMPONENT_ACTION();
    ~GAMEPLAY_COMPONENT_ACTION();

    void operator() (GAMEPLAY_COMPONENT_ENTITY * entity) ;

    void SetActionCallback( const CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * > & callback ) {ActionCallback = callback; }

    //CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_ACTION, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Action)

    static int
        ComponentType;

private :

    //TODO: This needs to be a resource
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        ActionCallback;



XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_ACTION_hpp */
