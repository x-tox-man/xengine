//
//  NETWORK_CLIENT_DELEGATE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/11/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_CLIENT_DELEGATE_h
#define NETWORK_CLIENT_DELEGATE_h

#include "SERVICE_NETWORK_CONNECTION.h"
#include "NETWORK_PLAYER.h"
#include "GAMEPLAY_ACTION_COMMAND_SERVER_INFO.h"

class NETWORK_CLIENT_DELEGATE {
    
public :
    
    NETWORK_CLIENT_DELEGATE() {
        
    }
    
    virtual ~NETWORK_CLIENT_DELEGATE() {
        
    }
    
    virtual void OnServerDiscovered( SERVICE_NETWORK_COMMAND * connexion ) = 0;
    virtual void OnServerAccepted( NETWORK_PLAYER * player ) = 0;
    virtual void OnServerInfo( GAMEPLAY_ACTION_COMMAND_SERVER_INFO * info ) = 0;
    virtual void OnServerRefused() = 0;
    virtual void OnServerDisconnected() = 0;
    virtual void OnGameStarted() = 0;
};

#endif /* NETWORK_CLIENT_DELEGATE_h */
