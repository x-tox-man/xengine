//
//  APPLICATION_NETWORK_BROWSER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_NETWORK_BROWSER.h"
#include "GRAPHIC_UI_FRAME_LIST_ADAPTER.h"
#include "NETWORK_PLAYER_LOBBY_CELL.h"
#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h"
#include "APPLICATION_SCREENS_NAVIGATION.h"

#include "Application.h"

APPLICATION_NETWORK_BROWSER::APPLICATION_NETWORK_BROWSER() :
    GRAPHIC_UI_FRAME(),
    ServersList(),
    MessageReceivedCount(0),
    LastMessage( NULL ),
    Client( NULL ),
    ListAdapter( NULL ) {
    
}

APPLICATION_NETWORK_BROWSER::~APPLICATION_NETWORK_BROWSER() {
    
    CORE_MEMORY_ObjectSafeDeallocation( LastMessage );
}

void APPLICATION_NETWORK_BROWSER::Initialize() {
    
    Client = &((MyTestApp *)&CORE_APPLICATION::GetApplicationInstance())->GetClient();
    
    NETWORK_PLAYER_LOBBY_CELL * item_template = (NETWORK_PLAYER_LOBBY_CELL*) new NETWORK_PLAYER_LOBBY_CELL();
    item_template->Initialize();
    
    GetPlacement().SetSize(CORE_MATH_VECTOR(500.0f, 500.0f));
    
    GRAPHIC_UI_FRAME * list_frame = new GRAPHIC_UI_FRAME;
    
    ServersList.resize(0);
    
    CORE_HELPERS_CALLBACK_1<APPLICATION_NETWORK_REMOTE_SERVER_INFO *> callback(&Wrapper1< APPLICATION_NETWORK_BROWSER , APPLICATION_NETWORK_REMOTE_SERVER_INFO *, &APPLICATION_NETWORK_BROWSER::ConnectToServer >,this);
    
    ListAdapter = new NETWORK_BROWSER_LIST_ADAPTER(list_frame, item_template);
    ListAdapter->SetCollection(&ServersList);
    ListAdapter->SetServerSelectedCallback(callback);
    
    list_frame->GetPlacement().SetSize(CORE_MATH_VECTOR(500.0f, 500.0f));
    list_frame->SetAdapter(ListAdapter);
    SetObjectForIdentifier(IdServerList, list_frame);
    
    list_frame->Initialize();
    
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * > set_server_callback(&Wrapper1<APPLICATION_NETWORK_BROWSER, SERVICE_NETWORK_COMMAND *, &APPLICATION_NETWORK_BROWSER::SetServer >, this);
    
    Client->SetOnServerStatusCallback(set_server_callback);
}

void APPLICATION_NETWORK_BROWSER::Finalize() {
    
}

void APPLICATION_NETWORK_BROWSER::OnShow() {
    
}

void APPLICATION_NETWORK_BROWSER::OnHide() {
    
}

void APPLICATION_NETWORK_BROWSER::SetServer( SERVICE_NETWORK_COMMAND * server_connection_command ) {
    
    std::vector< APPLICATION_NETWORK_REMOTE_SERVER_INFO * >::iterator it;
    
    it = ServersList.begin();
    
    if ( it == ServersList.end() ) {
        
        APPLICATION_NETWORK_REMOTE_SERVER_INFO * info = new APPLICATION_NETWORK_REMOTE_SERVER_INFO(server_connection_command, NULL);
        
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
        
        
        APPLICATION_NETWORK_REMOTE_SERVER_INFO * info = new APPLICATION_NETWORK_REMOTE_SERVER_INFO(server_connection_command , NULL );
        
        ServersList.push_back( info );
        ListAdapter->OnCollectionChanged();
    }
}

void APPLICATION_NETWORK_BROWSER::ConnectToServer( APPLICATION_NETWORK_REMOTE_SERVER_INFO * info ) {
    
    Client->SelectServer( info->GetServerConnexionCommand() );
    
    APPLICATION_SCREENS_NAVIGATION::GetInstance().NavigateToAsync<APPLICATION_MULTIPLAYER_GAME_CONFIGURATION>( "NetworkGameRoom" );
}

void APPLICATION_NETWORK_BROWSER::StartServer() {
    
}

CORE_HELPERS_IDENTIFIER
    APPLICATION_NETWORK_BROWSER::IdServerList( "NB:ServerList" );
