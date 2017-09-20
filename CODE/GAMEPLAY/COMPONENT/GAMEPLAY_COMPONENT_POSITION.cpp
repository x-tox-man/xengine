//
//  GAMEPLAY_COMPONENT_POSITION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"


CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_COMPONENT_POSITION )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD( CORE_MATH_VECTOR &, GAMEPLAY_COMPONENT_POSITION, GetPosition )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_POSITION, SetPosition, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_VOID_METHOD_1(GAMEPLAY_COMPONENT_POSITION, SetOrientation, const CORE_MATH_QUATERNION & )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_COMPONENT_POSITION )

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
    
    static std::vector< INTERNAL_ARRAY > * iv = InternalVector = InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_POSITION>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_POSITION::operator delete  ( void* ptr ) {
    
}

bool GAMEPLAY_COMPONENT_POSITION::Intersects( const CORE_MATH_RAY & ray ) {
    
    return true;
}

void GAMEPLAY_COMPONENT_POSITION::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_POSITION::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( int i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_POSITION) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            auto ptr = (*InternalVector)[ i ].MemoryArray;
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_POSITION::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY, GAMEPLAY_COMPONENT_POSITION>( *InternalVector, i );
        
        
        size_t b = sizeof(GAMEPLAY_COMPONENT_POSITION) * GAMEPLAY_COMPONENT_BASE_COUNT;
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, b );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        auto ptr = (*InternalVector)[ i ].MemoryArray;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

std::vector< GAMEPLAY_COMPONENT_POSITION::INTERNAL_ARRAY >
    * GAMEPLAY_COMPONENT_POSITION::InternalVector;
int GAMEPLAY_COMPONENT_POSITION::LastIndex = -1;
int GAMEPLAY_COMPONENT_POSITION::LastOffset = -1;
