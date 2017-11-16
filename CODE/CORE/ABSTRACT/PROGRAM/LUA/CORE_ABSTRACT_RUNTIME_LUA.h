//
//  CORE_ABSTRACT_RUNTIME_LUA.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"
#include "SERVICE_LOGGER.h"
#include "CORE_DATA_TYPES.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// -- OTHER

// -- PUBLIC TYPES

template< typename T>
struct USER_DATA_TYPE
{
    T InnerType;
    bool ItWasAllocated;
};

template <typename TEMPLATE_TYPE>
union INNER_USER_DATA_TYPE {
    
    TEMPLATE_TYPE * ObjectPointer;
    void (TEMPLATE_TYPE::*voidFunctionPointer)(void);
    void (*staticVoidFunctionPointer)(void);
};

template <typename TEMPLATE_TYPE, typename __TYPE_1__ >
union INNER_USER_DATA_TYPE_1 {
    
    TEMPLATE_TYPE * ObjectPointer;
    void (TEMPLATE_TYPE::*voidFunctionPointer)( __TYPE_1__ );
    void (*staticVoidFunctionPointer)( __TYPE_1__ );
};

template <typename TEMPLATE_TYPE, typename __TYPE_1__, typename __TYPE_2__ >
union INNER_USER_DATA_TYPE_2 {
    
    TEMPLATE_TYPE * ObjectPointer;
    void (TEMPLATE_TYPE::*voidFunctionPointer)(__TYPE_1__, __TYPE_2__);
    void (*staticVoidFunctionPointer)( __TYPE_1__, __TYPE_2__ );
};

template <typename TEMPLATE_TYPE, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
union INNER_USER_DATA_TYPE_3 {
    
    TEMPLATE_TYPE * ObjectPointer;
    void (TEMPLATE_TYPE::*voidFunctionPointer)(__TYPE_1__, __TYPE_2__, __TYPE_3__ );
    void (*staticVoidFunctionPointer)( __TYPE_1__, __TYPE_2__, __TYPE_3__ );
};

template < typename __TYPE_1__, typename TEMPLATE_TYPE >
union INNER_YIELD_USER_DATA_TYPE {
    
    TEMPLATE_TYPE * ObjectPointer;
    __TYPE_1__ (TEMPLATE_TYPE::* yieldFunctionPointer)(void);
    __TYPE_1__ (*StaticYieldFunctionPointer)(void);
};

template < typename __RETURN_TYPE__, typename TEMPLATE_TYPE, typename __TYPE_1__ >
union INNER_YIELD_USER_DATA_TYPE_1 {
    
    TEMPLATE_TYPE * ObjectPointer;
    __RETURN_TYPE__ (TEMPLATE_TYPE::*yieldFunctionPointer)( __TYPE_1__ );
    __RETURN_TYPE__ (*StaticYieldFunctionPointer)( __TYPE_1__ );
};

template < typename __RETURN_TYPE__, typename TEMPLATE_TYPE, typename __TYPE_1__, typename __TYPE_2__ >
union INNER_YIELD_USER_DATA_TYPE_2 {
    
    TEMPLATE_TYPE * ObjectPointer;
    __RETURN_TYPE__ (TEMPLATE_TYPE::*yieldFunctionPointer)( __TYPE_1__, __TYPE_2__ );
    __RETURN_TYPE__ (*StaticYieldFunctionPointer)( __TYPE_1__, __TYPE_2__ );
};

template < typename __RETURN_TYPE__, typename TEMPLATE_TYPE, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
union INNER_YIELD_USER_DATA_TYPE_3 {
    
    TEMPLATE_TYPE * ObjectPointer;
    __RETURN_TYPE__ (TEMPLATE_TYPE::*yieldFunctionPointer)( __TYPE_1__, __TYPE_2__, __TYPE_3__ );
    __RETURN_TYPE__ (*StaticYieldFunctionPointer)( __TYPE_1__, __TYPE_2__, __TYPE_3__ );
};

// -- PUBLIC METHODS

template<typename __CUSTOM_TYPE__, size_t size>
class InnerTypeForValueType;

template< typename __CUSTOM_TYPE__ >
class InnerTypeForValueType < __CUSTOM_TYPE__, 0 > {
    
    public :
    static __CUSTOM_TYPE__ LUA_ToValueRefOrPointer( lua_State * state ) {
        
        typedef typename XS_TYPE_< __CUSTOM_TYPE__ >::Type UserDataType;
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > * data = (USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > *)lua_touserdata( state, 1 );
        
        return *data->InnerType.ObjectPointer;
    }
};

