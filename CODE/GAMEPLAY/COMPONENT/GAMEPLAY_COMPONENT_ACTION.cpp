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
#include "GAMEPLAY_COMPONENT_BASE_ENTITY.h"

GAMEPLAY_COMPONENT_ACTION::GAMEPLAY_COMPONENT_ACTION() :
    GAMEPLAY_COMPONENT(),
    ActionCallback() {
    
}

GAMEPLAY_COMPONENT_ACTION::GAMEPLAY_COMPONENT_ACTION( const GAMEPLAY_COMPONENT_ACTION & other ) :
    GAMEPLAY_COMPONENT(),
    ActionCallback() {
        
        abort();
}

GAMEPLAY_COMPONENT_ACTION::~GAMEPLAY_COMPONENT_ACTION() {
    
}

void * GAMEPLAY_COMPONENT_ACTION::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY > * iv = InternalVector = InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_ACTION>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_ACTION::operator delete  ( void* ptr ) {
    
}

void GAMEPLAY_COMPONENT_ACTION::operator() (GAMEPLAY_COMPONENT_ENTITY * entity) {
    
    ActionCallback(entity);
}

void GAMEPLAY_COMPONENT_ACTION::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_ACTION::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( size_t i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_ACTION) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_ACTION::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( size_t i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_ACTION>( *InternalVector, i );
        
        X_VERY_LONG b = (X_VERY_LONG) sizeof(GAMEPLAY_COMPONENT_ACTION) * GAMEPLAY_COMPONENT_BASE_COUNT;
        stream.OutputBytes((char *) (*InternalVector)[ i ].MemoryArray, b );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

std::vector< GAMEPLAY_COMPONENT_ACTION::INTERNAL_ARRAY > * GAMEPLAY_COMPONENT_ACTION::InternalVector = NULL ;
int GAMEPLAY_COMPONENT_ACTION::LastIndex = -1;
int GAMEPLAY_COMPONENT_ACTION::LastOffset = -1;
