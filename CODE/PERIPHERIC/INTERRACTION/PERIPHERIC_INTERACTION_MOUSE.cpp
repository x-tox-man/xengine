//
//  PERIPHERIC_INTERACTION_MOUSE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "PERIPHERIC_INTERACTION_MOUSE.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( PERIPHERIC_INTERACTION_MOUSE )

CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( PERIPHERIC_INTERACTION_MOUSE )

PERIPHERIC_INTERACTION_MOUSE::PERIPHERIC_INTERACTION_MOUSE() :
    LeftButton( MOUSE_BUTTON_STATE_Up ),
    RightButton( MOUSE_BUTTON_STATE_Up ),
    ScreenCoordinates( CORE_MATH_VECTOR::Zero ),
    NormalizedDisplacement( CORE_MATH_VECTOR::Zero ),
    PreviousScreenCoordinates( CORE_MATH_VECTOR::Zero ),
    CenteredCoordinates( CORE_MATH_VECTOR::Zero ),
    ScrollCoordinates( CORE_MATH_VECTOR::Zero ) {
    
    ScreenCoordinates = CORE_MATH_VECTOR::Zero;
    PreviousScreenCoordinates = CORE_MATH_VECTOR::XAxis;
}

PERIPHERIC_INTERACTION_MOUSE::~PERIPHERIC_INTERACTION_MOUSE() {

}

void PERIPHERIC_INTERACTION_MOUSE::Initialize() {

    LeftButton = MOUSE_BUTTON_STATE_Up;
    RightButton = MOUSE_BUTTON_STATE_Up;
}

void PERIPHERIC_INTERACTION_MOUSE::Update() {
    
    LeftButton = LeftButton & ~MOUSE_BUTTON_STATE_Released;
    RightButton = RightButton & ~MOUSE_BUTTON_STATE_Released;
    
    PreviousScreenCoordinates = ScreenCoordinates;
    NormalizedDisplacement = CORE_MATH_VECTOR::Zero;
    ScrollCoordinates = CORE_MATH_VECTOR::Zero;
}
