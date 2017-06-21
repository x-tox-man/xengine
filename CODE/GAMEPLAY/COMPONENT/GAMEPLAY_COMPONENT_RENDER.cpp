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
#include "CORE_DATA_STREAM.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

GAMEPLAY_COMPONENT_RENDER::GAMEPLAY_COMPONENT_RENDER() :
    GAMEPLAY_COMPONENT(),
    ObjectProxy(),
    EffectProxy(),
    BoundingObject(),
    ScaleFactor( 1.0f ) {
    
}

GAMEPLAY_COMPONENT_RENDER::~GAMEPLAY_COMPONENT_RENDER() {

}

void * GAMEPLAY_COMPONENT_RENDER::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY_R > * iv = InternalVector = InitializeMemory<INTERNAL_ARRAY_R, GAMEPLAY_COMPONENT_RENDER>();
    
    LastIndex = ( *InternalVector)[ 0 ].LastIndex + 1;
    LastOffset = 0;
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_RENDER::operator delete ( void* ptr ) {
    
}

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component ) {
    
    GRAPHIC_OBJECT
        * object = ObjectProxy.GetResource< GRAPHIC_OBJECT >();
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options;
    
    options.SetPosition( component->GetPosition() );
    options.SetOrientation(component->GetOrientation() );
    options.SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );

    object->Render( renderer, options, EffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >() );
}

void GAMEPLAY_COMPONENT_RENDER::Clear() {
    
    LastIndex = -1;
    LastOffset = -1;
    
    InternalVector->clear();
}

void GAMEPLAY_COMPONENT_RENDER::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector ) {
        
        stream << InternalVector->size();
        
        for ( int i = 0; i< InternalVector->size(); i++ ) {
            
            stream.InputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_RENDER) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            auto ptr = (*InternalVector)[ i ].MemoryArray;
            
            stream << (*InternalVector)[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_RENDER::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    InternalVector->resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        InitializeMemory<INTERNAL_ARRAY_R, GAMEPLAY_COMPONENT_RENDER>( *InternalVector, i );
        
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_RENDER) * GAMEPLAY_COMPONENT_BASE_COUNT );
        
        auto ptr = &(*InternalVector)[0].MemoryArray[0];
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

std::vector< GAMEPLAY_COMPONENT_RENDER::INTERNAL_ARRAY_R >
    * GAMEPLAY_COMPONENT_RENDER::InternalVector;
int GAMEPLAY_COMPONENT_RENDER::LastIndex = -1;
int GAMEPLAY_COMPONENT_RENDER::LastOffset = -1;
