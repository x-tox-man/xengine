//
//  R3D_PLAYER_SHIP.hpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_SHIP_hpp
#define R3D_PLAYER_SHIP_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "R3D_PLAYER_PARTS_COLLECTION.h"
#include "GRAPHIC_CAMERA.h"
#include "GRAPHICS_STEAM_ENGINE.h"
#include "R3D_PLAYER_MODIFIER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_PLAYER_SHIP, GAMEPLAY_COMPONENT_ENTITY )

    XS_DEFINE_SERIALIZABLE

    R3D_PLAYER_SHIP();
    ~R3D_PLAYER_SHIP();

    void Initialize();
    void Update( float step );
    void Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );

    void CreateWeaponSystem(  const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation );
    inline const GRAPHIC_CAMERA & GetFront() const { return Front; }
    inline GRAPHIC_CAMERA & GetFront() { return Front; }
    inline const GRAPHIC_CAMERA & GetRear() const { return Rear; }
    inline GRAPHIC_CAMERA & GetRear() { return Rear; }

    inline const GRAPHIC_CAMERA & GetTop() const { return Top; }
    inline GRAPHIC_CAMERA & GetTop() { return Top; }

    inline void SetThrust( float thrust ) { Thrust = thrust; }
    inline void SetRotation( float orientation ) { Rotation = orientation; }
    inline float GetThrust() const { return Thrust; }
    inline float GetRotation() const { return Rotation; }
    inline std::map< CORE_HELPERS_IDENTIFIER, R3D_PLAYER_MODIFIER > & GetModifiersMap() { return ModifiersMap; }

    void ApplyInputParamters( float thrust, float orientation ) {
        
        SetThrust( thrust );
        SetRotation( orientation );
    }

private:

    R3D_PLAYER_PARTS_COLLECTION
        Parts;
    GRAPHIC_CAMERA
        Front,
        Rear,
        Top;
    GRAPHICS_STEAM_ENGINE
        Steam;
    float
        Thrust,
        Rotation;
    std::map< CORE_HELPERS_IDENTIFIER, R3D_PLAYER_MODIFIER >
        ModifiersMap;

XS_CLASS_END

#endif /* R3D_PLAYER_SHIP_hpp */
