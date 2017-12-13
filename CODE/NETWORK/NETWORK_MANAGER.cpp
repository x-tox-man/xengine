//
//  NETWORK_MANAGER.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 6/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "NETWORK_MANAGER.h"

NETWORK_MANAGER::NETWORK_MANAGER() :
    Multiplayer( false ),
    Client( NULL ),
    Server( NULL ) {
    
}
NETWORK_MANAGER::~NETWORK_MANAGER() {
    
}

void NETWORK_MANAGER::Initialize() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Initialize();
}
void NETWORK_MANAGER::Finalize() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Finalize();
    SERVICE_NETWORK_SYSTEM::RemoveInstance();
}

void NETWORK_MANAGER::Update( const float step ) {
    
    if ( Multiplayer ) {
        
        SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
        
        if ( Client != NULL ) {
            
            Client->Update( step );
        }
        else if ( Server != NULL ) {
            
            Server->Update( step );
        }
    }
}

void NETWORK_MANAGER::InitializeServer(int seed) {
    
    assert( Client == NULL && Server == NULL );
    
    Server = new NETWORK_SERVER;
    Server->Initialize( 0.2f );
    Server->SetSeed( seed );
    
    Multiplayer = true;
}

void NETWORK_MANAGER::InitializeClient() {
    
    assert( Client == NULL && Server == NULL );
        
    Client = new NETWORK_CLIENT;
    Client->Initialize();
    
    Multiplayer = true;
}

void NETWORK_MANAGER::FinalizeServer() {
    
    assert( Server != NULL );
    Server->Finalize();
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    delete Server;
    Server = NULL;
    
    
    Multiplayer = false;
}

void NETWORK_MANAGER::FinalizeClient() {

    assert( Client != NULL );
    Client->Finalize();
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    
    delete Client;
    Client = NULL;
    
    Multiplayer = false;
}

void NETWORK_MANAGER::SendCommand( SERVICE_NETWORK_COMMAND * command ) {
    
    if ( Multiplayer ) {
        
        if ( Client != NULL ) {
            
            Client->DispatchMessageToAllPlayers( command );
        }
        else if ( Server != NULL ) {
            
            Server->DispatchMessageToAllPlayers( command );
        }
    }
}
