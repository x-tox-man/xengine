//
//  GAMEPLAY_COMPONENT_ACTION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ACTION.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"

GAMEPLAY_COMPONENT_ACTION::GAMEPLAY_COMPONENT_ACTION() :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_ACTION ) ),
    ActionCallback() {
    
}

GAMEPLAY_COMPONENT_ACTION::GAMEPLAY_COMPONENT_ACTION( const GAMEPLAY_COMPONENT_ACTION & other ) :
    GAMEPLAY_COMPONENT( sizeof( GAMEPLAY_COMPONENT_ACTION ) ),
    ActionCallback() {
        
    CORE_RUNTIME_Abort();
}

GAMEPLAY_COMPONENT_ACTION::~GAMEPLAY_COMPONENT_ACTION() {
    
}

void GAMEPLAY_COMPONENT_ACTION::operator() (GAMEPLAY_COMPONENT_ENTITY * entity) {
    
    ActionCallback(entity);
}
