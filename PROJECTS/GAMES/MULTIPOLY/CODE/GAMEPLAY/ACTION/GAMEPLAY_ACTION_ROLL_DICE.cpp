//
//  GAMEPLAY_ACTION_ROLL_DICE.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 11/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_ACTION_ROLL_DICE.h"
#include "MULTIPOLY_APPLICATION.h"
#include "GAMEPLAY_PLAYER.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_ROLL_DICE )
    XS_DEFINE_ClassMember(int , Result.FirstDice)
    XS_DEFINE_ClassMember(int , Result.SecondDice)
    XS_DEFINE_ClassMember(int , Result.Total)
    XS_DEFINE_ClassMember(int , Result.DoublesInRowCount)
    XS_DEFINE_ClassMember(bool , Result.IsDouble)
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_ROLL_DICE, GAMEPLAY_ACTION_TYPE_Custom_4 )

GAMEPLAY_ACTION_ROLL_DICE::GAMEPLAY_ACTION_ROLL_DICE() :
    GAMEPLAY_ACTION(),
    Result() {
    
}

GAMEPLAY_ACTION_ROLL_DICE::GAMEPLAY_ACTION_ROLL_DICE( GAMEPLAY_DICE_ROLL_RESULT & result ) :
    GAMEPLAY_ACTION(),
    Result( result ) {
    
}

GAMEPLAY_ACTION_ROLL_DICE::~GAMEPLAY_ACTION_ROLL_DICE() {
    
}

void GAMEPLAY_ACTION_ROLL_DICE::Apply() {
    
    auto state_machine = &((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().GetCurrentPlayer()->GetStateMachine();
    
    state_machine->DispatchEvent( GAMEPLAY_PLAYER::MULTIPLAYER_ROLL_DICE(Result));
}
