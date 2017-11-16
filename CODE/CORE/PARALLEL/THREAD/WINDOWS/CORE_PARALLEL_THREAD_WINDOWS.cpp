//
//  CORE_PARALLEL_THREAD_POSIX.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_THREAD.h"

#if __WINDOWS_THREAD__

CORE_PARALLEL_THREAD::~CORE_PARALLEL_THREAD() {

}

void CORE_PARALLEL_THREAD::Start() {

    CreateThread( NULL, 0, &CORE_PARALLEL_THREAD::ThreadBody, 0, 0, 0 );
}

void CORE_PARALLEL_THREAD::Stop() {
    
}

void CORE_PARALLEL_THREAD::Pause() {
    
    CORE_RUNTIME_Abort();
}

void CORE_PARALLEL_THREAD::Resume() {
    
    CORE_RUNTIME_Abort();
}


#endif
