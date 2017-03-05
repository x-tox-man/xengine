//
//  GAMEPLAY_RULE_PROPERTY_SERVICE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 5/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PROPERTY_SERVICE.h"

GAMEPLAY_RULE_PROPERTY_SERVICE::GAMEPLAY_RULE_PROPERTY_SERVICE( int amount, int mortgage_price, GAMEPLAY_RULE_PROPERTY_GROUP * group ) :
    GAMEPLAY_RULE_PROPERTY(amount, 0, 0, mortgage_price, group ) {
    
}

GAMEPLAY_RULE_PROPERTY_SERVICE::~GAMEPLAY_RULE_PROPERTY_SERVICE() {
    
}

bool GAMEPLAY_RULE_PROPERTY_SERVICE::CanBuyHouse( GAMEPLAY_PLAYER * player ) {
    
    return false;
}

int GAMEPLAY_RULE_PROPERTY_SERVICE::CalculateAmount(GAMEPLAY_PLAYER * player) {
    
    int amount = 0;
    
    if ( GetPropertyGroup()->DoesPlayerOwnAllPropertiesInGroup( GetOwner() ) ) {
        
        amount = player->GetRollResult().Total * 10;
    }
    else {
        
        amount = player->GetRollResult().Total * 4;
    }
    
    return amount;
}
