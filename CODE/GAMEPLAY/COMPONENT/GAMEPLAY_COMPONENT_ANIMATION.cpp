//
//  GAMEPLAY_COMPONENT_ANIMATION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_ANIMATION::GAMEPLAY_COMPONENT_ANIMATION() :
    GAMEPLAY_COMPONENT() {
    
}

GAMEPLAY_COMPONENT_ANIMATION::~GAMEPLAY_COMPONENT_ANIMATION() {
    
    for ( int i = 0; i < InternalVector.size(); i++ ) {
        
        CORE_MEMORY_ALLOCATOR_Free( InternalVector[ i ].MemoryArray );
    }
}

void * GAMEPLAY_COMPONENT_ANIMATION::operator new( size_t size ) {
    
    int index = (int) InternalVector.size();
    
    if( index == 0) {
        
        if ( GAMEPLAY_COMPONENT_ANIMATION::InternalVector.size() != 16 ) {
            
            GAMEPLAY_COMPONENT_ANIMATION::InternalVector.resize(16);
        }
        
        GAMEPLAY_COMPONENT_ANIMATION::InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_ANIMATION * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_ANIMATION ) );
        GAMEPLAY_COMPONENT_ANIMATION::InternalVector[0].LastIndex = -1;
    }
    
    return ( void *) &( GAMEPLAY_COMPONENT_ANIMATION::InternalVector[ 0 ].MemoryArray[++GAMEPLAY_COMPONENT_ANIMATION::InternalVector[ 0 ].LastIndex] );
}

void GAMEPLAY_COMPONENT_ANIMATION::UpdateAnimation( float time_step ) {
    
    //TODO: float t = Animation->GetAnimation( 0 )->GetJointTable()[0]->GetDuration();
    
    if ( time_step + Animation->GetCurrentTimeFrame() < Animation->GetAnimation( 0 )->GetJointTable()[0]->GetDuration() ) {
        
        Animation->Update( time_step );
    }
    else {
        
        Animation->Reset();
    }
}

std::vector< GAMEPLAY_COMPONENT_ANIMATION::INTERNAL_ARRAY_A > GAMEPLAY_COMPONENT_ANIMATION::InternalVector = std::vector< GAMEPLAY_COMPONENT_ANIMATION::INTERNAL_ARRAY_A >();
