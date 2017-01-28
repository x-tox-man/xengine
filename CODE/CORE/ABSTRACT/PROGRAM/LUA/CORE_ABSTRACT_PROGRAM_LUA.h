//
//  CORE_ABSTRACT_PROGRAM_LUA.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_LUA__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_LUA__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"
#include <assert.h>

XS_CLASS_BEGIN_WITH_ANCESTOR(CORE_ABSTRACT_PROGRAM_LUA, CORE_ABSTRACT_PROGRAM_FACTORY)

    CORE_HELPERS_FACTORY_Element(CORE_ABSTRACT_PROGRAM_LUA, CORE_ABSTRACT_PROGRAM_FACTORY, CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE, CORE_ABSTRACT_PROGRAM_RUNTIME_Lua)

    CORE_ABSTRACT_PROGRAM_LUA();

    virtual void Load( const char *, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME & );
    virtual void Execute();
    virtual void ExecuteFunction( const char * function, int args, int results, int error_func );

    template <typename __PARAMETER__>
    void AddParameter( __PARAMETER__ parameter, int index) {
        
        CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer< __PARAMETER__, std::is_pointer< __PARAMETER__ >::value >::PushObjectOrPointer( parameter, Runtime->getLuaState() );
    }

private:

    CORE_ABSTRACT_RUNTIME_LUA *
        Runtime;

XS_CLASS_END


#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_LUA__) */
