//
//  GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.cpp
//  GAME-ENGINE-REBORN
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

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Update( float time_step ) {
    
    for (int i = 0; i < EntitiesVector.size(); i++) {
        
        GAMEPLAY_COMPONENT_POSITION * position = ( GAMEPLAY_COMPONENT_POSITION *) EntitiesVector[i]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        position->Position[0] += position->Velocity[0] * time_step;
        position->Position[1] += position->Velocity[1] * time_step;
        position->Position[2] += position->Velocity[2] * time_step;
        
        
        position->Orientation[0] += position->Spin[0] * time_step;
        position->Orientation[1] += position->Spin[1] * time_step;
        position->Orientation[2] += position->Spin[2] * time_step;
        
        position->Orientation.Normalize();
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Render() {
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Finalize() {
    
}