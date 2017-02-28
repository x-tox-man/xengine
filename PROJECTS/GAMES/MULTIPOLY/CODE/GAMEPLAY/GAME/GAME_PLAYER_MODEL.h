//
//  PLAYER_MODEL.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 23/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef PLAYER_MODEL_h
#define PLAYER_MODEL_h

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_COLOR.h"

struct GAME_PLAYER_MODEL {
    std::string Name;
    CORE_HELPERS_COLOR Color;
    bool IsHuman;
};

#endif /* PLAYER_MODEL_h */
