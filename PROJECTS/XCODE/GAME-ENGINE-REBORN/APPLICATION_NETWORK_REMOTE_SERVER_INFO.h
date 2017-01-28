//
//  APPLICATION_NETWORK_REMOTE_SERVER_INFO.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_NETWORK_REMOTE_SERVER_INFO_h
#define APPLICATION_NETWORK_REMOTE_SERVER_INFO_h

#include "NETWORK_SERVER_INFO.h"
#include "NETWORK_CLIENT.h"
#include "CORE_DATA_MODEL.h"

class APPLICATION_NETWORK_REMOTE_SERVER_INFO : public CORE_DATA_MODEL {
    
public :
    APPLICATION_NETWORK_REMOTE_SERVER_INFO(SERVICE_NETWORK_COMMAND * command, NETWORK_SERVER_INFO * info ) : ServerConnexionCommand( command ), Info( info ) {
        
        InitializeObservable();
    }
    
    SERVICE_NETWORK_COMMAND * GetServerConnexionCommand() { return ServerConnexionCommand; }
    NETWORK_SERVER_INFO * GetInfo() { return Info; }
    
private :
    SERVICE_NETWORK_COMMAND * ServerConnexionCommand;
    NETWORK_SERVER_INFO * Info;
};

#endif /* APPLICATION_NETWORK_REMOTE_SERVER_INFO_h */
