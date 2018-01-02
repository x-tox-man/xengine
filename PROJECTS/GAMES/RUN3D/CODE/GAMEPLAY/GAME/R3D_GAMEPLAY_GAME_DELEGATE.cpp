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

R3D_GAMEPLAY_GAME_DELEGATE::R3D_GAMEPLAY_GAME_DELEGATE() :
    PlayersList( NULL ),
    Thrust( 0.0f ),
    Orientation( 0.0f )  {
    
}

void R3D_GAMEPLAY_GAME_DELEGATE::OnEndGame() {
    
    GRAPHIC_UI_SYSTEM::GetInstance().GetNavigation().NavigateToAsync< UI_ENDGAME >( "UI_ENDGAME" );
}
