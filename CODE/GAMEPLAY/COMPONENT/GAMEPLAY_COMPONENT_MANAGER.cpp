//
//  GAMEPLAY_COMPONENT_MANAGER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "CORE_MEMORY.h"
#include "CORE_DATA_STREAM.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "GAMEPLAY_COMPONENT_ACTION.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"

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
        InternalVector[0].LastIndex = 0;
    }
    
    GAMEPLAY_COMPONENT_ENTITY * en = (GAMEPLAY_COMPONENT_ENTITY *) new (InternalVector[ 0 ].MemoryArray + ( ++InternalVector[ 0 ].LastIndex ) ) GAMEPLAY_COMPONENT_ENTITY();
    
    en->GetHandle().SetIndex( InternalVector[ 0 ].LastIndex );
    en->GetHandle().SetOffset( 0 );
    
    return en;
}

void GAMEPLAY_COMPONENT_MANAGER::Clear() {
    
    InternalVector.clear();
    
    if ( InternalVector.size() != 16 ) {
        
        InternalVector.resize(16);
    }
    
    for (int i = 0; i < 16; i++) {
        
        InternalVector[i].MemoryArray = (GAMEPLAY_COMPONENT_ENTITY * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( GAMEPLAY_COMPONENT_ENTITY ) );
        InternalVector[i].LastIndex = 0;
    }
}

void GAMEPLAY_COMPONENT_MANAGER::SaveToStream( CORE_DATA_STREAM & stream ) {
    
    if ( InternalVector.size() ) {
        
        stream << InternalVector.size();
        
        for ( int i = 0; i< InternalVector.size(); i++ ) {
            
            stream.InputBytes((uint8_t *) &InternalVector[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_ENTITY) * GAMEPLAY_COMPONENT_BASE_COUNT );
            
            stream << InternalVector[ i ].LastIndex;
        }
    }
}

void GAMEPLAY_COMPONENT_MANAGER::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
    size_t size;
    
    stream >> size;
    
    GAMEPLAY_COMPONENT * components[ GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS ];
    
    for (int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS; i++) {
        
        components[ i ] = NULL;
    }
    
    components[ GAMEPLAY_COMPONENT_TYPE_Position ] = GAMEPLAY_COMPONENT_POSITION::GetFactoryElement();
    components[ GAMEPLAY_COMPONENT_TYPE_Render ] = GAMEPLAY_COMPONENT_RENDER::GetFactoryElement();
    components[ GAMEPLAY_COMPONENT_TYPE_Action ] = GAMEPLAY_COMPONENT_ACTION::GetFactoryElement();
    components[ GAMEPLAY_COMPONENT_TYPE_Animation ] = GAMEPLAY_COMPONENT_ANIMATION::GetFactoryElement();
    components[ GAMEPLAY_COMPONENT_TYPE_Script ] = GAMEPLAY_COMPONENT_SCRIPT::GetFactoryElement();
    components[ GAMEPLAY_COMPONENT_TYPE_Physics ] = GAMEPLAY_COMPONENT_PHYSICS::GetFactoryElement();
    
    InternalVector.resize( size );
    
    for ( int i = 0; i< size; i++ ) {
        
        stream.OutputBytes((uint8_t *) InternalVector[ i ].MemoryArray, sizeof(GAMEPLAY_COMPONENT_ENTITY) * GAMEPLAY_COMPONENT_BASE_COUNT );
        stream >> InternalVector[ i ].LastIndex;
        
        for (int k = 0; k < GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS; k++ ){
            
            if ( components[ k ] != NULL ) {
                
                auto item = components[ k ];
                
                for ( int j = 0; j < InternalVector[ i ].LastIndex; j++ ) {
                    
                    InternalVector[ i ].MemoryArray[ j ].PatchMemory( k, item );
                }
            }
            else {
                
                continue;
            }
        }
    }
}

