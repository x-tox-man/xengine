//
//  R3D_PLAYER_MODIFIER.hpp
//  Run3d
//
//  Created by Christophe Bernard on 7/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_PLAYER_MODIFIER_hpp
#define R3D_PLAYER_MODIFIER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"

class R3D_PLAYER;

XS_CLASS_BEGIN( R3D_PLAYER_MODIFIER )

    R3D_PLAYER_MODIFIER();

    inline void SetValue( float value ) { ModifierValue = value; }
    inline float GetValue() { return ModifierValue; }

    void Apply( R3D_PLAYER * player );
    void Discard( R3D_PLAYER * player );

    static CORE_HELPERS_IDENTIFIER
        MaxSpeedModifier,
        HorsePowerModifier,
        FuelCapacityModifier,
        WeaponReloadTimeModifier,
        GravityModifier,
        MassModifier,
        ExperienceGainModifier;

private:

    float
        ModifierValue;
    CORE_HELPERS_IDENTIFIER
        ModifierIdentifier;

XS_CLASS_END

#endif /* R3D_PLAYER_MODIFIER_hpp */
