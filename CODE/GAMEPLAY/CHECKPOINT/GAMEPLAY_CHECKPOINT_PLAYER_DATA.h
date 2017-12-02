//
//  GAMEPLAY_CHECKPOINT_PLAYER_DATA.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CHECKPOINT_PLAYER_DATA_hpp
#define GAMEPLAY_CHECKPOINT_PLAYER_DATA_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_CHECKPOINT_PLAYER_DATA )

    GAMEPLAY_CHECKPOINT_PLAYER_DATA();
    ~GAMEPLAY_CHECKPOINT_PLAYER_DATA();

    inline void Reset() { Occurence = 0; }
    inline int GetOccurence() { return Occurence; }
    inline void SetIsActive( bool active ) { Active = active; }
    inline bool IsActive() const { return Active; }
    inline GAMEPLAY_COMPONENT_ENTITY_HANDLE & GetEntityHandle() { return EntityHandle; }
    inline void SetEntityHandle( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle ) { EntityHandle = handle; }

    bool Collides( GAMEPLAY_COMPONENT_ENTITY * entity );

    void operator = ( const GAMEPLAY_CHECKPOINT_PLAYER_DATA & other ) {
        Occurence = other.Occurence;
        Active = other.Active;
        EntityHandle = other.EntityHandle;
    }

private:

    int
        Occurence;
    bool
        Active;
    GAMEPLAY_COMPONENT_ENTITY_HANDLE
        EntityHandle;

XS_CLASS_END

#endif /* GAMEPLAY_CHECKPOINT_PLAYER_DATA_hpp */
