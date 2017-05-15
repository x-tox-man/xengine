//
//  GAMEPLAY_LIGHT.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_LIGHT.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

GAMEPLAY_LIGHT::GAMEPLAY_LIGHT() :
    GAMEPLAY_COMPONENT_ENTITY(),
    Light( NULL ) {
    
}

GAMEPLAY_LIGHT::~GAMEPLAY_LIGHT() {
    
}

void GAMEPLAY_LIGHT::Initialize() {
    
    auto position_component = ( GAMEPLAY_COMPONENT_POSITION * ) GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position );
    SetCompononent( position_component, GAMEPLAY_COMPONENT_TYPE_Position );
}
