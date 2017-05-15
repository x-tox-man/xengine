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
    Material( NULL ),
    ScaleFactor( 1.0f ) {
    
}

GAMEPLAY_COMPONENT_RENDER::~GAMEPLAY_COMPONENT_RENDER() {

}

void * GAMEPLAY_COMPONENT_RENDER::operator new( size_t size ) {
    
    static std::vector< INTERNAL_ARRAY_R > * InternalVector = InitializeMemory<INTERNAL_ARRAY_R, GAMEPLAY_COMPONENT_RENDER>();
    
    return ( void *) &( (*InternalVector)[ 0 ].MemoryArray[ ++(( *InternalVector)[ 0 ].LastIndex) ] );
}

void GAMEPLAY_COMPONENT_RENDER::operator delete ( void* ptr ) {
    
}

void GAMEPLAY_COMPONENT_RENDER::Render( GRAPHIC_RENDERER & renderer, GAMEPLAY_COMPONENT_POSITION * component ) {
    
    renderer.EnableColor(true);
    Object->SetPosition( component->GetPosition() );
    Object->SetOrientation(component->GetOrientation() );
    Object->SetColor( Material->GetColor() );
    Object->SetScaleFactor( CORE_MATH_VECTOR(ScaleFactor, ScaleFactor,ScaleFactor, 1.0f) );
    Object->GetShaderTable()[0] = &Material->GetEffect()->GetProgram();
    Object->Render( renderer );
    renderer.EnableColor(false);
}
