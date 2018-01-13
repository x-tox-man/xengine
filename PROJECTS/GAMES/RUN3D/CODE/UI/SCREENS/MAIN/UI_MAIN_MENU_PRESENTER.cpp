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

UI_MAIN_MENU_PRESENTER::UI_MAIN_MENU_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {

}

void UI_MAIN_MENU_PRESENTER::Configure() {
    
}

void UI_MAIN_MENU_PRESENTER::OnClickStartGame( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        std::vector< GAME_PLAYER_MODEL >
            players_model;
        
        players_model.resize( 2 );
        players_model[ 0 ].GamePlayer = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
        players_model[ 0 ].Identifier = R3D_APP_PTR->GetGame()->GetThisPlayerIndex();
        players_model[ 1 ].GamePlayer = new R3D_PLAYER();
        players_model[ 1 ].Identifier = CORE_HELPERS_UNIQUE_IDENTIFIER( "BOT0" );
        
        R3D_APP_PTR->GetGame()->SelectLevel( (*R3D_APP_PTR->GetGame()->GetLevelManager().GetAllLevels().begin()) );
        R3D_APP_PTR->GetGame()->SetPlayers( players_model );
        R3D_APP_PTR->GetGame()->Restart();
        
        OpenAnimated< UI_INGAME >( "UI_INGAME" );
    }
}

void UI_MAIN_MENU_PRESENTER::OnClickToGarage( GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        OpenAnimated< UI_GARAGE >( "UI_GARAGE" );
    }
}

void UI_MAIN_MENU_PRESENTER::OnNetworkButtonPressed(GRAPHIC_UI_ELEMENT * element, GRAPHIC_UI_ELEMENT_EVENT state ) {
    
    if ( state == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        OpenAnimated< NETWORK_BROWSER_PAGE >( "NETWORK_BROWSER_PAGE" );
    }
}
