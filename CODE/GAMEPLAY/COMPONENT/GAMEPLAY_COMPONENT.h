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

template <typename INTERNAL_ARRAY, typename _COMPONENT_TYPE_ >
static std::vector< INTERNAL_ARRAY > * InitializeMemory() {
    
    auto internal_vector = new std::vector< INTERNAL_ARRAY >();
    
    int index = (int) internal_vector->size();
    
    if( index == 0) {
        
        internal_vector->resize(1);
        (*internal_vector)[0].MemoryArray = (_COMPONENT_TYPE_ * ) CORE_MEMORY_ALLOCATOR::Allocate(2048 * sizeof( _COMPONENT_TYPE_ ) );
        (*internal_vector)[0].LastIndex = -1;
    }
    
    return internal_vector;
}

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT();
    virtual ~GAMEPLAY_COMPONENT();

CORE_HELPERS_FACTORY_Define(GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE )

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT__) */
