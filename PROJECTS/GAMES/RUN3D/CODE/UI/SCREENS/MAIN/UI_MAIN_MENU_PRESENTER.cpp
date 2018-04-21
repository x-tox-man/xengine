//
//  UI_MAIN_MENU_PRESENTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 4/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_MAIN_MENU_PRESENTER.h"
#include "RUN3D_APPLICATION.h"
#include "UI_GARAGE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "NETWORK_BROWSER_PAGE.h"
#include "UI_INGAME.h"
#include "R3D_UI_FRAME_ANIMATION.h"
#include "SELECT_LEVEL.h"
#include "AUDIO_SYSTEM.h"
#include "R3D_AUDIO_MUSIC_MANAGER.h"

UI_MAIN_MENU_PRESENTER::UI_MAIN_MENU_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {

}

void UI_MAIN_MENU_PRESENTER::Configure() {
    
}

void UI_MAIN_MENU_PRESENTER::OnClickStartGame( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
        
        OpenAnimated< SELECT_LEVEL >( "SELECT_LEVEL" );
    }
}

void UI_MAIN_MENU_PRESENTER::OnClickToGarage( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
        
        OpenAnimated< UI_GARAGE >( "UI_GARAGE" );
    }
}

void UI_MAIN_MENU_PRESENTER::OnNetworkButtonPressed(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
        
        OpenAnimated< NETWORK_BROWSER_PAGE >( "NETWORK_BROWSER_PAGE" );
    }
}
