//
//  GRAPHIC_PARTICLE_SYSTEM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_PARTICLE_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"

GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::GAMEPLAY_COMPONENT_PARTICLE_SYSTEM() :
    GAMEPLAY_COMPONENT_SYSTEM(){
    
}

GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::~GAMEPLAY_COMPONENT_PARTICLE_SYSTEM() {
    
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Initialize() {
    
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((uint8_t*) ecs_base_pointer) + it->GetOffset());
        
        
        
        it++;
    }
    /*std::vector<GRAPHIC_PARTICLE_MANAGER *>::iterator it = ManagerTable.begin();
     
     while( it != ManagerTable.end() ) {
     
     (*it)->Update(time_step);
     ++it;
     }*/
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((uint8_t*) ecs_base_pointer) + it->GetOffset());
        
        GAMEPLAY_COMPONENT_RENDER * renderable = entity->GetComponentRender();
        GAMEPLAY_COMPONENT_POSITION * located = entity->GetComponentPosition();
        
        renderable->Render( renderer, located, NULL );
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Finalize() {
    
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Update(float time_step, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat) {
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_PARTICLE_SYSTEM::Render( GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}

