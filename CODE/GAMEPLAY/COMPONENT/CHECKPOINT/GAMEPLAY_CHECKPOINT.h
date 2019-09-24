//
//  GAMEPLAY_CHECKPOINT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CHECKPOINT_hpp
#define GAMEPLAY_CHECKPOINT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_CHECKPOINT_PLAYER_DATA.h"

XS_CLASS_BEGIN_WITH_COPY( GAMEPLAY_CHECKPOINT )

    GAMEPLAY_CHECKPOINT( GAMEPLAY_COMPONENT_ENTITY * entity );

    ~GAMEPLAY_CHECKPOINT();

    inline GAMEPLAY_COMPONENT_ENTITY * GetEntity() { return Entity; }

    void operator =( const GAMEPLAY_CHECKPOINT & other ) {
    
        Entity = other.Entity;
    }

    bool ProcessCollision( GAMEPLAY_COMPONENT_ENTITY * entity );
    void ActivateFor( GAMEPLAY_COMPONENT_ENTITY * entity );
    void DeactivateFor( GAMEPLAY_COMPONENT_ENTITY * entity );
    void AddNext( GAMEPLAY_CHECKPOINT * cp );
    void SetParent( GAMEPLAY_CHECKPOINT * entity );
    void Reset();

    inline bool IsLast() const { return NextCheckpoints.size() == 0; }

private:


    void ActivateNextCheckpoints( GAMEPLAY_COMPONENT_ENTITY * entity );
    void DeactivateNextCheckpoints( GAMEPLAY_COMPONENT_ENTITY * entity );

    GAMEPLAY_COMPONENT_ENTITY
        * Entity;
    GAMEPLAY_CHECKPOINT *
        Parent;
    std::vector< GAMEPLAY_CHECKPOINT_PLAYER_DATA >
        PlayerData;
    std::vector< GAMEPLAY_CHECKPOINT * >
        NextCheckpoints;

XS_CLASS_END

#endif /* GAMEPLAY_CHECKPOINT_hpp */
