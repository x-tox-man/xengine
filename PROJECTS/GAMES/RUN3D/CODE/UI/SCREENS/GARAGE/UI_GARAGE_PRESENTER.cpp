//
//  UI_GARAGE_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_GARAGE_PRESENTER.h"
#include "RUN3D_APPLICATION.h"
#include "UI_GARAGE.h"
#include "R3D_GARAGE_SHIPS_ADAPTER.h"
#include "AUDIO_SYSTEM.h"
#include "R3D_AUDIO_MUSIC_MANAGER.h"

UI_GARAGE_PRESENTER::UI_GARAGE_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ),
    PlayerShips(),
    Player( NULL ),
    Adapter( NULL ) {
    
}

void UI_GARAGE_PRESENTER::Configure() {
    
    Player = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
    PlayerShips = Player->GetAllShipsOwned();
    
    Adapter->SetCellDimension( CORE_MATH_VECTOR( 128.0f, 128.0f ) );
    Adapter->SetPlayerShips( &PlayerShips );
}

void UI_GARAGE_PRESENTER::OnClick( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
    }
}
