//
//  GAMEPLAY_CHECKPOINT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_CHECKPOINT.h"

GAMEPLAY_CHECKPOINT::GAMEPLAY_CHECKPOINT( GAMEPLAY_COMPONENT_ENTITY * entity ) :
    Entity( entity ),
    Parent( NULL ),
    PlayerData(),
    NextCheckpoints() {
    
}

GAMEPLAY_CHECKPOINT::GAMEPLAY_CHECKPOINT( const GAMEPLAY_CHECKPOINT & other ) :
    Entity(other.Entity ),
    Parent( other.Parent ),
    PlayerData( other.PlayerData ),
    NextCheckpoints( other.NextCheckpoints ) {
}

GAMEPLAY_CHECKPOINT::~GAMEPLAY_CHECKPOINT() {
    
}

bool GAMEPLAY_CHECKPOINT::ProcessCollision( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT_PLAYER_DATA >::iterator it = PlayerData.begin();
    
    while (it != PlayerData.end() ) {
        
        if ( it->Collides( entity ) ) {
            
            DeactivateFor( entity );
            
            if ( Parent != NULL ) {
                
                Parent->DeactivateNextCheckpoints( entity );
            }
            
            ActivateNextCheckpoints( entity );
            
            return true;
        }
        
        it++;
    }
    
    return false;
}

void GAMEPLAY_CHECKPOINT::ActivateFor( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT_PLAYER_DATA >::iterator
        it = PlayerData.begin();
    
    CORE_RUNTIME_Abort();
    
    /*while (it != PlayerData.end() ) {
        
        if ( it->GetEntityHandle() == entity->GetHandle() ) {
            
            it->SetIsActive( true );
            
            return;
        }
        
        it++;
    }

    GAMEPLAY_CHECKPOINT_PLAYER_DATA
        d;
    
    d.SetIsActive( true );
    d.SetEntityHandle( entity->GetHandle() );
    
    PlayerData.push_back( d );*/
}

void GAMEPLAY_CHECKPOINT::DeactivateFor( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT_PLAYER_DATA >::iterator it = PlayerData.begin();
    
    CORE_RUNTIME_Abort();
    
    /*while (it != PlayerData.end() ) {
        
        if ( it->GetEntityHandle() == entity->GetHandle() ) {
            
            it->SetIsActive( false );
            
            return;
        }
        
        it++;
    }*/
}

void GAMEPLAY_CHECKPOINT::AddNext( GAMEPLAY_CHECKPOINT * cp ) {
    
    cp->SetParent( this );
    NextCheckpoints.push_back( cp );
}

void GAMEPLAY_CHECKPOINT::Reset() {
    
    PlayerData.clear();
}

void GAMEPLAY_CHECKPOINT::SetParent( GAMEPLAY_CHECKPOINT * entity ) {
    
    Parent = entity;
}

void GAMEPLAY_CHECKPOINT::ActivateNextCheckpoints( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT * >::iterator it = NextCheckpoints.begin();
    
    while (it != NextCheckpoints.end() ) {
        
        (*it)->ActivateFor( entity );
        it++;
    }
}

void GAMEPLAY_CHECKPOINT::DeactivateNextCheckpoints( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    std::vector< GAMEPLAY_CHECKPOINT * >::iterator it = NextCheckpoints.begin();
    
    while (it != NextCheckpoints.end() ) {
        
        (*it)->DeactivateFor( entity );
        it++;
    }
}
