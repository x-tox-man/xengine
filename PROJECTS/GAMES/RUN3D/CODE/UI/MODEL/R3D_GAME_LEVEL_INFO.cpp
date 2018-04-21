//
//  R3D_GAME_LEVEL_INFO.cpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GAME_LEVEL_INFO.h"

R3D_GAME_LEVEL_INFO::R3D_GAME_LEVEL_INFO() :
    LevelName( NULL ),
    LevelPicto( NULL ),
    Scores(),
    PlayerBest( -1.0f ) {
    
}

R3D_GAME_LEVEL_INFO::R3D_GAME_LEVEL_INFO( const R3D_GAME_LEVEL_INFO & other ) :
    LevelName( other.LevelName ),
    LevelPicto( other.LevelPicto ) {
    
}
