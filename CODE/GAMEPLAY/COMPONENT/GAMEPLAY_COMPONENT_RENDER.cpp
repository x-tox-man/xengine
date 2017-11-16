//
//  GAMEPLAY_COMPONENT_RENDER.cpp
//  GAME-ENGINE
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
    ShadowmapEffectProxy(),
    BoundingObject(),
    ScaleFactor( 1.0f ) {
    
}

GAMEPLAY_COMPONENT_RENDER::GAMEPLAY_COMPONENT_RENDER( const GAMEPLAY_COMPONENT_RENDER & other ) :
    GAMEPLAY_COMPONENT(),
    ObjectProxy( other.ObjectProxy ),
    EffectProxy( other.EffectProxy ),
    ShadowmapEffectProxy( other.ShadowmapEffectProxy ),
    BoundingObject( other.BoundingObject ),
    ScaleFactor( other.ScaleFactor ) {
    
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

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_COMPONENT_POSITION * parent ) {
    
    GRAPHIC_OBJECT
        * object = ObjectProxy.GetResource< GRAPHIC_OBJECT >();
    GRAPHIC_OBJECT_RENDER_OPTIONS
        options,
        * parent_options = NULL;
    
    options.SetPosition( component->GetPosition() + component->GetPositionOffset() );
    options.SetOrientation(component->GetOrientation() );
    options.SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
    
    if ( parent != NULL ) {
        
        parent_options = new GRAPHIC_OBJECT_RENDER_OPTIONS;
        parent_options->SetPosition( parent->GetPosition() + parent->GetPositionOffset() );
        parent_options->SetOrientation(parent->GetOrientation() );
        parent_options->SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
        
        options.SetParent( parent_options );
    }

    if ( renderer.GetPassIndex() == 0 ) {
        
        object->Render( renderer, options, EffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >() );
    }
    else if ( renderer.GetPassIndex() == 1 ) {
        
        object->Render( renderer, options, ShadowmapEffectProxy.GetResource< GRAPHIC_SHADER_EFFECT >() );
    }
    
    if ( parent_options != NULL  ) {
        delete parent_options;
    }
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
        
        size_t b = sizeof(GAMEPLAY_COMPONENT_RENDER) * GAMEPLAY_COMPONENT_BASE_COUNT;
        stream.OutputBytes((uint8_t *) (*InternalVector)[ i ].MemoryArray, b );
        
        stream >> (*InternalVector)[ i ].LastIndex;
        
        LastIndex = (*InternalVector)[ i ].LastIndex;
        LastOffset = i;
    }
}

std::vector< GAMEPLAY_COMPONENT_RENDER::INTERNAL_ARRAY_R >
    * GAMEPLAY_COMPONENT_RENDER::InternalVector;
int GAMEPLAY_COMPONENT_RENDER::LastIndex = -1;
int GAMEPLAY_COMPONENT_RENDER::LastOffset = -1;
