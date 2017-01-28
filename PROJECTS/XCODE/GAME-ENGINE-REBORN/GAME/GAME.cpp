//
//  GAME.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAME.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"

GAME::GAME() :
    GameStartTime( 0 ),
    Scene( NULL ) {
    
}

GAME::~GAME() {
    
}

void GAME::Initialize() {
    
    Scene = new GAMEPLAY_SCENE();
    
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * bullet_system = new GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION;
    
    bullet_system->Initialize();
    
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene->InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    Scene->InsertUpdatableSystem( bullet_system );
    
    Scene->InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
}

void GAME::Finalize() {
    
    delete Scene;
    
    Scene = NULL;
}

void GAME::Update( const float time_step) {
    
}

void GAME::Start() {
    
}

void GAME::Pause() {
    
}

void GAME::Resume() {
    
}

void GAME::End() {
    
}
