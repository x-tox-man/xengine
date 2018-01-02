//
//  NETWORK_REMOTE_GAME_INFO.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 23/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "NETWORK_REMOTE_GAME_INFO.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( NETWORK_REMOTE_GAME_INFO )
    XS_DEFINE_ClassMemberArray( "LevelName", char, (char **) &LevelName, (int)strlen( LevelName ) )
XS_END_INTERNAL_MEMORY_LAYOUT
