//
//  CORE_ABSTRACT_RUNTIME_LUA.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"
#include "SERVICE_LOGGER.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

XS_CLASS_BEGIN_WITH_ANCESTOR( CORE_ABSTRACT_RUNTIME_LUA, CORE_ABSTRACT_PROGRAM_RUNTIME< CORE_ABSTRACT_RUNTIME_LUA > )

CORE_ABSTRACT_RUNTIME_LUA () : CORE_ABSTRACT_PROGRAM_RUNTIME() {
    
}

private :
int LuaMethods;
int LuaMetatable;

template <typename TEMPLATE_TYPE>
union USER_DATA_TYPE {
    TEMPLATE_TYPE * ptr;
    void (TEMPLATE_TYPE::*vfp)(void);
    void (*svfp)(void);
};

template <typename TEMPLATE_TYPE, typename __TYPE_1__ >
union USER_DATA_TYPE_1 {
    TEMPLATE_TYPE * ptr;
    void (TEMPLATE_TYPE::*vfp)(__TYPE_1__);
};

template <typename TEMPLATE_TYPE, typename __TYPE_1__, typename __TYPE_2__ >
union USER_DATA_TYPE_2 {
    TEMPLATE_TYPE * ptr;
    void (TEMPLATE_TYPE::*vfp)(__TYPE_2__);
};

template < typename __TYPE_1__, typename TEMPLATE_TYPE >
union YIELD_USER_DATA_TYPE {
    TEMPLATE_TYPE * ptr;
    __TYPE_1__ (TEMPLATE_TYPE::*vfp)(void);
    __TYPE_1__ (*svfp)(void);
};

public :

template < typename CLASS_TO_BIND >
void initBindings() {
    //-----------------------------
    // first init step
    //-----------------------------
    
    lua_newtable( runtimeLuaState );
    LuaMethods = lua_gettop( runtimeLuaState );
    
    luaL_newmetatable( runtimeLuaState, CLASS_TO_BIND::CLASS_NAME );
    LuaMetatable = lua_gettop( runtimeLuaState );
    
    // store method table in globals so that
    // scripts can add functions written in Lua.
    lua_pushstring( runtimeLuaState, CLASS_TO_BIND::CLASS_NAME );
    lua_pushvalue( runtimeLuaState, LuaMethods );
    //lua_pushglobaltable( runtimeLuaState );
    lua_setglobal(runtimeLuaState, CLASS_TO_BIND::CLASS_NAME );
    
    lua_pushliteral( runtimeLuaState, "__metatable" );
    lua_pushvalue( runtimeLuaState, LuaMethods );
    lua_settable( runtimeLuaState, LuaMetatable );  // hide metatable from Lua getmetatable()
    
    lua_pushliteral( runtimeLuaState, "__index" );
    lua_pushvalue(runtimeLuaState, LuaMethods );
    lua_settable( runtimeLuaState, LuaMetatable );
    
    lua_pushliteral( runtimeLuaState, "__tostring" );
    lua_pushcfunction( runtimeLuaState, tostring_T<CLASS_TO_BIND> );
    lua_settable( runtimeLuaState, LuaMetatable );

    lua_pushliteral( runtimeLuaState, "__gc" );
    lua_pushcfunction( runtimeLuaState, gc_T< CLASS_TO_BIND > );
    lua_settable( runtimeLuaState, LuaMetatable );

    lua_newtable( runtimeLuaState );                // mt for method table
    int mt = lua_gettop( runtimeLuaState );
    lua_pushliteral( runtimeLuaState, "__call" );
    lua_pushcfunction( runtimeLuaState, new_T< CLASS_TO_BIND > );
    lua_pushliteral( runtimeLuaState, "new" );
    lua_pushvalue( runtimeLuaState, -2 );           // dup new_T function
    lua_settable( runtimeLuaState, LuaMethods );       // add new_T to method table
    lua_settable( runtimeLuaState, mt );            // mt.__call = new_T
    lua_setmetatable( runtimeLuaState, LuaMethods );
}

template < typename CLASS_TO_BIND >
void bind( void (CLASS_TO_BIND::*voidPointerFunction)(void), const char * methodName ) {

    USER_DATA_TYPE< CLASS_TO_BIND> * vfpu = new USER_DATA_TYPE< CLASS_TO_BIND>();
    vfpu->vfp = voidPointerFunction;
    lua_pushstring( runtimeLuaState, methodName );
    lua_pushlightuserdata( runtimeLuaState, vfpu );
    lua_pushcclosure( runtimeLuaState, thunk<CLASS_TO_BIND>, 1 );
    lua_settable( runtimeLuaState, LuaMethods );
}

