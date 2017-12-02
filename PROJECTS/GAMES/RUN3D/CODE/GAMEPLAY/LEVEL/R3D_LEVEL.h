//
//  R3D_LEVEL.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_hpp
#define R3D_LEVEL_hpp

#include "CORE_HELPERS_CLASS.h"
#include "LEVEL_ENVIRONMENT.h"
#include "R3D_PLAYER.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GAMEPLAY_CHECKPOINT_SYSTEM.h"

XS_CLASS_BEGIN( R3D_LEVEL )

    R3D_LEVEL();

    void Initialize();
    void Finalize();

    void Start();

    void Update( const float time_step );

    inline std::vector<R3D_PLAYER::PTR> & GetPlayerTable() { return PlayerTable; }
    inline GAMEPLAY_CHECKPOINT_SYSTEM & GetCheckpoints() { return Checkpoints; }

    void OnCheckpointCollision( GAMEPLAY_COMPONENT_ENTITY * entity );
    void OnEndGame( GAMEPLAY_COMPONENT_ENTITY * entity );

private :

    void ComputeCollisions( const float );

    void CreateTracks();
    void CreateGround();

    std::vector<R3D_PLAYER::PTR>
        PlayerTable;
    LEVEL_ENVIRONMENT::PTR
        Environment;
    GAMEPLAY_CHECKPOINT_SYSTEM
        Checkpoints;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        EndGameCallback;

XS_CLASS_END

#endif /* R3D_LEVEL_hpp */
