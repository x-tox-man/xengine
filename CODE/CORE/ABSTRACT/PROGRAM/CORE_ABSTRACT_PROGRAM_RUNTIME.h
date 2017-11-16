//
//  CORE_ABSTRACT_PROGRAM_RUNTIME.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_RUNTIME__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_RUNTIME__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_BASE_PROGRAM_RUNTIME.h"

template< typename DERIVED_CLASS >
class CORE_ABSTRACT_PROGRAM_RUNTIME : public CORE_ABSTRACT_BASE_PROGRAM_RUNTIME {

public :
    CORE_ABSTRACT_PROGRAM_RUNTIME() {

    }
    
    virtual ~CORE_ABSTRACT_PROGRAM_RUNTIME() {
        
    }

    virtual void Initialize() = 0;
    virtual void Finalize() = 0;

    template <typename CLASS_TO_BIND >
    void bind( void (CLASS_TO_BIND::*voidPointerFunction)(void), const char * methodName ) {

        DERIVED_CLASS::bind( &CLASS_TO_BIND::voidPointerFunction);
    }

};

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_RUNTIME__) */
