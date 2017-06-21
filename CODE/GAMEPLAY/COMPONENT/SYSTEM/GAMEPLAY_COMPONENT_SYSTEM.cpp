//
//  GAMEPLAY_COMPONENT_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

XS_IMPLEMENT_INTERNAL_STL_MAP_MEMORY_LAYOUT(GAMEPLAY_COMPONENT_ENTITY_PROXY *, GAMEPLAY_COMPONENT_ENTITY_HANDLE)

typedef std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * > MGCEHH;
XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_SYSTEM )
    XS_DEFINE_ClassMember( MGCEHH , EntitiesTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GAMEPLAY_COMPONENT_SYSTEM::GAMEPLAY_COMPONENT_SYSTEM() :
    EntitiesTable() {
    
}

GAMEPLAY_COMPONENT_SYSTEM::~GAMEPLAY_COMPONENT_SYSTEM() {

    EntitiesTable.clear();
}

void GAMEPLAY_COMPONENT_SYSTEM::Initialize() {
    
    /*  Tricky, for now I decide to create vectors of 16 element that hold pointers
        Every internal vector will have 2048 places for its component type
     
     TODO : factorize all this code at GAMEPLAY_COMPONENT level
     */
    
    /*GAMEPLAY_COMPONENT_POSITION::InternalVector.resize(16);
    GAMEPLAY_COMPONENT_POSITION::InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_POSITION * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_POSITION ) );
    GAMEPLAY_COMPONENT_POSITION::InternalVector[0].LastIndex = -1;
    
    GAMEPLAY_COMPONENT_PHYSICS::InternalVector.resize(16);
    GAMEPLAY_COMPONENT_PHYSICS::InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_PHYSICS * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_PHYSICS ) );
    GAMEPLAY_COMPONENT_PHYSICS::InternalVector[0].LastIndex = -1;
    
    GAMEPLAY_COMPONENT_ORIENTATION::InternalVector.resize(16);
    GAMEPLAY_COMPONENT_ORIENTATION::InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_ORIENTATION * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_ORIENTATION ) );
    GAMEPLAY_COMPONENT_ORIENTATION::InternalVector[0].LastIndex = -1;*/
}

void GAMEPLAY_COMPONENT_SYSTEM::Update( float time_step ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::Render() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::Finalize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM::AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    EntitiesTable[ handle ] = new GAMEPLAY_COMPONENT_ENTITY_PROXY( entity );
}

void GAMEPLAY_COMPONENT_SYSTEM::RemoveEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    EntitiesTable.erase( handle );
}

void GAMEPLAY_COMPONENT_SYSTEM::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    XS_CLASS_SERIALIZER< GAMEPLAY_COMPONENT_SYSTEM >::Serialize< std::true_type >( *this, stream );
}

void GAMEPLAY_COMPONENT_SYSTEM::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    XS_CLASS_SERIALIZER< GAMEPLAY_COMPONENT_SYSTEM >::Serialize< std::false_type >( *this, stream );
    
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        it->second->SetEntity( GAMEPLAY_COMPONENT_MANAGER::GetInstance().FindEntity( it->first ) );
        
        it++;
    }
}
