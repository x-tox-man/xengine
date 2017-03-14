//
//  GAMEPLAY_RULE_FIELD.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PROPERTY.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"
#include "MULTIPOLY_APPLICATION.h"
#include "GAMEPLAY_GAME_HOUSE.h"
#include "GLOBAL_RESOURCES.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "GAMEPLAY_ACTION_BUY_PROPERTY.h"
#include "GAMEPLAY_ACTION_BUY_HOUSE.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_PROPERTY )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_PROPERTY, GAMEPLAY_ACTION_TYPE_Custom_15 )

GAMEPLAY_RULE_PROPERTY::GAMEPLAY_RULE_PROPERTY() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    PropertyGroup( NULL ),
    Owner( NULL ),
    BuyPrice( 0 ),
    HousePrice( 0 ),
    RentPrice( 0 ),
    MortgagePrice( 0 ),
    ItIsInMortgage( false ),
    HouseTable() {
    
}

GAMEPLAY_RULE_PROPERTY::GAMEPLAY_RULE_PROPERTY( int front_price, int rent_price, int house_price, int mortgage_price, GAMEPLAY_RULE_PROPERTY_GROUP * group ) :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    PropertyGroup( group ),
    Owner( NULL ),
    BuyPrice( front_price ),
    HousePrice( house_price ),
    RentPrice( rent_price ),
    MortgagePrice( mortgage_price ),
    ItIsInMortgage( false ),
    HouseTable() {
    
    if ( PropertyGroup ) {
        
        PropertyGroup->AddProperty( this );
    }
}

GAMEPLAY_RULE_PROPERTY::~GAMEPLAY_RULE_PROPERTY() {
    
}

void GAMEPLAY_RULE_PROPERTY::OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    if ( Owner && Owner == player ) {
        //Actions are enabled
    }
    else {
        
        //Actions are disabled except from buying
    }
}

void GAMEPLAY_RULE_PROPERTY::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PROPERTY::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_PROPERTY::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    Apply( cell, player );
}

bool GAMEPLAY_RULE_PROPERTY::Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {

    if ( Owner && Owner != player ) {
        
        if ( ItIsInMortgage ) {
            
            return 0;
        }
        
        int amount = CalculateAmount( player );
        
        int res = player->AttemptPay( amount );
        
        if ( res == amount ) {
            
            Owner->AddMoney( amount );
            return false;
        }
        else {
            abort();
            //TODO: médiation de dettes
            return false;
        }
    }
    else if ( Owner == player && !player->IsMultiplayer() ) {
        
        if ( CanBuyHouse( player ) ) {
            
            ProposeBuyHouse( cell, player );
        }
    }
    else {
        if ( !player->IsMultiplayer() ) {
            
            ProposeBuy( cell, player );
            //TODO : enchères
        }
    }
    
    return false;
}

void GAMEPLAY_RULE_PROPERTY::OnPicked(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    //TODO : Show property detail
    
    if ( Owner == player ) {
        
        if ( CanBuyHouse( player ) ) {
            
            ProposeBuyHouse( cell, player );
        }
    }
}

void GAMEPLAY_RULE_PROPERTY::OnDismiss(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().GetUIGameHudPresenter()->HidePropertyAndHouse();
}

int GAMEPLAY_RULE_PROPERTY::CalculateAmount( GAMEPLAY_PLAYER * player ) {

    int amount = 0;
    bool complete = PropertyGroup->DoesPlayerOwnAllPropertiesInGroup( Owner );
    
    if ( HouseTable.size() > 0 ) {
        
    }
    else if ( complete ) {
        
        amount = RentPrice * 2;
    }
    else {
        
        amount = RentPrice;
    }
    
    return amount;
}

void GAMEPLAY_RULE_PROPERTY::ProposeBuy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player) {
    
    if ( player->GetMoney() >= BuyPrice ) {
        
        if ( player->IsHuman() ) {
            
            ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().ProposeBuyProperty( cell, player );
        }
        else {
            
            Buy( cell, player );
        }
    }
    else {
        //enchères
        abort();
    }
}

void GAMEPLAY_RULE_PROPERTY::ProposeBuyHouse( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player) {
    
    if ( player->GetMoney() >= BuyPrice ) {
        
        if ( player->IsHuman() ) {
            
            ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().ProposeBuyHouse( cell, player );
        }
        else {
            
            BuyHouse(&(((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame()).GetScene(), cell, player, (((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame()).GetNextHouse() );
        }
    }
}

void GAMEPLAY_RULE_PROPERTY::Buy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    if ( player->GetMoney() >= BuyPrice ) {
        
        player->RemoveMoney( BuyPrice );
        
        TransferTo( player );
        
        auto render = (GAMEPLAY_COMPONENT_RENDER*) cell->GetComponent(GAMEPLAY_COMPONENT_TYPE_Render);
        render->SetColor(player->GetPlayerColor() );
        
        GAMEPLAY_ACTION_BUY_PROPERTY
            action;
        auto command = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand< GAMEPLAY_ACTION_BUY_PROPERTY >( action );
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetNetworkManager().SendCommand( command );
        
        if ( CanBuyHouse( player ) ) {
            
            ProposeBuyHouse( cell, player );
        }
    }
}

void GAMEPLAY_RULE_PROPERTY::TransferTo( GAMEPLAY_PLAYER * player ) {
    
    Owner = player;
}

bool GAMEPLAY_RULE_PROPERTY::CanBuyHouse( GAMEPLAY_PLAYER * player ) {
    
    if ( player->GetMoney() < HousePrice ) {
        
        return false;
    }
    
    if ( PropertyGroup->DoesPlayerOwnAllPropertiesInGroup( player ) && HouseTable.size() < 5 && PropertyGroup->HouseOnGroupAreEven((int)HouseTable.size() + 1 ) ) {
        
        return true;
    }
    
    return false;
}

void GAMEPLAY_RULE_PROPERTY::BuyHouse( GAMEPLAY_SCENE * scene, GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player, GAMEPLAY_GAME_HOUSE * house ) {
    
    if( CanBuyHouse(player) ) {
        
        player->RemoveMoney( HousePrice );
        
        auto pos = ( GAMEPLAY_COMPONENT_POSITION * ) cell->GetComponent(GAMEPLAY_COMPONENT_TYPE_Position);
        
        house->SetColor(player->GetPlayerColor());
        house->SetupAnimation(pos->GetPosition(), CORE_MATH_QUATERNION() );
        HouseTable.push_back( house );
        
        GAMEPLAY_ACTION_BUY_HOUSE
            action;
        
        auto command = GAMEPLAY_ACTION_SYSTEM::CreateNetworkCommand< GAMEPLAY_ACTION_BUY_HOUSE >( action );
        ((MULTIPOLY_APPLICATION*)&CORE_APPLICATION::GetApplicationInstance())->GetNetworkManager().SendCommand( command );
    }
    else {
        
        //Hide button
    }
}

void GAMEPLAY_RULE_PROPERTY::Apply() {
    
}
