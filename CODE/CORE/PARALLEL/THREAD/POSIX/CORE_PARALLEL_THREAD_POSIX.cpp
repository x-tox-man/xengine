//
//  CORE_PARALLEL_THREAD_POSIX.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_THREAD.h"

#if __P__THREAD__

CORE_PARALLEL_THREAD::~CORE_PARALLEL_THREAD() {
    
}

void CORE_PARALLEL_THREAD::Start() {
    
    pthread_create( &Thread, NULL, &CORE_PARALLEL_TASK::Execute, (void*) Task );
}

void CORE_PARALLEL_THREAD::Stop() {
    
    pthread_join(Thread, NULL);
}

void CORE_PARALLEL_THREAD::Pause() {
    
    CORE_RUNTIME_Abort();
}

void CORE_PARALLEL_THREAD::Resume() {
    
    CORE_RUNTIME_Abort();
}


#endif