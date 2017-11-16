//
//  CORE_PARALLEL_LOCK.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_PARALLEL_LOCK_hpp
#define CORE_PARALLEL_LOCK_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_PARALLEL_LOCK_MUTEX.h"

XS_CLASS_BEGIN(CORE_PARALLEL_LOCK)

CORE_PARALLEL_LOCK(CORE_PARALLEL_LOCK_MUTEX & lock_mutex );
~CORE_PARALLEL_LOCK();

private:
std::lock_guard<std::mutex>
    ThisLock;

XS_CLASS_END

#endif /* CORE_PARALLEL_LOCK_hpp */
