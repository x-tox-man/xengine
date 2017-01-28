//
//  APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.h"

APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER::APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER() :
    GRAPHIC_UI_PRESENTER(),
    GameIsStarting( false ),
    CountDown( 5.0f ) {
    
}

APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER::~APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER() {
    
}

void APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER::Update( const float time_step) {
    
    if ( GameIsStarting ) {
        CountDown -= time_step;
        
        if ( CountDown <= 0.0f ) {
            
            OnGameStarting();
        }
    }
}
