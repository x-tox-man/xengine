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

XS_CLASS_BEGIN( R3D_LEVEL )

    R3D_LEVEL();

    void Initialize();
    void Finalize();

    void Update( const float time_step );

    inline std::vector<R3D_PLAYER::PTR> & GetPlayerTable() { return PlayerTable; }

private :

    void ComputeCollisions( const float );

    void CreateTracks();
    void CreateGround();

    std::vector<R3D_PLAYER::PTR>
        PlayerTable;
    LEVEL_ENVIRONMENT::PTR
        Environment;

XS_CLASS_END

#endif /* R3D_LEVEL_hpp */
