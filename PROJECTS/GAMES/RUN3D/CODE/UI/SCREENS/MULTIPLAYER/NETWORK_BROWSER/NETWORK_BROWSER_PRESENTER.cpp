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
    Client( NULL ) {
    
}

NETWORK_BROWSER_PRESENTER::~NETWORK_BROWSER_PRESENTER() {
    
    CORE_MEMORY_ObjectSafeDeallocation( LastMessage );
}

void NETWORK_BROWSER_PRESENTER::Configure() {
    
    NavigationIsRequested = false;
    ServersList.resize(0);
    
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * > set_server_callback(&Wrapper1<NETWORK_BROWSER_PRESENTER, SERVICE_NETWORK_COMMAND *, &NETWORK_BROWSER_PRESENTER::SetServer >, this);

    ListAdapter->SetCollection( &ServersList );
    
    Client = R3D_APP_PTR->GetNetworkManager().GetClient();
    
    if ( Client == NULL ) {
        
        R3D_APP_PTR->GetNetworkManager().InitializeClient();
        Client = R3D_APP_PTR->GetNetworkManager().GetClient();
    }
    
    Client->SetOnServerStatusCallback( set_server_callback );
}

void NETWORK_BROWSER_PRESENTER::SetServer( SERVICE_NETWORK_COMMAND * server_connection_command ) {
    
    std::vector< NETWORK_REMOTE_SERVER_INFO * >::iterator
        it = ServersList.begin();
    
    if ( it == ServersList.end() ) {
        
        NETWORK_REMOTE_SERVER_INFO
            * info = new NETWORK_REMOTE_SERVER_INFO( server_connection_command, NULL );
        
        ServersList.push_back( info );
        ListAdapter->OnCollectionChanged();
    }
    else {
        
        while ( it != ServersList.end() ) {
            
            if ( (*it)->GetServerConnexionCommand() == server_connection_command ) {
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
    
    if ( !NavigationIsRequested ) {
        
        NavigationIsRequested = true;
        Client->SelectServer( info->GetServerConnexionCommand() );

        //TODO : Navigate on connexion success
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
    }
}

void NETWORK_BROWSER_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Client = NULL;
        
        R3D_APP_PTR->GetNetworkManager().FinalizeClient();
        
        NavigationIsRequested = true;
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateBackAsync();
    }
}

void NETWORK_BROWSER_PRESENTER::OnStartLobbyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Client = NULL;
        
        R3D_APP_PTR->GetNetworkManager().FinalizeClient();
        R3D_APP_PTR->GetNetworkManager().InitializeServer( R3D_APP_PTR->GetSeed() );
        
        NavigationIsRequested = true;
        GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
    }
}
