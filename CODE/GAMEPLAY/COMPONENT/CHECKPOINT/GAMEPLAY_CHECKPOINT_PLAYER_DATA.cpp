//
//  GAMEPLAY_CHECKPOINT_PLAYER_DATA.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_CHECKPOINT_PLAYER_DATA.h"

GAMEPLAY_CHECKPOINT_PLAYER_DATA::GAMEPLAY_CHECKPOINT_PLAYER_DATA() :
    Occurence( 0 ),
    Active( false ),
    EntityHandle() {
    
}

GAMEPLAY_CHECKPOINT_PLAYER_DATA::GAMEPLAY_CHECKPOINT_PLAYER_DATA( const GAMEPLAY_CHECKPOINT_PLAYER_DATA & other ) :
    Occurence( other.Occurence ),
    Active( other.Active ),
    EntityHandle( other.EntityHandle ) {
    
}

GAMEPLAY_CHECKPOINT_PLAYER_DATA::~GAMEPLAY_CHECKPOINT_PLAYER_DATA() {
    
}

bool GAMEPLAY_CHECKPOINT_PLAYER_DATA::Collides( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    CORE_RUNTIME_Abort();
    /*if ( Active && EntityHandle.GetOffset() == -1 && EntityHandle.GetIndex() == -1 ) {
        
        EntityHandle.SetIndex( entity->GetHandle().GetIndex() );
        EntityHandle.SetOffset( entity->GetHandle().GetOffset() );
        ++Occurence;
        return true;
    }
    
    if ( Active && EntityHandle.GetOffset() == entity->GetHandle().GetOffset() && EntityHandle.GetIndex() == entity->GetHandle().GetIndex() ) {
        
        ++Occurence;
        return true;
    }*/
    
    return false;
}
