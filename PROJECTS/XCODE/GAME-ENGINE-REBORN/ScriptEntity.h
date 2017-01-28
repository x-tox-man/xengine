//
//  ScriptEntity.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 11/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__ScriptEntity__
#define __GAME_ENGINE_REBORN__ScriptEntity__

#include "CORE_HELPERS_CLASS.h"

#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_FILESYSTEM.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"

XS_CLASS_BEGIN( ScriptEntity )

CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( ScriptEntity );

ScriptEntity();
static void Ping();

void Initialize( CORE_FILESYSTEM_PATH path );

void mySuperScriptMethod();
void mySuperScriptMethodWithParameter(const char *);
int mySuperScriptMethodWithParameterAndReturnType(const char *);
    
XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__ScriptEntity__) */