template< typename __CUSTOM_TYPE__ >
class InnerTypeForValueType< __CUSTOM_TYPE__, 1 > {
    
    public :
    static __CUSTOM_TYPE__ LUA_ToValueRefOrPointer( lua_State * state ) {
        
        typedef typename XS_TYPE_< __CUSTOM_TYPE__ >::Type UserDataType;
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > * data = (USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > *)lua_touserdata( state, 1 );
        
        return data->InnerType.ObjectPointer;
    }
};

template < typename __CUSTOM_TYPE__ >
__CUSTOM_TYPE__ LUA_ToValue( lua_State * state ) {
    
    __CUSTOM_TYPE__ user_data = InnerTypeForValueType< __CUSTOM_TYPE__, std::is_pointer< __CUSTOM_TYPE__ >::value >::LUA_ToValueRefOrPointer( state );
    
    lua_remove( state, 1 );

    return user_data;
}

template <>
const char * LUA_ToValue< const char * >( lua_State * state );
template <>
int LUA_ToValue< int >( lua_State * state );

template <>
long LUA_ToValue< long >( lua_State * state );

template <>
bool LUA_ToValue< bool >( lua_State * state );

template <>
float LUA_ToValue< float >( lua_State * state );

template <>
double LUA_ToValue< double >( lua_State * state );

// -- END of LUA_ToValue overloads

// -- BEGIN of LUA_FromValue

template< typename __USER_DATA__, typename __CUSTOM_TYPE__, size_t size>
class InnerTypeForFromValue;

template< typename __USER_DATA__, typename __CUSTOM_TYPE__ >
class InnerTypeForFromValue < __USER_DATA__, __CUSTOM_TYPE__, 0 > {
    
    public :
    static void LUA_TypeMemcpy( __USER_DATA__ * data_to_copy_to, __CUSTOM_TYPE__ value  ) {
        
        data_to_copy_to->InnerType.ObjectPointer = value;
    }
};

template< typename __USER_DATA__, typename __CUSTOM_TYPE__  >
class InnerTypeForFromValue< __USER_DATA__, __CUSTOM_TYPE__, 1 > {
    
    public :
    static void LUA_TypeMemcpy( __USER_DATA__ * data_to_copy_to, __CUSTOM_TYPE__ value ) {
        
        data_to_copy_to->InnerType.ObjectPointer = &value;
    }
};

template < typename __CUSTOM_TYPE__ >
static void LUA_FromValue( __CUSTOM_TYPE__ value, lua_State * state ) {
    
    typedef typename XS_TYPE_< __CUSTOM_TYPE__ >::Type UserDataType;
    
    USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > * data = static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > > * >(lua_newuserdata( state, sizeof( USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > >)));
    
    InnerTypeForFromValue< USER_DATA_TYPE<INNER_USER_DATA_TYPE< UserDataType > >, __CUSTOM_TYPE__, std::is_reference< __CUSTOM_TYPE__ >::value >::LUA_TypeMemcpy( data, value );
    
    data->ItWasAllocated = false;
    
    luaL_getmetatable( state, UserDataType::CLASS_NAME );  // lookup metatable in Lua registry
    lua_setmetatable( state, -2);
}

template <>
void LUA_FromValue< const char * >( const char * value, lua_State * state ) {
    
    //lua_tostring( state, lua_gettop( state ) );
    //lua_remove( state, 1 );
    
    lua_pushstring( state, value );
}

template <>
void LUA_FromValue< int >( int value, lua_State * state ) {
    
    lua_pushinteger(state, value );
}

template <>
void LUA_FromValue< long >( long value, lua_State * state ) {
    
    lua_pushinteger(state, value );
}

template <>
void LUA_FromValue< bool >( bool value, lua_State * state ) {
    
    lua_pushboolean(state, value);
}

template <>
void LUA_FromValue< float >( float value, lua_State * state ) {
    
    lua_pushnumber( state, (lua_Number) value );
}

template <>
void LUA_FromValue< double >( double value, lua_State * state ) {
    
    lua_pushnumber( state, (lua_Number) value );
}

// -- END of LUA_FromValue overloads

XS_CLASS_BEGIN_WITH_ANCESTOR( CORE_ABSTRACT_RUNTIME_LUA, CORE_ABSTRACT_PROGRAM_RUNTIME< CORE_ABSTRACT_RUNTIME_LUA > )

    CORE_ABSTRACT_RUNTIME_LUA();
    virtual ~CORE_ABSTRACT_RUNTIME_LUA();

    void ExecuteCommand( const char * command );

