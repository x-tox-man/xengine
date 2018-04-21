//
//  NETWORK_BROWSER_PRESENTER.cpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_BROWSER_PRESENTER.h"
#include "NETWORK_SETUP_PAGE.h"
#include "RUN3D_APPLICATION.h"
#include "GRAPHIC_UI_SYSTEM.h"

NETWORK_BROWSER_PRESENTER::NETWORK_BROWSER_PRESENTER( GRAPHIC_UI_FRAME * view ) :
    R3D_BASE_PRESENTER( view ),
    ServersList(),
    MessageReceivedCount( 0 ),
    LastMessage( NULL ),
    ListAdapter( NULL ),
    Client( NULL ),
    Delegate() {
    
}

NETWORK_BROWSER_PRESENTER::~NETWORK_BROWSER_PRESENTER() {
    
    CORE_MEMORY_ObjectSafeDeallocation( LastMessage );
}

void NETWORK_BROWSER_PRESENTER::Configure() {
    
    ServersList.resize(0);
    
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * > set_server_callback(&Wrapper1<NETWORK_BROWSER_PRESENTER, SERVICE_NETWORK_COMMAND *, &NETWORK_BROWSER_PRESENTER::SetServer >, this);

    ListAdapter->SetCollection( &ServersList );
    
    Client = R3D_APP_PTR->GetNetworkManager().GetClient();
    
    if ( Client == NULL ) {
        
        R3D_APP_PTR->GetNetworkManager().InitializeClient();
    }
    
    Client = R3D_APP_PTR->GetNetworkManager().GetClient();
    Client->SetDelegate( &Delegate );
    Delegate.Presenter = this;
}

void NETWORK_BROWSER_PRESENTER::SetServer( SERVICE_NETWORK_COMMAND * server_connection_command ) {
    
    std::vector< NETWORK_REMOTE_SERVER_INFO * >::iterator
        it = ServersList.begin();
    
    if ( server_connection_command->Address[0] == 0 &&
        server_connection_command->Address[1]  == 0 &&
        server_connection_command->Address[2]  == 0 &&
        server_connection_command->Address[3] == 0 ) {
        
        return;
    }
    
    if ( it == ServersList.end() ) {
        
        NETWORK_REMOTE_SERVER_INFO
            * info = new NETWORK_REMOTE_SERVER_INFO( server_connection_command, NULL );
        
        ServersList.push_back( info );
        ListAdapter->OnCollectionChanged();
        
        return;
    }
    else {
        
        while ( it != ServersList.end() ) {
            
            if ( (*it)->GetServerConnexionCommand()->Address[0] == server_connection_command->Address[0] &&
                (*it)->GetServerConnexionCommand()->Address[1] == server_connection_command->Address[1] &&
                (*it)->GetServerConnexionCommand()->Address[2] == server_connection_command->Address[2] &&
                (*it)->GetServerConnexionCommand()->Address[3] == server_connection_command->Address[3]) {
                //Update server info
                
                return;
            }
            
            it++;
        }
        
        NETWORK_REMOTE_SERVER_INFO
            * info = new NETWORK_REMOTE_SERVER_INFO( server_connection_command , NULL );
        
        ServersList.push_back( info );
        ListAdapter->OnCollectionChanged();
    }
}

void NETWORK_BROWSER_PRESENTER::ConnectToServer( NETWORK_REMOTE_SERVER_INFO * info ) {
    
    assert( Client );
    
    SERVICE_LOGGER_Error( "NETWORK_BROWSER_PRESENTER::ConnectToServer" );

    Client->SelectServer( info->GetServerConnexionCommand() );
    R3D_APP_PTR->GetNetworkManager().SetServer( false );
}

void NETWORK_BROWSER_PRESENTER::OnserverConnected() {
    
    //TODO : Navigate on connexion success
    OpenAnimated< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
}

void NETWORK_BROWSER_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {

        R3D_APP_PTR->GetNetworkManager().FinalizeClient();
        
        BackAnimated();
    }
}

void NETWORK_BROWSER_PRESENTER::OnStartLobbyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( event == GRAPHIC_UI_ELEMENT_EVENT_OnTouchOut ) {
        
        R3D_APP_PTR->GetNetworkManager().FinalizeClient();
        R3D_APP_PTR->GetNetworkManager().SetServer( true );
        R3D_APP_PTR->GetNetworkManager().InitializeServer( R3D_APP_PTR->GetSeed() );
        
        OpenAnimated< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
    }
}
