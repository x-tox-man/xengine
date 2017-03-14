//
//  APPLICATION_NETWORK_REMOTE_SERVER_INFO.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_NETWORK_REMOTE_SERVER_INFO_h
#define APPLICATION_NETWORK_REMOTE_SERVER_INFO_h

#include "CORE_HELPERS_CLASS.h"
#include "NETWORK_SERVER_INFO.h"
#include "NETWORK_CLIENT.h"
#include "CORE_DATA_MODEL.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_REMOTE_SERVER_INFO, CORE_DATA_MODEL)
    
public :
    NETWORK_REMOTE_SERVER_INFO(SERVICE_NETWORK_COMMAND * command, NETWORK_SERVER_INFO * info ) : ServerConnexionCommand( command ), Info( info ) {
        
        InitializeObservable();
    }
    
    SERVICE_NETWORK_COMMAND * GetServerConnexionCommand() { return ServerConnexionCommand; }
    NETWORK_SERVER_INFO * GetInfo() { return Info; }
    
private :
    SERVICE_NETWORK_COMMAND * ServerConnexionCommand;
    NETWORK_SERVER_INFO * Info;

XS_CLASS_END

#endif /* APPLICATION_NETWORK_REMOTE_SERVER_INFO_h */
