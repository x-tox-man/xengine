//
//  APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 6/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_SERVER_PRESENTER.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "APPLICATION_LOADER_SCREEN.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"

APPLICATION_SERVER_PRESENTER::APPLICATION_SERVER_PRESENTER( NETWORK_SERVER * server ) :
    APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER(),
    Server( server ) {
    
}

APPLICATION_SERVER_PRESENTER::~APPLICATION_SERVER_PRESENTER() {
    
}

void APPLICATION_SERVER_PRESENTER::Configure() {
    
    auto * view = (APPLICATION_MULTIPLAYER_GAME_CONFIGURATION * ) GetView();
    
    NETWORK_PLAYER * current_player = &Server->GetCurrentPlayer();
    
    view->GetPlayersList().push_back(current_player);
    view->GetPlayersListAdapter()->OnCollectionChanged();
    
    CORE_HELPERS_CALLBACK_1<NETWORK_PLAYER *> callback ( &Wrapper1<APPLICATION_SERVER_PRESENTER, NETWORK_PLAYER *, &APPLICATION_SERVER_PRESENTER::OnClientConnected>, this);
    
    Server->SetOnPlayerConnectedCallback(callback);
}

void APPLICATION_SERVER_PRESENTER::StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !GameIsStarting && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        GameIsStarting = true;
        
        abort();
        /*APPLICATION_GAMEPLAY_COMMAND_LOAD_GAME
            command;
        
        
        Server->DispatchMessageToAllPlayers( APPLICATION_COMMAND_MANAGER::CreateNetworkCommand(command));*/
    }
}

void APPLICATION_SERVER_PRESENTER::SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
}

void APPLICATION_SERVER_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if (!GameIsStarting && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Server->Finalize();
        
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateBackAsync();
    }
}

void APPLICATION_SERVER_PRESENTER::OnClientConnected(NETWORK_PLAYER * player) {
    
    auto * view = (APPLICATION_MULTIPLAYER_GAME_CONFIGURATION * ) GetView();
    
    view->GetPlayersList().push_back(player);
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void APPLICATION_SERVER_PRESENTER::OnClientDisconnected(NETWORK_PLAYER * player) {
    
}

void APPLICATION_SERVER_PRESENTER::OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) {
    
}

void APPLICATION_SERVER_PRESENTER::OnGameStarting() {
    
    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_LOADER_SCREEN>( "LoadingScreen" );
}

void APPLICATION_SERVER_PRESENTER::OnStoppedGameStarting() {
    
}
