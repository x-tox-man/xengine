//
//  NETWORK_REMOTE_SERVER_INFO.h
//  Run3d
//
//  Created by Christophe Bernard on 23/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef NETWORK_REMOTE_SERVER_INFO_h
#define NETWORK_REMOTE_SERVER_INFO_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_MODEL.h"

XS_CLASS_BEGIN( NETWORK_REMOTE_GAME_INFO )

    XS_DEFINE_SERIALIZABLE

    NETWORK_REMOTE_GAME_INFO() : LevelName( NULL ) {
        
    }

    void SetLevelName(const char * level_name) {
        
        LevelName = (char*) malloc( strlen(level_name) + 1);
        
        strcpy(LevelName, level_name);
        LevelName[strlen(level_name)] = '\0';
    }

    inline const char * GetLevelName() const { return LevelName; }

private :

    char
        * LevelName;

XS_CLASS_END

#endif /* NETWORK_REMOTE_SERVER_INFO_h */
