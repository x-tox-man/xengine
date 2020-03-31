//
//  GAMEPLAY_GAME.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/01/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_GAME.h"

GAMEPLAY_GAME::GAMEPLAY_GAME() :
    Scene(),
    BulletSystem( new GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION() ) {
    
}

GAMEPLAY_GAME::~GAMEPLAY_GAME() {
    
}

void GAMEPLAY_GAME::Render( GRAPHIC_RENDERER & renderer, int transparent_mask ) {
    
    Scene.Render( renderer, transparent_mask );
}

void GAMEPLAY_GAME::Update( const float step ) {
    
    Scene.Update( step );
}

void GAMEPLAY_GAME::Initialize() {
    
}

void GAMEPLAY_GAME::Finalize() {
    
}
