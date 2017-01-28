//
//  CORE_MEMORY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/01/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_MEMORY__
#define __GAME_ENGINE_REBORN__CORE_MEMORY__

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN( CORE_MEMORY_ALLOCATOR )
public :
    static void * Allocate( unsigned int size );
    static void Free( void * memory_pointer );

private:
    CORE_MEMORY_ALLOCATOR();

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_MEMORY__) */
