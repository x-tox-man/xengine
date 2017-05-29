//
//  GAMEPLAY_COMPONENT_SCRIPT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SCRIPT.h"

GAMEPLAY_COMPONENT_SCRIPT::GAMEPLAY_COMPONENT_SCRIPT() {
    
}

GAMEPLAY_COMPONENT_SCRIPT::~GAMEPLAY_COMPONENT_SCRIPT() {
    
}

void * GAMEPLAY_COMPONENT_SCRIPT::operator new(size_t size) {
    
    static std::vector< INTERNAL_ARRAY_S > * InternalVector = InitializeMemory<INTERNAL_ARRAY_S, GAMEPLAY_COMPONENT_SCRIPT>();
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_SCRIPT::operator delete( void* ptr ) {
    
}
