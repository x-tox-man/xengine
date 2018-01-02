//
//  R3D_GAME_LEVEL_INFO.hpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GAME_LEVEL_INFO_hpp
#define R3D_GAME_LEVEL_INFO_hpp

#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_COPY( R3D_GAME_LEVEL_INFO )

    R3D_GAME_LEVEL_INFO();
    ~R3D_GAME_LEVEL_INFO() {
        
    }

    void operator = ( const R3D_GAME_LEVEL_INFO & other ) {
        
        abort();
    }

    bool operator == ( const R3D_GAME_LEVEL_INFO & other ) const {
        
        return LevelName != NULL && other.LevelName != NULL && strcmp(LevelName, other.LevelName ) == 0;
    }

    char
        * LevelName,
        * LevelPicto;

XS_CLASS_END

#endif /* R3D_GAME_LEVEL_INFO_hpp */
