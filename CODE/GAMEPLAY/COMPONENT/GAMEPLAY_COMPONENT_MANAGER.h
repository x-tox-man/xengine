//
//  GAMEPLAY_COMPONENT_MANAGER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_HELPERS_UNIQUE.h"

XS_CLASS_BEGIN( GAMEPLAY_COMPONENT_MANAGER )

XS_DEFINE_UNIQUE( GAMEPLAY_COMPONENT_MANAGER )

void Initialize();

GAMEPLAY_COMPONENT_ENTITY * CreateEntity();

inline GAMEPLAY_COMPONENT_ENTITY * GetEntity( int index ) {
    
    return &InternalVector[0].MemoryArray[ index ];
}

private :

struct INTERNAL_ARRAY{
    int LastIndex;
    GAMEPLAY_COMPONENT_ENTITY * MemoryArray;
};

std::vector< INTERNAL_ARRAY > InternalVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_MANAGER__) */
