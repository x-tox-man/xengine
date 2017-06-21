//
//  GAMEPLAY_COMPONENT_SCRIPT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "CORE_DATA_STREAM.h"

GAMEPLAY_COMPONENT_SCRIPT::GAMEPLAY_COMPONENT_SCRIPT() {
    
}

GAMEPLAY_COMPONENT_SCRIPT::~GAMEPLAY_COMPONENT_SCRIPT() {
    
}

void * GAMEPLAY_COMPONENT_SCRIPT::operator new(size_t size) {
    
    static std::vector< INTERNAL_ARRAY_S > * iv = InternalVector = InitializeMemory<INTERNAL_ARRAY_S, GAMEPLAY_COMPONENT_SCRIPT>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_SCRIPT::operator delete( void* ptr ) {
    
}

void GAMEPLAY_COMPONENT_SCRIPT::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_SCRIPT::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( int i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_SCRIPT) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            int index = (*InternalVector)[ i ].LastIndex;
            
            stream << index;
        }
    }
}

void GAMEPLAY_COMPONENT_SCRIPT::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY_S, GAMEPLAY_COMPONENT_SCRIPT>( *InternalVector, i );
        
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_SCRIPT) * GAMEPLAY_COMPONENT_BASE_COUNT );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

std::vector< GAMEPLAY_COMPONENT_SCRIPT::INTERNAL_ARRAY_S >
    * GAMEPLAY_COMPONENT_SCRIPT::InternalVector;
int GAMEPLAY_COMPONENT_SCRIPT::LastIndex = -1;
int GAMEPLAY_COMPONENT_SCRIPT::LastOffset = -1;
