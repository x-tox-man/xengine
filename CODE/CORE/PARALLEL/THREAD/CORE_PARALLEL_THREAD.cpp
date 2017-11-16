//
//  CORE_PARALLEL_THREAD.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_THREAD.h"
#include "CORE_MEMORY.h"

CORE_PARALLEL_THREAD::CORE_PARALLEL_THREAD() :
    Task( NULL ),
    ThreadName( NULL ) {
    
    ThreadName = (char *) CORE_MEMORY_ALLOCATOR::Allocate(strlen(DefaultThreadName));
    strcpy( ThreadName, DefaultThreadName );
}

void CORE_PARALLEL_THREAD::Initialize( const char *thread_name, CORE_PARALLEL_TASK & thread_task ) {
    
    ThreadName = (char *) CORE_MEMORY_ALLOCATOR::Allocate(strlen( thread_name ) );
    strcpy( ThreadName, thread_name );
    
    Task = &thread_task;
}

const char * CORE_PARALLEL_THREAD::DefaultThreadName = "X_Thread0";
