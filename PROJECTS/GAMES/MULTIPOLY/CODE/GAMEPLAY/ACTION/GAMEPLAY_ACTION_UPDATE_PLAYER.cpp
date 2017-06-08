//
//  GAMEPLAY_ACTION_UPDATE_PLAYER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 14/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_ACTION_UPDATE_PLAYER.h"
#include "GAMEPLAY_ACTION_END_TURN.h"
#include "MULTIPOLY_APPLICATION.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_UPDATE_PLAYER )
    XS_DEFINE_ClassMember(GAMEPLAY_PLAYER, &PlayerToUpdate )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_UPDATE_PLAYER, GAMEPLAY_ACTION_TYPE_Custom_18 )

GAMEPLAY_ACTION_UPDATE_PLAYER::GAMEPLAY_ACTION_UPDATE_PLAYER() :
    GAMEPLAY_ACTION(),
    PlayerToUpdate() {
    
}

GAMEPLAY_ACTION_UPDATE_PLAYER::~GAMEPLAY_ACTION_UPDATE_PLAYER() {
    
}

void GAMEPLAY_ACTION_UPDATE_PLAYER::Apply() {
    
    ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().UpdatePlayer( PlayerToUpdate );
}