//
//  GAMEPLAY_RULE_PARK.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_PARK.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "MULTIPOLY_APPLICATION.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_RULE_PARK )
    XS_DEFINE_ClassMember(int , ParkAmount)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_RULE_PARK, GAMEPLAY_ACTION_TYPE_Custom_10 )

GAMEPLAY_RULE_PARK::GAMEPLAY_RULE_PARK() :
    GAMEPLAY_RULE(),
    GAMEPLAY_ACTION(),
    ParkAmount( 0 ),
    BillsRenderers() {
    
}

GAMEPLAY_RULE_PARK::~GAMEPLAY_RULE_PARK() {
    
}

void GAMEPLAY_RULE_PARK::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}

void GAMEPLAY_RULE_PARK::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
}

void GAMEPLAY_RULE_PARK::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    player->AddMoney(ParkAmount);
    ParkAmount = 0;
    
    std::vector<GAMEPLAY_COMPONENT_RENDER *>::iterator it = BillsRenderers.begin();
    
    auto render_system = ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().GetScene().GetRenderableSystemTable()[0];
    
    while (it != BillsRenderers.end() ) {
        
        it++;
    }
}

void GAMEPLAY_RULE_PARK::AddAmount( int amount ) {
    
    AddBill( amount, NULL );
}

void GAMEPLAY_RULE_PARK::AddBill( int amount, GAMEPLAY_COMPONENT_RENDER * template_bill ) {
    
    ParkAmount += amount;
}

void GAMEPLAY_RULE_PARK::Apply() {
    
}
