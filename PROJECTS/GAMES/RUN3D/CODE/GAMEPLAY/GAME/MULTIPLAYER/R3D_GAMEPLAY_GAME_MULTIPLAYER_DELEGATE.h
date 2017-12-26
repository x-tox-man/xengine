//
//  R3D_GAMEPLAY_GAME_MULTIPLAYER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_GAME_MULTIPLAYER_hpp
#define R3D_GAMEPLAY_GAME_MULTIPLAYER_hpp

#include "R3D_GAMEPLAY_GAME_DELEGATE.h"
#include "R3D_GAMEPLAY_GAME.h"
#include "NETWORK_REMOTE_GAME_INFO.h"
#include "GAME_PLAYER_MODEL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE, R3D_GAMEPLAY_GAME_DELEGATE )

    R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE();
    virtual ~R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE() {
        
    }

    inline const NETWORK_REMOTE_GAME_INFO & GetInfo() const { return Info; }
    inline NETWORK_REMOTE_GAME_INFO & GetInfo() { return Info; }
    void SetInfo( const NETWORK_REMOTE_GAME_INFO & info );

    virtual void InternalUpdateGame( const float step ) override;

private:

    NETWORK_REMOTE_GAME_INFO
        Info;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_GAME_MULTIPLAYER_hpp */
