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
    
    for (int i = 0; i < EntitiesVector.size(); i++) {
        
        GAMEPLAY_COMPONENT_SCRIPT * script = ( GAMEPLAY_COMPONENT_SCRIPT *) EntitiesVector[i]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Script );
        
        CORE_ABSTRACT_PROGRAM_FACTORY * abstract_script = script->GetScript();
        
        abstract_script->ExecuteFunction( "Update", 1, 0, 0 );
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Render() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT::Finalize() {
    
}
