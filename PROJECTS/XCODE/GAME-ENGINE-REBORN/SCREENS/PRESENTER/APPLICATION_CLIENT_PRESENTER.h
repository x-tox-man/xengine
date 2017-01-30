//
//  APPLICATION_CLIENT_PRESENTER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef APPLICATION_CLIENT_PRESENTER_hpp
#define APPLICATION_CLIENT_PRESENTER_hpp

#include "APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER.h"
#include "NETWORK_CLIENT.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(APPLICATION_CLIENT_PRESENTER, APPLICATION_MULTIPLAYER_GAME_CONFIGURATION_PRESENTER)

    APPLICATION_CLIENT_PRESENTER( NETWORK_CLIENT * client );
    virtual ~APPLICATION_CLIENT_PRESENTER();

    virtual void Configure() override;

    virtual void StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) override;
    virtual void SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) override;
    virtual void OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event ) override;

    virtual void OnClientConnected(NETWORK_PLAYER * player) override;
    virtual void OnClientDisconnected(NETWORK_PLAYER * player) override;
    virtual void OnChatMessageReceived(NETWORK_PLAYER * player, const char * message) override;
    virtual void OnGameStarting() override;
    virtual void OnStoppedGameStarting() override;

private:

    NETWORK_CLIENT
        * Client;

XS_CLASS_END

#endif /* APPLICATION_CLIENT_PRESENTER_hpp */
