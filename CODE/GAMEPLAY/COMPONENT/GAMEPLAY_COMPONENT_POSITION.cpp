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

    for ( int i = 0; i < InternalVector.size(); i++ ) {
        
        CORE_MEMORY_ALLOCATOR_Free( InternalVector[ i ].MemoryArray );
    }
}

void * GAMEPLAY_COMPONENT_POSITION::operator new( size_t size ) {
    
    int index = (int) InternalVector.size();
    
    if( index == 0) {

        InternalVector.resize(16);
        InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_POSITION * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_POSITION ) );
        InternalVector[0].LastIndex = -1;
    }
    
    return ( void *) &( InternalVector[ 0 ].MemoryArray[++InternalVector[ 0 ].LastIndex] );
}

bool GAMEPLAY_COMPONENT_POSITION::Intersects( const CORE_MATH_RAY & ray ) {
    
    return true;
}

std::vector< GAMEPLAY_COMPONENT_POSITION::INTERNAL_ARRAY > GAMEPLAY_COMPONENT_POSITION::InternalVector;