template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
void staticBind( __RETURN_TYPE__ (*voidPointerFunction)(void), const char * methodName ) {
    
    YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> * vfpu = new YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND>();
    vfpu->svfp = voidPointerFunction;
    lua_pushstring( runtimeLuaState, methodName );
    lua_pushlightuserdata( runtimeLuaState, vfpu );
    lua_pushcclosure( runtimeLuaState, yield_thunk<__RETURN_TYPE__, CLASS_TO_BIND>, 1 );
    lua_settable( runtimeLuaState, LuaMethods );
}

template < typename CLASS_TO_BIND >
void staticBind( void (*voidPointerFunction)(void), const char * methodName ) {
    
    USER_DATA_TYPE< CLASS_TO_BIND> * vfpu = new USER_DATA_TYPE< CLASS_TO_BIND>();
    
    vfpu->svfp = voidPointerFunction;
    lua_pushstring( runtimeLuaState, methodName );
    lua_pushlightuserdata( runtimeLuaState, vfpu );
    lua_pushcclosure( runtimeLuaState, sthunk< CLASS_TO_BIND >, 1 );
    lua_settable( runtimeLuaState, LuaMethods );
}

template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
void bind( __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)(void), const char * methodName ) {
    
    YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> * vfpu = new YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND>();
    
    vfpu->vfp = yieldPointerFunction;
    lua_pushstring( runtimeLuaState, methodName );
    lua_pushlightuserdata( runtimeLuaState, vfpu );
    lua_pushcclosure( runtimeLuaState, thunk<CLASS_TO_BIND>, 1 );
    lua_settable( runtimeLuaState, LuaMethods );
}

void completeBindings() {
    
    lua_pop( runtimeLuaState, 2 );  // drop metatable and method table
}

template <typename CLASS_TO_BIND, typename __PARAM_TYPE_1__ >
void bind( void (CLASS_TO_BIND::*voidPointerFunction)( __PARAM_TYPE_1__ ), const char * methodName ) {
    
    USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__> * vfpu = new USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__ >();
    vfpu->vfp = voidPointerFunction;
    lua_pushstring( runtimeLuaState, methodName );
    lua_pushlightuserdata( runtimeLuaState, vfpu );
    lua_pushcclosure( runtimeLuaState, thunk_1< CLASS_TO_BIND, __PARAM_TYPE_1__ >, 1 );
    lua_settable( runtimeLuaState, LuaMethods );
}

template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND>
void bind(RETURN_TYPE returnType ) {
    
}

template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER1, typename PARAMETER2>
void bind(RETURN_TYPE returnType ) {
    
}

template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER, typename PARAMETER2, typename PARAMETER3>
void bind(RETURN_TYPE returnType ) {
    
}

template <typename CLASS_NAME, typename RETURN_TYPE, typename FUNCTION_TO_BIND, typename PARAMETER, typename PARAMETER2, typename PARAMETER3, typename PARAMETER4>
void bind(RETURN_TYPE returnType ) {
    
}

template < typename CLASS_TO_BIND >
static int thunk(lua_State *L) {
    // stack has userdata, followed by method args
    CLASS_TO_BIND *obj = check_lua_object<CLASS_TO_BIND>( L, 1 );  // get 'self', or if you prefer, 'this'
    lua_remove(L, 1);  // remove self so member function args start at index 1
    // get member function from upvalue
    
    typedef void (CLASS_TO_BIND::*voidPointerFunction)(void);
    
    USER_DATA_TYPE< CLASS_TO_BIND> * vfpu = (USER_DATA_TYPE< CLASS_TO_BIND> * ) lua_touserdata(L, lua_upvalueindex(1));

    (obj->*(vfpu->vfp))();
    return 1;  // call member function
}

template < typename CLASS_TO_BIND >
static int sthunk(lua_State *L) {
    // stack has userdata, followed by method args

    lua_remove(L, 1);  // remove self so member function args start at index 1
    // get member function from upvalue
    
    typedef void (*voidPointerFunction)(void);
    
    USER_DATA_TYPE< CLASS_TO_BIND> * vfpu = (USER_DATA_TYPE< CLASS_TO_BIND> * ) lua_touserdata(L, lua_upvalueindex(1));
    
    (*(vfpu->svfp))();
    return 1;  // call member function
}

