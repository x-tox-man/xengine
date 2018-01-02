//
//  NETWORK_SERVER_DELEGATE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_SERVER_DELEGATE_h
#define NETWORK_SERVER_DELEGATE_h

#include "SERVICE_NETWORK_CONNECTION.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_SERVER_INFO.h"

class NETWORK_SERVER_DELEGATE {
    
    public :
    
    NETWORK_SERVER_DELEGATE() {
        
    }
    
    virtual ~NETWORK_SERVER_DELEGATE() {
        
    }
    
    virtual void OnClientConnected( SERVICE_NETWORK_CONNECTION * connexion ) = 0;
    virtual void OnClientConnected( NETWORK_PLAYER * player ) = 0;
    virtual void OnClientDisconnected( NETWORK_PLAYER * player ) = 0;
    virtual void FillGameInfo( NETWORK_SERVER_INFO & info ) = 0;
    virtual void OnClientReady( NETWORK_PLAYER * player, bool ready ) = 0;
};

#endif /* NETWORK_SERVER_DELEGATE_h */
