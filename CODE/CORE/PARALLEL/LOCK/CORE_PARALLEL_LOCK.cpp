//
//  CORE_PARALLEL_LOCK.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_LOCK.h"

CORE_PARALLEL_LOCK::CORE_PARALLEL_LOCK(CORE_PARALLEL_LOCK_MUTEX & lock_mutex ) :
    ThisLock(lock_mutex.GetMutex() ) {
    
}

CORE_PARALLEL_LOCK::~CORE_PARALLEL_LOCK() {
    
}
