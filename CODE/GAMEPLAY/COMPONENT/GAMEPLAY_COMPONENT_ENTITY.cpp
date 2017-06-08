//
//  GAMEPLAY_COMPONENT_ENTITY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_COMPONENT_ENTITY )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( GAMEPLAY_COMPONENT::PTR, GAMEPLAY_COMPONENT_ENTITY, GetComponent, int )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_COMPONENT_ENTITY )


GAMEPLAY_COMPONENT_ENTITY::GAMEPLAY_COMPONENT_ENTITY() :
    Components(),
    Parent( NULL ),
    ChildEntities(),
    Index( -1 ) {
    
    for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS; i++ ) {
        
        Components[ i ] = NULL;
    }
    
    for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
        
        ChildEntities[ i ] = NULL;
    }
}

GAMEPLAY_COMPONENT_ENTITY::~GAMEPLAY_COMPONENT_ENTITY() {

}

void GAMEPLAY_COMPONENT_ENTITY::SetPosition( const CORE_MATH_VECTOR & position ) {
    
    GAMEPLAY_COMPONENT_POSITION * position_component = (GAMEPLAY_COMPONENT_POSITION *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    GAMEPLAY_COMPONENT_PHYSICS * physics_component = (GAMEPLAY_COMPONENT_PHYSICS *) GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    position_component->SetPosition( position );
    physics_component->ForcePosition( position );
}
