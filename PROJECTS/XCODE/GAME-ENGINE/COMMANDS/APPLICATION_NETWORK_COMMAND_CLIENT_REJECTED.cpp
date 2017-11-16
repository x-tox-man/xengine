//
//  APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_COMMAND.h"
#include "Application.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED, APPLICATION_NETWORK_COMMAND_ClientRejected)

void APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED::Apply() {
    ((MyTestApp &) MyTestApp::GetApplicationInstance()).GetClient().SetClientIsConnected( false );
}
