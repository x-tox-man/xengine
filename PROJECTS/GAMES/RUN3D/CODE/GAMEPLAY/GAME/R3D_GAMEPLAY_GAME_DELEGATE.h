//
//  R3D_GAMEPLAY_GAME_DELEGATE.hpp
//  Run3d
//
//  Created by Christophe Bernard on 26/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_GAMEPLAY_GAME_DELEGATE_hpp
#define R3D_GAMEPLAY_GAME_DELEGATE_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_PLAYER.h"

XS_CLASS_BEGIN( R3D_GAMEPLAY_GAME_DELEGATE )

    R3D_GAMEPLAY_GAME_DELEGATE();
    virtual ~R3D_GAMEPLAY_GAME_DELEGATE() {
        
    }

    virtual void InternalUpdateGame( const float step ) {
        
        (*PlayersList)[0]->GetShip()->ApplyInputParamters( Thrust, Orientation );
    }

    virtual void InitializePlayers() {
        
    }

    void SetPlayers( std::vector<R3D_PLAYER::PTR> * players_table ) {
        
        PlayersList = players_table;
        InitializePlayers();
    }

    virtual void OnEndGame();

    inline std::vector< R3D_PLAYER::PTR > * GetPlayers() { return PlayersList; }
    inline void SetThrust( float thrust ) { Thrust = thrust; }
    inline void SetOrientation( float orientation ) { Orientation = orientation; }

protected:

    std::vector< R3D_PLAYER::PTR >
        * PlayersList;
    float
        Thrust,
        Orientation;

XS_CLASS_END

#endif /* R3D_GAMEPLAY_GAME_DELEGATE_hpp */
