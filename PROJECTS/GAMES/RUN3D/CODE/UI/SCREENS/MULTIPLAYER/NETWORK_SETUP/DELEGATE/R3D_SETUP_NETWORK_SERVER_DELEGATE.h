//
//  R3D_BROWSER_NETWORK_SERVER_DELEGATE.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_BROWSER_NETWORK_SERVER_DELEGATE_hpp
#define R3D_BROWSER_NETWORK_SERVER_DELEGATE_hpp

#include "NETWORK_SERVER_DELEGATE.h"

class NETWORK_SETUP_PRESENTER;

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_SETUP_NETWORK_SERVER_DELEGATE, NETWORK_SERVER_DELEGATE )

    R3D_SETUP_NETWORK_SERVER_DELEGATE();
    virtual ~R3D_SETUP_NETWORK_SERVER_DELEGATE() {
        
    }

    virtual void OnClientConnected( SERVICE_NETWORK_CONNECTION * connexion ) override;
    virtual void OnClientConnected( NETWORK_PLAYER * player ) override;
    virtual void OnClientDisconnected( NETWORK_PLAYER * player ) override;
    virtual void FillGameInfo( NETWORK_SERVER_INFO & info ) override;
    virtual void OnClientReady( NETWORK_PLAYER * player, bool ready ) override;

    NETWORK_SETUP_PRESENTER * Presenter;

XS_CLASS_END

#endif /* R3D_BROWSER_NETWORK_SERVER_DELEGATE_hpp */
