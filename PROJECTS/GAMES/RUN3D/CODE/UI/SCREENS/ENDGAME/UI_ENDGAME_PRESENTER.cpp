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

UI_ENDGAME_PRESENTER::UI_ENDGAME_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {
    
}

void UI_ENDGAME_PRESENTER::Configure() {
    
}

void UI_ENDGAME_PRESENTER::OnProceedButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< UI_MAIN_MENU >( "UI_MAIN_MENU" );
    }
}
