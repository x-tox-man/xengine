//
//  R3D_BROWSER_NETWORK_CLIENT_DELEGATE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_BROWSER_NETWORK_CLIENT_DELEGATE.h"
#include "NETWORK_BROWSER_PRESENTER.h"


R3D_BROWSER_NETWORK_CLIENT_DELEGATE::R3D_BROWSER_NETWORK_CLIENT_DELEGATE() :
    NETWORK_CLIENT_DELEGATE(),
    Presenter( NULL ) {
    
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnServerDiscovered( SERVICE_NETWORK_COMMAND * connexion ) {
    
    Presenter->SetServer( connexion );
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnServerAccepted( NETWORK_PLAYER * player ) {
    
    Presenter->OnserverConnected();
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnServerRefused() {
    
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnServerDisconnected() {
    
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnServerInfo( GAMEPLAY_ACTION_COMMAND_SERVER_INFO * info ) {
    
}

void R3D_BROWSER_NETWORK_CLIENT_DELEGATE::OnGameStarted() {
    
}
