//
//  GAMEPLAY_LIGHT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_LIGHT.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

GAMEPLAY_COMPONENT_LIGHT::GAMEPLAY_COMPONENT_LIGHT() :
    Light() {
    
}

GAMEPLAY_COMPONENT_LIGHT::GAMEPLAY_COMPONENT_LIGHT( const GAMEPLAY_COMPONENT_LIGHT & other ) :
    Light() {
    
}

GAMEPLAY_COMPONENT_LIGHT::~GAMEPLAY_COMPONENT_LIGHT() {
    
}

void GAMEPLAY_COMPONENT_LIGHT::Clear() {
    
}

void GAMEPLAY_COMPONENT_LIGHT::SaveToStream( CORE_DATA_STREAM & stream ) {
    
}

void GAMEPLAY_COMPONENT_LIGHT::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
}

int GAMEPLAY_COMPONENT_LIGHT::ComponentType = GAMEPLAY_COMPONENT_TYPE_Light;
