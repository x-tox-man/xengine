//
//  INGAM_OPTIONS_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "INGAME_OPTIONS_PRESENTER.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "MULTIPOLY_APPLICATION.h"

INGAME_OPTIONS_PRESENTER::INGAME_OPTIONS_PRESENTER() :
    GRAPHIC_UI_PRESENTER(),
    NavigationIsRequested( false ) {
    
}

INGAME_OPTIONS_PRESENTER::~INGAME_OPTIONS_PRESENTER() {
    
}

void INGAME_OPTIONS_PRESENTER::Configure() {
    
    NavigationIsRequested = false;
}

void INGAME_OPTIONS_PRESENTER::OnBackButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        NavigationIsRequested = true;
        
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().Pause( false );
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateBackAsync();
    }
}
