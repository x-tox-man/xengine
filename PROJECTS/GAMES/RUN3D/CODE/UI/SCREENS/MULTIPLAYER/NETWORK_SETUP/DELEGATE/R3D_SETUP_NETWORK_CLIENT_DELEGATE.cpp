//
//  R3D_SETUP_NETWORK_CLIENT_DELEGATE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_SETUP_NETWORK_CLIENT_DELEGATE.h"
#include "NETWORK_SETUP_PRESENTER.h"
#include "GAME_PLAYER_MODEL.h"
#include "UI_INGAME.h"
#include "RUN3D_APPLICATION.h"

R3D_SETUP_NETWORK_CLIENT_DELEGATE::R3D_SETUP_NETWORK_CLIENT_DELEGATE() :
    NETWORK_CLIENT_DELEGATE(),
    Presenter( NULL ) {
    
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnServerDiscovered( SERVICE_NETWORK_COMMAND * connexion ) {
    
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnServerAccepted( NETWORK_PLAYER * player ) {
    
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnServerRefused() {
    
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnServerDisconnected() {
    
    Presenter->OnServerDisconnected();
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnServerInfo( GAMEPLAY_ACTION_COMMAND_SERVER_INFO * info ) {
    
    Presenter->OnServerInfo( info );
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnGameStarted() {
    
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnLoadGame( std::vector<NETWORK_PLAYER *> & players ) {
    
    Presenter->ClientLoadGame( players );
}

void R3D_SETUP_NETWORK_CLIENT_DELEGATE::OnPingUpdated( float ping ) {
    
}
