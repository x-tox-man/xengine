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
    GAMEPLAY_COMPONENT(),
    Light() {
    
}

GAMEPLAY_COMPONENT_LIGHT::GAMEPLAY_COMPONENT_LIGHT( const GAMEPLAY_COMPONENT_LIGHT & other ) :
    GAMEPLAY_COMPONENT(),
    Light() {
    
    abort(); // TODO : clone program
}

GAMEPLAY_COMPONENT_LIGHT::~GAMEPLAY_COMPONENT_LIGHT() {
    
}

void GAMEPLAY_COMPONENT_LIGHT::Clear() {
    
}

void GAMEPLAY_COMPONENT_LIGHT::SaveToStream( CORE_DATA_STREAM & stream ) {
    
}

void GAMEPLAY_COMPONENT_LIGHT::LoadFromStream( CORE_DATA_STREAM & stream ) {
    
}

int GAMEPLAY_COMPONENT_LIGHT::LastIndex = -1;
int GAMEPLAY_COMPONENT_LIGHT::LastOffset = -1;
