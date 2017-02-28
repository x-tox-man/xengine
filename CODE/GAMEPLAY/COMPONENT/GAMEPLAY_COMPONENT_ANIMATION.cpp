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
    
}

void * GAMEPLAY_COMPONENT_ANIMATION::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY_A > * InternalVector = InitializeMemory<INTERNAL_ARRAY_A, GAMEPLAY_COMPONENT_ANIMATION>();
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_ANIMATION::operator delete  ( void* ptr ) {
    
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

