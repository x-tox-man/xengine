//
//  UI_GARAGE_PRESENTER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "UI_GARAGE_PRESENTER.h"
#include "RUN3D_APPLICATION.h"

UI_GARAGE_PRESENTER::UI_GARAGE_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ),
    PlayerShips() {
    
}

void UI_GARAGE_PRESENTER::Configure() {
    
    abort();
    
    //PlayerShips =
}

void UI_GARAGE_PRESENTER::OnClick( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
    }
}
