//
//  NETWORK_GAME_INFO.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_GAME_INFO_h
#define NETWORK_GAME_INFO_h

#include "CORE_HELPERS_CLASS.h"

XS_CLASS_BEGIN(NETWORK_GAME_INFO)

    XS_DEFINE_SERIALIZABLE

    NETWORK_GAME_INFO();
    ~NETWORK_GAME_INFO();
    NETWORK_GAME_INFO(const char *, const char *);

private :

    char
        * GameId,
        * GameStartedTime;

XS_CLASS_END

#endif /* NETWORK_GAME_INFO_h */
