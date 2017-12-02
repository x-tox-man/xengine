//
//  APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 10/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_COMMAND.h"
#include "Application.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED )
    XS_DEFINE_ClassMember( "player", NETWORK_PLAYER, &Player )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED, APPLICATION_NETWORK_COMMAND_ClientConnected)

void APPLICATION_NETWORK_COMMAND_CLIENT_CONNECTED::Apply() {
    
    ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetClient().SetClientIsConnected( true );
}
