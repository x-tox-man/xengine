//
//  CORE_ABSTRACT_PROGRAM_RUNTIME.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"
#include "CORE_ABSTRACT_RUNTIME_V8.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"

template class CORE_ABSTRACT_PROGRAM_RUNTIME<CORE_ABSTRACT_RUNTIME_V8>;
template class CORE_ABSTRACT_PROGRAM_RUNTIME<CORE_ABSTRACT_RUNTIME_LUA>;
