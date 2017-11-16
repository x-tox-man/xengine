//
//  CORE_PARALLEL_LOCK_POSIX.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "CORE_PARALLEL_LOCK.h"

#if __P__THREAD__

CORE_PARALLEL_LOCK();

void Lock();
void Unlock();

#endif
