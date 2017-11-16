//
//  CORE_RUNTIME_ENVIRONMENT_OSX.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 27/07/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <Windowsx.h>

#include <map>
#include <list>
#include <vector>
#include <string>
#include <array>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <thread>
#include <mutex>

#if DEBUG
    #define CORE_RUNTIME_Abort() \
        DebugBreak();
#else
    #define CORE_RUNTIME_Abort() \
        abort();
#endif
