//
//  GAMEPLAY_COMPONENT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

#define GAMEPLAY_COMPONENT_BASE_COUNT 2048

template <typename INTERNAL_ARRAY, typename _COMPONENT_TYPE_ >
static std::vector< INTERNAL_ARRAY > * InitializeMemory() {
    
    auto internal_vector = new std::vector< INTERNAL_ARRAY >();
    
    int index = (int) internal_vector->size();
    
    if( index == 0) {
        
        internal_vector->resize(1);
        (*internal_vector)[0].MemoryArray = (_COMPONENT_TYPE_ * ) CORE_MEMORY_ALLOCATOR::Allocate( GAMEPLAY_COMPONENT_BASE_COUNT * sizeof( _COMPONENT_TYPE_ ) );
        (*internal_vector)[0].LastIndex = -1;
    }
    
    return internal_vector;
}

template <typename INTERNAL_ARRAY, typename _COMPONENT_TYPE_ >
static void InitializeMemory( std::vector< INTERNAL_ARRAY > & internal_vector, int index) {
    
    internal_vector[index].MemoryArray = (_COMPONENT_TYPE_ * ) CORE_MEMORY_ALLOCATOR::Allocate( GAMEPLAY_COMPONENT_BASE_COUNT * sizeof( _COMPONENT_TYPE_ ) );
    internal_vector[index].LastIndex = -1;
}

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT();
    virtual ~GAMEPLAY_COMPONENT();

    virtual GAMEPLAY_COMPONENT * GetComponentAt( int index, int offset ) {
        return NULL;
    }

    XS_DEFINE_SERIALIZABLE

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GAMEPLAY_COMPONENT );

    CORE_HELPERS_FACTORY_Define(GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE )

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__) */
