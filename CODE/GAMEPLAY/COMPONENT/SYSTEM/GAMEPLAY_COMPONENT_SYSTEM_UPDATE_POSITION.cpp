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

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Update( float time_step ) {
    
    std::map< GAMEPLAY_COMPONENT_ENTITY_HANDLE, GAMEPLAY_COMPONENT_ENTITY_PROXY * >::iterator it = EntitiesTable.begin();
    
    while (it != EntitiesTable.end() ) {
        
        GAMEPLAY_COMPONENT_POSITION * position = ( GAMEPLAY_COMPONENT_POSITION *) it->second->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        position->SetPosition( position->GetPosition() * position->GetVelocity() * time_step );
        position->SetOrientation( position->GetOrientation() * position->GetSpin()  * time_step );
        
        //position->Orientation.Normalize();
        
        it++;
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Render( GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}

void GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION::Finalize() {
    
}
