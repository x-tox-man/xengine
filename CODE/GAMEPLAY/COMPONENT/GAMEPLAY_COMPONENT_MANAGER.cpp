//
//  GAMEPLAY_COMPONENT_MANAGER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "CORE_MEMORY.h"

GAMEPLAY_COMPONENT_MANAGER::GAMEPLAY_COMPONENT_MANAGER() :
    InternalVector() {
    
}

GAMEPLAY_COMPONENT_MANAGER::~GAMEPLAY_COMPONENT_MANAGER() {

    for ( int i = 0; i < InternalVector.size(); i++ ) {
        
        CORE_MEMORY_ALLOCATOR_Free( InternalVector[ i ].MemoryArray );
    }
}

void GAMEPLAY_COMPONENT_MANAGER::Initialize() {

}

GAMEPLAY_COMPONENT_ENTITY * GAMEPLAY_COMPONENT_MANAGER::CreateEntity() {
    
    int index = (int) InternalVector.size();
    
    if( index == 0) {
        
        if ( InternalVector.size() != 16 ) {
            
            InternalVector.resize(16);
        }
        
        InternalVector[0].MemoryArray = (GAMEPLAY_COMPONENT_ENTITY * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_ENTITY ) );
        InternalVector[0].LastIndex = -1;
    }
    
    return new (InternalVector[ 0 ].MemoryArray + ( ++InternalVector[ 0 ].LastIndex ) ) GAMEPLAY_COMPONENT_ENTITY();
}
