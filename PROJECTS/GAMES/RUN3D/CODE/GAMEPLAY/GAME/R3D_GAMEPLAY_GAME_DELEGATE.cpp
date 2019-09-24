//
//  R3D_GAMEPLAY_GAME_DELEGATE.cpp
//  Run3d
//
//  Created by Christophe Bernard on 26/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GAMEPLAY_GAME_DELEGATE.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "UI_ENDGAME.h"
#include "RUN3D_APPLICATION.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "R3D_COMMAND_PLAYER_UPDATE.h"

R3D_GAMEPLAY_GAME_DELEGATE::R3D_GAMEPLAY_GAME_DELEGATE() :
    PlayersList( NULL ),
    Thrust( 0.0f ),
    Orientation( 0.0f )  {
    
}

void R3D_GAMEPLAY_GAME_DELEGATE::OnEndGame() {
    
    GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< UI_ENDGAME >( "UI_ENDGAME" );
}

void R3D_GAMEPLAY_GAME_DELEGATE::InternalUpdateGame( const float step ) {
    
    auto command = new R3D_COMMAND_PLAYER_UPDATE;
    command->Thrust = Thrust;
    command->Orientation = Orientation;
    command->UniqueId = R3D_APP_PTR->GetPlayerIdentityManager().GetPlayerId();
    //command->Position =
    
    auto ev = new CORE_TIMELINE_EVENT();
    ev->Setup( GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().GetTick() + 1, CORE_HELPERS_UNIQUE_IDENTIFIER(), command );
    
    GAMEPLAY_ACTION_SYSTEM::GetInstance().GetTimeline().InsertNewEvent( ev );
}

void R3D_GAMEPLAY_GAME_DELEGATE::SetPlayerUpdate( R3D_COMMAND_PLAYER_UPDATE::PTR player_update ) {
    
    abort();
    //(*PlayersList)[ R3D_APP_PTR->GetGame()->GetThisPlayerIndex() ]->GetShip()->ApplyInputParamters( Thrust, Orientation );
}
