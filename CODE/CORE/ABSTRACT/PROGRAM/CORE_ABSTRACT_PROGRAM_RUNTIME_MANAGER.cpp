//
//  CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 28/12/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_RUNTIME_V8.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"

CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER() :
    DefaultProgramRuntimeTable(),
    CustomProgramRuntimeTable() {
        
}

CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::~CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER() {
    std::map<CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE, CORE_ABSTRACT_BASE_PROGRAM_RUNTIME * >::iterator it = DefaultProgramRuntimeTable.begin();
    
    while ( it != DefaultProgramRuntimeTable.end() ) {
        
        delete it->second;
        
        it++;
    }
    
    std::map<CORE_HELPERS_IDENTIFIER, CORE_ABSTRACT_BASE_PROGRAM_RUNTIME * >::iterator it2 = CustomProgramRuntimeTable.begin();
    
    while ( it2 != CustomProgramRuntimeTable.end() ) {
        
        delete it2->second;
        
        it2++;
    }
}

void CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::Initialize() {
    
    CORE_ABSTRACT_RUNTIME_LUA * lua = new CORE_ABSTRACT_RUNTIME_LUA();
    lua->Initialize();
    CORE_ABSTRACT_RUNTIME_V8 * v8 = new CORE_ABSTRACT_RUNTIME_V8();
    v8->Initialize();
    
    DefaultProgramRuntimeTable[ CORE_ABSTRACT_PROGRAM_RUNTIME_Lua ] = lua;
    DefaultProgramRuntimeTable[ CORE_ABSTRACT_PROGRAM_RUNTIME_V8 ] = v8;
}