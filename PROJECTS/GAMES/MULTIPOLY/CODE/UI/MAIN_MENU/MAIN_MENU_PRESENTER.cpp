//
//  MAIN_MENU_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "MAIN_MENU_PRESENTER.h"
#include "GAME_HUD_PAGE.h"
#include "MULTIPLAYER_GAME_HUD_PAGE.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "OPTIONS_PAGE.h"
#include "MULTIPOLY_APPLICATION.h"

MAIN_MENU_PRESENTER::MAIN_MENU_PRESENTER() :
    GRAPHIC_UI_PRESENTER(),
    NavigationIsRequested( false ) {
    
}

MAIN_MENU_PRESENTER::~MAIN_MENU_PRESENTER() {
    
}

void MAIN_MENU_PRESENTER::Configure() {
    
    NavigationIsRequested = false;
}

void MAIN_MENU_PRESENTER::StartSingleGameButtonClicked( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        NavigationIsRequested = true;
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<GAME_HUD_PAGE>( "igame_hud" );
        
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().Start();
    }
}

void MAIN_MENU_PRESENTER::StartBrowsingMultiplayerButtonClicked( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        NavigationIsRequested = true;
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<MULTIPLAYER_GAME_HUD_PAGE>( "multiplayer_igame_hud" );
    }
}

void MAIN_MENU_PRESENTER::NavigateToOptions() {

    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<OPTIONS_PAGE>( "options_page" );
}
