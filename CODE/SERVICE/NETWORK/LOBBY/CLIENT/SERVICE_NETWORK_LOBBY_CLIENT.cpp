//
//  SERVICE_NETWORK_LOBBY_CLIENT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_LOBBY_CLIENT.h"
#include "SERVICE_NETWORK_CONNECTION.h"

SERVICE_NETWORK_LOBBY_CLIENT::SERVICE_NETWORK_LOBBY_CLIENT() :
    UDPBroadcastConnection( NULL ),
    UDPListenConnection( NULL ),
    TCPConnection( NULL ),
    OnTcpConnectedCallback(),
    OnTCPConnectionLostCallback(),
    OnTCPConnectionResumedCallback(),
    OnUdpBroadcastMessageReceivedCallback() {
    
}

SERVICE_NETWORK_LOBBY_CLIENT::~SERVICE_NETWORK_LOBBY_CLIENT() {
    
}

void SERVICE_NETWORK_LOBBY_CLIENT::Initialize() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().OnTCPDataReceivedCallback = new CORE_HELPERS_CALLBACK_2< SERVICE_NETWORK_COMMAND *, uv_stream_t * >( Wrapper2< SERVICE_NETWORK_LOBBY_CLIENT, SERVICE_NETWORK_COMMAND *, uv_stream_t *, &SERVICE_NETWORK_LOBBY_CLIENT::OnTCPDataReceived >, this );
    
    SERVICE_NETWORK_CONNECTION::OnNewConnexionCallback = CORE_HELPERS_CALLBACK_1<uv_connect_t*>(Wrapper1<SERVICE_NETWORK_LOBBY_CLIENT, uv_connect_t*, &SERVICE_NETWORK_LOBBY_CLIENT::OnTcpConnected>, this );
}

void SERVICE_NETWORK_LOBBY_CLIENT::OnTcpConnected( uv_connect_t* connexion_data) {
    
    TCPConnection->UVConnection.TCPType.TCPServer = connexion_data->handle;
    OnTcpConnectedCallback();
}

void SERVICE_NETWORK_LOBBY_CLIENT::Finalize() {
    if ( UDPListenConnection ) {
        
        UDPListenConnection->Stop();
        
        CORE_MEMORY_ObjectSafeDeallocation( UDPListenConnection );
    }
}

void SERVICE_NETWORK_LOBBY_CLIENT::Update(const float time_step) {
    
}

void SERVICE_NETWORK_LOBBY_CLIENT::StartTCPConnexion(SERVICE_NETWORK_COMMAND * command) {
    
    if ( TCPConnection == NULL && ( command->Address[0] != 0 || command->Address[1] != 0 || command->Address[2] != 0 || command->Address[3] != 0 ) ) {
        
        TCPConnection = SERVICE_NETWORK_SYSTEM::GetInstance().CreateConnection(
            SERVICE_NETWORK_CONNECTION_TYPE_Tcp,
            command->Address,
            SERVICE_NETWORK_SYSTEM::AllInterfaces,
            1339,
            SERVICE_NETWORK_SYSTEM::BroadcastPortDefault,
            false,
            false,
            true);
        
        TCPConnection->Start();
        TCPConnection->InitializeCommunicationThread();
        UV_CHECK_ERROR( uv_read_start( ( uv_stream_t * ) &TCPConnection->UVConnection.TCPType.TCPSocket, &SERVICE_NETWORK_CONNECTION::AllocateReceiveBuffer, &SERVICE_NETWORK_CONNECTION::TCPReceivePacket ); )
        
        SERVICE_LOGGER_Error( "Network tcp connexion started \n" );
    }
}

void SERVICE_NETWORK_LOBBY_CLIENT::StartUDPListen() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().OnUPDDataReceivedCallback = new CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >( Wrapper1< SERVICE_NETWORK_LOBBY_CLIENT, SERVICE_NETWORK_COMMAND *, &SERVICE_NETWORK_LOBBY_CLIENT::OnUDPDataReceived >, this );
    
    UDPListenConnection = SERVICE_NETWORK_SYSTEM::GetInstance().CreateConnection(
        SERVICE_NETWORK_CONNECTION_TYPE_Udp,
        SERVICE_NETWORK_SYSTEM::AllInterfaces,
        SERVICE_NETWORK_SYSTEM::AllInterfaces,
        1338,
        SERVICE_NETWORK_SYSTEM::BroadcastPortDefault,
        true,
        false );
    
    UDPListenConnection->Start();
}

void SERVICE_NETWORK_LOBBY_CLIENT::StopUDPListen() {
    
    UDPListenConnection->Stop();
}

void SERVICE_NETWORK_LOBBY_CLIENT::OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command, uv_stream_t * tcp_stream) {
    
    (*OnTCPNetworkCommandReceivedCallback)( command );
}

void SERVICE_NETWORK_LOBBY_CLIENT::OnUDPDataReceived( SERVICE_NETWORK_COMMAND * command ) {

    OnUDPNetworkCommandReceivedCallback->operator()(command);
}

void SERVICE_NETWORK_LOBBY_CLIENT::Listen() {
    
}

void SERVICE_NETWORK_LOBBY_CLIENT::SendTcpCommand( CORE_DATA_STREAM & data_to_send, SERVICE_NETWORK_CONNECTION * connexion ) {
    
    if ( data_to_send.GetOffset() > 0 ) {
        
        const char * end = "--END--";
        
        data_to_send.InputBytes((char*) end, 7);
        
        TCPConnection->Send( data_to_send );
    }
}
