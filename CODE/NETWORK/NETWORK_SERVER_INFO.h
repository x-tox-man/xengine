//
//  NETWORK_SERVER_INFO.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_SERVER_INFO_hpp
#define NETWORK_SERVER_INFO_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"

XS_CLASS_BEGIN( NETWORK_SERVER_INFO )

    NETWORK_SERVER_INFO();
    NETWORK_SERVER_INFO(const char *, const char *, const char *, int, int);
    ~NETWORK_SERVER_INFO();

    XS_DEFINE_SERIALIZABLE

    CORE_DATA_BUFFER & GetSpecificGameInfo() { return SpecificGameInfo; }

    char
        * Name,
        * GameTitle,
        * Adress;
    int
        PlayersCount,
        MaxPlayers,
        AppVersion;
    CORE_DATA_BUFFER
        SpecificGameInfo;

XS_CLASS_END

#endif /* NETWORK_SERVER_INFO_hpp */
