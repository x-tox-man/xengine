//
//  NETWORK_BROWSER_PRESENTER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_BROWSER_PRESENTER.h"
#include "MULTIPOLY_APPLICATION.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "NETWORK_SETUP_PAGE.h"

NETWORK_BROWSER_PRESENTER::NETWORK_BROWSER_PRESENTER() :
    GRAPHIC_UI_PRESENTER(),
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
    
    Client = ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetClient();
    
    if ( Client == NULL ) {
        
        ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().InitializeClient();
        Client = ((MULTIPOLY_APPLICATION*) &MULTIPOLY_APPLICATION::GetApplicationInstance())->GetNetworkManager().GetClient();
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
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
    }
}

void NETWORK_BROWSER_PRESENTER::OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Client = NULL;
        
        ( ( MULTIPOLY_APPLICATION * ) &MULTIPOLY_APPLICATION::GetApplicationInstance() )->GetNetworkManager().FinalizeClient();
        
        NavigationIsRequested = true;
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateBackAsync();
    }
}

void NETWORK_BROWSER_PRESENTER::OnStartLobbyButtonPressed( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) {
    
    if ( !NavigationIsRequested && event == GRAPHIC_UI_ELEMENT_STATE_Pressed ) {
        
        Client = NULL;
        
        ( ( MULTIPOLY_APPLICATION * ) &MULTIPOLY_APPLICATION::GetApplicationInstance() )->GetNetworkManager().FinalizeClient();
        ( ( MULTIPOLY_APPLICATION * ) &MULTIPOLY_APPLICATION::GetApplicationInstance() )->GetNetworkManager().InitializeServer( ( ( MULTIPOLY_APPLICATION * ) &MULTIPOLY_APPLICATION::GetApplicationInstance() )->GetSeed() );
        
        NavigationIsRequested = true;
        APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync< NETWORK_SETUP_PAGE >( "NETWORK_SETUP_PAGE" );
    }
}
