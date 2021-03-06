//
//  CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 9/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE_h
#define GAME_ENGINE_REBORN_CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE_h

enum CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE {
    CORE_ABSTRACT_PROGRAM_RUNTIME_None = -1,
    CORE_ABSTRACT_PROGRAM_RUNTIME_Lua = 0,
    CORE_ABSTRACT_PROGRAM_RUNTIME_V8,
    CORE_ABSTRACT_PROGRAM_RUNTIME_NativeLibrary,
    CORE_ABSTRACT_PROGRAM_RUNTIME_Count
};

#endif
