//
//  SERVICE_NETWORK_SYSTEM.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_SYSTEM.h"

SERVICE_NETWORK_SYSTEM::SERVICE_NETWORK_SYSTEM() :
    Loop( NULL ),
    OnNewTCPConnectionCallback( NULL ),
    OnTCPDataReceivedCallback( NULL ),
    OnUPDDataReceivedCallback( NULL ) {
    
}

SERVICE_NETWORK_SYSTEM::~SERVICE_NETWORK_SYSTEM() {

}

void SERVICE_NETWORK_SYSTEM::Initialize() {
    
    Loop = ( uv_loop_t * ) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( uv_loop_t ) );
    
    UV_CHECK_ERROR( uv_loop_init( Loop ); )
}

void SERVICE_NETWORK_SYSTEM::Update( bool it_waits ) {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( SERVICE_NETWORK_SYSTEM::NetworkLock )
        UV_CHECK_ERROR( uv_run( Loop, it_waits ? UV_RUN_ONCE : UV_RUN_NOWAIT ); )
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void SERVICE_NETWORK_SYSTEM::Update( bool it_waits, uv_loop_t * loop ) {
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( SERVICE_NETWORK_SYSTEM::NetworkLock )
        UV_CHECK_ERROR( uv_run( loop, it_waits ? UV_RUN_ONCE : UV_RUN_NOWAIT ); )
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
}

void SERVICE_NETWORK_SYSTEM::Finalize() {
    
    OnNewTCPConnectionCallback = NULL;
    OnTCPDataReceivedCallback = NULL;
    OnUPDDataReceivedCallback = NULL;
    
    UV_CHECK_ERROR( uv_run( Loop, UV_RUN_DEFAULT ); )
    UV_CHECK_ERROR( uv_loop_close( Loop ); )
    
    CORE_MEMORY_ALLOCATOR_Free( Loop );
}

SERVICE_NETWORK_CONNECTION * SERVICE_NETWORK_SYSTEM::CreateConnection(
    const SERVICE_NETWORK_CONNECTION_TYPE type,
    const unsigned char ip_addr[4],
    const unsigned char broadcast_addr[4],
    const unsigned short port,
    const unsigned short broadcast_port,
    const bool receiver,
    const bool broadcasts,
    const bool create_loop ) {
    
    SERVICE_NETWORK_CONNECTION * connection = new SERVICE_NETWORK_CONNECTION();
    
    connection->Info.IPAddres[0] = ip_addr[0];
    connection->Info.IPAddres[1] = ip_addr[1];
    connection->Info.IPAddres[2] = ip_addr[2];
    connection->Info.IPAddres[3] = ip_addr[3];
    
    connection->Info.ConnectionType = type;
    connection->Info.ItIsReceiver = receiver;
    connection->Info.ItBroadcasts = broadcasts;
    
    char buffer[16];
    char broadcast_buffer[16];
    
    sprintf( buffer, "%d.%d.%d.%d", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3] );
    
    connection->Info.Port = port;
    
    if ( create_loop ) {

        connection->SelfLoop = ( uv_loop_t * ) CORE_MEMORY_ALLOCATOR::Allocate( sizeof( uv_loop_t ) );
        
        UV_CHECK_ERROR( uv_loop_init( connection->SelfLoop ); )
    }
    
    UV_CHECK_ERROR( uv_ip4_addr( buffer, port, &connection->SocketConnectionAddress ); )
    
    switch ( connection->Info.ConnectionType ) {
            
        case SERVICE_NETWORK_CONNECTION_TYPE_Udp: {
            
            UV_CHECK_ERROR( uv_udp_init( create_loop ? connection->SelfLoop : Loop, &connection->UVConnection.UDPType.UDPSocket ); )
            
            if ( connection->Info.ItBroadcasts ) {
                
                connection->Info.BroadcastIPAddress[0] = broadcast_addr[0];
                connection->Info.BroadcastIPAddress[1] = broadcast_addr[1];
                connection->Info.BroadcastIPAddress[2] = broadcast_addr[2];
                connection->Info.BroadcastIPAddress[3] = broadcast_addr[3];
                
                sprintf( broadcast_buffer, "%d.%d.%d.%d", broadcast_addr[0], broadcast_addr[1], broadcast_addr[2], broadcast_addr[3] );
                
                UV_CHECK_ERROR( uv_ip4_addr( broadcast_buffer, broadcast_port, &connection->BroadcastAddress); )
            }
            
            int flag = 0;
            
            if ( receiver ) {
                
                flag |= UV_UDP_REUSEADDR;
            }
            
            if ( connection->Info.ItBroadcasts ) {
                
                UV_CHECK_ERROR( uv_udp_bind( &connection->UVConnection.UDPType.UDPSocket, (const struct sockaddr *) &connection->BroadcastAddress, flag ); )
            }
            else {
                UV_CHECK_ERROR( uv_udp_bind( &connection->UVConnection.UDPType.UDPSocket, (const struct sockaddr *) &connection->SocketConnectionAddress, flag ); )
            }
            
            if ( connection->Info.ItBroadcasts ) {
                
                UV_CHECK_ERROR( uv_udp_set_broadcast( &connection->UVConnection.UDPType.UDPSocket, 1 ); )
            }
            
            break;
        }
        case SERVICE_NETWORK_CONNECTION_TYPE_Tcp: {
            
            UV_CHECK_ERROR( uv_tcp_init( create_loop ? connection->SelfLoop : Loop, &connection->UVConnection.TCPType.TCPSocket ); )
            
            if ( receiver ) {
                
                UV_CHECK_ERROR( uv_tcp_bind(&connection->UVConnection.TCPType.TCPSocket, (const struct sockaddr *) &connection->SocketConnectionAddress, 0 ); )
                
                UV_CHECK_ERROR( uv_listen( (uv_stream_t*) &connection->UVConnection.TCPType.TCPSocket, 5, SERVICE_NETWORK_CONNECTION::OnTCPAccesNewConnection); )
            }
            else {
                
                //UV_CHECK_ERROR( uv_tcp_bind(&connection->UVConnection.TCPType.TCPSocket, (const struct sockaddr *) &connection->SocketConnectionAddress, 0 ); )
                
                UV_CHECK_ERROR( uv_tcp_connect( &connection->UVConnection.TCPType.TCPConnect, &connection->UVConnection.TCPType.TCPSocket, (const struct sockaddr *) &connection->SocketConnectionAddress, SERVICE_NETWORK_CONNECTION::TCPConnectionCallback ); )
            }
            
            break;
        }
            
        case SERVICE_NETWORK_CONNECTION_TYPE_TcpAccept: {
            
            UV_CHECK_ERROR( uv_tcp_init( create_loop ? connection->SelfLoop : Loop, &connection->UVConnection.TCPType.TCPSocket ); )
        }
            
        default: {
            
            break;
        }
    }
    
    return connection;
}

void SERVICE_NETWORK_SYSTEM::NewConnection( uv_stream_t * server ) {

    if ( OnNewTCPConnectionCallback ) {
        
        ( *OnNewTCPConnectionCallback )( server );
    }
}

unsigned char SERVICE_NETWORK_SYSTEM::AllInterfaces[4] = { 0,0,0,0 };
unsigned char SERVICE_NETWORK_SYSTEM::AllBroadcastAddress[4] = { 255,255, 255, 255 };
short int SERVICE_NETWORK_SYSTEM::BroadcastPortDefault = 0;
CORE_PARALLEL_LOCK_MUTEX SERVICE_NETWORK_SYSTEM::NetworkLock;
