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

UI_MAIN_MENU_PRESENTER::UI_MAIN_MENU_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {

}

void UI_MAIN_MENU_PRESENTER::Configure() {
    
}

void UI_MAIN_MENU_PRESENTER::OnClick( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        R3D_APP_PTR->GetGame().Restart();
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< UI_GARAGE >( "Garage" );
    }
}

void UI_MAIN_MENU_PRESENTER::OnNetworkButtonPressed(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< NETWORK_BROWSER_PAGE >( "NetworkBrowser" );
    }
}
