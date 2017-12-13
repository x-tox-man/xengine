//
//  GAMEPLAY_CHECKPOINT_SYSTEM.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/11/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_CHECKPOINT_SYSTEM_hpp
#define GAMEPLAY_CHECKPOINT_SYSTEM_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_CHECKPOINT.h"
#include "CORE_HELPERS_CALLBACK.h"

XS_CLASS_BEGIN( GAMEPLAY_CHECKPOINT_SYSTEM )

    GAMEPLAY_CHECKPOINT_SYSTEM();
    ~GAMEPLAY_CHECKPOINT_SYSTEM();

    void AddCheckpoint( GAMEPLAY_COMPONENT_ENTITY * entity );
    void AddCheckpoint( GAMEPLAY_COMPONENT_ENTITY * entity, bool repeats, int repeat_count );
    void AddCheckpoint( GAMEPLAY_COMPONENT_ENTITY * checkpoint, GAMEPLAY_COMPONENT_ENTITY * previous, bool repeats, int repeat_count );

    void OnCheckpointCollision( GAMEPLAY_COMPONENT_ENTITY * checkpoint, GAMEPLAY_COMPONENT_ENTITY * entity );

    inline void SetPlayerFinishedCallback( CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * > & callback ) { PlayerFinishedCallback = callback; }

    void Start( std::vector< GAMEPLAY_COMPONENT_ENTITY * > & players );
    void Reset( GAMEPLAY_COMPONENT_ENTITY * );
    void Reset();

private:

    std::vector< GAMEPLAY_CHECKPOINT * >
        Checkpoints;
    CORE_HELPERS_CALLBACK_2< GAMEPLAY_COMPONENT_ENTITY *, GAMEPLAY_COMPONENT_ENTITY * >
        CheckpointCallback;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        PlayerFinishedCallback;

XS_CLASS_END

#endif /* GAMEPLAY_CHECKPOINT_SYSTEM_hpp */
