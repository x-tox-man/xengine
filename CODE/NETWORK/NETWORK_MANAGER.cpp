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
    ItIsServer( true ),
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
        
        if ( Client != NULL && !ItIsServer ) {
            
            Client->Update( step );
        }
        else if ( Server != NULL && ItIsServer ) {
            
            Server->Update( step );
        }
    }
}

void NETWORK_MANAGER::InitializeServer(int seed, float refresh_rate) {
    
    assert( Server == NULL );
    
    Server = new NETWORK_SERVER;
    Server->Initialize( refresh_rate, "XS_SERVER_ACCEPTS_CONNECTIONS\0" );
    Server->SetSeed( seed );
    
    Multiplayer = true;
}

void NETWORK_MANAGER::InitializeClient() {
    
    assert( Client == NULL );
        
    Client = new NETWORK_CLIENT;
    Client->Initialize();
    
    Multiplayer = true;
}

void NETWORK_MANAGER::FinalizeServer() {
    
    assert( Server != NULL );
    Server->Finalize();
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    CORE_MEMORY_ObjectSafeDeallocation( Server );
}

void NETWORK_MANAGER::FinalizeClient() {

    assert( Client != NULL );
    
    SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    Client->Finalize();
    
    CORE_MEMORY_ObjectSafeDeallocation( Client );
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
