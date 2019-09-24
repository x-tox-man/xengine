//
//  GAMEPLAY_COMPONENT_SYSTEM_CAMERA.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/05/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_CAMERA.h"

GAMEPLAY_COMPONENT_SYSTEM_CAMERA::GAMEPLAY_COMPONENT_SYSTEM_CAMERA() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_CAMERA::~GAMEPLAY_COMPONENT_SYSTEM_CAMERA() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_CAMERA::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_CAMERA::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        CORE_RUNTIME_Abort();
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_CAMERA::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_CAMERA::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}
