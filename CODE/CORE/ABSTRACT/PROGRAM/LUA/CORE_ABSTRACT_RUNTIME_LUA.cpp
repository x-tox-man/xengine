//
//  CORE_ABSTRACT_RUNTIME_LUA.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

CORE_ABSTRACT_RUNTIME_LUA::CORE_ABSTRACT_RUNTIME_LUA() {

}

CORE_ABSTRACT_RUNTIME_LUA::~CORE_ABSTRACT_RUNTIME_LUA() {

    if ( runtimeLuaState ) {
        
        Finalize();
    }
}
/*
#if PLATFORM_WINDOWS
    template< >
    CORE_ABSTRACT_PROGRAM_RUNTIME< CORE_ABSTRACT_RUNTIME_LUA >::~CORE_ABSTRACT_PROGRAM_RUNTIME< CORE_ABSTRACT_RUNTIME_LUA >() {

    }
#else

#endif
*/
void CORE_ABSTRACT_RUNTIME_LUA::Initialize() {
    
    runtimeLuaState = luaL_newstate();
    
    luaopen_io(runtimeLuaState); // provides io.*
    luaopen_base(runtimeLuaState);
    luaopen_table(runtimeLuaState);
    luaopen_string(runtimeLuaState);
    luaopen_math(runtimeLuaState);
    luaL_openlibs(runtimeLuaState);
}

void CORE_ABSTRACT_RUNTIME_LUA::Finalize() {
    
    lua_gc(runtimeLuaState, LUA_GCCOLLECT, 0 );
    lua_close( runtimeLuaState );
    
    runtimeLuaState = 0;
}

void CORE_ABSTRACT_RUNTIME_LUA::ExecuteCommand( const char * command ) {
    
    luaL_dostring( runtimeLuaState, command );
}

template <>
const char * LUA_ToValue< const char * >( lua_State * state ) {

    const char * char_value=( const char * ) lua_tostring( state, 1 );
    lua_remove( state, 1 );

    return char_value;
}

template <>
int LUA_ToValue< int >( lua_State * state ) {

    int int_value = (int) lua_tointeger( state, 1 );
    lua_remove( state, 1 );

    return int_value;
}

template <>
long LUA_ToValue< long >( lua_State * state ) {

    long int_value=lua_tointeger( state, 1 );
    lua_remove( state, 1 );

    return int_value;
}

template <>
bool LUA_ToValue< bool >( lua_State * state ) {

    bool boolean_value=lua_toboolean( state, 1 );
    lua_remove( state, 1 );

    return boolean_value;
}

template <>
float LUA_ToValue< float >( lua_State * state ) {

    float float_number=lua_tonumber( state, 1 );
    lua_remove( state, 1 );

    return float_number;
}

template <>
double LUA_ToValue< double >( lua_State * state ) {

    double double_number=lua_tonumber( state, 1 );
    lua_remove( state, 1 );

    return double_number;
}