template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
static int yield_sthunk(lua_State *L) {
    // stack has userdata, followed by method args
    
    lua_remove(L, 1);  // remove self so member function args start at index 1
    // get member function from upvalue
    
    typedef void (*voidPointerFunction)(void);
    
    YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> * vfpu = ( YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> * ) lua_touserdata(L, lua_upvalueindex(1));
    
    __RETURN_TYPE__ & result = (*(vfpu->svfp))();
    
    return 1;  // call member function
}

template < typename CLASS_TO_BIND, typename __TYPE_1__ >
static int thunk_1(lua_State *L) {
    // stack has userdata, followed by method args
    CLASS_TO_BIND *obj = check_lua_object<CLASS_TO_BIND>( L, 1);  // get 'self', or if you prefer, 'this'
    lua_remove(L, 1);  // remove self so member function args start at index 1
    // get member function from upvalue
    
    typedef void (CLASS_TO_BIND::*voidPointerFunction)(void);
    
    USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> * vfpu = (USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> * ) lua_touserdata(L, lua_upvalueindex(1));
    
    ( obj->*( vfpu->vfp ) )( lua_tostring( L, lua_gettop( L ) ) );
    return 1;  // call member function
}

template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
static int yield_thunk(lua_State *L) {
    // stack has userdata, followed by method args
    CLASS_TO_BIND *obj = check_lua_object<CLASS_TO_BIND>( L, 1);  // get 'self', or if you prefer, 'this'
    lua_remove(L, 1);  // remove self so member function args start at index 1
    // get member function from upvalue
    
    typedef __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)(void);
    
    YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND > * vfpu = (YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND > * ) lua_touserdata(L, lua_upvalueindex(1));
    
    int argc = lua_gettop(L);
    
    char * test = (char * )lua_tostring(L, lua_gettop(L));
    
    
    (obj->*(vfpu->vfp))(test);
    return 1;  // call member function
}

// get userdata from Lua stack and return pointer to T object
template < typename CLASS_TO_BIND >
static CLASS_TO_BIND *check_lua_object(lua_State *L, int nargs) {
    USER_DATA_TYPE< CLASS_TO_BIND > *ud =
    static_cast< USER_DATA_TYPE< CLASS_TO_BIND > *>(luaL_checkudata(L, nargs, CLASS_TO_BIND::CLASS_NAME));
    if(!ud) SERVICE_LOGGER_Error( "error");//luaL_typerror(L, nargs, CLASS_TO_BIND::CLASS_NAME );
    return ud->ptr;  // pointer to T object
}

// create a new T object and
// push onto the Lua stack a userdata containing a pointer to T object
template < typename CLASS_TO_BIND >
static int new_T(lua_State *L) {
    lua_remove(L, 1);   // use classname:new(), instead of classname.new()
    CLASS_TO_BIND *obj = new CLASS_TO_BIND();  // call constructor for T objects
    USER_DATA_TYPE< CLASS_TO_BIND > *ud =
    static_cast< USER_DATA_TYPE< CLASS_TO_BIND > *>(lua_newuserdata(L, sizeof(USER_DATA_TYPE< CLASS_TO_BIND >)));
    ud->ptr = obj;  // store pointer to object in userdata
    luaL_getmetatable(L, CLASS_TO_BIND::CLASS_NAME);  // lookup metatable in Lua registry
    lua_setmetatable(L, -2);
    return 1;  // userdata containing pointer to T object
}

// garbage collection metamethod
template < typename CLASS_TO_BIND >
static int gc_T(lua_State *L) {
    USER_DATA_TYPE< CLASS_TO_BIND > *ud = static_cast< USER_DATA_TYPE< CLASS_TO_BIND > * >(lua_touserdata(L, 1));
    CLASS_TO_BIND *obj = ud->ptr;
    delete obj;  // call destructor for T objects
    return 0;
}

template < typename CLASS_TO_BIND >
static int tostring_T (lua_State *L) {
    char buff[32];
    USER_DATA_TYPE< CLASS_TO_BIND > *ud = static_cast< USER_DATA_TYPE< CLASS_TO_BIND > * >(lua_touserdata(L, 1));
    CLASS_TO_BIND *obj = ud->ptr;
    SERVICE_LOGGER_Info(buff, "%p", obj);
    lua_pushfstring(L, "%s (%s)", CLASS_TO_BIND::CLASS_NAME, buff);
    return 1;
}

virtual void Initialize();

virtual void Finalize();

lua_State * getLuaState() { return runtimeLuaState; }

private:

    lua_State
        * runtimeLuaState;
    
XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__) */
