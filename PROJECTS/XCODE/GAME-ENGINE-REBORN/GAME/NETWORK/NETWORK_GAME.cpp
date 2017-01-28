//
//  NETWORK_GAME.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "NETWORK_GAME.h"

NETWORK_GAME::NETWORK_GAME() :
    GAME(),
    PlayerTable() {
    
}

NETWORK_GAME::~NETWORK_GAME() {
    
}

void NETWORK_GAME::Initialize() {
    
    GAME::Initialize();
}

void NETWORK_GAME::Finalize() {
    
    GAME::Finalize();
    PlayerTable.clear();
}

void NETWORK_GAME::Start() {
    
}

void NETWORK_GAME::Pause() {
    
}

void NETWORK_GAME::Resume() {
    
}

void NETWORK_GAME::End() {
    
}
