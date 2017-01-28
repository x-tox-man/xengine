//
//  CORE_ABSTRACT_RUNTIME_V8.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_V8__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_V8__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(CORE_ABSTRACT_RUNTIME_V8, CORE_ABSTRACT_PROGRAM_RUNTIME< CORE_ABSTRACT_RUNTIME_V8 >)

    CORE_ABSTRACT_RUNTIME_V8();

    virtual void Initialize();
    virtual void Finalize();


    template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND>
    void bind(RETURN_TYPE returnType ) {
    
        CORE_RUNTIME_Abort();
    }

    template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER1, typename PARAMETER2>
    void bind(RETURN_TYPE returnType ) {
    
        CORE_RUNTIME_Abort();
    }

    template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER, typename PARAMETER2, typename PARAMETER3>
    void bind(RETURN_TYPE returnType ) {
    
        CORE_RUNTIME_Abort();
    }

    template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER, typename PARAMETER2, typename PARAMETER3, typename PARAMETER4>
    void bind(RETURN_TYPE returnType ) {
    
        CORE_RUNTIME_Abort();
    }

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_V8__) */
