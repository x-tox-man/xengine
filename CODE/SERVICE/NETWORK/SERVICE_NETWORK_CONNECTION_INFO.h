//
//  SERVICE_NETWORK_CONNECTION_INFO.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION_INFO__
#define __GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION_INFO__

#include "CORE_HELPERS_CLASS.h"
#include "SERVICE_NETWORK_CONNECTION_TYPE.h"

XS_CLASS_BEGIN( SERVICE_NETWORK_CONNECTION_INFO )

    SERVICE_NETWORK_CONNECTION_INFO();
    ~SERVICE_NETWORK_CONNECTION_INFO();

    inline bool operator == ( const SERVICE_NETWORK_CONNECTION_INFO & other ) {
        return IPAddres[0] == other.IPAddres[0] && IPAddres[1] == other.IPAddres[1] && IPAddres[2] == other.IPAddres[2] && IPAddres[3] == other.IPAddres[3] && Port == other.Port;
    }

    SERVICE_NETWORK_CONNECTION_TYPE
        ConnectionType;
    unsigned char
        IPAddres[4],
        BroadcastIPAddress[4];
    bool
        ItIsReceiver;
    unsigned short
        Port;
    bool
        ItBroadcasts;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_NETWORK_CONNECTION_INFO__) */
