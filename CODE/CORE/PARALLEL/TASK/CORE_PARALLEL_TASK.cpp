//
//  CORE_PARALLEL_TASK.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_TASK.h"

CORE_PARALLEL_TASK::CORE_PARALLEL_TASK() :
    ExecuteCallback( NULL ) {
    
}

CORE_PARALLEL_TASK::~CORE_PARALLEL_TASK() {

}

CORE_PARALLEL_TASK::CORE_PARALLEL_TASK( CORE_HELPERS_CALLBACK * callback ) :
    ExecuteCallback( callback ) {
    
}

void CORE_PARALLEL_TASK::Execute() {

    (*ExecuteCallback)();
}
