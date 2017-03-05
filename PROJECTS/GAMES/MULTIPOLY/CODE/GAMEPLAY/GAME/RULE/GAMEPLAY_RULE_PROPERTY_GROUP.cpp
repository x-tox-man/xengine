//
//  GAMEPLAY_RULE_PROPERTY_GROUP.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 4/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PROPERTY_GROUP.h"
#include "GAMEPLAY_RULE_PROPERTY.h"
#include "GAMEPLAY_PLAYER.h"

GAMEPLAY_RULE_PROPERTY_GROUP::GAMEPLAY_RULE_PROPERTY_GROUP() :
    GAMEPLAY_RULE(),
    Properties() {
    
}

GAMEPLAY_RULE_PROPERTY_GROUP::~GAMEPLAY_RULE_PROPERTY_GROUP() {
    
}

void GAMEPLAY_RULE_PROPERTY_GROUP::AddProperty( GAMEPLAY_RULE_PROPERTY * property ) {
    
    Properties.push_back( property );
}

/**
 * Calculate if a player owns all houses (in order to allow to buy a house or to double the rent
 *
 */
bool GAMEPLAY_RULE_PROPERTY_GROUP::DoesPlayerOwnAllPropertiesInGroup( GAMEPLAY_PLAYER * player ) {
    
    std::vector<GAMEPLAY_RULE_PROPERTY *>::iterator it = Properties.begin();
    
    while (it != Properties.end() ) {
        
        if ( (*it)->GetOwner() == NULL || (*it)->GetOwner() != player || (*it)->IsInMortgage() ) {
            
            return false;
        }
        
        it++;
    }
    
    return true;
}

bool GAMEPLAY_RULE_PROPERTY_GROUP::HouseOnGroupAreEven(int size_to_ask ) {
    
    bool even = true;
    std::vector<GAMEPLAY_RULE_PROPERTY *>::iterator it = Properties.begin();
    
    while (it != Properties.end() ) {
        
        if ( (*it)->GetHouseTable().size() < size_to_ask - 1) {
            
            return false;
        }
        
        it++;
    }
    
    return even;
}
