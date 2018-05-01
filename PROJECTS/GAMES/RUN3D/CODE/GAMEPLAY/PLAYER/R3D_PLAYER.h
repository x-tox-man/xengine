
//
//  R3D_PLAYER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_hpp
#define R3D_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "R3D_PLAYER_SHIP.h"
#include "R3D_PLAYER_SHIP_MODEL.h"
#include "CORE_DATA_UTF8_TEXT.h"
#include "R3D_PLAYER_MODIFIER.h"

XS_CLASS_BEGIN( R3D_PLAYER )

    R3D_PLAYER();

    void Initialize();
    void Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );
    void SetupNewPlayer( );

    inline R3D_PLAYER_SHIP::PTR GetShip() { return Ship; }
    inline void SetPlayerName( const CORE_DATA_UTF8_TEXT & name ) { PlayerName = name; }
    inline const CORE_DATA_UTF8_TEXT & GetPlayerName() { return PlayerName; }

    bool Buy( int amount );
    std::vector<R3D_PLAYER_SHIP_MODEL::PTR> GetAllShipsOwned();

    const CORE_MATH_QUATERNION & GetOrientation() const;
    CORE_MATH_VECTOR GetPosition() const;

private :

    R3D_PLAYER_SHIP::PTR
        Ship;
    CORE_DATA_UTF8_TEXT
        PlayerName;
    int
        VirtualCredits,
        RealMoney,
        TotalExperience,
        Level;
    float
        TotalRunTime;
    std::map< CORE_HELPERS_IDENTIFIER, R3D_PLAYER_MODIFIER >
        ModifiersMap;

XS_CLASS_END

#endif /* R3D_PLAYER_hpp */
