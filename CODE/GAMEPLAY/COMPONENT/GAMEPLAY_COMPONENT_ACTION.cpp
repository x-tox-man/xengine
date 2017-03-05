//
//  GAMEPLAY_COMPONENT_ACTION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ACTION.h"

#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_ACTION::GAMEPLAY_COMPONENT_ACTION() :
    GAMEPLAY_COMPONENT(),
    ActionCallback() {
    
}

GAMEPLAY_COMPONENT_ACTION::~GAMEPLAY_COMPONENT_ACTION() {
    
}

void * GAMEPLAY_COMPONENT_ACTION::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY > * InternalVector = InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_ACTION>();
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_ACTION::operator delete  ( void* ptr ) {
    
}

void GAMEPLAY_COMPONENT_ACTION::operator() (GAMEPLAY_COMPONENT_ENTITY * entity) {
    
    ActionCallback(entity);
}

