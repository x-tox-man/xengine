//
//  CORE_ABSTRACT_PROGRAM_LUA.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

CORE_ABSTRACT_PROGRAM_LUA::CORE_ABSTRACT_PROGRAM_LUA() : CORE_ABSTRACT_PROGRAM_FACTORY(), Runtime( NULL ) {
    
}

CORE_ABSTRACT_PROGRAM_LUA::~CORE_ABSTRACT_PROGRAM_LUA() {

}

void CORE_ABSTRACT_PROGRAM_LUA::Load( const char * path, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME & runtime ) {
    
    SERVICE_LOGGER_Error( "CORE_ABSTRACT_PROGRAM_LUA::Load 1" );
    CORE_ABSTRACT_RUNTIME_LUA & luaRuntime = * ((CORE_ABSTRACT_RUNTIME_LUA*) &runtime);
    SERVICE_LOGGER_Error( "CORE_ABSTRACT_PROGRAM_LUA::Load 2" );
    int s = luaL_loadfile( luaRuntime.getLuaState(), path );
    SERVICE_LOGGER_Error( "CORE_ABSTRACT_PROGRAM_LUA::Load 3" );
    if( s != 0 ) {
        
        printf( "%s\n", lua_tostring( luaRuntime.getLuaState(), -1 ) );
        
        SERVICE_LOGGER_Error( "CORE_ABSTRACT_PROGRAM_LUA::Load 4" );
        
        CORE_RUNTIME_Abort();
    }

    Runtime = &luaRuntime;
}

void CORE_ABSTRACT_PROGRAM_LUA::Execute() {
    
    CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram = this;
    
    int result = lua_pcall( Runtime->getLuaState(), 0, 0, 0 );
    
    if( result != 0 ) {
        
        printf( "%s\n", lua_tostring( Runtime->getLuaState(), -1 ) );
        
        CORE_RUNTIME_Abort();
    }
    
    CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram = NULL;
}

void CORE_ABSTRACT_PROGRAM_LUA::ExecuteFunction( const char * function, int args, int results, int error_func ) {
    
    CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram = this;
    lua_getglobal( Runtime->getLuaState(), function );
    
    if ( args == 1 ) {
        
        lua_pushvalue( Runtime->getLuaState(), -2 );
    }
    else if ( args == 2 ) {
        
        lua_pushvalue( Runtime->getLuaState(), -3 );
        lua_pushvalue( Runtime->getLuaState(), -3 );
    }
    
    int s = lua_pcall( Runtime->getLuaState(), args, results, error_func );
    
    if( s != 0 ) {
        
        printf( "%s\n", lua_tostring( Runtime->getLuaState(), -1 ) );
        
        CORE_RUNTIME_Abort();
    }
    
    lua_settop( Runtime->getLuaState(), 0);
    
    CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram = NULL;
}