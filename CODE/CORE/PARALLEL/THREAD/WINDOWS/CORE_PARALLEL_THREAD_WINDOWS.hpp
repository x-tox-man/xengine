//
//  CORE_PARALLEL_THREAD_WINDOWS.c
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

static DWORD WINAPI ThreadBody( LPVOID lpParam ) {

    CORE_PARALLEL_TASK::Execute( &lpParam );

    return 1;
}

HANDLE Thread;
