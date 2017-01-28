//
//  PERIPHERIC_INTERACTION_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "PERIPHERIC_INTERACTION_SYSTEM.h"

PERIPHERIC_INTERACTION_SYSTEM::PERIPHERIC_INTERACTION_SYSTEM() :
    Keyboard(),
    Mouse() {
    
    Keyboard.Initialize();
    Mouse.Initialize();
}

PERIPHERIC_INTERACTION_SYSTEM::~PERIPHERIC_INTERACTION_SYSTEM() {

}

void PERIPHERIC_INTERACTION_SYSTEM::Update() {
    
    Keyboard.Update();
    Mouse.Update();
}