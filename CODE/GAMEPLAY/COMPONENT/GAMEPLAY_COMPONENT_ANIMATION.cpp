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
    
    static std::vector< GAMEPLAY_COMPONENT_ANIMATION::INTERNAL_ARRAY_A > * iv = InternalVector = InitializeMemory<GAMEPLAY_COMPONENT_ANIMATION::INTERNAL_ARRAY_A, GAMEPLAY_COMPONENT_ANIMATION>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
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

void GAMEPLAY_COMPONENT_ANIMATION::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_ANIMATION::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( int i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_ANIMATION) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_ANIMATION::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY_A, GAMEPLAY_COMPONENT_ANIMATION>( *InternalVector, i );
        
        size_t b = sizeof(GAMEPLAY_COMPONENT_ANIMATION) * GAMEPLAY_COMPONENT_BASE_COUNT;
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, b );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}


std::vector< GAMEPLAY_COMPONENT_ANIMATION::INTERNAL_ARRAY_A> * GAMEPLAY_COMPONENT_ANIMATION::InternalVector =  NULL;
int GAMEPLAY_COMPONENT_ANIMATION::LastIndex = -1;
int GAMEPLAY_COMPONENT_ANIMATION::LastOffset = -1;
