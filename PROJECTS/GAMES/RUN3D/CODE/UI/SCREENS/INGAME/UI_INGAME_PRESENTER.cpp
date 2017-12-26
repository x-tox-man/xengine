//
//  UI_INGAME_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 17/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_INGAME_PRESENTER.h"

UI_INGAME_PRESENTER::UI_INGAME_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {
    
}

void UI_INGAME_PRESENTER::Configure() {
    
}

void UI_INGAME_PRESENTER::OnPauseButtonPressed( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
    }
}