private :

    int
        LuaMethods;
    int
        LuaMetatable;

public :

    static void PushObject( const double & item, lua_State * state ) {
        
        lua_pushnumber( state, item );
    }

    static void PushObject( const float & item, lua_State * state ) {
        
        lua_pushnumber( state, item );
    }

    static void PushObject( const int & item, lua_State * state ) {
        
        lua_pushinteger( state, item );
    }

    static void PushObject( const long & item, lua_State * state ) {
        
        lua_pushinteger( state, item );
    }

    static void PushObject( const CHAR_ARRAY_POINTER & item, lua_State * state ) {
        
        lua_pushstring( state, item );
    }

    static void PushObject( const bool & item, lua_State * state ) {
        
        lua_pushboolean( state, item );
    }

    template<typename OBJECT_TYPE_TO_PUSH, size_t size>
    class InnerTypeForPushObjectOrPointer;

    template< typename OBJECT_TYPE_TO_PUSH >
    class InnerTypeForPushObjectOrPointer < OBJECT_TYPE_TO_PUSH, 0 > {
        
        public : 
        
        static void PushObjectOrPointer( OBJECT_TYPE_TO_PUSH item, lua_State * state ) {
            
            PushObject( item, state );
        }
    };

    template< typename OBJECT_TYPE_TO_PUSH >
    class InnerTypeForPushObjectOrPointer < OBJECT_TYPE_TO_PUSH, 1 > {
        
        public :
        
        static void PushObjectOrPointer( OBJECT_TYPE_TO_PUSH item, lua_State * state ) {
            
            /*lua_pushlightuserdata(runtimeLuaState , (void * ) item);
             
             luaL_getmetatable( runtimeLuaState, OBJECT_TYPE_TO_PUSH::CLASS_NAME);  // lookup metatable in Lua registry
             lua_setmetatable( runtimeLuaState, -2 );*/
            
            typedef typename XS_TYPE_<OBJECT_TYPE_TO_PUSH>::Type T;
            
            USER_DATA_TYPE<INNER_USER_DATA_TYPE< T > > *ud = static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< T > > *>(lua_newuserdata( state, sizeof(USER_DATA_TYPE<INNER_USER_DATA_TYPE< T > >)));
            
            ud->ItWasAllocated = false;
            ud->InnerType.ObjectPointer = item;  // store pointer to object in userdata
            luaL_getmetatable( state, T::CLASS_NAME);  // lookup metatable in Lua registry
            lua_setmetatable( state, -2);
            
            
        }
    };

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
        
        lua_pushcfunction( runtimeLuaState, new_T<CLASS_TO_BIND> );
        lua_pushliteral( runtimeLuaState, "new" );
        lua_pushvalue( runtimeLuaState, -2 );           // dup new_T function
        lua_settable( runtimeLuaState, LuaMethods );       // add new_T to method table
        lua_settable( runtimeLuaState, mt );            // mt.__call = new_T
        lua_setmetatable( runtimeLuaState, LuaMethods );
    }

    void completeBindings() {
        
        lua_pop( runtimeLuaState, 2 );  // drop metatable and method table
    }

    // -- BEGIN OF STATIC BINDINGS --

    template < typename CLASS_TO_BIND >
    void staticBind( void (*voidPointerFunction)(void), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> >();
        
        vfpu->InnerType.staticVoidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticVoidThunkVoid< CLASS_TO_BIND >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename CLASS_TO_BIND, typename __PARAM_TYPE_1__ >
    void staticBind( void (*voidPointerFunction)( __PARAM_TYPE_1__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__ > > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__ > >();
        
        vfpu->InnerType.staticVoidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticVoidThunk1< CLASS_TO_BIND, __PARAM_TYPE_1__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__ >
    void staticBind( void (*voidPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ > > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ > >();
        
        vfpu->InnerType.staticVoidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticVoidThunk2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__, typename __PARAM_TYPE_3__ >
    void staticBind( void (*voidPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > >();
        
        vfpu->InnerType.staticVoidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticVoidThunk3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
    void staticBind( __RETURN_TYPE__ (*yieldPointerFunction)(void), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> >();
        
        vfpu->InnerType.StaticYieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticYieldThunkVoid<__RETURN_TYPE__, CLASS_TO_BIND>, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__ >
    void staticBind( __RETURN_TYPE__ (*yieldPointerFunction)( __PARAM_TYPE_1__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__> >();
        
        vfpu->InnerType.StaticYieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticYieldThunk1<__RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__>, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__ >
    void staticBind( __RETURN_TYPE__ (*yieldPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__> >();
        
        vfpu->InnerType.StaticYieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticYieldThunk2<__RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__>, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__, typename __PARAM_TYPE_3__ >
    void staticBind( __RETURN_TYPE__ (*yieldPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > >();
        
        vfpu->InnerType.StaticYieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, StaticYieldThunk3<__RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__>, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    // -- END OF STATIC BINDINGS --

    // -- BEGIN OF NORMAL METHODS BINDINGS --

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
    void bind( __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)(void), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> >();
        
        vfpu->InnerType.yieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, YieldThunkVoid< __RETURN_TYPE__, CLASS_TO_BIND >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__ >
    void bind( __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)( __PARAM_TYPE_1__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__> >();
        
        vfpu->InnerType.yieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, YieldThunk1< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__ >
    void bind( __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__> >();
        
        vfpu->InnerType.yieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, YieldThunk2< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__, typename __PARAM_TYPE_3__ >
    void bind( __RETURN_TYPE__ (CLASS_TO_BIND::*yieldPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__> > * vfpu = new USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__> >();
        
        vfpu->InnerType.yieldFunctionPointer = yieldPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, YieldThunk3< __RETURN_TYPE__, CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template < typename CLASS_TO_BIND >
    void bind( void (CLASS_TO_BIND::*voidPointerFunction)(void), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> >();
        
        vfpu->InnerType.voidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, VoidThunkVoid< CLASS_TO_BIND >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template <typename CLASS_TO_BIND, typename __PARAM_TYPE_1__ >
    void bind( void (CLASS_TO_BIND::*voidPointerFunction)( __PARAM_TYPE_1__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__> > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __PARAM_TYPE_1__> >();
        
        vfpu->InnerType.voidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, VoidThunk1< CLASS_TO_BIND, __PARAM_TYPE_1__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template <typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__ >
    void bind( void (CLASS_TO_BIND::*voidPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ > > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ > >();
        
        vfpu->InnerType.voidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, VoidThunk2< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    template <typename CLASS_TO_BIND, typename __PARAM_TYPE_1__, typename __PARAM_TYPE_2__, typename __PARAM_TYPE_3__ >
    void bind( void (CLASS_TO_BIND::*voidPointerFunction)( __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ ), const char * methodName ) {
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > > * vfpu = new USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ > >();
        
        vfpu->InnerType.voidFunctionPointer = voidPointerFunction;
        lua_pushstring( runtimeLuaState, methodName );
        lua_pushlightuserdata( runtimeLuaState, vfpu );
        lua_pushcclosure( runtimeLuaState, VoidThunk3< CLASS_TO_BIND, __PARAM_TYPE_1__, __PARAM_TYPE_2__, __PARAM_TYPE_3__ >, 1 );
        lua_settable( runtimeLuaState, LuaMethods );
    }

    // -- END OF NORMAL METHODS BINDINGS --

    // -- BEGIN OF Void thunks --

    template < typename CLASS_TO_BIND >
    static int VoidThunkVoid( lua_State * state ) {
        // stack has userdata, followed by method args
        CLASS_TO_BIND *obj = check_lua_object<CLASS_TO_BIND>( state, 1 );  // get 'self', or if you prefer, 'this'
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * vfpu = (USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * ) lua_touserdata( state, lua_upvalueindex(1));

        (obj->*(vfpu->InnerType.voidFunctionPointer))();
        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__ >
    static int VoidThunk1( lua_State * state ) {
        // stack has userdata, followed by method args
        CLASS_TO_BIND *obj = check_lua_object< CLASS_TO_BIND >( state, 1 );  // get 'self', or if you prefer, 'this'
        
        // remove self so member function args start at index 1
        lua_remove( state, 1 );
        
        // get member function from upvalue
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> > * vfpu = ( USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> > * ) lua_touserdata( state, lua_upvalueindex( 1 ) );
        
        ( obj->*( vfpu->InnerType.voidFunctionPointer ) )( LUA_ToValue< __TYPE_1__ >( state ) );

        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__ >
    static int VoidThunk2( lua_State * state ) {
        // stack has userdata, followed by method args
        CLASS_TO_BIND *obj = check_lua_object< CLASS_TO_BIND >( state, 1 );  // get 'self', or if you prefer, 'this'
        
        // remove self so member function args start at index 1
        lua_remove( state, 1 );
        
        // get member function from upvalue
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__ > > * vfpu = (USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__ > > * ) lua_touserdata( state, lua_upvalueindex( 1 ) );
        
        ( obj->*( vfpu->InnerType.voidFunctionPointer ) )( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ) );
        
        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
    static int VoidThunk3( lua_State * state ) {
        
        // stack has userdata, followed by method args
        CLASS_TO_BIND *obj = check_lua_object<CLASS_TO_BIND>( state, 1 );  // get 'self', or if you prefer, 'this'

        // remove self so member function args start at index 1
        lua_remove( state, 1 );
        
        // get member function from upvalue
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__> > * vfpu = (USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__> > * ) lua_touserdata( state, lua_upvalueindex( 1 ) );
        
        ( obj->*( vfpu->InnerType.voidFunctionPointer ) )( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ), LUA_ToValue< __TYPE_3__ >( state ) );
        
        return 1;  // call member function
    }

    // -- END OF Void thunks --

    // -- BEGIN OF Yield thunks --

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
    static int YieldThunkVoid( lua_State * state ) {
        
        // stack has userdata, followed by method args
        CLASS_TO_BIND * obj = check_lua_object<CLASS_TO_BIND>( state, 1 );  // get 'self', or if you prefer, 'this'
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        
        // get member function from upvalue
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND > > * vfpu = (USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = ( obj->*( vfpu->InnerType.yieldFunctionPointer))();

        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__ >
    static int YieldThunk1( lua_State * state ) {
        
        // stack has userdata, followed by method args
        CLASS_TO_BIND * obj = check_lua_object<CLASS_TO_BIND>( state, 1 );
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        typedef void (*voidPointerFunction)(void);
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__> > * vfpu = (USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = ( obj->*( vfpu->InnerType.yieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__ >
    static int YieldThunk2( lua_State * state ) {
        
        CLASS_TO_BIND * obj = check_lua_object<CLASS_TO_BIND>( state, 1 );
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * vfpu = (USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = ( obj->*( vfpu->InnerType.yieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
    static int YieldThunk3( lua_State * state ) {
        
        // stack has userdata, followed by method args
        CLASS_TO_BIND * obj = check_lua_object<CLASS_TO_BIND>( state, 1 );
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__ > > * vfpu = (USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__ > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = ( obj->*( vfpu->InnerType.yieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ), LUA_ToValue< __TYPE_3__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    // -- END OF Yield thunks --

    // -- BEGIN OF Static void thunks --

    template < typename CLASS_TO_BIND >
    static int StaticVoidThunkVoid( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > * vfpu = ( USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        (*(vfpu->InnerType.staticVoidFunctionPointer))();
        
        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__ >
    static int StaticVoidThunk1( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> > * vfpu = ( USER_DATA_TYPE<INNER_USER_DATA_TYPE_1< CLASS_TO_BIND, __TYPE_1__> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        (*(vfpu->InnerType.staticVoidFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ) );
        
        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__ >
    static int StaticVoidThunk2( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__> > * vfpu = ( USER_DATA_TYPE<INNER_USER_DATA_TYPE_2< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        (*(vfpu->InnerType.staticVoidFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ) );
        
        return 1;  // call member function
    }

    template < typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
    static int StaticVoidThunk3( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__> > * vfpu = ( USER_DATA_TYPE<INNER_USER_DATA_TYPE_3< CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        (*(vfpu->InnerType.staticVoidFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ), LUA_ToValue< __TYPE_3__ >( state ) );
        
        return 1;  // call member function
    }

    // -- END OF Static void thunks --

    // -- BEGIN OF Static Yield thunks --

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND >
    static int StaticYieldThunkVoid( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> > * vfpu = ( USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE< __RETURN_TYPE__, CLASS_TO_BIND> > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = (*(vfpu->InnerType.StaticYieldFunctionPointer))();
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__ >
    static int StaticYieldThunk1( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__ > > * vfpu = ( USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_1< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__ > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = (*(vfpu->InnerType.StaticYieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__ >
    static int StaticYieldThunk2( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__, __TYPE_2__ > > * vfpu = ( USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_2< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__, __TYPE_2__ > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = (*(vfpu->InnerType.StaticYieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    template < typename __RETURN_TYPE__, typename CLASS_TO_BIND, typename __TYPE_1__, typename __TYPE_2__, typename __TYPE_3__ >
    static int StaticYieldThunk3( lua_State * state ) {
        // stack has userdata, followed by method args
        
        lua_remove( state, 1);  // remove self so member function args start at index 1
        // get member function from upvalue
        
        USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__ > > * vfpu = ( USER_DATA_TYPE<INNER_YIELD_USER_DATA_TYPE_3< __RETURN_TYPE__, CLASS_TO_BIND, __TYPE_1__, __TYPE_2__, __TYPE_3__ > > * ) lua_touserdata( state, lua_upvalueindex(1));
        
        __RETURN_TYPE__ result = (*(vfpu->InnerType.StaticYieldFunctionPointer))( LUA_ToValue< __TYPE_1__ >( state ), LUA_ToValue< __TYPE_2__ >( state ), LUA_ToValue< __TYPE_3__ >( state ) );
        
        LUA_FromValue< __RETURN_TYPE__ >( result, state );
        
        return 1;  // call member function
    }

    // -- END OF Static Yield thunks --

    // get userdata from Lua stack and return pointer to T object
    template < typename CLASS_TO_BIND >
    static CLASS_TO_BIND *check_lua_object(lua_State * state, int nargs) {
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *ud = static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *>(luaL_checkudata( state, nargs, CLASS_TO_BIND::CLASS_NAME));
        
        if(!ud) {
            
            SERVICE_LOGGER_Error( "error");//luaL_typerror( state, nargs, CLASS_TO_BIND::CLASS_NAME );
        }
        return ud->InnerType.ObjectPointer;  // pointer to T object
    }

    template<typename CLASS_TO_BIND, size_t size>
    class InnerTypeForNewType;

    template< typename CLASS_TO_BIND >
    class InnerTypeForNewType < CLASS_TO_BIND, 0 > {
        
        public :
        
        static int new_T_impl( lua_State * state ) {
            
            CLASS_TO_BIND *obj = new CLASS_TO_BIND();  // call constructor for T objects
            USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *ud =
            static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *>(lua_newuserdata( state, sizeof(USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > >)));
            ud->InnerType.ObjectPointer = obj;  // store pointer to object in userdata
            ud->ItWasAllocated = true;
            luaL_getmetatable( state, CLASS_TO_BIND::CLASS_NAME);  // lookup metatable in Lua registry
            lua_setmetatable( state, -2);
            
            return 1;
        }
    };

    template< typename CLASS_TO_BIND >
    class InnerTypeForNewType < CLASS_TO_BIND, 1 > {
        
        public :
        
        static int new_T_impl( lua_State * state ) {
            
            // OK But does nothing could return getinstance?
            return 1;
        }
    };

    // create a new T object and
    // push onto the Lua stack a userdata containing a pointer to T object
    template < typename CLASS_TO_BIND >
    static int new_T( lua_State * state ) {

        lua_remove( state, 1);   // use classname:new(), instead of classname.new()
        
        InnerTypeForNewType< CLASS_TO_BIND, XS_CLASS_TEMPLATE_SINGLETON< CLASS_TO_BIND >::Value >::new_T_impl( state );
        
        return 1;
    }

    // garbage collection metamethod
    template < typename CLASS_TO_BIND >
    static int gc_T( lua_State * state ) {

        //lua_remove( state, 1);   // use classname:new(), instead of classname.new()
        
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *ud = static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > * >(lua_touserdata( state, 1));

        if ( ud->ItWasAllocated ) {

            CORE_MEMORY_ObjectSafeDeallocation( ud->InnerType.ObjectPointer );  // call destructor for T objects
        }
        
        return 0;
    }

    template < typename CLASS_TO_BIND >
    static int tostring_T ( lua_State * state ) {
        char buff[32];
        USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > *ud = static_cast< USER_DATA_TYPE<INNER_USER_DATA_TYPE< CLASS_TO_BIND > > * >(lua_touserdata( state, 1));
        CLASS_TO_BIND *obj = ud->InnerType.ObjectPointer;
        SERVICE_LOGGER_Info(buff, "%p", obj);
        lua_pushfstring( state, "%s (%s)", CLASS_TO_BIND::CLASS_NAME, buff);
        return 1;
    }

    virtual void Initialize() override;
    virtual void Finalize() override;

    lua_State * getLuaState() { return runtimeLuaState; }

private:

    lua_State
        * runtimeLuaState;
    
XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_RUNTIME_LUA__) */
