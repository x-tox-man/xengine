//
//  GAMEPLAY_COMPONENT_SYSTEM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_STL_VECTOR_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY_HANDLE )

typedef std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE > MGCEHH;

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_SYSTEM )
    XS_DEFINE_ClassMember( "EntitiesTable", MGCEHH , EntitiesTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GAMEPLAY_COMPONENT_SYSTEM::GAMEPLAY_COMPONENT_SYSTEM() :
    EntitiesTable(),
    Mask( 0 ) {
    
}

GAMEPLAY_COMPONENT_SYSTEM::~GAMEPLAY_COMPONENT_SYSTEM() {

    EntitiesTable.clear();
}

void GAMEPLAY_COMPONENT_SYSTEM::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::Update( void * ecs_base_pointer, float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::Finalize() {
    
    EntitiesTable.clear();
}

void GAMEPLAY_COMPONENT_SYSTEM::AddEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    EntitiesTable.push_back( entity->GetHandle() );
}

void GAMEPLAY_COMPONENT_SYSTEM::RemoveEntity( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    int offset = entity->GetHandle().GetOffset();
    
    while ( it != EntitiesTable.end() ) {
        
        if ( it->GetOffset() == offset ) {
            
            EntitiesTable.erase( it );
            break;
        }
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    XS_CLASS_SERIALIZER< GAMEPLAY_COMPONENT_SYSTEM, CORE_DATA_STREAM >::Serialize< std::true_type >( "system", *this, stream );
}

void GAMEPLAY_COMPONENT_SYSTEM::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    XS_CLASS_SERIALIZER< GAMEPLAY_COMPONENT_SYSTEM, CORE_DATA_STREAM >::Serialize< std::false_type >( "system", *this, stream );
}
