//
//  NETWORK_SETUP_PRESENTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_SETUP_PRESENTER.h"
#include "NETWORK_SETUP_PAGE.h"
#include "GAMEPLAY_ACTION_COMMAND_START_GAME.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "RUN3D_APPLICATION.h"
#include "GRAPHIC_UI_SYSTEM.h"

NETWORK_SETUP_PRESENTER::NETWORK_SETUP_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ),
    NavigationIsRequested( false ),
    GameIsStarting( false ),
    Server( NULL ),
    Client( NULL ),
    CountDown( 0.0f ) {
    
}

NETWORK_SETUP_PRESENTER::~NETWORK_SETUP_PRESENTER() {
    
}

void NETWORK_SETUP_PRESENTER::Update( const float step ) {
    
}

void NETWORK_SETUP_PRESENTER::Configure() {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    
    Server = R3D_APP_PTR->GetNetworkManager().GetServer();
    Client = R3D_APP_PTR->GetNetworkManager().GetClient();
    
    NETWORK_PLAYER * current_player = &Server->GetCurrentPlayer();
    
    view->GetPlayersList().push_back(current_player);
    view->GetPlayersListAdapter()->OnCollectionChanged();
    
    CORE_HELPERS_CALLBACK_1<NETWORK_PLAYER *> callback ( &Wrapper1<NETWORK_SETUP_PRESENTER, NETWORK_PLAYER *, &NETWORK_SETUP_PRESENTER::OnClientConnected>, this);
    
    if ( Server ) {
        
        Server->SetOnPlayerConnectedCallback( callback );
    }
    else {
        CORE_HELPERS_CALLBACK_2< std::vector< NETWORK_PLAYER* > &, int > callback( &Wrapper2< NETWORK_SETUP_PRESENTER, std::vector< NETWORK_PLAYER * > &, int, &NETWORK_SETUP_PRESENTER::GameStarted >, this);
        GAMEPLAY_ACTION_COMMAND_START_GAME::SetGameStartingCallback( callback );
    }
}

void NETWORK_SETUP_PRESENTER::GameStarted( std::vector<NETWORK_PLAYER *> & players, int seed) {
    
    abort();
    
    /*std::vector< GAME_PLAYER_MODEL >
        players_model;

    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<MULTIPLAYER_GAME_HUD_PAGE>("MULTIPLAYER_GAME_HUD_PAGE");
    
    players_model.resize( players.size() );
    
    for (int i = 0; i < players.size(); i++) {
        
        players_model[i].IsHuman = true;
        players_model[i].Color = CORE_COLOR_White;
        players_model[i].Name = players[i]->GetName();
        players_model[i].IsMultiplayer = !( players[i]->GetUniqueId() == R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId() );
    }
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().SetPlayers( players_model );
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetGame().Start( seed );
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()*/
}

void NETWORK_SETUP_PRESENTER::StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( Server && !GameIsStarting && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        GameIsStarting = true;
        
        Server->StartCountDown();
        
        abort();
        
        //GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync<MULTIPLAYER_GAME_HUD_PAGE>("MULTIPLAYER_GAME_HUD_PAGE");
    }
}

void NETWORK_SETUP_PRESENTER::SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
}

void NETWORK_SETUP_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( !NavigationIsRequested && !GameIsStarting && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        NavigationIsRequested = true;
        
        if ( Server ) {
            
            R3D_APP_PTR->GetNetworkManager().FinalizeServer();
        }
        
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateBackAsync();
    }
}

void NETWORK_SETUP_PRESENTER::OnClientConnected(NETWORK_PLAYER * player) {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    
    view->GetPlayersList().push_back(player);
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void NETWORK_SETUP_PRESENTER::OnClientDisconnected(NETWORK_PLAYER * player) {
    
}

void NETWORK_SETUP_PRESENTER::OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) {
    
}

void NETWORK_SETUP_PRESENTER::OnGameStarting() {
    
    if ( !NavigationIsRequested && !GameIsStarting ) {
        
        NavigationIsRequested = true;
        //GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< GAME_LOADER_SCREEN >( "LoadingScreen" );
    }
}

void NETWORK_SETUP_PRESENTER::OnStoppedGameStarting() {
    
}
