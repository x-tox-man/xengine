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
    Ship( NULL ) {
    
}

void R3D_PLAYER::Initialize() {
    
    Ship = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_PLAYER_SHIP >();
    Ship->Initialize();
}

void R3D_PLAYER::Reset( const CORE_MATH_VECTOR & position, const CORE_MATH_QUATERNION & orientation ) {
    
    Ship->Reset( position, orientation);
}

std::vector< R3D_PLAYER_SHIP_MODEL::PTR > R3D_PLAYER::GetAllShipsOwned() {
    std::vector< R3D_PLAYER_SHIP_MODEL::PTR > all_ships;
    
    auto ship = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship );
    auto ship2 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship2 );
    auto ship3 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship3 );
    auto ship4 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship4 );
    auto ship5 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship5 );
    auto ship6 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship6 );
    ship6 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship6 );
    ship6 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship6 );
    ship6 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship6 );
    ship6 = new R3D_PLAYER_SHIP_MODEL;
    all_ships.push_back( ship6 );
    

    return all_ships;
}
