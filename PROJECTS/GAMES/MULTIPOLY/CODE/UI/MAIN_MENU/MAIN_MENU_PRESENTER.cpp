//
//  MAIN_MENU_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "MAIN_MENU_PRESENTER.h"
#include "GAME_HUD_PAGE.h"
#include "NETWORK_BROWSER_PAGE.h"
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
        
        auto app = ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance());
        
        std::vector< GAME_PLAYER_MODEL > players;
        GAME_PLAYER_MODEL mod, mod2, mod3;
        mod.Name = std::string("Christophe");
        mod.Color = CORE_COLOR_Red;
        mod.IsHuman = true;
        mod.IsMultiplayer = false;
        
        mod2.Name = std::string("Charlotte");
        mod2.Color = CORE_COLOR_Blue;
        mod2.IsHuman = false;
        mod2.IsMultiplayer = false;
        
        mod3.Name = std::string("Kp");
        mod3.Color = CORE_COLOR_Green;
        mod3.IsHuman = false;
        mod3.IsMultiplayer = false;
        
        players.push_back(mod);
        players.push_back(mod2);
        players.push_back(mod3);
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<GAME_HUD_PAGE>( "igame_hud" );
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
            app->GetGame().SetPlayers( players );
            app->GetGame().Start();
        CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    }
}

void MAIN_MENU_PRESENTER::StartBrowsingMultiplayerButtonClicked( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        NavigationIsRequested = true;
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<NETWORK_BROWSER_PAGE>( "multiplayer_browser" );
    }
}

void MAIN_MENU_PRESENTER::NavigateToOptions() {

    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<OPTIONS_PAGE>( "options_page" );
}
