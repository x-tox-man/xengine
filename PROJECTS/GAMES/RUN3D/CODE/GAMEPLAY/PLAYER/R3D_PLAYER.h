
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
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

XS_CLASS_BEGIN( R3D_PLAYER )

    R3D_PLAYER();

    void Initialize();
    void InitializeEntity();
    void Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );
    void SetupNewPlayer( );

    inline GAMEPLAY_COMPONENT_ENTITY::PTR GetShip() { return Ship; }
    inline void SetPlayerName( const CORE_DATA_UTF8_TEXT & name ) { PlayerName = name; }
    inline const CORE_DATA_UTF8_TEXT & GetPlayerName() { return PlayerName; }

    bool Buy( int amount );
    std::vector<R3D_PLAYER_SHIP_MODEL::PTR> GetAllShipsOwned();

    const CORE_MATH_QUATERNION & GetOrientation() const;
    CORE_MATH_VECTOR GetPosition() const;

    inline const GRAPHIC_CAMERA & GetFront() const { return Front; }
    inline GRAPHIC_CAMERA & GetFront() { return Front; }
    inline const GRAPHIC_CAMERA & GetRear() const { return Rear; }
    inline GRAPHIC_CAMERA & GetRear() { return Rear; }

    inline const GRAPHIC_CAMERA & GetTop() const { return Top; }
    inline GRAPHIC_CAMERA & GetTop() { return Top; }

    inline std::map< CORE_HELPERS_IDENTIFIER, R3D_PLAYER_MODIFIER > & GetModifiersMap() { return ModifiersMap; }

private :

    void CreateWeaponSystem(  const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );
    void UpdateCamera( float step, GAMEPLAY_COMPONENT_POSITION::PTR pos, GAMEPLAY_COMPONENT_PHYSICS::PTR phys );
    void Fire();

    int
        VirtualCredits,
        RealMoney,
        TotalExperience,
        Level;
    float
        TotalRunTime;
    GAMEPLAY_COMPONENT_ENTITY::PTR
        Ship;
    CORE_DATA_UTF8_TEXT
        PlayerName;
    GRAPHIC_CAMERA
        Front,
        Rear,
        Top;
    std::map< CORE_HELPERS_IDENTIFIER, R3D_PLAYER_MODIFIER >
        ModifiersMap;

XS_CLASS_END

#endif /* R3D_PLAYER_hpp */
