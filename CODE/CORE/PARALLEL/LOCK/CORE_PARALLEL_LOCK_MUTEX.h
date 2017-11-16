//
//  CORE_PARALLEL_LOCK_MUTEX.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_PARALLEL_LOCK_MUTEX_hpp
#define CORE_PARALLEL_LOCK_MUTEX_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

XS_CLASS_BEGIN(CORE_PARALLEL_LOCK_MUTEX)

CORE_PARALLEL_LOCK_MUTEX();
~CORE_PARALLEL_LOCK_MUTEX();

std::mutex & GetMutex() { return Mutex; }

private:

std::mutex
    Mutex;

XS_CLASS_END

#endif /* CORE_PARALLEL_LOCK_MUTEX_hpp */
