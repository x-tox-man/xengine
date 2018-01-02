//
//  UI_INGAME_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_INGAME_PRESENTER.h"
#include "GAMEPLAY_COMPONENT_PHYSICS.h"
#include "UI_INGAME.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"

UI_INGAME_PRESENTER::UI_INGAME_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {
    
}

void UI_INGAME_PRESENTER::Configure() {
    
    CurrentPlayer = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
}

void UI_INGAME_PRESENTER::Update( float time_step ) {
    
    auto cmp = (GAMEPLAY_COMPONENT_PHYSICS::PTR) CurrentPlayer->GetShip()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Physics );
    
    const CORE_MATH_VECTOR & v = cmp->GetVelocity();
    float speed = v.ComputeLength();
    ((UI_INGAME::PTR) GetView())->SetSpeed( speed );
    ((UI_INGAME::PTR) GetView())->SetEllapsedTime( R3D_APP_PTR->GetGame()->GetGameDuration() );
}

void UI_INGAME_PRESENTER::OnPauseButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
    }
}
