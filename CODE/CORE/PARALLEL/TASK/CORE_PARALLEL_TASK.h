//
//  CORE_PARALLEL_TASK.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_PARALLEL_TASK__
#define __GAME_ENGINE_REBORN__CORE_PARALLEL_TASK__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_CALLBACK.h"

template <typename __LABMDA_TYPE>
class CORE_PARALLEL_LAMBDA_TASK {
    
public:
    CORE_PARALLEL_LAMBDA_TASK( __LABMDA_TYPE lambda_function_parameter ) : Lambda( lambda_function_parameter) {
        
    }
    
    void Execute() {
        
        Lambda();
    }
    
    static void * Execute( void * context ) {
        
        CORE_PARALLEL_LAMBDA_TASK * task = ( CORE_PARALLEL_LAMBDA_TASK *) context;
        
        task->Execute();
        
        return 0;
    }
    
private:
    __LABMDA_TYPE Lambda;
};

XS_CLASS_BEGIN( CORE_PARALLEL_TASK )

CORE_PARALLEL_TASK();
CORE_PARALLEL_TASK(CORE_HELPERS_CALLBACK * callback);

void Execute();

static void * Execute( void * context ) {
    
    CORE_PARALLEL_TASK * task = ( CORE_PARALLEL_TASK *) context;
    
    task->Execute();
    
    return 0;
}

CORE_HELPERS_CALLBACK
    * ExecuteCallback;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_PARALLEL_TASK__) */
