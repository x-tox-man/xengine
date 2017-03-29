//
//  GAMEPLAY_ACTION_COMMAND_START_GAME.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 6/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_ACTION_COMMAND_START_GAME_hpp
#define GAMEPLAY_ACTION_COMMAND_START_GAME_hpp

#include "GAMEPLAY_ACTION.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_ACTION_COMMAND_START_GAME, GAMEPLAY_ACTION )
    XS_DEFINE_SERIALIZABLE

    GAMEPLAY_ACTION_COMMAND_START_GAME();
    GAMEPLAY_ACTION_COMMAND_START_GAME( std::vector<NETWORK_PLAYER*> & players, int seed );
    ~GAMEPLAY_ACTION_COMMAND_START_GAME();

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_ACTION_COMMAND_START_GAME, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_GameStarting );

    static void SetGameStartingCallback( const CORE_HELPERS_CALLBACK_2< std::vector< NETWORK_PLAYER* > &, int > & callback ) { GameStartingCallback = callback; }

    SimpleTrickForSerialization()

    virtual void Apply() override;

    static CORE_HELPERS_CALLBACK_2< std::vector< NETWORK_PLAYER* > &, int >
        GameStartingCallback;

    std::vector<NETWORK_PLAYER*>
        Players;
    int
        Seed;

private:
    

XS_CLASS_END

#endif /* GAMEPLAY_ACTION_COMMAND_START_GAME_hpp */
