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
    BoundingObject(),
    Color( CORE_COLOR_White ),
    ScaleFactor( 1.0f ) {
    
}

GAMEPLAY_COMPONENT_RENDER::~GAMEPLAY_COMPONENT_RENDER() {

}

void * GAMEPLAY_COMPONENT_RENDER::operator new( size_t size ) {
    
    unsigned int index = (int) InternalVector.size();
    
    if ( index == 0 ) {
        
        if ( GAMEPLAY_COMPONENT_RENDER::InternalVector.size() != 16 ) {
            
            GAMEPLAY_COMPONENT_RENDER::InternalVector.resize(16);
        }
        
        GAMEPLAY_COMPONENT_RENDER::InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_RENDER * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_RENDER ) );
        GAMEPLAY_COMPONENT_RENDER::InternalVector[0].LastIndex = -1;
    }
    
    return ( void *) &( GAMEPLAY_COMPONENT_RENDER::InternalVector[ 0 ].MemoryArray[++GAMEPLAY_COMPONENT_RENDER::InternalVector[ 0 ].LastIndex] );
}

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component ) {
    
    renderer.EnableColor(true);
    Object->SetPosition( component->GetPosition() );
    Object->SetOrientation(component->GetOrientation() );
    Object->SetColor( Color );
    Object->SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
    
    Object->Render( renderer );
    renderer.EnableColor(false);
}

std::vector< GAMEPLAY_COMPONENT_RENDER::INTERNAL_ARRAY_R > GAMEPLAY_COMPONENT_RENDER::InternalVector = std::vector< GAMEPLAY_COMPONENT_RENDER::INTERNAL_ARRAY_R >();
