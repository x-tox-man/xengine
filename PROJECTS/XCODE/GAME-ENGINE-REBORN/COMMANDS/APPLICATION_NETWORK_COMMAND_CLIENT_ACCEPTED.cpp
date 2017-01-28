//
//  APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_COMMAND.h"
#include "Application.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED, APPLICATION_NETWORK_COMMAND_ClientAccepted)

void APPLICATION_NETWORK_COMMAND_CLIENT_ACCEPTED::Apply() {
    ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetClient().SetClientIsConnected( true );
}
