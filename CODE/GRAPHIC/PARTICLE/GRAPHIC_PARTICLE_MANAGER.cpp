//
//  GRAPHIC_PARTICLE_MANAGER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/08/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_PARTICLE_MANAGER.h"

GRAPHIC_PARTICLE_MANAGER::GRAPHIC_PARTICLE_MANAGER() :
    EmitersTable() {
    
}

GRAPHIC_PARTICLE_MANAGER::~GRAPHIC_PARTICLE_MANAGER() {
    
}

void GRAPHIC_PARTICLE_MANAGER::Update(float time_step) {
    
    std::vector<GRAPHIC_PARTICLE_EMITER_BASE_CLASS *>::iterator it = EmitersTable.begin();
    
    while( it != EmitersTable.end() ) {
        
        (*it)->Update(time_step);
        ++it;
    }
}

void GRAPHIC_PARTICLE_MANAGER::Render( GRAPHIC_RENDERER & renderer) {
    
    std::vector<GRAPHIC_PARTICLE_EMITER_BASE_CLASS *>::iterator it = EmitersTable.begin();
    
    while( it != EmitersTable.end() ) {
        
        (*it)->Render(renderer);
        ++it;
    }
}

void GRAPHIC_PARTICLE_MANAGER::AddEmiter( GRAPHIC_PARTICLE_EMITER_BASE_CLASS & emiter ) {
    
    EmitersTable.push_back( &emiter );
}