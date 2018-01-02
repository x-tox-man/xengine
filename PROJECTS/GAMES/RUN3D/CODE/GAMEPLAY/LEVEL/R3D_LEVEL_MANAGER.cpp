//
//  R3D_LEVEL_MANAGER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_MANAGER.h"
#include "CORE_FILESYSTEM.h"

R3D_LEVEL_MANAGER::R3D_LEVEL_MANAGER() :
    AllLevels(),
    CurrentLevel( NULL ) {
    
}

R3D_LEVEL_MANAGER::~R3D_LEVEL_MANAGER() {
    
    AllLevels.clear();
}

void R3D_LEVEL_MANAGER::Initialize() {
    
    //std::vector< CORE_FILESYSTEM_PATH> all_path = CORE_FILESYSTEM_PATH::FindAllFilePaths( "*" , "lvx", "LEVELS" );
    R3D_GAME_LEVEL_INFO
        info;
    
    info.LevelName = (char *) malloc( strlen( "level1\0" ) );
    strcpy( info.LevelName, "level1\0" );
    
    AllLevels.push_back(info);
}

R3D_LEVEL::PTR R3D_LEVEL_MANAGER::LoadLevel( const R3D_GAME_LEVEL_INFO & info ) {

    if ( CurrentLevel != NULL ) {
        
        CurrentLevel->Finalize();
    }
    
    if ( strcmp( info.LevelName, "level1\0" ) == 0 ) {
        
        CurrentLevel = new R3D_LEVEL;
        CurrentLevel->Initialize();
    }
    else {
        
        abort();
    }
    
    return CurrentLevel;
}


