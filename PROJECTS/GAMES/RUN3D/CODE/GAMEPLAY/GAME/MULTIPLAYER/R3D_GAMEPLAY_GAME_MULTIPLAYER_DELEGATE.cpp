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
#include "GAMEPLAY_ACTION_SYSTEM.h"

R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE() :
    R3D_GAMEPLAY_GAME_DELEGATE(),
    Info(),
    Command() {
    
    Info.SetLevelName( "TestLevel\0" );
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::SetInfo( const NETWORK_REMOTE_GAME_INFO & info ) {
    
    Info.SetLevelName( info.GetLevelName() );
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::InternalUpdateGame( const float step ) {
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        R3D_COMMAND_PLAYER_UPDATE
            command;
        
        command.Thrust = Thrust;
        command.Orientation = Orientation;
        command.UniqueId = R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId();
        
        SetPlayerUpdate( &command );
        R3D_APP_PTR->GetNetworkManager().GetServer()->DispatchMessageToAllPlayers( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand( Command ) );
    }
    else {
        R3D_COMMAND_PLAYER_UPDATE
            command;
        
        command.Thrust = Thrust;
        command.Orientation = Orientation;
        command.UniqueId = R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId();
        
        R3D_APP_PTR->GetNetworkManager().GetClient()->DispatchMessageToServer( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand( command ) );
    }
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::SetPlayerUpdate( R3D_COMMAND_PLAYER_UPDATE::PTR player_update ) {
    
    for ( int i = 0; i < Command.PlayersUpdates.size(); i++ ) {
        
        if ( Command.PlayersUpdates[i].UniqueId.GetChecksum() == 0 ) {
            
            Command.PlayersUpdates[i].Set( *player_update );
            break;
        }
        if ( Command.PlayersUpdates[i].UniqueId == player_update->UniqueId ) {
            
            Command.PlayersUpdates[i].Set( *player_update );
            
            break;
        }
    }
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::InitializePlayers() {
    
    Command.PlayersUpdates.resize( PlayersList->size() );
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        R3D_APP_PTR->GetGame()->SetThisPlayerIndex( 1 );
    }
    else {
        
        R3D_APP_PTR->GetGame()->SetThisPlayerIndex( 0 );
    }
}

