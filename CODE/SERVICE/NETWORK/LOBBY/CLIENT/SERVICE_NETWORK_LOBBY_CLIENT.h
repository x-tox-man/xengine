//
//  SERVICE_NETWORK_CLIENT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef SERVICE_NETWORK_CLIENT_h
#define SERVICE_NETWORK_CLIENT_h

#include "CORE_HELPERS_CLASS.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_PARALLEL.h"
#include "SERVICE_NETWORK_LOBBY.h"

XS_CLASS_BEGIN( SERVICE_NETWORK_LOBBY_CLIENT )

    SERVICE_NETWORK_LOBBY_CLIENT();
    ~SERVICE_NETWORK_LOBBY_CLIENT();

    void Initialize();
    void Finalize();
    void Update( const float time_step );

    void OnTCPNewConnection( uv_stream_t * server );
    void OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command, uv_stream_t * tcp_stream );
    void OnUDPDataReceived( SERVICE_NETWORK_COMMAND * command );

    void OnTcpConnected( uv_connect_t* connexion_data);

    void StartTCPConnexion(SERVICE_NETWORK_COMMAND * connexion);
    void StartUDPListen();
    void StopUDPListen();

    void Listen();
    void SendTcpCommand( CORE_DATA_STREAM & command, SERVICE_NETWORK_CONNECTION * connexion );

    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >
        * OnTCPNetworkCommandReceivedCallback,
        * OnUDPNetworkCommandReceivedCallback;
    CORE_HELPERS_CALLBACK
        OnTcpConnectedCallback;

private :

    SERVICE_NETWORK_CONNECTION
        * UDPBroadcastConnection,
        * UDPListenConnection,
        * TCPConnection;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_CONNECTION * >
        OnTCPConnectionLostCallback,
        OnTCPConnectionResumedCallback;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >
        OnUdpBroadcastMessageReceivedCallback;

XS_CLASS_END

#endif /* SERVICE_NETWORK_LOBBY_CLIENT */
