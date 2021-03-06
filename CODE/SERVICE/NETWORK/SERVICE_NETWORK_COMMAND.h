//
//  SERVICE_NETWORK_COMMAND.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 26/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__SERVICE_NETWORK_COMMAND__
#define __GAME_ENGINE_REBORN__SERVICE_NETWORK_COMMAND__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_JSON.h"
#include "SERVICE_NETWORK_CONNECTION_TYPE.h"
#include "SERVICE_NETWORK_CONNECTION.h"

XS_CLASS_BEGIN( SERVICE_NETWORK_COMMAND )

    XS_DEFINE_SERIALIZABLE

    SERVICE_NETWORK_COMMAND();
    ~SERVICE_NETWORK_COMMAND();

    SERVICE_NETWORK_COMMAND::PTR Clone() {
        auto p = new SERVICE_NETWORK_COMMAND;
        
        p->Type = Type;
        p->Size = Size;
        p->Address[0] = Address[0];
        p->Address[1] = Address[1];
        p->Address[2] = Address[2];
        p->Address[3] = Address[3];
        p->Connection = Connection;
        p->Data = Data;
        
        return p;
    }

    SERVICE_NETWORK_CONNECTION_TYPE
        Type;
    int
        Size;
    unsigned char
        Address[4];
    void
        * Data;
    SERVICE_NETWORK_CONNECTION
        * Connection;
    static float
        ServiceVersion;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__SERVICE_NETWORK_COMMAND__) */
