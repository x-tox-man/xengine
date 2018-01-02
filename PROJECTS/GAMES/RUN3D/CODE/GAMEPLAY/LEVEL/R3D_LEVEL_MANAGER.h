//
//  R3D_LEVEL_MANAGER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_LEVEL_MANAGER_hpp
#define R3D_LEVEL_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "LEVEL_ENVIRONMENT.h"
#include "R3D_PLAYER.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GAMEPLAY_CHECKPOINT_SYSTEM.h"
#include "R3D_LEVEL.h"
#include "R3D_GAME_LEVEL_INFO.h"

XS_CLASS_BEGIN( R3D_LEVEL_MANAGER )

    R3D_LEVEL_MANAGER();
    ~R3D_LEVEL_MANAGER();

    void Initialize();

    inline R3D_LEVEL::PTR GetCurrentLevel() { return CurrentLevel; }
    inline std::vector< R3D_GAME_LEVEL_INFO > & GetAllLevels() { return AllLevels; }

    R3D_LEVEL::PTR LoadLevel( const R3D_GAME_LEVEL_INFO & info );

private:

    std::vector< R3D_GAME_LEVEL_INFO >
        AllLevels;
    R3D_LEVEL::PTR
        CurrentLevel;

XS_CLASS_END

#endif /* R3D_LEVEL_MANAGER_hpp */
