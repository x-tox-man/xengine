//
//  GAMEPLAY_COMPONENT_SCRIPT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_COMPONENT_SCRIPT_hpp
#define GAMEPLAY_COMPONENT_SCRIPT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_HELPERS_SCALAR.h"
#include "RESOURCE_PROXY.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_SCRIPT )

    GAMEPLAY_COMPONENT_SCRIPT();
    ~GAMEPLAY_COMPONENT_SCRIPT();

    //CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_SCRIPT, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Script)

    /*struct INTERNAL_ARRAY_S{
        int LastIndex;
        GAMEPLAY_COMPONENT_SCRIPT * MemoryArray;
    };*/

    void SetScript( CORE_ABSTRACT_PROGRAM_FACTORY * script ) { Script = script; }

    CORE_ABSTRACT_PROGRAM_FACTORY * GetScript() { return Script; }

    static int
        ComponentType;

private :

    //TODO: This needs to be a resource
    CORE_ABSTRACT_PROGRAM_FACTORY
        * Script;

XS_CLASS_END

#endif /* GAMEPLAY_COMPONENT_SCRIPT_hpp */
