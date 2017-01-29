//
//  CORE_ABSTRACT_PROGRAM_LUA_HELPERS.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 23/01/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_LUA_HELPERS.h"
#include "GRAPHIC_UI_ELEMENT.h"

typedef CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > XS_UI_CALLBACK;

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( CORE_ABSTRACT_PROGRAM_LUA_HELPERS )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1(
                                                              XS_UI_CALLBACK &,
                                                              CORE_ABSTRACT_PROGRAM_LUA_HELPERS,
                                                              CreateLuaCallback,
                                                              const char * )

CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( CORE_ABSTRACT_PROGRAM_LUA_HELPERS )

CORE_ABSTRACT_PROGRAM_LUA_HELPERS::CORE_ABSTRACT_PROGRAM_LUA_HELPERS() {
    
}

CORE_ABSTRACT_PROGRAM_LUA_HELPERS::~CORE_ABSTRACT_PROGRAM_LUA_HELPERS() {
    
}

template <>
CORE_HELPERS_CALLBACK_2< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE > & CORE_ABSTRACT_PROGRAM_LUA_HELPERS::CreateLuaCallback( const char * function_name ) {
    
    CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA > * function = new CORE_ABSTRACT_FUNCTION< CORE_ABSTRACT_PROGRAM_LUA >( function_name );
    
    return GenerateLuaCallback< GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE >( function );
}
