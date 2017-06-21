//
//  GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"

GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::~GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Update( float time_step ) {
    
    CORE_ABSTRACT_RUNTIME_LUA::PTR runtime = ( CORE_ABSTRACT_RUNTIME_LUA::PTR ) CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[CORE_ABSTRACT_PROGRAM_RUNTIME_Lua];
    
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        GAMEPLAY_COMPONENT_SCRIPT * script = ( GAMEPLAY_COMPONENT_SCRIPT *) it->second->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );
        
        CORE_ABSTRACT_PROGRAM_FACTORY * abstract_script = script->GetScript();
        
        CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer<GAMEPLAY_COMPONENT_ENTITY *, std::is_pointer< GAMEPLAY_COMPONENT_ENTITY * >::value >::PushObjectOrPointer((GAMEPLAY_COMPONENT_ENTITY *) it->second, runtime->getLuaState() );
        
        abstract_script->ExecuteFunction( "Update", 1, 0, 0 );
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Render() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Finalize() {
    
}
