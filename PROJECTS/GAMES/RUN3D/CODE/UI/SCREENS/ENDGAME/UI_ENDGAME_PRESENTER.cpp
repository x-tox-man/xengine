//
//  UI_ENDGAME_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 28/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_ENDGAME_PRESENTER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "UI_MAIN_MENU.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_BASE_PRESENTER.h"

UI_ENDGAME_PRESENTER::UI_ENDGAME_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {
    
}

void UI_ENDGAME_PRESENTER::Configure() {
    
}

void UI_ENDGAME_PRESENTER::OnProceedButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
        
        OpenAnimated< UI_MAIN_MENU >( "UI_MAIN_MENU" );
    }
}

void UI_ENDGAME_PRESENTER::OnRetryButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Vibrate( 0.1f );
        
        AUDIO_SYSTEM::GetInstance().PlaySound( R3D_AUDIO_MUSIC_MANAGER::ATone );
        
        R3D_APP_PTR->GetGame()->Restart();
        
        BackAnimated();
    }
}
