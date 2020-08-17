//
//  GAMEPLAY_COMPONENT_SCRIPT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 28/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SCRIPT.h"
#include "CORE_DATA_STREAM.h"

GAMEPLAY_COMPONENT_SCRIPT::GAMEPLAY_COMPONENT_SCRIPT() :
    Script( NULL ){
    
}

GAMEPLAY_COMPONENT_SCRIPT::GAMEPLAY_COMPONENT_SCRIPT( const GAMEPLAY_COMPONENT_SCRIPT & other ) :
    Script() {
    
    CORE_RUNTIME_Abort(); // TODO: clone program
}


GAMEPLAY_COMPONENT_SCRIPT::~GAMEPLAY_COMPONENT_SCRIPT() {
    
}

int GAMEPLAY_COMPONENT_SCRIPT::ComponentType = GAMEPLAY_COMPONENT_TYPE_Script;
