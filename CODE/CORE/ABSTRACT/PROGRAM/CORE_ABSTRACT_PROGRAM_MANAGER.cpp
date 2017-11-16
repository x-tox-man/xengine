//
//  CORE_ABSTRACT_PROGRAM_MANAGER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"

CORE_ABSTRACT_PROGRAM_MANAGER::CORE_ABSTRACT_PROGRAM_MANAGER() :
    ProgramTable() {
    
}

CORE_ABSTRACT_PROGRAM_MANAGER::~CORE_ABSTRACT_PROGRAM_MANAGER() {

    std::map< const char *, CORE_ABSTRACT_PROGRAM_FACTORY *>::iterator it = ProgramTable.begin();
    
    while( it != ProgramTable.end() ) {
        
        CORE_MEMORY_ObjectSafeDeallocation( it->second );
        
        it++;
    }
}

CORE_ABSTRACT_PROGRAM_FACTORY * CORE_ABSTRACT_PROGRAM_MANAGER::LoadProgram( const char * path, const CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE type, CORE_ABSTRACT_BASE_PROGRAM_RUNTIME * customRuntime ) {
    
    CORE_ABSTRACT_PROGRAM_FACTORY * script = CORE_ABSTRACT_PROGRAM_FACTORY::FactoryCreate(type);
    
    if ( customRuntime != NULL ) {
        
        script->Load( path, *customRuntime );
    }
    else {
        
        const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME * runtime = CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().getDefaultProgramRuntimeTable()[type];
        
        script->Load( path, *runtime );
    }
    
    ProgramTable[path] = script;
    
    return script;
}
