//
//  R3D_PLAYER_SHIP.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER_SHIP.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_HELPER.h"
#include "GRAPHIC_RENDERER.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_SCRIPT.h"

R3D_PLAYER_SHIP::R3D_PLAYER_SHIP() :
    //Steam(),
    Thrust( 0.0f ),
    Rotation( 0.0f ) {

    
}

R3D_PLAYER_SHIP::~R3D_PLAYER_SHIP() {
    
}

