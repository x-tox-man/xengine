//
//  GRAPHIC_PARTICLE_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 7/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_PARTICLE_SYSTEM.h"

GRAPHIC_PARTICLE_SYSTEM::GRAPHIC_PARTICLE_SYSTEM() :
    ManagerTable(){
    
}

GRAPHIC_PARTICLE_SYSTEM::~GRAPHIC_PARTICLE_SYSTEM() {
    
    std::vector<GRAPHIC_PARTICLE_MANAGER *>::iterator it = ManagerTable.begin();
    
    while ( it != ManagerTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( *it );
        
        it++;
    }
}

void GRAPHIC_PARTICLE_SYSTEM::Update(float time_step, const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & lookat) {
    
    std::vector<GRAPHIC_PARTICLE_MANAGER *>::iterator it = ManagerTable.begin();
    
    while( it != ManagerTable.end() ) {
        
        (*it)->Update(time_step);
        ++it;
    }
}

void GRAPHIC_PARTICLE_SYSTEM::Render( GRAPHIC_RENDERER & renderer ) {
    
    std::vector<GRAPHIC_PARTICLE_MANAGER *>::iterator it = ManagerTable.begin();
    
    while( it != ManagerTable.end() ) {
        
        (*it)->Render( renderer );
        ++it;
    }
}

void GRAPHIC_PARTICLE_SYSTEM::AddManager( GRAPHIC_PARTICLE_MANAGER & manager ) {
    
    ManagerTable.push_back( &manager );
}
