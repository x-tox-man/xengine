//
//  GRAPHIC_UI_ELEMENT_SCRIPTED.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/12/15.
//  Copyright © 2015 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_UI_ELEMENT_SCRIPTED.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_UI_FRAME.h"

GRAPHIC_UI_ELEMENT_SCRIPTED::GRAPHIC_UI_ELEMENT_SCRIPTED() :
    LuaProgram( NULL ),
    IsRunning( false ) {
    
}

GRAPHIC_UI_ELEMENT_SCRIPTED::~GRAPHIC_UI_ELEMENT_SCRIPTED() {

}

void GRAPHIC_UI_ELEMENT_SCRIPTED::Initialize( const CORE_FILESYSTEM_PATH & path, void * element_ptr ) {
    
    CORE_ABSTRACT_RUNTIME_LUA::PTR runtime = ( CORE_ABSTRACT_RUNTIME_LUA::PTR ) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[CORE_ABSTRACT_PROGRAM_RUNTIME_Lua];
    
    LuaProgram = (CORE_ABSTRACT_PROGRAM_LUA::PTR )CORE_ABSTRACT_PROGRAM_MANAGER::GetInstance().LoadProgram(
                                                                          path.GetPath(),
                                                                          CORE_ABSTRACT_PROGRAM_RUNTIME_Lua
                                                                          );

    LuaProgram->Execute();
    
    CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer<GRAPHIC_UI_ELEMENT *, std::is_pointer< GRAPHIC_UI_ELEMENT * >::value >::PushObjectOrPointer((GRAPHIC_UI_ELEMENT *) element_ptr, runtime->getLuaState() );
    
    LuaProgram->ExecuteFunction( "Setup", 1, 0, 0 );
    
    IsRunning = true;
}

void GRAPHIC_UI_ELEMENT_SCRIPTED::InitializeFrame( const CORE_FILESYSTEM_PATH & path, void * frame_ptr ) {
    
    CORE_ABSTRACT_RUNTIME_LUA::PTR runtime = ( CORE_ABSTRACT_RUNTIME_LUA::PTR ) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[CORE_ABSTRACT_PROGRAM_RUNTIME_Lua];
    
    LuaProgram = (CORE_ABSTRACT_PROGRAM_LUA::PTR )CORE_ABSTRACT_PROGRAM_MANAGER::GetInstance().LoadProgram(
                                                                                                           path.GetPath(),
                                                                                                           CORE_ABSTRACT_PROGRAM_RUNTIME_Lua
                                                                                                           );
    
    LuaProgram->Execute();
    
    CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer<GRAPHIC_UI_FRAME *, std::is_pointer< GRAPHIC_UI_ELEMENT * >::value >::PushObjectOrPointer((GRAPHIC_UI_FRAME *) frame_ptr, runtime->getLuaState() );
    
    LuaProgram->ExecuteFunction( "Setup", 1, 0, 0 );
    
    IsRunning = true;
}

void GRAPHIC_UI_ELEMENT_SCRIPTED::Start() {
    
    LuaProgram->Execute();
    
    IsRunning = true;
}

void GRAPHIC_UI_ELEMENT_SCRIPTED::Update( float time_step ) {
    
    if ( IsRunning ) {
        
        CORE_ABSTRACT_RUNTIME_LUA::PTR runtime = ( CORE_ABSTRACT_RUNTIME_LUA::PTR ) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[CORE_ABSTRACT_PROGRAM_RUNTIME_Lua];
        
        CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer<float, std::is_pointer< float >::value >::PushObjectOrPointer( time_step, runtime->getLuaState() );
        
        LuaProgram->ExecuteFunction( "update", 1, 0, 0 );
    }
}

void GRAPHIC_UI_ELEMENT_SCRIPTED::Reset() {
    
    IsRunning = false;
}

void GRAPHIC_UI_ELEMENT_SCRIPTED::Copy( GRAPHIC_UI_ELEMENT_SCRIPTED & other ) {
    
    other.IsRunning = false;
    other.LuaProgram = LuaProgram;
}
