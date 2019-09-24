//
//  GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::~GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION() {

}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Update( void * ecs_base_pointer, float time_step ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY_HANDLE >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        GAMEPLAY_COMPONENT_POSITION * position = (( GAMEPLAY_COMPONENT_ENTITY *) (((uint8_t*) ecs_base_pointer) + it->GetOffset()))->GetComponentPosition();
        
        position->SetPosition( position->GetPosition() + position->GetVelocity() * time_step );
        
        position->GetOrientation().RotateZ( position->GetSpin().Z() * time_step );
        position->GetOrientation().RotateY( position->GetSpin().Y() * time_step );
        position->GetOrientation().RotateX( position->GetSpin().X() * time_step );
        
        position->GetOrientation().Normalize();
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}
