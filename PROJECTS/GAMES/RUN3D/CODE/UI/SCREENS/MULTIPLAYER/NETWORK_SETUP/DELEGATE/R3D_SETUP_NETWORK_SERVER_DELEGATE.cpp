//
//  R3D_BROWSER_NETWORK_SERVER_DELEGATE.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_SETUP_NETWORK_SERVER_DELEGATE.h"
#include "NETWORK_SETUP_PRESENTER.h"
#include "RUN3D_APPLICATION.h"
#include "CORE_DATA_LOADER.h"
#include "R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE.h"

R3D_SETUP_NETWORK_SERVER_DELEGATE::R3D_SETUP_NETWORK_SERVER_DELEGATE() :
    NETWORK_SERVER_DELEGATE(),
    Presenter( NULL ) {
    
}

void R3D_SETUP_NETWORK_SERVER_DELEGATE::OnClientConnected( SERVICE_NETWORK_CONNECTION * connexion ) {
    
}

void R3D_SETUP_NETWORK_SERVER_DELEGATE::OnClientConnected( NETWORK_PLAYER * player ) {
    
    Presenter->OnClientConnected( player );
}

void R3D_SETUP_NETWORK_SERVER_DELEGATE::OnClientDisconnected( NETWORK_PLAYER * player ) {
    
    Presenter->OnClientDisconnected( player );
}

void R3D_SETUP_NETWORK_SERVER_DELEGATE::FillGameInfo( NETWORK_SERVER_INFO & info ) {
    
    CORE_DATA_BUFFER
        & info_buffer = info.GetSpecificGameInfo();
    CORE_DATA_STREAM
        st;
    
    info.Adress = (char*) malloc( 2 );
    info.Name = (char*) malloc( 6 );
    info.GameTitle = (char*) malloc( 6 );
    info.AppVersion = R3D_APP_VERSION;
    
    strcpy( info.Adress, "0\0" );
    strcpy( info.Name, "Test0\0" );
    strcpy( info.GameTitle, "Test1\0" );
    
    st.Open();
    
    XS_CLASS_SERIALIZER< NETWORK_REMOTE_GAME_INFO, CORE_DATA_STREAM >::template Serialize< std::true_type >( "object", ((R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::PTR) R3D_APP_PTR->GetGame()->GetDelegate())->GetInfo(), st );
    
    st.Close();
    
    info_buffer.InitializeWithMemory(st.GetSize(), 1, st.GetMemoryBuffer() );
}

void R3D_SETUP_NETWORK_SERVER_DELEGATE::OnClientReady( NETWORK_PLAYER * player, bool ready ) {
    
    Presenter->UpdateClientReady( player, ready );
}
