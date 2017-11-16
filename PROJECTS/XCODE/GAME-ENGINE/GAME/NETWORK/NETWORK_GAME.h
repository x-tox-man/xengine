//
//  NETWORK_GAME.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_GAME_hpp
#define NETWORK_GAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAME.h"
#include "NETWORK_GAME_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_GAME, GAME)

    NETWORK_GAME();
    virtual ~NETWORK_GAME();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Start() override;
    virtual void Pause() override;
    virtual void Resume() override;
    virtual void End() override;

private:

    std::vector< NETWORK_GAME_PLAYER * >
        PlayerTable;


XS_CLASS_END

#endif /* NETWORK_GAME_hpp */
