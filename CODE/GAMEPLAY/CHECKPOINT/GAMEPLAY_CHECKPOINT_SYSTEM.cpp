//
//  GAMEPLAY_CHECKPOINT_SYSTEM.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_CHECKPOINT_SYSTEM.h"

GAMEPLAY_CHECKPOINT_SYSTEM::GAMEPLAY_CHECKPOINT_SYSTEM() :
    Checkpoints(),
    CheckpointCallback( &Wrapper2<GAMEPLAY_CHECKPOINT_SYSTEM, GAMEPLAY_COMPONENT_ENTITY *, GAMEPLAY_COMPONENT_ENTITY *, &GAMEPLAY_CHECKPOINT_SYSTEM::OnCheckpointCollision>, this ),
    PlayerFinishedCallback() {
    
}

GAMEPLAY_CHECKPOINT_SYSTEM::~GAMEPLAY_CHECKPOINT_SYSTEM() {
    
}

void GAMEPLAY_CHECKPOINT_SYSTEM::Start( std::vector< GAMEPLAY_COMPONENT_ENTITY * > & entities ) {
    
    std::vector< GAMEPLAY_COMPONENT_ENTITY * >::iterator it = entities.begin();
    
    if ( Checkpoints.size() == 0 ) {
        
        return;
    }
    
    while ( it != entities.end() ) {
        
        Checkpoints.front()->ActivateFor( *it );
        it++;
    }
}

void GAMEPLAY_CHECKPOINT_SYSTEM::Reset( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    abort();
}

void GAMEPLAY_CHECKPOINT_SYSTEM::Reset() {
    
    std::vector< GAMEPLAY_CHECKPOINT * >::iterator it = Checkpoints.begin();
    
    while (it != Checkpoints.end() ) {
        
        (*it)->Reset();
        
        it++;
    }
}

void GAMEPLAY_CHECKPOINT_SYSTEM::AddCheckpoint( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    GAMEPLAY_CHECKPOINT::PTR cp = new GAMEPLAY_CHECKPOINT( entity );
    
    if ( Checkpoints.size() > 0) {
        
        Checkpoints.back()->AddNext( cp );
    }
    
    Checkpoints.insert(Checkpoints.end(), cp );
}

void GAMEPLAY_CHECKPOINT_SYSTEM::OnCheckpointCollision( GAMEPLAY_COMPONENT_ENTITY * checkpoint, GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT * >::iterator it = Checkpoints.begin();
    
    while (it != Checkpoints.end() ) {
        
        if ( checkpoint->GetHandle() == (*it)->GetEntity()->GetHandle() ) {
            
            if ( (*it)->ProcessCollision( entity ) ) {
                
                if ( (*it)->IsLast() ) {
                    
                    PlayerFinishedCallback( entity );
                }
            }
            
            break;
        }
        
        it++;
    }
}
