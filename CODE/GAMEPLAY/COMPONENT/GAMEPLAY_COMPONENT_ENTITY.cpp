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
#include "GAMEPLAY_COMPONENT_HANDLE.h"
#include "CORE_DATA_STREAM.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( GAMEPLAY_COMPONENT_ENTITY )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_YIELD_METHOD_1( GAMEPLAY_COMPONENT::PTR, GAMEPLAY_COMPONENT_ENTITY, GetComponent, int )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( GAMEPLAY_COMPONENT_ENTITY )

int l = GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY )
    XS_DEFINE_ClassMember( GAMEPLAY_COMPONENT_ENTITY_HANDLE, Handle )
    XS_DEFINE_ClassMemberArray( GAMEPLAY_COMPONENT_HANDLE , ( GAMEPLAY_COMPONENT_HANDLE* & ) *Components, l)
XS_END_INTERNAL_MEMORY_LAYOUT

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY )
XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY * )

GAMEPLAY_COMPONENT_ENTITY::GAMEPLAY_COMPONENT_ENTITY() :
    Components(),
    Parent( NULL ),
    ChildEntities() {
    
    for( int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++ ) {
        
        ChildEntities[ i ] = NULL;
    }
}

GAMEPLAY_COMPONENT_ENTITY::GAMEPLAY_COMPONENT_ENTITY( const GAMEPLAY_COMPONENT_ENTITY & other ) :
    Components(),
    Parent( other.GetParent() ),
    ChildEntities() {
        
    abort();
    
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

void GAMEPLAY_COMPONENT_ENTITY::PatchMemory( int index, GAMEPLAY_COMPONENT * component ) {
    
    Components[ index ].SetComponent( component->GetComponentAt( Components[ index ].GetIndex(), Components[ index ].GetOffset() + 1 ) );
}
