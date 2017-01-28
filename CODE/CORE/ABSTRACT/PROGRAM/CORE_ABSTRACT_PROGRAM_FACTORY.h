//
//  CORE_ABSTRACT_PROGRAM_FACTORY.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_FACTORY__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_FACTORY__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_RUNTIME_V8.h"
#include "CORE_ABSTRACT_FUNCTION_PARAMETER.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN(CORE_ABSTRACT_PROGRAM_FACTORY)

    CORE_HELPERS_FACTORY_Define( CORE_ABSTRACT_PROGRAM_FACTORY, CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE )

public :

    CORE_ABSTRACT_PROGRAM_FACTORY();


    virtual void Load( const char *, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME &);
    virtual void Execute();
    virtual void ExecuteFunction( const char * function, int parameters, int results, int error_func );

    template <typename __PARAMETER__>
    void AddParameter( __PARAMETER__ parameter, int index) {
        
        CORE_RUNTIME_Abort();
    }

    //Wrong :
    static CORE_ABSTRACT_PROGRAM_FACTORY * CurrentProgram;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM__) */
