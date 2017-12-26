//
//  NETWORK_MANAGER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 6/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_MANAGER_hpp
#define NETWORK_MANAGER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "NETWORK_CLIENT.h"
#include "NETWORK_SERVER.h"

XS_CLASS_BEGIN( NETWORK_MANAGER )

    NETWORK_MANAGER();
    ~NETWORK_MANAGER();

    void Initialize();
    void Finalize();
    void Update( const float step );

    void InitializeServer(int seed);
    void InitializeClient();

    void FinalizeServer();
    void FinalizeClient();

    void SendCommand( SERVICE_NETWORK_COMMAND * command );

    inline NETWORK_CLIENT * GetClient() { return Client; }
    inline NETWORK_SERVER * GetServer() { return Server; }

    inline bool IsServer() const { return ItIsServer; }
    inline void SetServer( bool server) { ItIsServer = server; }

private:

    bool
        Multiplayer,
        ItIsServer;
    NETWORK_CLIENT
        * Client;
    NETWORK_SERVER
        * Server;

XS_CLASS_END

#endif /* NETWORK_MANAGER_hpp */
