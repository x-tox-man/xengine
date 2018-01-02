//
//  R3D_BASE_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_BASE_PRESENTER.h"
#include "GRAPHIC_UI_SYSTEM.h"

R3D_BASE_PRESENTER::R3D_BASE_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    GRAPHIC_UI_PRESENTER() {
    
    Initialize( view );
}

void R3D_BASE_PRESENTER::Back( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateBackAsync();
    }
}
