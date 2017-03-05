//
//  GAMEPLAY_RULE_STATION.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_STATION.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_STATION::GAMEPLAY_RULE_STATION( int amount, int mortgage_price, GAMEPLAY_RULE_PROPERTY_GROUP * group ) :
    GAMEPLAY_RULE_PROPERTY(amount, 0, 0, mortgage_price, group) {

}

GAMEPLAY_RULE_STATION::~GAMEPLAY_RULE_STATION() {
    
}

bool GAMEPLAY_RULE_STATION::CanBuyHouse( GAMEPLAY_PLAYER * player ) {
    
    return false;
}


int GAMEPLAY_RULE_STATION::CalculateAmount( GAMEPLAY_PLAYER * player ) {
    
    int station_count = 0;
    
    station_count += (GetPropertyGroup()->GetProperties()[0]->GetOwner() == GetOwner()) ? 1 : 0;
    station_count += (GetPropertyGroup()->GetProperties()[1]->GetOwner() == GetOwner()) ? 1 : 0;
    station_count += (GetPropertyGroup()->GetProperties()[2]->GetOwner() == GetOwner()) ? 1 : 0;
    station_count += (GetPropertyGroup()->GetProperties()[3]->GetOwner() == GetOwner()) ? 1 : 0;
    
    switch (station_count) {
        case 0:
            return 0;
            break;
            
        case 1:
            return 25;
            break;
            
        case 2:
            return 50;
            break;
            
        case 3:
            return 100;
            break;
            
        case 4:
            return 200;
            break;
            
        default:
            abort();
            break;
    }
}
