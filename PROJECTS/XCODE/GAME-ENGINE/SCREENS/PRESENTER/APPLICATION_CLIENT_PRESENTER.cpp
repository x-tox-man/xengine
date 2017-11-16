//
//  APPLICATION_CLIENT_PRESENTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_CLIENT_PRESENTER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "APPLICATION_LOADER_SCREEN.h"
#include "GAMEPLAY_ACTION_COMMAND_START_GAME.h"

APPLICATION_CLIENT_PRESENTER::APPLICATION_CLIENT_PRESENTER( NETWORK_CLIENT * client ) :
    APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER(),
    Client( client ) {
    
}

APPLICATION_CLIENT_PRESENTER::~APPLICATION_CLIENT_PRESENTER() {
    
}

void APPLICATION_CLIENT_PRESENTER::Configure() {
    
    auto * view = (APPLICATION_MULTIPLAYER_GAME_CONFIGURATION * ) GetView();
    
    NETWORK_PLAYER * current_player = &Client->GetCurrentPlayer();
    
    view->GetPlayersList().push_back(current_player);
    
    abort();
    /*GAMEPLAY_ACTION_COMMAND_START_GAME::GameStartingCallback.Connect(Wrapper<APPLICATION_CLIENT_PRESENTER, &APPLICATION_CLIENT_PRESENTER::OnGameStarting>, this);*/
}

void APPLICATION_CLIENT_PRESENTER::StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
}

void APPLICATION_CLIENT_PRESENTER::SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
}

void APPLICATION_CLIENT_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    
    
    if (event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        Client->Disconnect();
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateBackAsync();
    }
}

void APPLICATION_CLIENT_PRESENTER::OnClientConnected(NETWORK_PLAYER * player) {
    
    auto * view = (APPLICATION_MULTIPLAYER_GAME_CONFIGURATION * ) GetView();
    
    view->GetPlayersList().push_back(player);
}

void APPLICATION_CLIENT_PRESENTER::OnClientDisconnected(NETWORK_PLAYER * player) {
    
}

void APPLICATION_CLIENT_PRESENTER::OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) {
    
}

void APPLICATION_CLIENT_PRESENTER::OnGameStarting() {
    
    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_LOADER_SCREEN>( "LoadingScreen" );
}

void APPLICATION_CLIENT_PRESENTER::OnStoppedGameStarting() {
    
}
