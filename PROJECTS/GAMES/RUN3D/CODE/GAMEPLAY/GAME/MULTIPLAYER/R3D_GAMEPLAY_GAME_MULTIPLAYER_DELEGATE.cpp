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
        command.ShipOrientation = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetOrientation();
        command.Position = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition();
        command.UniqueId = R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId();
        
        
        SetPlayerUpdate( &command );
        auto net_command = GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand( Command, (GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().GetTick() + ComputeMinimumTickLag() ) );
        
        R3D_APP_PTR->GetNetworkManager().GetServer()->DispatchMessageToAllPlayers( net_command );
    }
    else {
        R3D_COMMAND_PLAYER_UPDATE
            command;
        
        command.Thrust = Thrust;
        command.Orientation = Orientation;
        command.ShipOrientation = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetOrientation();
        command.Position = R3D_APP_PTR->GetPlayerIdentityManager().GetCurrentPlayer()->GetPosition();
        command.UniqueId = R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId();
        
        R3D_APP_PTR->GetNetworkManager().GetClient()->DispatchMessageToServer( GAMEPLAY_ACTION_SYSTEM::GetInstance().CreateNetworkCommand( command, 0 ) );
    }
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::SetPlayerUpdate( R3D_COMMAND_PLAYER_UPDATE::PTR player_update ) {
    
    Command.PlayersUpdates[ player_update->UniqueId ].Set( *player_update );
}

void R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::InitializePlayers() {
    
    if ( R3D_APP_PTR->GetNetworkManager().IsServer() ) {
        
        R3D_APP_PTR->GetGame()->SetThisPlayerIndex( R3D_APP_PTR->GetNetworkManager().GetServer()->GetCurrentPlayer().GetUniqueId() );
    }
    else {
        
        R3D_APP_PTR->GetGame()->SetThisPlayerIndex( R3D_APP_PTR->GetNetworkManager().GetClient()->GetCurrentPlayer().GetUniqueId() );
    }
}

unsigned int R3D_GAMEPLAY_GAME_MULTIPLAYER_DELEGATE::ComputeMinimumTickLag() {
    
    float lag = 1.0f / 30.0f;
    
    for( int i = 0; i < R3D_APP_PTR->GetNetworkManager().GetServer()->GetPlayerTable().size(); i++ ) {
        
        if ( R3D_APP_PTR->GetNetworkManager().GetServer()->GetPlayerTable()[ i ] != NULL ) {
            
            if ( R3D_APP_PTR->GetNetworkManager().GetServer()->GetPlayerTable()[ i ]->GetPing() - lag > 0.001f ) {
                
                lag = R3D_APP_PTR->GetNetworkManager().GetServer()->GetPlayerTable()[ i ]->GetPing();
            }
        }
    }
    
    return (unsigned int) ( lag * 30.0f );
}
