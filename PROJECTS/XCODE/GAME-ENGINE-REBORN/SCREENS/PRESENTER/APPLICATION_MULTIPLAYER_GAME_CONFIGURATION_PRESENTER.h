//
//  APPLICATION_MULTIPLAYER_GAME_CONFIGURATION.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_h
#define APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_h

#include "GRAPHIC_UI_PRESENTER.h"
#include "NETWORK_PLAYER.h"
#include "MULTIPLAYER_GAME_LAUNCH_VALIDATOR.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER, GRAPHIC_UI_PRESENTER)

    APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER();
    virtual ~APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER();

    void Update( const float);

    virtual void Configure() = 0;

    virtual void StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) = 0;
    virtual void SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) = 0;
    virtual void OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) = 0;

    virtual void OnClientConnected(NETWORK_PLAYER * player) = 0;
    virtual void OnClientDisconnected(NETWORK_PLAYER * player) = 0;
    virtual void OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) = 0;
    virtual void OnGameStarting() = 0;
    virtual void OnStoppedGameStarting() = 0;

private :

    MULTIPLAYER_GAME_LAUNCH_VALIDATOR
        Validator;

protected :

    bool
        GameIsStarting;
    float
        CountDown;

XS_CLASS_END

#endif /* APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_h */
