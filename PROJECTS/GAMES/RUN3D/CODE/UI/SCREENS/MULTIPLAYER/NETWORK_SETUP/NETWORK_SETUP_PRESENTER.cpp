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
#include "UI_INGAME.h"
#include "GAME_PLAYER_MODEL.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE.h"

NETWORK_SETUP_PRESENTER::NETWORK_SETUP_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ) {
    
}

NETWORK_SETUP_PRESENTER::~NETWORK_SETUP_PRESENTER() {
    
}

void NETWORK_SETUP_PRESENTER::Update( const float step ) {
    
}

void NETWORK_SETUP_PRESENTER::Configure() {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        R3D_APP_PTR->GetNetworkManager().GetServer()->SetDelegate( &ServerDelegate );
        ServerDelegate.Presenter = this;
        
        NETWORK_PLAYER * current_player = &R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer();
        
        view->GetPlayersList().push_back(current_player);
    }
    else {
        
        R3D_APP_PTR->GetNetworkManager().GetClient()->SetDelegate( &ClientDelegate );
        ClientDelegate.Presenter = this;
        
        CORE_HELPERS_CALLBACK_2< std::vector< NETWORK_PLAYER* > &, int > callback( &Wrapper2< NETWORK_SETUP_PRESENTER, std::vector< NETWORK_PLAYER * > &, int, &NETWORK_SETUP_PRESENTER::ClientGameStarted >, this);
        GAMEPLAY_ACTION_COMMAND_START_GAME::SetGameStartingCallback( callback );
        
        NETWORK_PLAYER * current_player = &R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer();
        
        view->GetPlayersList().push_back(current_player);
    }
    
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void NETWORK_SETUP_PRESENTER::ClientGameStarted( std::vector<NETWORK_PLAYER *> & players, int seed) {
    
    std::vector< GAME_PLAYER_MODEL >
        players_model;
    
    players_model.resize( players.size() );
    
    for (int i = 0; i < players.size(); i++) {
        
        players_model[i].NetworkPlayer = players[ i ];
        
        if ( players_model[i].NetworkPlayer->GetUniqueId() == R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId() ) {
            
            players_model[i].GamePlayer = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
        }
        else {
            players_model[i].GamePlayer = new R3D_PLAYER();
            players_model[i].GamePlayer->Initialize();
        }
        
        players_model[i].Identifier = players[i]->GetUniqueId();
    }

    R3D_APP_PTR->GetGame()->SelectLevel( ( *R3D_APP_PTR->GetGame()->GetLevelManager().GetAllLevels().begin() ) );
    R3D_APP_PTR->GetGame()->SetPlayers( players_model );
    R3D_APP_PTR->GetGame()->Restart();
    
    OpenAnimated< UI_INGAME >( "UI_INGAME" );
}

void NETWORK_SETUP_PRESENTER::ServerGameStarted() {
    
    R3D_APP_PTR->GetGame()->Restart();

    OpenAnimated< UI_INGAME >( "UI_INGAME" );
}

void NETWORK_SETUP_PRESENTER::StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( R3D_APP_PTR->GetNetworkManager().GetServer() && event == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        int
            i = 0;
        auto view = (NETWORK_SETUP_PAGE * ) GetView();
        std::vector< NETWORK_PLAYER * >::iterator
            it = view->GetPlayersList().begin();
        std::vector< GAME_PLAYER_MODEL >
            players_model;
        
        players_model.resize( view->GetPlayersList().size() );
        
        while (it != view->GetPlayersList().end() ) {
            if ( !(*it)->Ready() ) {
                
                return;
            }
            else {
                players_model[i].NetworkPlayer = *it;
                
                if ( players_model[i].NetworkPlayer->GetUniqueId() == R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId() ) {
                    
                    players_model[i].GamePlayer = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer();
                }
                else {
                    players_model[i].GamePlayer = new R3D_PLAYER();
                    players_model[i].GamePlayer->Initialize();
                }
                
                players_model[i].Identifier = players_model[i].NetworkPlayer->GetUniqueId();
                
                i++;
            }
            
            it++;
        }
        
        CORE_HELPERS_CALLBACK callback( &Wrapper<NETWORK_SETUP_PRESENTER, &NETWORK_SETUP_PRESENTER::ServerGameStarted>, this );
        
        R3D_APP_PTR->GetGame()->SelectLevel( (*R3D_APP_PTR->GetGame()->GetLevelManager().GetAllLevels().begin()) );
        R3D_APP_PTR->GetNetworkManager().GetServer()->SetGameStartedCallback( callback );
        R3D_APP_PTR->GetGame()->SetPlayers( players_model );
        R3D_APP_PTR->GetNetworkManager().GetServer()->StartCountDown();
    }
}

void NETWORK_SETUP_PRESENTER::SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
}

void NETWORK_SETUP_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
            
            R3D_APP_PTR->GetNetworkManager().GetServer()->SetAcceptsConnexions( false );
            R3D_APP_PTR->GetNetworkManager().GetServer()->DisconnectAll();
            R3D_APP_PTR->GetNetworkManager().FinalizeServer();
        }
        else {
            R3D_APP_PTR->GetNetworkManager().GetClient()->SendDisconnectCommand();
        }
        
        BackAnimated();
    }
}

void NETWORK_SETUP_PRESENTER::OnClientConnected(NETWORK_PLAYER * player) {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    
    view->GetPlayersList().push_back(player);
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void NETWORK_SETUP_PRESENTER::OnClientDisconnected(NETWORK_PLAYER * player) {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    std::vector< NETWORK_PLAYER * >::iterator it = view->GetPlayersList().begin();
    
    while (it != view->GetPlayersList().end() ) {
        if ( player->GetUniqueId() == (*it)->GetUniqueId() ) {
            
            view->GetPlayersList().erase( it );
            break;
        }
        
        it++;
    }
    view->GetPlayersListAdapter()->SetCollection( &view->GetPlayersList() );
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void NETWORK_SETUP_PRESENTER::OnServerDisconnected() {
    
    BackAnimated();
}

void NETWORK_SETUP_PRESENTER::UpdateClientReady( NETWORK_PLAYER * player, bool ready ) {
    
    auto * view = (NETWORK_SETUP_PAGE * ) GetView();
    std::vector< NETWORK_PLAYER * >::iterator it = view->GetPlayersList().begin();
    
    while (it != view->GetPlayersList().end() ) {
        if ( player->GetUniqueId() == (*it)->GetUniqueId() ) {
            
            (*it)->SetIsReady( ready );
            break;
        }
        
        it++;
    }
    view->GetPlayersListAdapter()->OnCollectionChanged();
}

void NETWORK_SETUP_PRESENTER::OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) {
    
}

void NETWORK_SETUP_PRESENTER::OnStoppedGameStarting() {
    
}

void NETWORK_SETUP_PRESENTER::OnServerInfo( GAMEPLAY_ACTION_COMMAND_SERVER_INFO * info ) {
    
    auto view = (NETWORK_SETUP_PAGE * ) GetView();
    std::vector< NETWORK_PLAYER * >::iterator
        it = info->Players.begin();
    
    view->GetPlayersList().clear();
    
    while (it != info->Players.end() ) {
        
        view->GetPlayersList().push_back( *it );
        
        it++;
    }
    
    view->GetPlayersListAdapter()->SetCollection( &view->GetPlayersList() );
    view->GetPlayersListAdapter()->OnCollectionChanged();
}
