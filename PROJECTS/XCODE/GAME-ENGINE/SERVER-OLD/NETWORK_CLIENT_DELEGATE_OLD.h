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

class NETWORK_CLIENT_DELEGATE {
    
public :
    
    NETWORK_CLIENT_DELEGATE() {
        
    }
    virtual ~NETWORK_CLIENT_DELEGATE() {
        
    }
    
    virtual void OnServerDiscover( SERVICE_NETWORK_CONNECTION * connexion ) = 0;

};

#endif /* NETWORK_CLIENT_DELEGATE_h */
