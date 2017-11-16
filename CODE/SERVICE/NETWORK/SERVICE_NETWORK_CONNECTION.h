//
//  SERVICE_NETWORK_CONNECTION.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION__
#define __GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION__

#include "CORE_HELPERS_CLASS.h"
#include "SERVICE_NETWORK_CONNECTION_INFO.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "CORE_PARALLEL_THREAD.h"
#include "CORE_PARALLEL.h"
#include <uv.h>

struct UVTCP {
    
    uv_tcp_t
        TCPSocket;
    uv_write_t
        TCPRequest;
    uv_connect_t
        TCPConnect;
    uv_stream_t
        * TCPServer;
    uv_buf_t
        Buffer;
};

struct UVUDP {
    
    uv_udp_send_t
        UDPRequest;
    uv_udp_t
        UDPSocket;
};

union UVUnion {
    UVTCP
        TCPType;
    UVUDP
        UDPType;
};


XS_CLASS_BEGIN( SERVICE_NETWORK_CONNECTION )

    SERVICE_NETWORK_CONNECTION();
    ~SERVICE_NETWORK_CONNECTION();

    void Start();
    void Stop();
    void Send( const CORE_DATA_STREAM & data_to_send );
    void Receive();
    void InitializeCommunicationThread();
    void Listen();

    static void UDPReceivePacket(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf, const struct sockaddr *addr, unsigned flags);
    static void TCPReceivePacket(uv_stream_t *req, ssize_t nread, const uv_buf_t *buf);
    static void UDPSend( uv_udp_send_t* req, int status );
    static void TCPSend( uv_write_t* req, int status );
    static void AllocateReceiveBuffer( uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf );
    static void TCPConnectionCallback( uv_connect_t* req, int status );
    static void OnTCPAccesNewConnection( uv_stream_t * server, int status );
    static void TCPClose( uv_handle_t* handle );

    SERVICE_NETWORK_CONNECTION_INFO
        Info;
    UVUnion
        UVConnection;
    struct sockaddr_in
        BroadcastAddress,
        SocketConnectionAddress;
    static CORE_HELPERS_CALLBACK_1<uv_connect_t*>
        OnNewConnexionCallback;
    CORE_PARALLEL_THREAD
        TcpClientCommunicationThread;
    CORE_PARALLEL_TASK
        * TcpCommunicationTask;
    uv_loop_t
        * SelfLoop;
    CORE_HELPERS_CALLBACK
        * ListenCallback;
    CORE_PARALLEL_LOCK_MUTEX
        ConnexionLock;

private:

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION__) */
