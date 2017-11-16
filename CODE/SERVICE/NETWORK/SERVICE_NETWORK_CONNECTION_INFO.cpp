//
//  SERVICE_NETWORK_CONNECTION_INFO.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 24/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_CONNECTION_INFO.h"

SERVICE_NETWORK_CONNECTION_INFO::SERVICE_NETWORK_CONNECTION_INFO() :
    ConnectionType( SERVICE_NETWORK_CONNECTION_TYPE_None ),
    IPAddres(),
    ItIsReceiver( false ),
    Port( 1337 ),
    ItBroadcasts( false ) {
    
    IPAddres[0] = 0;
    IPAddres[1] = 0;
    IPAddres[2] = 0;
    IPAddres[3] = 0;
    
    BroadcastIPAddress[0] = 0;
    BroadcastIPAddress[1] = 0;
    BroadcastIPAddress[2] = 0;
    BroadcastIPAddress[3] = 0;
}

SERVICE_NETWORK_CONNECTION_INFO::~SERVICE_NETWORK_CONNECTION_INFO() {

}
