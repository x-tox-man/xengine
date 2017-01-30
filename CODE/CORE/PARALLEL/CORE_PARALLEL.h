//
//  CORE_PARALLEL.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_PARALLEL_h
#define CORE_PARALLEL_h

#include "CORE_PARALLEL_TASK.h"
#include "CORE_PARALLEL_THREAD.h"
#include "CORE_PARALLEL_LOCK.h"
#include "CORE_PARALLEL_LOCK_MUTEX.h"

#define CORE_PARALLEL_TASK_BEGIN(...) \
{ \
auto __func = [__VA_ARGS__] () {


#if PLATFORM_WINDOWS || PLATFORM_ANDROID
    #define CORE_PARALLEL_TASK_END() \
        }; \
        CORE_PARALLEL_LAMBDA_TASK< decltype( __func ) > * __task = new CORE_PARALLEL_LAMBDA_TASK< decltype( __func ) > ( __func ); \
        CORE_PARALLEL_THREAD_TYPED< CORE_PARALLEL_LAMBDA_TASK< decltype( __func ) > > * __taskThread = new CORE_PARALLEL_THREAD_TYPED< CORE_PARALLEL_LAMBDA_TASK< decltype( __func ) > >(); \
        __taskThread->Initialize("XS background task", *__task ); \
        __taskThread->Start(); \
        }
#else
    #define CORE_PARALLEL_TASK_END() \
        }; \
        CORE_PARALLEL_LAMBDA_TASK< typeof( __func ) > * __task = new CORE_PARALLEL_LAMBDA_TASK< typeof( __func ) > ( __func ); \
        CORE_PARALLEL_THREAD_TYPED< CORE_PARALLEL_LAMBDA_TASK< typeof( __func ) > > * __taskThread = new CORE_PARALLEL_THREAD_TYPED< CORE_PARALLEL_LAMBDA_TASK< typeof( __func ) > >(); \
        __taskThread->Initialize("XS background task", *__task ); \
        __taskThread->Start(); \
        }
#endif

#define CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(__LOCK_MUTEX__) \
{ \
    CORE_PARALLEL_LOCK Lock(__LOCK_MUTEX__);

#define CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END() }
#endif /* CORE_PARALLEL_h */
