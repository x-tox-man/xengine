//
//  SERVICE_NETWORK_LOBBY.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_NETWORK_LOBBY__
#define __GAME_ENGINE_REBORN__SERVICE_NETWORK_LOBBY__

#include "CORE_HELPERS_CLASS.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_PARALLEL.h"

#ifndef NETWORK_SERVICE_LOBBY_BROADCAST_INTERVAL
    #define NETWORK_SERVICE_LOBBY_BROADCAST_INTERVAL 2.5f
#endif

#ifndef NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS
    #define NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS 8
#endif

XS_CLASS_BEGIN( SERVICE_NETWORK_LOBBY )

    SERVICE_NETWORK_LOBBY();
    ~SERVICE_NETWORK_LOBBY();

    void Initialize( int max_pool_size, const char * discover_message, const float interval = NETWORK_SERVICE_LOBBY_BROADCAST_INTERVAL );
    void Finalize();
    void Update( const float time_step );

    void OnTCPNewConnection( uv_stream_t * server );
    void OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command, uv_stream_t * tcp_stream );

    void StartTCPListen();
    void StopTCPListen();

    void StartBroadcast();
    void StopBroadcast();

    void SendTcpCommand( CORE_DATA_STREAM & command, SERVICE_NETWORK_CONNECTION * connexion );

    void UpdateDiscoverMessage( const char * discover_message );

    std::array< SERVICE_NETWORK_CONNECTION * , NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS >
        ConnectionPool;
    SERVICE_NETWORK_CONNECTION
        * UDPBroadcastConnection,
        * TCPClientConnection;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_CONNECTION * >
        OnTCPConnectionLostCallback,
        OnTCPConnectionResumedCallback;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_CONNECTION * >
        OnTCPNewConnectionCallback;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * > *
        OnTCPNetworkCommandReceivedCallback;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >
        OnUdpBroadcastMessageReceivedCallback;
    CORE_DATA_STREAM
        UDPBroadcastMessage;
    CORE_PARALLEL_THREAD
        UdpBroadcastThread,
        TcpNewConnectionThread;
    CORE_PARALLEL_TASK
        * UdpBroadcastTask;
    int
        MaxPoolSize;
    float
        UdpBroadcastMinimumInterval;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_NETWORK_LOBBY__) */
