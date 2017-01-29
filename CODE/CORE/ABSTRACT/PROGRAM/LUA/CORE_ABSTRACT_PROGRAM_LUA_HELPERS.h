//
//  CORE_ABSTRACT_PROGRAM_LUA_HELPERS.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_ABSTRACT_PROGRAM_LUA_HELPERS_h
#define CORE_ABSTRACT_PROGRAM_LUA_HELPERS_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_ABSTRACT_FUNCTION.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"

XS_CLASS_BEGIN( CORE_ABSTRACT_PROGRAM_LUA_HELPERS )

CORE_ABSTRACT_PROGRAM_LUA_HELPERS();
~CORE_ABSTRACT_PROGRAM_LUA_HELPERS();

CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( CORE_ABSTRACT_PROGRAM_LUA_HELPERS )

template <typename __TYPE1__, typename __TYPE2__>
static CORE_HELPERS_CALLBACK_2< __TYPE1__ , __TYPE2__ > & CreateLuaCallback( const char * function_name ) {
    
    CORE_RUNTIME_Abort();// must implement
}

template <typename __TYPE1__>
static CORE_HELPERS_CALLBACK_1< __TYPE1__ > GenerateLuaCallback( __TYPE1__ param1, CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA > * function ) {
    
}

template <typename __TYPE1__, typename __TYPE2__>
static CORE_HELPERS_CALLBACK_2< __TYPE1__, __TYPE2__ > & GenerateLuaCallback( CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA > * function ) {
    
    CORE_HELPERS_CALLBACK_2< __TYPE1__, __TYPE2__ > * callback = new CORE_HELPERS_CALLBACK_2< __TYPE1__, __TYPE2__ >( &Wrapper2< CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA >, __TYPE1__, __TYPE2__, &CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA >::CallLuaCallback< __TYPE1__, __TYPE2__ > >, function );
    
    return *callback;
}

XS_CLASS_END

#endif /* CORE_ABSTRACT_PROGRAM_LUA_HELPERS_h */
