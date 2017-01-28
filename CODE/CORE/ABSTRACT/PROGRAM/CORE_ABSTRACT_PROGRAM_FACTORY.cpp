//
//  CORE_ABSTRACT_PROGRAM_FACTORY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"

CORE_ABSTRACT_PROGRAM_FACTORY::CORE_ABSTRACT_PROGRAM_FACTORY() {
    
}

CORE_ABSTRACT_PROGRAM_FACTORY::~CORE_ABSTRACT_PROGRAM_FACTORY() {

    CurrentProgram = NULL;
}

void CORE_ABSTRACT_PROGRAM_FACTORY::Load( const char * path, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME & runtime ) {
    
}

void CORE_ABSTRACT_PROGRAM_FACTORY::Execute() {
    
}

void CORE_ABSTRACT_PROGRAM_FACTORY::ExecuteFunction( const char * function, int parameters, int results, int error_func ) {
    
}

CORE_ABSTRACT_PROGRAM_FACTORY * CORE_ABSTRACT_PROGRAM_FACTORY::CurrentProgram = NULL;