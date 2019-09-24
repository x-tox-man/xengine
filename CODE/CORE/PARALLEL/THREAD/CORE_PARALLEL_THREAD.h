//
//  CORE_PARALLEL_THREAD.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_PARALLEL_THREAD__
#define __GAME_ENGINE_REBORN__CORE_PARALLEL_THREAD__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_PARALLEL_TASK.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"

#if PLATFORM_WINDOWS
	#define __WINDOWS_THREAD__ 1
#else
	#define __P__THREAD__ 1

    #include <pthread.h>
#endif

XS_CLASS_BEGIN( CORE_PARALLEL_THREAD )

CORE_PARALLEL_THREAD();
virtual ~CORE_PARALLEL_THREAD();

void Initialize( const char * thread_name, CORE_PARALLEL_TASK & task );

virtual void Start();

protected:

void Stop();
void Pause();
void Resume();

char
    ThreadName[64];

private:

CORE_PARALLEL_TASK
    * Task;

static const char * DefaultThreadName;

#if __P__THREAD__
    #include "CORE_PARALLEL_THREAD_POSIX.hpp"
#else
    public:
    #include "CORE_PARALLEL_THREAD_WINDOWS.hpp"
    private:
#endif

XS_CLASS_END

template <typename __TASK_TYPE>
class CORE_PARALLEL_THREAD_TYPED : CORE_PARALLEL_THREAD {
public:

    CORE_PARALLEL_THREAD_TYPED() :CORE_PARALLEL_THREAD() {
        
    }

void Initialize( const char * thread_name, __TASK_TYPE & task ) {
    
    CORE_DATA_COPY_STRING( ThreadName, thread_name );
    
    TypedTask = &task;
}
    
    void Start() {
#if __P__THREAD__
        pthread_create( &Thread, NULL, &__TASK_TYPE::Execute, (void*) TypedTask );
#else
       
       CreateThread( NULL, 0, &__TASK_TYPE::ExecuteWindows, ( void* ) TypedTask, 0, 0 );

        //TODO WINDOWS PART : Attention, this code is awfully
#endif
    }


__TASK_TYPE
    * TypedTask;

#if __P__THREAD__
    #include "CORE_PARALLEL_THREAD_POSIX.hpp"
#else
    public:
    #include "CORE_PARALLEL_THREAD_WINDOWS.hpp"
    private:
#endif

XS_CLASS_END



#endif /* defined(__GAME_ENGINE_REBORN__CORE_PARALLEL_THREAD__) */
