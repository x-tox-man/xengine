//
//  GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.cpp
//  GAME-ENGINE
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

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + it->GetOffset());
        
        /*GAMEPLAY_COMPONENT_SCRIPT * script = entity->GetComponentScript();
        
        CORE_ABSTRACT_PROGRAM_FACTORY * abstract_script = script->GetScript();
        
        CORE_ABSTRACT_RUNTIME_LUA::InnerTypeForPushObjectOrPointer<GAMEPLAY_COMPONENT_ENTITY *, std::is_pointer< GAMEPLAY_COMPONENT_ENTITY * >::value >::PushObjectOrPointer((GAMEPLAY_COMPONENT_ENTITY *) entity, ((CORE_ABSTRACT_PROGRAM_LUA*)script->GetScript())->GetRuntime()->getLuaState() );
        
        abstract_script->ExecuteFunction( "Update", 1, 0, 0 );*/
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}
