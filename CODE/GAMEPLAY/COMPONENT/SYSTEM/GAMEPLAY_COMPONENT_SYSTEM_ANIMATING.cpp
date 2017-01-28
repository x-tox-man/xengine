//
//  GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::~GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() {

}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Update( float time_step ) {
    
    for ( int i = 0; i < EntitiesVector.size(); i++ ) {
        
        GAMEPLAY_COMPONENT_ANIMATION * animation = ( GAMEPLAY_COMPONENT_ANIMATION *) EntitiesVector[i]->GetComponent( GAMEPLAY_COMPONENT_TYPE_Animation );
        
        animation->UpdateAnimation( time_step );
    }
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Finalize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Render() {
    
    CORE_RUNTIME_Abort();
}