//
//  R3D_LEVEL_MANAGER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 29/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_LEVEL_MANAGER.h"
#include "CORE_FILESYSTEM.h"
#include "RUN3D_APPLICATION.h"

R3D_LEVEL_MANAGER::R3D_LEVEL_MANAGER() :
    AllLevels(),
    CurrentLevel( NULL ) {
    
}

R3D_LEVEL_MANAGER::~R3D_LEVEL_MANAGER() {
    
    AllLevels.clear();
}

void R3D_LEVEL_MANAGER::Initialize() {
    
    //std::vector< CORE_FILESYSTEM_PATH> all_path = CORE_FILESYSTEM_PATH::FindAllFilePaths( "*" , "lvx", "LEVELS" );
    
    for (int i = 0; i < 10; i++ ) {
        
        wchar_t * level_name = (wchar_t*) malloc( wcslen( L"level100000" ) * sizeof( wchar_t ) );
        char * level_picto = (char*) malloc( strlen( "level100000_picto" ) );
        
        
        swprintf( level_name, 40, L"Level %d\0", i );
        sprintf( level_picto, "level%d_picto", i );
        
        auto info = new R3D_GAME_LEVEL_INFO;
        info->LevelName = level_name;
        info->LevelPicto = level_picto;
        info->Scores[0] = 10.0f;
        info->Scores[1] = 8.0f;
        info->Scores[2] = 7.0f;
        info->Scores[3] = 6.5f;
        AllLevels.push_back( info );
    }
}

R3D_LEVEL::PTR R3D_LEVEL_MANAGER::LoadLevel( R3D_GAME_LEVEL_INFO::PTR info ) {

    if ( CurrentLevel != NULL ) {
        
        CurrentLevel->Finalize();
    }
    
    CurrentLevel = new R3D_LEVEL;
    CurrentLevel->Initialize( CORE_FILESYSTEM_PATH::FindFilePath( "level2", "lua", "SCRIPTS") );
    CurrentLevel->SetInfo( info );
    
    return CurrentLevel;
}

void R3D_LEVEL_MANAGER::HandleLevelComplete() {
    
    float duration = R3D_APP_PTR->GetGame()->GetGameDuration();
    
    R3D_GAME_LEVEL_INFO & info = *CurrentLevel->GetInfo();
    
    if ( duration < info.PlayerBest || info.PlayerBest == -1.0f ) {
        
        info.PlayerBest = duration;
        
        if ( duration < info.Scores[0] ) {
            //Best
        }
        else if ( duration < info.Scores[1] ) {
            //Gold
            
        }
        else if ( duration < info.Scores[2] ) {
            //Silver
        }
        else if ( duration < info.Scores[3] ) {
            //Bronze
        }
    }
}
