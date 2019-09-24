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
#include "R3D_GAME_LEVEL_INFO.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"

XS_CLASS_BEGIN( R3D_LEVEL )

    R3D_LEVEL();

    void Initialize();
    void Initialize( const CORE_FILESYSTEM_PATH & path );
    void Finalize();

    void Start();
    void Restart();

    void Update( const float time_step );

    inline std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_PLAYER::PTR > & GetPlayerTable() { return PlayerTable; }
    inline GAMEPLAY_CHECKPOINT_SYSTEM & GetCheckpoints() { return Checkpoints; }

    void OnCheckpointCollision( GAMEPLAY_COMPONENT_ENTITY * entity );
    void OnPlayerCompleted( GAMEPLAY_COMPONENT_ENTITY * entity );
    void OnPlayerTouchedCheckPoint( GAMEPLAY_COMPONENT_ENTITY * checkpoint, GAMEPLAY_COMPONENT_ENTITY * ship );
    inline R3D_GAME_LEVEL_INFO::PTR GetInfo() { return Info; }
    inline void SetInfo( R3D_GAME_LEVEL_INFO::PTR info ) { Info = info; }

private :

    void ComputeCollisions( const float );

    void CreateTracks();
    void CreateGround();
    void CreateSky();
    void CreateMoon();

    float
        Gravity;
    int
        MaxPlayerCount;
    bool
        Reverse;
    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_PLAYER::PTR >
        PlayerTable;
    LEVEL_ENVIRONMENT::PTR
        Environment;
    GAMEPLAY_CHECKPOINT_SYSTEM
        Checkpoints;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_COMPONENT_ENTITY * >
        EndGameCallback;
    CORE_HELPERS_CALLBACK_2< GAMEPLAY_COMPONENT_ENTITY *, GAMEPLAY_COMPONENT_ENTITY * >
        TouchCheckpointCallback;
    R3D_GAME_LEVEL_INFO::PTR
        Info;
    CORE_ABSTRACT_PROGRAM_FACTORY
        * Script;
    GAMEPLAY_COMPONENT_ENTITY::PTR
        Sky;
#if DEBUG
    CORE_FILESYSTEM_FILE_WATCHER
        * Watcher;
#endif


XS_CLASS_END

#endif /* R3D_LEVEL_hpp */
