//
//  GAMEPLAY_COMPONENT_RENDER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "CORE_MEMORY.h"
#include "GAMEPLAY_COMPONENT.h"

GAMEPLAY_COMPONENT_RENDER::GAMEPLAY_COMPONENT_RENDER() :
    GAMEPLAY_COMPONENT(),
    Object(),
    BoundingObject() {
    
}

GAMEPLAY_COMPONENT_RENDER::~GAMEPLAY_COMPONENT_RENDER() {

    for ( int i = 0; i < InternalVector.size(); i++ ) {
        
        CORE_MEMORY_ALLOCATOR_Free( InternalVector[ i ].MemoryArray );
    }
}

void * GAMEPLAY_COMPONENT_RENDER::operator new( size_t size ) {
    
    unsigned int index = (int) InternalVector.size();
    
    if ( index == 0 ) {
        
        InternalVector.resize(16);
        InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_RENDER * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_RENDER ) );
        InternalVector[0].LastIndex = -1;
    }
    
    return ( void *) &( InternalVector[ 0 ].MemoryArray[++InternalVector[ 0 ].LastIndex] );
}

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component ) {
    
    Object->SetPosition( component->GetPosition() );
    Object->SetOrientation(component->GetOrientation() );
    
    Object->Render( renderer );
}

std::vector< GAMEPLAY_COMPONENT_RENDER::INTERNAL_ARRAY > GAMEPLAY_COMPONENT_RENDER::InternalVector;
