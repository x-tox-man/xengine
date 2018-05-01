//
//  R3D_PLAYER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

R3D_PLAYER::R3D_PLAYER() :
    Ship( NULL ),
    VirtualCredits( 0 ),
    RealMoney( 0 ),
    TotalExperience( 0 ),
    Level( 1 ),
    TotalRunTime( 0.0f ),
    ModifiersMap() {

    ModifiersMap[ R3D_PLAYER_MODIFIER::MaxSpeedModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::HorsePowerModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::FuelCapacityModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::WeaponReloadTimeModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::GravityModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::MassModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::ExperienceGainModifier ].SetValue( 0.0f );
    ModifiersMap[ R3D_PLAYER_MODIFIER::BrakeModifier ].SetValue( 0.0f );
}

void R3D_PLAYER::Initialize() {
    
    Ship = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_PLAYER_SHIP >();
    Ship->Initialize();
}

void R3D_PLAYER::Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    Ship->Reset( position, orientation);
    TotalRunTime = 0.0f;
}

std::vector< R3D_PLAYER_SHIP_MODEL::PTR > R3D_PLAYER::GetAllShipsOwned() {
    
    std::vector< R3D_PLAYER_SHIP_MODEL::PTR > all_ships;
    
    auto ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    
    return all_ships;
}

bool R3D_PLAYER::Buy( int amount ) {
    
    if ( VirtualCredits >= amount ) {
        
        VirtualCredits -= amount;
        
        return true;
    }
    
    return false;
}

const CORE_MATH_QUATERNION & R3D_PLAYER::GetOrientation() const {
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) Ship->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
    
    return pos->GetOrientation();
}

CORE_MATH_VECTOR R3D_PLAYER::GetPosition() const {
    
    if( Ship ) {
        auto pos = (GAMEPLAY_COMPONENT_POSITION::PTR) Ship->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position );
        
        return pos->GetPosition();
    }
    
    return CORE_MATH_VECTOR();
}
