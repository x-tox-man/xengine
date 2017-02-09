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

GAMEPLAY_COMPONENT_SYSTEM::GAMEPLAY_COMPONENT_SYSTEM() :
    EntitiesVector() {
    
}

GAMEPLAY_COMPONENT_SYSTEM::~GAMEPLAY_COMPONENT_SYSTEM() {

    std::vector< GAMEPLAY_COMPONENT_ENTITY * >::iterator it = EntitiesVector.begin();
    
    while (it != EntitiesVector.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
    }
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

void GAMEPLAY_COMPONENT_SYSTEM::AddEntity( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    EntitiesVector.push_back( entity );
}
