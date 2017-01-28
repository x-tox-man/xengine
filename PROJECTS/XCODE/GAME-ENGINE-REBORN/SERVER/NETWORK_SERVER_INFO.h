//
//  NETWORK_SERVER_INFO.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 4/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_SERVER_INFO_hpp
#define NETWORK_SERVER_INFO_hpp

#include "CORE_HELPERS_CLASS.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN(NETWORK_SERVER_INFO)

NETWORK_SERVER_INFO();
NETWORK_SERVER_INFO(const char *, const char *, const char *, int, int);

XS_DEFINE_SERIALIZABLE

private :

char
    * Name,
    * GameTitle,
    * Adress;
int
    PlayersCount,
    MaxPlayers;
std::vector<NETWORK_PLAYER *>
    Players;

XS_CLASS_END

#endif /* NETWORK_SERVER_INFO_hpp */
