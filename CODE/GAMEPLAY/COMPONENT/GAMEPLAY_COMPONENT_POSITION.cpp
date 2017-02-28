//
//  GAMEPLAY_COMPONENT_POSITION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_POSITION::GAMEPLAY_COMPONENT_POSITION() :
    GAMEPLAY_COMPONENT(),
    Position(),
    Velocity(),
    Orientation(),
    Spin() {
    
}

GAMEPLAY_COMPONENT_POSITION::~GAMEPLAY_COMPONENT_POSITION() {

}

void * GAMEPLAY_COMPONENT_POSITION::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY > * InternalVector = InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_POSITION>();
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_POSITION::operator delete  ( void* ptr ) {
    
}

bool GAMEPLAY_COMPONENT_POSITION::Intersects( const CORE_MATH_RAY & ray ) {
    
    return true;
}
