//
//  R3D_GAMEPLAY_GAME_MULTIPLAYER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 24/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE.h"
#include "RUN3D_APPLICATION.h"
#include "R3D_COMMAND_PLAYER_UPDATE.h"
#include "R3D_COMMAND_GAME_STATUS.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"

R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE() :
    R3D_GAMEPLAY_GAME_DELEGATE(),
    Info() {
    
    Info.SetLevelName( "TestLevel\0" );
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::SetInfo( const NETWORK_REMOTE_GAME_INFO & info ) {
    
    Info.SetLevelName( info.GetLevelName() );
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::InternalUpdateGame( const float step ) {
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        R3D_COMMAND_GAME_STATUS
            command;
        
        R3D_APP_PTR->GetNetworkManager().GetServer()->DispatchMessageToAllPlayers( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand(command) );
    }
    else {
        R3D_COMMAND_PLAYER_UPDATE
            command;
        
        R3D_APP_PTR->GetNetworkManager().GetClient()->DispatchMessageToServer( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand(command) );
    }
}

