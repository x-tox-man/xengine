//
//  SERVICE_NETWORK_SYSTEM.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_NETWORK_SYSTEM__
#define __GAME_ENGINE_REBORN__SERVICE_NETWORK_SYSTEM__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "SERVICE_NETWORK_COMMAND.h"

#include <uv.h>

#ifndef NETWORK_SERVICE_VERSION
    #define NETWORK_SERVICE_VERSION 1.0
#endif

#if DEBUG
    #define UV_CHECK_ERROR( __CODE__ ) \
    { \
        int __ERROR_CODE__ = __CODE__ \
        if ( __ERROR_CODE__ < 0 ) { \
            SERVICE_LOGGER_Error( "UV_ERROR : %s - %s\n", uv_err_name( __ERROR_CODE__ ), uv_strerror( __ERROR_CODE__ ) ); \
        } \
    }
#else 
    #define UV_CHECK_ERROR( __CODE__ ) __CODE__
#endif

XS_CLASS_BEGIN( SERVICE_NETWORK_SYSTEM )

    XS_DEFINE_UNIQUE( SERVICE_NETWORK_SYSTEM )

    ~SERVICE_NETWORK_SYSTEM();

    void Initialize();
    void Update( bool it_waits );
    void Update( bool it_waits, uv_loop_t * loop );

    void NewConnection( uv_stream_t * server );

    void Finalize();

    SERVICE_NETWORK_CONNECTION * CreateConnection(
        const SERVICE_NETWORK_CONNECTION_TYPE type,
        const unsigned char ip_addr[4],
        const unsigned char broadcast_addr[4],
        const unsigned short port,
        const unsigned short broadcast_port,
        const bool receiver,
        const bool broadcasts = false,
        const bool create_loop = false
        );

    uv_loop_t
        * Loop;
    CORE_HELPERS_CALLBACK_1< uv_stream_t * >
        * OnNewTCPConnectionCallback;
    CORE_HELPERS_CALLBACK_2< SERVICE_NETWORK_COMMAND *, uv_stream_t * >
        * OnTCPDataReceivedCallback;
    CORE_HELPERS_CALLBACK_1< SERVICE_NETWORK_COMMAND * >
        * OnUPDDataReceivedCallback;

    static unsigned char AllInterfaces[4];
    static unsigned char AllBroadcastAddress[4];
    static short int BroadcastPortDefault;
    static CORE_PARALLEL_LOCK_MUTEX NetworkLock;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_NETWORK_SYSTEM__) */
