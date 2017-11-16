//
//  NETWORK_GAME_PLAYER.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_GAME_PLAYER_hpp
#define NETWORK_GAME_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "NETWORK_PLAYER.h"
#include "GAME_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_GAME_PLAYER, GAME_PLAYER)

NETWORK_GAME_PLAYER();
virtual ~NETWORK_GAME_PLAYER();

private :

NETWORK_PLAYER *
    Player;
/**
 * GameStartMessageLatencyTable
 *      Collects the delta(Time) between two network messages for calculating the synchronized game start time
 *      Based on the result, the game shall begin nearly as simultaneously on each clients
 *      The framrate is the same for all the players : 30 fps of calculations
 *      Even in lower fps conditions the update loop will happen as often as required in order to allow maximum
 *      synchronization
 */
std::array<long int,150>
    GameStartMessageLatencyTable;

XS_CLASS_END

#endif /* NETWORK_GAME_PLAYER_hpp */
